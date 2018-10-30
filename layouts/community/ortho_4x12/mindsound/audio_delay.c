#include "audio_delay.h"

#include <string.h>

// "private" helper declarations:
bool is_audio_delay_entry_clear(audio_delay_entry *entry);
void audio_delay_clear_entry(audio_delay_entry *entry);
inline bool is_audio_delay_entry_clear(audio_delay_entry *entry) {
  return entry->delay_ms == 0;
}
inline void audio_delay_clear_entry(audio_delay_entry *entry) {
  entry->delay_ms = 0;
}


// implementations:

void audio_delay_clear(audio_delay_queue *queue) {
  memset(queue->entries, 0, sizeof queue->entries);
}

void audio_delay_push(audio_delay_queue *queue, uint16_t delay_ms, audio_delay_event event) {
  // iterate the queue looking for a clear entry
  audio_delay_entry *entry = NULL;
  for (int ii = 0; ii < AUDIO_DELAY_QUEUE_SIZE; ii++) {
    if (is_audio_delay_entry_clear(&(queue->entries[ii]))) {
      entry = &(queue->entries[ii]);
      break;
    }
  }

  // if no entry was clear, pick a random one
  if (entry == NULL) {
    int ii = rand() % AUDIO_DELAY_QUEUE_SIZE;
    entry = &(queue->entries[ii]);
  }

  entry->timer = timer_read32();
  entry->delay_ms = delay_ms;
  entry->event = event;
}

audio_delay_event *audio_delay_polling_pop(audio_delay_queue *queue) {
  static int calls;

  // only execute every AUDIO_DELAY_POLL_FACTOR-th call
  if (++calls % AUDIO_DELAY_POLL_FACTOR != 0) {
    return NULL;
  }

  // iterate the queue and return the first one whose timer has elapsed
  for (int ii = 0; ii < AUDIO_DELAY_QUEUE_SIZE; ii++) {
    audio_delay_entry *entry = &(queue->entries[ii]);

    if (is_audio_delay_entry_clear(entry)) continue;

    if (timer_elapsed(entry->timer) > entry->delay_ms) {
      audio_delay_clear_entry(entry);
      return &(entry->event);
    }
  }

  // fall-through:
  return NULL;
}
