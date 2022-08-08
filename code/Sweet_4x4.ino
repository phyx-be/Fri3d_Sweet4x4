// This code is for the sweet 4x4 badge addon

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
// https://playground.arduino.cc/Code/Keypad/

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

// Looking at the keypad from the front, the row pins are on the left.

byte colPins[ROWS] = {26,13,27,2}; //connect to the row pinouts of the keypad
byte rowPins[COLS] = {15,14,0,32}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// First param is name
// Second is manufacturer
// Third is initial battery level
BleKeyboard bleKeyboard("Sweet4x4", "Fri3d", 100);

void setup() {
  Serial.begin(9600);
  bleKeyboard.begin();
  pinMode (0, OUTPUT);
}

// This will hold down all the following buttons.
void sendMacroCommand(uint8_t key) {
  bleKeyboard.press(key);
}

void loop() {
  char key = keypad.getKey();

  // Only do something with the keypress if we
  // are connected to something via bluetooth
  
 // if (bleKeyboard.isConnected() && key) {
    Serial.println(key);
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
    delay(100);
    bleKeyboard.releaseAll(); // this releases the buttons
  // }
}
