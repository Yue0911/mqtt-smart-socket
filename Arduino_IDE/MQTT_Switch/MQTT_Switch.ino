//Include Library
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <PubSubClient.h>
//=====================================================================================================
//PV
String macval, espip;
#define LED_PIN D4             //Debug LED Pin
#define RelayPin D0            //RELAY
#define MQTT_LOOP_INTERVAL 50  // millisecond
bool shouldSaveConfig = false;
int error_con = 0;
unsigned int bmeread = millis();
unsigned int bmeDelay = 300000;  //5000，300000
//=====================================================================================================
//Define Wifi Manager
#define AP_PWD "12345678"  // 自訂的AP密碼
#define TRIGGER_PIN D1     // 啟用「Wi-Fi設置入口」的按鍵接腳

WiFiManager wm;

unsigned int timeout = 120;  // Wi-Fi管理員的運作秒數
unsigned int startTime = millis();
bool portalRunning = false;

char mqtt_server[40];        //MQTT Broker IP
char mqtt_username[20];      //MQTT User
char mqtt_password[20];      //MQTT Password
char mqtt_port[6] = "1883";  //MQTT Port
//=====================================================================================================
//Define Json
DeserializationError json_error;
//=====================================================================================================
// MQTT Broker
WiFiClient espClient;
PubSubClient client(espClient);

