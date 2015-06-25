# Leonardo_Keyboard
Simple Leonardo keyboard scanner to use Spectrum Keyboard as a USB keyboard

Two modes - FUSE and PC.   

Fuse mode - just sends keypressed as they are presented. Symbol Shift mapped to LEFT CTRL
PC mode - operates extended keypressed.  All punctuation marks work ./,';:@ etc.  EXTEND MODE + 1-0 = F1-F10
         GRAPHICS MODE = F11  INV VIDEO = ALT  SYM-SHIFT=L. CTRL  EDIT = TAB
         
See code for which pin is used to switch mode.

All pins use pull-up resitors to remove interference and get pulled low when keys are pressed.
