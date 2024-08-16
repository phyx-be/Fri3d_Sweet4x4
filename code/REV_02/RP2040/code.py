import board

from kmk.kmk_keyboard import KMKKeyboard
from kmk.keys import KC
from kmk.scanners import DiodeOrientation
from kmk.extensions.rgb import RGB
from kmk.extensions.media_keys import MediaKeys
from kmk.modules.layers import Layers
from kmk.modules.encoder import EncoderHandler

# Rotary

keyboard = KMKKeyboard()

keyboard.col_pins = (board.D0, board.D1, board.D2, board.D3)
keyboard.row_pins = (board.D10, board.D7, board.D8, board.D9)
keyboard.diode_orientation = DiodeOrientation.ROW2COL

# LEDs + colour on layer change
# Based on https://kmkfw.io/layers/#active-layer-indication-with-rgb

class LayerRGB(RGB):
    def on_layer_change(self, layer):
        print(f"Changing to layer {layer}")
        if layer == 0:
            self.set_hsv_fill(0, self.sat_default, self.val_default)   # red
        elif layer == 1:
            self.set_hsv_fill(170, self.sat_default, self.val_default) # blue
        elif layer == 2:
            self.set_hsv_fill(43, self.sat_default, self.val_default)  # yellow
        RGB.show()

RGB = LayerRGB(pixel_pin=board.D6, # GPIO pin of the status LED, or background RGB light
        num_pixels=9,                # one if status LED, more if background RGB light
        rgb_order=(1, 0, 2),         # RGB order may differ depending on the hardware
        hue_default=100,               # in range 0-255: 0/255-red, 85-green, 170-blue
        sat_default=255,
        val_default=10,
        )

keyboard.extensions.append(RGB)

class RGBLayers(Layers):
    def activate_layer(self, keyboard, layer, idx=None):
        super().activate_layer(keyboard, layer, idx)
        RGB.on_layer_change(layer)
        RGB.show()

    def deactivate_layer(self, keyboard, layer):
        super().deactivate_layer(keyboard, layer)
        RGB.on_layer_change(keyboard.active_layers[0])
        RGB.show()

keyboard.modules.append(RGBLayers())

# Rotary Encoder
# https://github.com/KMKfw/kmk_firmware/blob/master/docs/en/encoder.md

keyboard.extensions.append(MediaKeys())

encoder_handler = EncoderHandler()
keyboard.modules.append(encoder_handler)
encoder_handler.pins = (
    (board.D4, board.D5, None,), # encoder #1 
    )

encoder_handler.map = [ (( KC.VOLU, KC.VOLD, None), )]

keyboard.keymap = [
    [KC.N1,KC.N2,KC.N3,KC.N4,
     KC.N5,KC.N6,KC.N7,KC.N8,
     KC.A,KC.B,KC.C,KC.D,
     KC.RGB_TOG,KC.RGB_HUI,KC.RGB_HUD,KC.RGB_MODE_KNIGHT,
     ]
]

# For all keypresses check : https://kmkfw.io/keycodes/
# For RGB stuff check : https://kmkfw.io/rgb/

if __name__ == '__main__':
    keyboard.go()
