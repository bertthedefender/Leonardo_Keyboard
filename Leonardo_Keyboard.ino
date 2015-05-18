
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

int keyMode = 1;              // 1 = PC Mode, 2 = FUSE emulator mode


// Constants for membrane matrix positions
const int SPEC_KEY_1 = 0;
int SPEC_KEY_Q = 1;
int SPEC_KEY_A = 2;
int SPEC_KEY_0 = 3;
int SPEC_KEY_P = 4;
int SPEC_KEY_CAPS = 5;
int SPEC_KEY_ENTER = 6;
int SPEC_KEY_SPACE = 7;
int SPEC_KEY_2 = 8;
int SPEC_KEY_W = 9;
int SPEC_KEY_S = 10;
int SPEC_KEY_9 = 11;
int SPEC_KEY_O = 12;
int SPEC_KEY_Z = 13;
int SPEC_KEY_L = 14;
int SPEC_KEY_SYMBOL_SHIFT = 15;
int SPEC_KEY_3 = 16;
int SPEC_KEY_E = 17;
int SPEC_KEY_D = 18;
int SPEC_KEY_8 = 19;
int SPEC_KEY_I = 20;
int SPEC_KEY_X = 21;
int SPEC_KEY_K = 22;
int SPEC_KEY_M = 23;
int SPEC_KEY_4 = 24;
int SPEC_KEY_R = 25;
int SPEC_KEY_F = 26;
int SPEC_KEY_7 = 27;
int SPEC_KEY_U = 28;
int SPEC_KEY_C = 29;
int SPEC_KEY_J = 30;
int SPEC_KEY_N = 31;
int SPEC_KEY_5 = 32;
int SPEC_KEY_T = 33;
int SPEC_KEY_G = 34;
int SPEC_KEY_6 = 35;
int SPEC_KEY_Y = 36;
int SPEC_KEY_V = 37;
int SPEC_KEY_H = 38;
int SPEC_KEY_B = 39;

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
    case 1:  retVal = 'q';  break;
    case 2:  retVal = 'a';  break;
    case 3:  retVal = '0';  break;
    case 4:  retVal = 'p';  break;
    case 5:  retVal = KEY_LEFT_SHIFT; break;
    case 6:  retVal = KEY_RETURN; break;
    case 7:  retVal = ' ';  break;
    case 8:  retVal = '2';  break;
    case 9:  retVal = 'w';  break;
    case 10:  retVal = 's';  break;
    case 11:  retVal = '9';  break;
    case 12:  retVal = 'o';  break;
    case 13:  retVal = 'z';  break;
    case 14:  retVal = 'l';  break;
    case 15:  retVal = KEY_LEFT_CTRL;  break;        // Symbol shift
    case 16:  retVal = '3';  break;
    case 17:  retVal = 'e';  break;
    case 18:  retVal = 'd';  break;
    case 19:  retVal = '8';  break;
    case 20:  retVal = 'i';  break;
    case 21:  retVal = 'x';  break;
    case 22:  retVal = 'k';  break;
    case 23:  retVal = 'm';  break;
    case 24:  retVal = '4';  break;
    case 25:  retVal = 'r';  break;
    case 26:  retVal = 'f';  break;
    case 27:  retVal = '7';  break;
    case 28:  retVal = 'u';  break;
    case 29:  retVal = 'c';  break;
    case 30:  retVal = 'j';  break;
    case 31:  retVal = 'n';  break;
    case 32:  retVal = '5';  break;
    case 33:  retVal = 't';  break;
    case 34:  retVal = 'g';  break;
    case 35:  retVal = '6';  break;
    case 36:  retVal = 'y';  break;
    case 37:  retVal = 'v';  break;
    case 38:  retVal = 'h';  break;
    case 39:  retVal = 'b';  break;
    default:
      retVal = 0;
  }

  return retVal;
}

boolean useKeyboard() {
  return digitalRead(useKeyboardPin) == LOW;
}


void processKeys() {

  if (!useKeyboard()) {
    return;
  } 
 
  
  if (keyMode == 1) {          //PC Mode
    
    
    
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

