
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

void pressKey(int keyPos) {
  
  Serial.println("Key pressed " + keyPos);
  
}

void releaseKey(int keyPos) {
  
  Serial.println("Key released " + keyPos);
  
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

