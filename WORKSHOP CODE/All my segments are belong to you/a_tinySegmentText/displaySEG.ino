void displaySegment(int myLed){
  delay(pause);
  switch(myLed){
    // 1
  case 1:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
    break;

    // 2
  case 2:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(0, HIGH);
    break;

    // 3
  case 3:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    digitalWrite(0, HIGH);
    break;

    // 4
  case 4:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    digitalWrite(0, HIGH);
    break;

    // 5
  case 5:
    pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(1, HIGH);
    break;

    // 6
  case 6:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(1, HIGH);
    break;

    // 7
  case 7:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    digitalWrite(1, HIGH);
    break;

    // 8
  case 8:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    digitalWrite(1, HIGH);
    break;

    // 9
  case 9:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(2, HIGH);
    break;

    // 10
  case 10:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
    break;

    // 11
  case 11:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(3, LOW);
    digitalWrite(2, HIGH);
    break;

    // 12
  case 12:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    digitalWrite(2, HIGH);
    break;

    // 13
  case 13:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(0, LOW);
    digitalWrite(3, HIGH);
    break;

    // 14
  case 14:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(1, LOW);
    digitalWrite(3, HIGH);
    break;

    // 15
  case 15:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, INPUT);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    break;

    // 16
  case 16:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    digitalWrite(3, HIGH);
    break;

    // 17
  case 17:
    pinMode(0, OUTPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(0, LOW);
    digitalWrite(4, HIGH);
    break;

    // 18
  case 18:
    pinMode(0, INPUT);
    pinMode(1, OUTPUT);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(1, LOW);
    digitalWrite(4, HIGH);
    break;

    // 19
  case 19:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, OUTPUT);
    pinMode(3, INPUT);
    pinMode(4, OUTPUT);
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    break;

    // 20
  case 20:
    pinMode(0, INPUT);
    pinMode(1, INPUT);
    pinMode(2, INPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    break;
  }
}

