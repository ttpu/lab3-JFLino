#define BTN 33
#define RED 4
#define GRN 5
#define YLW 19
#define BLU 22

void setup() {
  pinMode(BTN, INPUT);

  Serial.begin(115200);
}

void loop() {
  static int count;
  static int prev_btn = LOW;

  int btn = digitalRead(BTN);
  //detect button pressed moment
  if(btn == HIGH && prev_btn == LOW){
    count++;
    Serial.println(count);
  }

  prev_btn = btn;
  delay(100);
}
