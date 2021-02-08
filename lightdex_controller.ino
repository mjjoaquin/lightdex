int modeNumber = 0;
int upButtonState = 0;
int downButtonState = 0;

void setup() {
  Serial.begin(9600);
  // 2^5, or 32 options. To add more, use a 6th pin
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  // Check up buton
  if (digitalRead(3) == HIGH) {
    modeNumber++;
    if (modeNumber > 31) {
      modeNumber = 0;
    }
    Serial.println(modeNumber);
    output(modeNumber);
    while(digitalRead(3) == HIGH) { //Stops the loop until the button is released
      delay(20);
    }
  }

  if (digitalRead(2) == HIGH) {
    modeNumber--;
    if (modeNumber < 0) {
      modeNumber = 31;
    }
    Serial.println(modeNumber);
    output(modeNumber);
    while(digitalRead(2) == HIGH) { //Stops the loop until the button is released
      delay(20);
    }
  }
}

void output(int modeNumber) {
  // formats into binary 
  String mode = String(modeNumber, BIN);
  if (modeNumber < 16) {
    mode = "0" + mode;
  }
  if (modeNumber < 8) {
    mode = "0" + mode;
  }
  if (modeNumber < 4) {
    mode = "0" + mode;
  }
  if (modeNumber < 2) {
    mode = "0" + mode;
  }
  
  // outputs to pins
  for (int i = 0; i <= 4; i++) {
    if (mode[i] == '1') {
      digitalWrite(12-i, HIGH);
    } else {
      digitalWrite(12-i, LOW);
    }
  }
}
