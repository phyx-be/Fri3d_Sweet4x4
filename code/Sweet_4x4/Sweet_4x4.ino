// This code is for the sweet 4x4 badge addon
#include <Adafruit_NeoPixel.h>
#include <Badge2020_TFT.h>
Badge2020_TFT tft;

#include <BleKeyboard.h>
// This library is for using BLE HID with your ESP32
// 
// This is not availble on the library manager so
// needs to be installed from Github
// https://github.com/T-vK/ESP32-BLE-Keyboard

#include <Keypad.h>
// This library is for interfacing with the 4x4 Matrix
// 
// Can be installed from the library manager, search for "keypad"
// and install the one by Mark Stanley and Alexander Brevig
// https://playground.arduino.cc/Code/Keypad/ - https://github.com/Chris--A/Keypad

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

// the library will return the character inside this array
// when the appropriate button is pressed.
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7', '8', '9', 'C'}, 
  {'*', '0', '#', 'D'}, 
};

// Because our Fri3d macropad is wired in row2col we need to change rows and columns around

byte colPins[ROWS] = {26,13,27,2}; //connect the column pinouts to the rows of the keypad
byte rowPins[COLS] = {15,14,0,32}; //connect the row pinouts to the columns of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// First param is name
// Second is manufacturer
// Third is initial battery level
BleKeyboard bleKeyboard("Sweet4x4", "Fri3d", 100);

#define LEDPIN 12
#define LEDPIN_INT 2
#define NUMPIXELS 9
#define NUMPIXELS_INT 5

Adafruit_NeoPixel strip(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_int(NUMPIXELS, LEDPIN_INT, NEO_GRB + NEO_KHZ800);
uint32_t warmwhite = strip.Color(255, 191, 0);

void setup() {
 // Serial.begin(9600);
  bleKeyboard.begin();
  pinMode (0, OUTPUT);
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip_int.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(10);
  strip_int.setBrightness(10);

  tft.init(240, 240);
  tft.setRotation( 2 );

  pinMode( BADGE2020_BACKLIGHT, OUTPUT );
  digitalWrite( BADGE2020_BACKLIGHT, HIGH );

  // Anything from the Adafruit GFX library can go here, see
  // https://learn.adafruit.com/adafruit-gfx-graphics-library
  
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.println("The cake is a lie");
  
}

// This will hold down all the following buttons.
void sendMacroCommand(uint8_t key) {
  bleKeyboard.press(key);
}

void loop() {
strip.fill(warmwhite, 0, 9);
strip.show();

for(int i=0; i<5; i++) { // For each pixel...
    strip_int.setPixelColor(i, strip_int.Color(0, 150, 0));
    strip_int.show();
}

  char key = keypad.getKey();

  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
 if (bleKeyboard.isConnected() && key) {
   // Serial.println(key);
    switch (key) {
      case '1':
        sendMacroCommand('1');
        break;
      case '2':
        sendMacroCommand('2');
        break;
      case '3':
        sendMacroCommand('3');
        break;
      case '4':
        sendMacroCommand('4');
        break;
      case '5':
        sendMacroCommand('5');
        break;
      case '6':
        sendMacroCommand('6');
        break;
      case '7':
        sendMacroCommand('7');
        break;
      case '8':
        sendMacroCommand('8');
        break;
      case '9':
        sendMacroCommand('9');
        break;
      case '0':
        sendMacroCommand('0');
        break;
      case '*':
        sendMacroCommand('a');
        break;
      case '#':
        sendMacroCommand('b');
        break;
      case 'A':
        sendMacroCommand('c');
        break;
      case 'B':
        sendMacroCommand('d');
        break;
      case 'C':
        sendMacroCommand('e');
        break;
      case 'D':
        sendMacroCommand('f');
        break;
    }
    //delay(50);
    bleKeyboard.releaseAll(); // this releases the buttons
   }
}
