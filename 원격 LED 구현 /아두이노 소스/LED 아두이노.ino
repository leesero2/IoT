#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DHT.h>

// Config Firebase
#define FIREBASE_HOST "led-project2.firebaseio.com"
#define FIREBASE_AUTH "y4GOUNyFON7LF55SH2KTZ1Owx7RUXOi6SfiPtDds"

// Config connect WiFi
#define WIFI_SSID "AndroidHotspot71_D6_56" // Put here your Wi-Fi SSID
#define WIFI_PASSWORD "123789456" // Put here your Wi-Fi password

// Config DHT
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
String red_fireStatus = "";  
int red_led = D4;       
void setup() 
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(red_led, OUTPUT);  
                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setString("LED_STATUS", "OFF"); 
}
 
void loop() 
{
  red_fireStatus = Firebase.getString("LED_STATUS");   
  if (red_fireStatus == "ON")   { 
    Serial.println("RED LED Turned ON");                                                        
    digitalWrite(red_led, HIGH);        
  } 
  else if (red_fireStatus == "OFF") {    
    Serial.println("RED LED Turned OFF");
    digitalWrite(red_led, LOW);      
  } else {
    Serial.println("Command Error! Please send ON/OFF");
  }
  delay(2000);
}
