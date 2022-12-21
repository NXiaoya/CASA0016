/*
This project will get the weather data from openweather API. And measure the room temperature and humidity from AM2302. The information will show on LCD screen. 
The show screen information will be triggered by PIR motion sensor. When it detected someone approaching the device. The information will appear, or the device will be put into sleep mode.
If it will rain today, it will show extra information on the the screen to inform the user to take the umbrella and the buzzer will turn on.
*/

//Include the library
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <ezTime.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include "rgb_lcd.h"

// Include the API key and WIFI information
#include "arduino_secrets.h" 
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

rgb_lcd lcd;

// The API key and WIFI passward
String openWeatherMapApiKey = SECRET_API;
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

// The city and country code information
String city = "London";
String countryCode = "GB";

// THE DEFAULT TIMER IS SET TO 5 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 1000;


String jsonBuffer;

String weather;
const String quote = "\""; 
String Rain = quote + "Rain" + quote;
int RainFlag = 0;

// Sensors - AM2302 and PIR
int buzzer = 14;
uint8_t AMPin = 13;        // on Pin 13 of the Huzzah  
int pirPin =12;                 // PIR Out pin 
int pirStat = 0;                   // PIR status
float Temperature;
float Humidity;
float TempOut;
char msg[50];

JSONVar myObject = " ";

// Date and time
Timezone GB;

// Initialize DHT sensor.
DHT dht(AMPin, DHTTYPE); 

void setup() {

  //start the serial communication
  Serial.begin(115200);

  // Set up the outputs to control the buzzer
  pinMode(buzzer, OUTPUT); 
  digitalWrite(buzzer, LOW);
  
  //start WIFI connection
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //Initialize PIR pin as input
  pinMode(pirPin, INPUT); 
  // start DHT sensor
  pinMode(AMPin, INPUT);
  dht.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
   
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {

  Serial.available();
  // Send an HTTP GET request
  pirStat = digitalRead(pirPin);
   if (pirStat == HIGH) {            // if motion detected
      Serial.println("Hey I got you!!!");
    }
  //dectect the motion every 5 seconds
  if ((millis() - lastTime) > timerDelay) {
    if (pirStat == HIGH) {            // if motion detected
       // Get weather information
      GetWeather();
      GetLocal();
      Serial.println("look at the weather!!!");
    } else {
      //clear LCD
      lcd.setRGB(0, 0, 0);
      lcd.clear();
    }
    //Record the time
    lastTime = millis();
  }
}

void GetLocal() {
    // Gets the values of the temperature
    Temperature = dht.readTemperature(); 
    snprintf (msg, 50, "%.1f", Temperature);
    Serial.print("The temperature in the room: ");
    Serial.println(msg);
    // Gets the values of the humidity
    Humidity = dht.readHumidity(); 
    snprintf (msg, 50, "%.0f", Humidity);
    Serial.print("The humidity in the room: ");
    Serial.println(msg);

    Serial.print("TempOut: ");
    Serial.println(TempOut);
    //Get the temperature difference between the room temperature and outside
    int TempDiff = Temperature - TempOut;
    //Display the information on LCD
    lcd.clear();
    lcd.setRGB(255, 255, 255);
    lcd.setCursor(0, 0);
    lcd.print("Temp diff");
    lcd.setCursor(10, 0);
    lcd.print("Room H");
    lcd.setCursor(2, 1);
    lcd.print(TempDiff);
    lcd.setCursor(10, 1);
    lcd.print(Humidity);
    lcd.setCursor(16, 1);
    lcd.print("%");

     delay(10000);

}
//function for unbrella notice
void checkUmb(){
 Serial.println(RainFlag);
   //If there will be rain today
   if(RainFlag == 1 ){
      lcd.clear();
      lcd.setRGB(0, 0, 155);
      // Print a message to the LCD.
      lcd.setCursor(0, 0);
      lcd.print("Rain Today");
      lcd.setCursor(0, 1);
      lcd.print("Your umbrella:)");
      //Turn on the buzzer
      tone(buzzer,784);
      delay(250); 
      
      noTone(buzzer);//Stop the buzzer
      delay(100);
      tone(buzzer,784);
      delay(500); 
      
      tone(buzzer,659);
      delay(250);

      tone(buzzer,587);
      delay(250); 
    
      tone(buzzer,523);
      delay(250); 

      tone(buzzer,440);
      delay(250); 

      
      noTone(buzzer);//Stop the buzzer
      delay(10000);
      //clear the flag
      RainFlag = 0;
  }


}
//Get the weather from API
void GetWeather() {
  // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + countryCode + "&APPID=" + openWeatherMapApiKey;
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      myObject = JSON.parse(jsonBuffer);
  
      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      
      Serial.print("JSON object = ");
      Serial.println(myObject);
      Serial.print("Weather: ");
      Serial.println(myObject["weather"][0]["main"]);
      weather = JSON.stringify(myObject["weather"][0]["main"]);
      Serial.println(weather);
      //Check if today's weather is rain
      if (weather == Rain){
        RainFlag = 1;
        Serial.println(weather);
      } else {
        Serial.println("Not Rain");
      }
      //convert the temperature to double(in Celsius)
      TempOut = (double)myObject["main"]["temp"] -273;

      lcd.clear();
      lcd.setRGB(255, 255, 255);
      // Print a message to the LCD.
       // (note: line 1 is the second row, since counting begins with 0):
      lcd.setCursor(0, 0);
      lcd.print("Today's weather:");
      lcd.setCursor(0, 1);
      lcd.print(myObject["weather"][0]["main"]);
      delay(10000);
      checkUmb(); 

       
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