char PublishTopic[16];        //MQTT 推送主題
char SubscriptionsTopic[16];  //MQTT 訂閱主題
//=====================================================================================================
//NTP Server Details
const char *ntpServer = "tock.stdtime.gov.tw";  //NTP IP
const int gmtOffset_sec = 28800;                //taiwan GMT+8*3600sec
const int daylightOffset_sec = 0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec);
//=====================================================================================================
//Define ESP12-Web_OTA
ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
//=====================================================================================================
//FS Save Config
void saveConfigCallback() {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}
//=====================================================================================================
//FS Read File
void mqttRead() {
  if (LittleFS.begin()) {
    Serial.println("mounted file system");
    if (LittleFS.exists("/config.json")) {
      Serial.println("reading config file");
      File configFile = LittleFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonDocument json(1024);
        auto deserializeError = deserializeJson(json, buf.get());
        serializeJson(json, Serial);
        if (!deserializeError) {
          Serial.println("\nparsed json");
          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_username, json["mqtt_username"]);
          strcpy(mqtt_password, json["mqtt_password"]);
          strcpy(mqtt_port, json["mqtt_port"]);
        } else {
          Serial.println("failed to load json config");
        }
        configFile.close();
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}
//=====================================================================================================
//Time Callback
String gettime() {
  // 儲存日期及時間的變數
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  String dayStamp = formattedDate.substring(0, splitT);
  String timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
  String datebuf = dayStamp + " " + timeStamp;
  return datebuf;
}
//=====================================================================================================
//GET Data To MQTT
String getvalumqtt(String cmd) {
  //字串轉JSON
  StaticJsonDocument<200> json_doc;
  char json_output[100];
  json_doc["Date"] = String(gettime());

  if (cmd == "Relay_state") {
    if (digitalRead(RelayPin)) {
      json_doc["Relay_state"] = String("On");
    } else {
      json_doc["Relay_state"] = String("Off");
    }
  }

  if (cmd == "ip") {
    espip = WiFi.localIP().toString();
    json_doc["ip"] = String(espip);
  }

  serializeJson(json_doc, json_output);
  return json_output;
}
//=====================================================================================================
//MQTT CallBack
void callback(char *topic, byte *payload, int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  String message;
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }

  if (message == "led_on") {
    digitalWrite(LED_PIN, LOW);
  } else if (message == "led_off") {
    digitalWrite(LED_PIN, HIGH);
  } else if (message == "ip") {
    client.publish(PublishTopic, (getvalumqtt("ip").c_str()));
  } else if (message == "On") {
    digitalWrite(RelayPin, HIGH);
  } else if (message == "Off") {
    digitalWrite(RelayPin, LOW);
  } else if (message == "RESET") {
    Serial.println("重制中");
    LittleFS.format();
    wm.resetSettings();
    delay(200);
    ESP.reset();
  } else if (message == "Relay") {
    client.publish(PublishTopic, (getvalumqtt("Relay_state").c_str()));
  }

  Serial.println("-----------------------");
  Serial.println(message);
  Serial.println("-----------------------");
}
//=====================================================================================================
//Wifi Config
void doWiFiManager() {
  if (portalRunning) {
    wm.process();
    if ((millis() - startTime) > (timeout * 1000)) {
      Serial.println("「Wi-Fi設置入口」操作逾時…");
      portalRunning = false;
      wm.stopConfigPortal();
    }
  }
  //若啟用「Wi-Fi設置入口」的接腳被按一下…
  if (digitalRead(TRIGGER_PIN) == LOW && (!portalRunning)) {
    Serial.println("按鈕被按下了，啟動設置入口。");
    httpServer.stop();
    digitalWrite(LED_PIN, LOW);
    wm.setConfigPortalBlocking(false);
    wm.startConfigPortal(macval.c_str(), AP_PWD);
    portalRunning = true;
    startTime = millis();
  }
}
//=====================================================================================================
//GET ESP MAC
String getMAC() {
  String rxbuf = WiFi.macAddress();
  String message = "ESP12_" + rxbuf.substring(12, 14);
  message += rxbuf.substring(15, 17);
  return message;
}
//=====================================================================================================
void setup() {
  Serial.begin(9600);
  pinMode(RelayPin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);

  digitalWrite(RelayPin, LOW);

  mqttRead();

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_username("username", "mqtt username", mqtt_username, 20);
  WiFiManagerParameter custom_mqtt_password("password", "mqtt password", mqtt_password, 20);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 6);
  //add all your parameters here
  wm.addParameter(&custom_mqtt_server);
  wm.addParameter(&custom_mqtt_username);
  wm.addParameter(&custom_mqtt_password);
  wm.addParameter(&custom_mqtt_port);

  wm.setSaveConfigCallback(saveConfigCallback);

  //Gat Mac Vale
  macval = getMAC();

  //Set MQTT Publish
  String msgPublish = "tele/" + macval;
  strcpy(PublishTopic, msgPublish.c_str());

  //Set MQTT Subscriptions
  String msgSubscriptions = "cmnd/" + macval;
  strcpy(SubscriptionsTopic, msgSubscriptions.c_str());

  //Connect to Wi-Fi
  WiFi.mode(WIFI_STA);

  //Init WiFiManager
  wm.setHostname(macval);  //主機名稱
  wm.autoConnect(macval.c_str(), AP_PWD);

  //WIFI Status
  if (WiFi.status() == WL_CONNECTED && wm.getWiFiIsSaved()) {
    Serial.println("\n晶片存有Wi-Fi連線資料！");
  } else {
    Serial.println("\n晶片沒有Wi-Fi連線資料…");
  }

  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_username, custom_mqtt_username.getValue());
  strcpy(mqtt_password, custom_mqtt_password.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());

  Serial.println("The values in the file are: ");
  Serial.println("\tmqtt_server : " + String(mqtt_server));
  Serial.println("\tmqtt_username : " + String(mqtt_username));
  Serial.println("\tmqtt_password : " + String(mqtt_password));
  Serial.println("\tmqtt_port : " + String(mqtt_port));

  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonDocument json(1024);
    json["mqtt_server"] = mqtt_server;
    json["mqtt_username"] = mqtt_username;
    json["mqtt_password"] = mqtt_password;
    json["mqtt_port"] = mqtt_port;
    File configFile = LittleFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }
    serializeJson(json, Serial);
    serializeJson(json, configFile);
    configFile.close();
    //end save
  }

  //Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  //Connect to MQTT
  client.setServer(mqtt_server, atoi(mqtt_port));

  client.setCallback(callback);
  while ((!client.connected()) & (error_con < 10)) {
    Serial.printf("The client %s connects to the mqtt broker\n", macval.c_str());
    if (client.connect(macval.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
      error_con++;
    }
  }

  //Init and get the time
  timeClient.begin();

  //配置webserver為更新server
  httpUpdater.setup(&httpServer);
  httpServer.begin();

  Serial.print("Publish:");
  Serial.println(PublishTopic);
  Serial.print("Subscriptions:");
  Serial.println(SubscriptionsTopic);

  //client.publish(topic, "hello emqx");
  client.subscribe(SubscriptionsTopic);
  digitalWrite(LED_PIN, HIGH);
}
//=====================================================================================================
void loop() {
  doWiFiManager();
  client.loop();
  timeClient.update();
  httpServer.handleClient();

  if ((millis() - bmeread) > bmeDelay) {
    client.publish(PublishTopic, (getvalumqtt("Relay_state").c_str()));
    bmeread = millis();
  }

  delay(MQTT_LOOP_INTERVAL);
}