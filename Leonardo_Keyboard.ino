
/*******
 NOTES:

 Arduino Leonardo ZX Spectrum keyboard interface (c) 2015 Simon McDonough

 The 8 "columns" of the spectrum keyboard matrix are mapped to pins 0-7
 The 5 "rows" of the matrix are mapped to pins 8-12

 Each of "columns" are set high using the internal pullup resistor and
 are shorted to ground when a key is pressed.

 PIN 13 MUST BE SHORTED TO GROUND IN ORDER TO SEND KEY PRESSES
 THIS IS SO THAT THE KEYBOARD INTERFACE CAN BE TURNED OFF

********/

int colStartPin = 0;
int rowStartPin = 8;

short previousState[40];
short currentState[40];

int useKeyboardPin = 13;      //If this goes LOW then send the keyboard signal

int changeModePin = 0;
int keyMode = 1;              // 1 = PC Mode, 2 = FUSE emulator mode


// Constants for membrane matrix positions
const int SPEC_KEY_1 = 0;
const int SPEC_KEY_Q = 1;
const int SPEC_KEY_A = 2;
const int SPEC_KEY_0 = 3;
const int SPEC_KEY_P = 4;
const int SPEC_KEY_SHIFT = 5;
const int SPEC_KEY_ENTER = 6;
const int SPEC_KEY_SPACE = 7;
const int SPEC_KEY_2 = 8;
const int SPEC_KEY_W = 9;
const int SPEC_KEY_S = 10;
const int SPEC_KEY_9 = 11;
const int SPEC_KEY_O = 12;
const int SPEC_KEY_Z = 13;
const int SPEC_KEY_L = 14;
const int SPEC_KEY_SYMBOL_SHIFT = 15;
const int SPEC_KEY_3 = 16;
const int SPEC_KEY_E = 17;
const int SPEC_KEY_D = 18;
const int SPEC_KEY_8 = 19;
const int SPEC_KEY_I = 20;
const int SPEC_KEY_X = 21;
const int SPEC_KEY_K = 22;
const int SPEC_KEY_M = 23;
const int SPEC_KEY_4 = 24;
const int SPEC_KEY_R = 25;
const int SPEC_KEY_F = 26;
const int SPEC_KEY_7 = 27;
const int SPEC_KEY_U = 28;
const int SPEC_KEY_C = 29;
const int SPEC_KEY_J = 30;
const int SPEC_KEY_N = 31;
const int SPEC_KEY_5 = 32;
const int SPEC_KEY_T = 33;
const int SPEC_KEY_G = 34;
const int SPEC_KEY_6 = 35;
const int SPEC_KEY_Y = 36;
const int SPEC_KEY_V = 37;
const int SPEC_KEY_H = 38;
const int SPEC_KEY_B = 39;

void setup() {

  Keyboard.begin();

  //Clear pins
  for (int row = 0; row < 5; row++) {
    pinMode(rowStartPin + row, OUTPUT);
    digitalWrite(rowStartPin + row, HIGH);
  }

  for (int col = 0; col < 8; col++) {
    pinMode(colStartPin + col, INPUT_PULLUP);
  }

  for (int x = 0; x < 40; x++) {
    previousState[x] = 0;
    currentState[x] = 0;
  }

  pinMode(useKeyboardPin, INPUT_PULLUP);
}

void setRowPressed(int rowPin) {

  for (int x = 0; x < 5; x++) {
    pinMode(rowStartPin + x, INPUT);
    digitalWrite(rowStartPin + x, HIGH);
  }


  pinMode(rowPin, OUTPUT);
  digitalWrite(rowPin, LOW);
}

void setColumnPressed(int colPin) {

  for (int x = 0; x < 8; x++) {
    digitalWrite(colStartPin + x, LOW);
  }
  digitalWrite(colPin, HIGH);
}


