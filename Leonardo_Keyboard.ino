
int colStartPin = 1;
int rowStartPin = 9;

short previousState[40];
short currentState[40];

void setup() {

  //Clear pins
  for (int row = 0; row < 5; row++) {
    pinMode(rowStartPin + row, OUTPUT);
    digitalWrite(rowStartPin + row, LOW);
  }

  for (int col = 0; col < 8; col++) {
    pinMode(colStartPin + col, INPUT);
  }

  for (int x = 0; x < 40; x++) {
    previousState[x] = 0;
    currentState[x] = 0;
  }
}

void setRowHigh(int rowPin) {
  digitalWrite(rowStartPin, LOW);
  digitalWrite(rowStartPin + 1, LOW);
  digitalWrite(rowStartPin + 2, LOW);
  digitalWrite(rowStartPin + 3, LOW);
  digitalWrite(rowStartPin + 4, LOW);
  digitalWrite(rowPin, HIGH);
}

void pressKey(int keyPos) {
}

void releaseKey(int keyPos) {
}

void loop() {

  //Scan keyboard matrix
  for (int row = 0; row < 5; row++) {
    setRowHigh(rowStartPin + row);
    for (int col = 0; col < 8; col++) {
      if (digitalRead(col)) {
        currentState[row * col + col] = 1;
      }
      else {
        currentState[row * col + col] = 0;
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

