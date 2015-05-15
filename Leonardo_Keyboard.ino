
int colStartPin = 0;
int rowStartPin = 8;

short previousState[40];
short currentState[40];

void setup() {

  Serial.begin(9600);
  
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
}

void setRowHigh(int rowPin) {
  digitalWrite(rowStartPin, HIGH);
  digitalWrite(rowStartPin + 1, HIGH);
  digitalWrite(rowStartPin + 2, HIGH);
  digitalWrite(rowStartPin + 3, HIGH);
  digitalWrite(rowStartPin + 4, HIGH);
  digitalWrite(rowPin, LOW);
}


int getKeyValue(int keyPos) {
  
  int retVal;
  
  switch (keyPos)
  {
    case 0:  retVal = '1';  break;
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

void pressKey(int keyPos) {
  
  Serial.println("Key pressed " +  char(getKeyValue(keyPos)));
  
}

void releaseKey(int keyPos) {
  
  Serial.println("Key released " + char(getKeyValue(keyPos)));
  
}

void loop() {

  //Scan keyboard matrix
  for (int row = 0; row < 5; row++) {
    setRowHigh(rowStartPin + row);
    for (int col = 0; col < 8; col++) {
      
      delay(10);
      
      if (!digitalRead(col)) {
        currentState[row * 8 + col] = 1;
      }
      else {
        currentState[row * 8 + col] = 0;
      } 
      
    }
  }

  for (int x=0; x<40; x++) {
    if (currentState[x] && !previousState[x])
       pressKey(x);
    
    if (previousState[x] && !currentState[x])
       releaseKey(x);
     
    previousState[x] = currentState[x];  
  }
  
  

}


/*
Algorithm:

Iterate rows, setting each row high in turn.
  Iterate columns, reading each pins status.
    If (row,col) pin == HIGH
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

