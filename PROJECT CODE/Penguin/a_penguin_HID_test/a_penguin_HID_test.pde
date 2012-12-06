// test code for sending keystrokes from arduino
// to computer via HID bluetooth module

int right,left,up,down,enter;
int r,l,u,d,e;

byte rightByte = 0x07;
byte leftByte = 0x0B;
byte upByte = 0x0E;
byte downByte = 0x0C;
byte enterByte = 0x0D;


void setup() {
  Serial.begin(115200); // begin serial communication at 115200 baud rate
  Serial.println("hello world");  // write hello world
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {
  
  //sendSCByte(SC_RIGHT_ARROW);
  
  right = digitalRead(5);
  left = digitalRead(6);
  up = digitalRead(7);
  down = digitalRead(8);
  enter = digitalRead(9);
  
  
  // RIGHT
  if(right == LOW && r == 1){
    r = 0;  
    Serial.write(rightByte);
    delay(500);
  }
  if(right == HIGH) r = 1;
  
  
  // LEFT
  if(left == LOW && l == 1){
    l = 0;  
    Serial.write(leftByte);
    delay(500);
  }
  if(left == HIGH) l = 1;
  
  
  // UP
  if(up == LOW && u == 1){
    u = 0;  
    Serial.write(upByte);
    delay(500);
  }
  if(up == HIGH) u = 1;
  
  
  // DOWN
  if(down == LOW && d == 1){
    d = 0;  
    Serial.write(downByte);
    delay(500);
  }
  if(down == HIGH) d = 1;
  
  
  // ENTER
  if(enter == LOW && e == 1){
    e = 0;  
    Serial.write(enterByte);
    delay(500);
  }
  if(enter == HIGH) e = 1;
}


void sendSCByte(byte byteToSend)
{
  // This function sends single scancode bytes.
  // If using this function to send MOD bytes,
  // keep in mind the above notes.
  Serial.print(byteToSend);
  delay(25);
}
