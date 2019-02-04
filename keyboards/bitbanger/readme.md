BitBanger
===

Keyboard Maintainer: QMK Community

Hardware Supported: Woodkeys 2-key kit (based on a standard Pro Micro)

Hardware Availability: https://woodkeys.click/product/2-key-kit/

This keyboard types 7-bit ASCII!  I didn't bother trying to support an 8 bit charset (CP1252, etc.) so, among other things, all the valid keycodes start with a '0'.  If I keep working on this, the next feature I want to add is a timeout.  Right now the firmware is fully stateful, so that, if you hit two keys and walk away for a day, tomorrow you can hit six keys and it'll output a keycode.  Counterintuitive.

Make example for this keyboard (after setting up your build environment):

    make bitbanger:default

To flash, short RST and GND (or type 00010001) and run:

    make bitbanger:default:avrdude

I hacked this together based on a branch /u/woodkeys_click had handy so I won't pretend to document the hardware.  :C
