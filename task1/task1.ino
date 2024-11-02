#define BTN 33
#define RED 4
#define GRN 5
#define YLW 19
#define BLU 22

void setup() {
  pinMode(BTN, INPUT);

  Serial.begin(115200);

  //LED configurations
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(BLU, OUTPUT);

}

void loop() {
  static int count;
  static int prev_btn = LOW;

  int btn = digitalRead(BTN);
  //detect button pressed moment
  if(btn == HIGH && prev_btn == LOW){
    count++;
    Serial.println(count);

    digitalWrite(RED, LOW);
    digitalWrite(GRN, LOW);
    digitalWrite(YLW, LOW);
    digitalWrite(BLU, LOW);
    
    if (count == 1) {
      digitalWrite(RED, HIGH);
    } else if(count == 2){
      digitalWrite(GRN, HIGH);
    } else if(count == 3){
      digitalWrite(YLW, HIGH);
    } else if(count == 4){
      digitalWrite(BLU, HIGH);
    }

    if(count >= 5){
      count = 0;
    }
    
  }

  prev_btn = btn;
  delay(100);
}