char getKeyValue(int keyPos) {

  int retVal;

  switch (keyPos)
  {
    case SPEC_KEY_1:  retVal = '1';  break;
    case SPEC_KEY_Q:  retVal = 'q';  break;
    case SPEC_KEY_A:  retVal = 'a';  break;
    case SPEC_KEY_0:  retVal = '0';  break;
    case SPEC_KEY_P:  retVal = 'p';  break;
    case SPEC_KEY_SHIFT:  retVal = KEY_LEFT_SHIFT; break;
    case SPEC_KEY_ENTER:  retVal = KEY_RETURN; break;
    case SPEC_KEY_SPACE:  retVal = ' ';  break;
    case SPEC_KEY_2:  retVal = '2';  break;
    case SPEC_KEY_W:  retVal = 'w';  break;
    case SPEC_KEY_S:  retVal = 's';  break;
    case SPEC_KEY_9:  retVal = '9';  break;
    case SPEC_KEY_O:  retVal = 'o';  break;
    case SPEC_KEY_Z:  retVal = 'z';  break;
    case SPEC_KEY_L:  retVal = 'l';  break;
    case SPEC_KEY_SYMBOL_SHIFT:  retVal = KEY_LEFT_CTRL;  break;        // Symbol shift
    case SPEC_KEY_3:  retVal = '3';  break;
    case SPEC_KEY_E:  retVal = 'e';  break;
    case SPEC_KEY_D:  retVal = 'd';  break;
    case SPEC_KEY_8:  retVal = '8';  break;
    case SPEC_KEY_I:  retVal = 'i';  break;
    case SPEC_KEY_X:  retVal = 'x';  break;
    case SPEC_KEY_K:  retVal = 'k';  break;
    case SPEC_KEY_M:  retVal = 'm';  break;
    case SPEC_KEY_4:  retVal = '4';  break;
    case SPEC_KEY_R:  retVal = 'r';  break;
    case SPEC_KEY_F:  retVal = 'f';  break;
    case SPEC_KEY_7:  retVal = '7';  break;
    case SPEC_KEY_U:  retVal = 'u';  break;
    case SPEC_KEY_C:  retVal = 'c';  break;
    case SPEC_KEY_J:  retVal = 'j';  break;
    case SPEC_KEY_N:  retVal = 'n';  break;
    case SPEC_KEY_5:  retVal = '5';  break;
    case SPEC_KEY_T:  retVal = 't';  break;
    case SPEC_KEY_G:  retVal = 'g';  break;
    case SPEC_KEY_6:  retVal = '6';  break;
    case SPEC_KEY_Y:  retVal = 'y';  break;
    case SPEC_KEY_V:  retVal = 'v';  break;
    case SPEC_KEY_H:  retVal = 'h';  break;
    case SPEC_KEY_B:  retVal = 'b';  break;
    default:
      retVal = 0;
  }

  return retVal;
}

boolean useKeyboard() {
  return digitalRead(useKeyboardPin) == LOW;
}

// Returns true if a key is in the current scan buffer but not in the previous buffer
boolean isNewlyPressed(int keyPos) {
    if (!previousState[keyPos] && currentState[keyPos]) {
       return true; 
    }
    return false;
}

void processKeys() {

  if (!useKeyboard()) {
    return;
  } 
 
  
  if (keyMode == 1) {          //PC Mode
    //Process special keys first 
    
    
    
  }
  
  
  
  
  if (keyMode == 2) {          //FUSE emulator mode
    
    for (int x = 0; x < 40; x++) {
      if (currentState[x] && !previousState[x])
        Keyboard.press(getKeyValue(x));

      if (previousState[x] && !currentState[x])
        Keyboard.release(getKeyValue(x));

      previousState[x] = currentState[x];
    }

  } 

}


void loop() {

  //Scan keyboard matrix
  for (int row = 0; row < 5; row++) {
    setRowPressed(rowStartPin + row);
    for (int col = 0; col < 8; col++) {
      setColumnPressed(colStartPin + col);
      if (digitalRead(col) == LOW) {
        delay(10);                          // debounce delay
        if (digitalRead(col) == LOW) {
          currentState[row * 8 + col] = 1;
        }
        else {
          currentState[row * 8 + col] = 0;
        }
      }
      else {
        currentState[row * 8 + col] = 0;
      }
    }
  }

  processKeys();





}


/*
Algorithm:

Iterate rows, setting each row high in turn.
  Iterate columns, reading each pins status.
    If (row,col) pin == LOW
         addToCurrentScanState
    end if
  NEXT
NEXT

Compare PreviousState to CurrentState
if (previousState(x,y) AND !currentState(x,y))
  keyRELEASE(desiredKey)
if (!previousState(x,y) AND currentState(x,y))
  keyPRESS(desiredKey)

PreviousState = CurrentState
Clear CurrentState


*/

