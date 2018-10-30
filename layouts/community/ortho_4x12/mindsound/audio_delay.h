#include QMK_KEYBOARD_H

#pragma once

// the fixed queue depth for delayed audio events
#define AUDIO_DELAY_QUEUE_SIZE 200

// setting this to n will poll the queue every nth matrix scan
#define AUDIO_DELAY_POLL_FACTOR 10

// represents an audio event to be delayed
typedef struct {
  float    freq1;
  float    freq2;
  uint16_t duration;
} audio_delay_event;

// represents an entry in the delay queue
typedef struct {
  uint32_t          timer;
  uint32_t          delay_ms;
  audio_delay_event event;
} audio_delay_entry;

// the high level queue data structure
typedef struct {
  audio_delay_entry entries[AUDIO_DELAY_QUEUE_SIZE];
} audio_delay_queue;

/*
 * Audio delay queue functions:
 *
 * The audio delay queue is a fixed-size queue (AUDIO_DELAY_QUEUE_SIZE).  Pushes take
 * place immediately.  Pops are a polling operation: events will not pop until
 * their delay time has elapsed.
 */

// clear out a delay queue
void audio_delay_clear(audio_delay_queue *queue);

// push an audio delay event onto the delay queue
void audio_delay_push(audio_delay_queue *queue, uint16_t delay_ms, audio_delay_event event);

// every AUDIO_DELAY_POLL_FACTOR calls, pop an audio delay event if elapsed;
// otherwise NULL
audio_delay_event *audio_delay_polling_pop(audio_delay_queue *queue);

