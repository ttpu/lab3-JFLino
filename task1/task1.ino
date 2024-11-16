#include <WiFi.h>
#include <PubSubClient.h>

#define BTN 33
#define RED 4
#define GRN 5
#define YLW 19
#define BLU 22

const char* ssid = "Jurat";
const char* pass = "3nuuad55ycu43fn";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void setup() {
  pinMode(BTN, INPUT);

  Serial.begin(115200);

  //LED configurations
  pinMode(RED, OUTPUT);
  pinMode(GRN, OUTPUT);
  pinMode(YLW, OUTPUT);
  pinMode(BLU, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while(WiFi.status() != WL_CONNECTED){
    Serial.println("trying to connect....");
    delay(1000);
  }

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());

  mqtt_client.setServer("mqtt.iotserver.uz", 1883);
  mqtt_client.setCallback(my_callback);

}

void loop() {
  while(!mqtt_client.connected()){
    //generate unique id
    String myID = "edacs_lab4";
    String macAddr = WiFi.macAddress();
    String macSuffix = macAddr.substring(macAddr.length() - 5);
    macSuffix.replace(":", "");
    myID += macSuffix;

    //connect to mqtt broker
    int mres = mqtt_client.connect(myID.c_str(), "userTTPU", "mqttpass");
    if (mres){
      Serial.print("mqtt connected: ");
      Serial.println(mres);
      mqtt_client.subscribe("ttpu/edacs/lab4");
      mqtt_client.subscribe("ttpu/edacs/fuadov");
      mqtt_client.publish("ttpu/edacs/msg", "hello fuadov");
    }else{
      Serial.print("mqtt NOT connected, trying ... ");
      Serial.println(mres);
      delay(3000);
    }
  }

  mqtt_client.loop();

  static int count;
  static int prev_btn = LOW;

  int btn = digitalRead(BTN);
  //detect button pressed moment
  if(btn == HIGH && prev_btn == LOW){
    count++;
    Serial.println(count);

    // digitalWrite(RED, LOW);
    // digitalWrite(GRN, LOW);
    // digitalWrite(YLW, LOW);
    // digitalWrite(BLU, LOW);
    
    // if (count == 1) {
    //   digitalWrite(RED, HIGH);
    // } else if(count == 2){
    //   digitalWrite(GRN, HIGH);
    // } else if(count == 3){
    //   digitalWrite(YLW, HIGH);
    // } else if(count == 4){
    //   digitalWrite(BLU, HIGH);
    // }

    if(count >= 5){
      count = 0;
    }

    String countmsg = String(count);
    mqtt_client.publish("ttpu/edacs/takhirov", countmsg.c_str());
    
  }

  prev_btn = btn;
  delay(100);
}

void my_callback(char* topic, byte* payload, unsigned int len){
  String msg;
  for(int i = 0; i <len; i++){
    msg+= (char)payload[i];
  }
  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Messsage: ");
  Serial.println(msg);

  String topicStr = String(topic);
  
  if(topicStr == "ttpu/edacs/fuadov"){

    if(msg == "0"){
      digitalWrite(RED, LOW);
      digitalWrite(GRN, LOW);
      digitalWrite(YLW, LOW);
      digitalWrite(BLU, LOW);
    }else if(msg == "1"){
      digitalWrite(RED, HIGH);
    }  else if(msg == "2"){
      digitalWrite(GRN, HIGH);
    } else if(msg == "3"){
      digitalWrite(YLW, HIGH);
    }else if(msg == "4"){
      digitalWrite(BLU, HIGH);
    }
  }
}
