#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DHT.h>

//read from digital pin 4 on ESP8266
#define DHTPIN 4     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11 Defines type of DHT sensor could be 11, 21, 22

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "homertr249";
const char* password = "shinyjade645";
int x =0;
//set webserver to http
//https svc causes memory issues, avoid for now
ESP8266WebServer server(80);

//IPAddress server(74,125,232,128);  
char thingServer[] = "api.thingspeak.com"; 
//api key is value from ThingSpeak for Write API Key
char api_key[] = "SNS7JHC9YZTLH37W";
//define string for ThingSpeak
String thingSpeakURL;

const int led = 13;
//status led for feedback
const int postled = 12;
ADC_MODE(ADC_VCC);

String stringOne;
float h, t, f;
int intgetDht = 0;

void getUptime() {

  long currentmillis = millis();
  long days=0;
  long hours=0;
  long mins=0;
  long secs=0;
  secs = currentmillis/1000; //convect milliseconds to seconds
  mins=secs/60; //convert seconds to minutes
  hours=mins/60; //convert minutes to hours
  days=hours/24; //convert hours to days
  secs=secs-(mins*60); //subtract the coverted seconds to minutes in order to display 59 secs max 
  mins=mins-(hours*60); //subtract the coverted minutes to hours in order to display 59 minutes max
  hours=hours-(days*24); //subtract the coverted hours to days in order to display 23 hours max
  
  //Display results
  Serial.println("Running Time");
  Serial.println("------------");
  
    if (days>0) // days will displayed only if value is greater than zero
  {
    Serial.print(days);
    Serial.print(" days and :");
  }
  
  Serial.print(hours);
  Serial.print(":");
  Serial.print(mins);
  Serial.print(":");
  Serial.println(secs);
  Serial.println();
}

void getMem() {
  Serial.println("Free Heap: " + String(ESP.getFreeHeap()));
  Serial.println("Flash Chip Size: " + String(ESP.getFlashChipSize()));
  return;
}

void getDht() {
  // Wait a few seconds between measurements.
  delay(2000);
  h = 0.0;
  t = 0.0;
  f = 0.0;
  intgetDht ++;
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  f = dht.readTemperature(true);

  Serial.println("Read DHT Sensor!");
  getMem();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.println("Successful exit DHT Sensor!");
}

void setDah() {
  digitalWrite(postled, 1);
  digitalWrite(postled, 0);
  delay(700);
  digitalWrite(postled, 1);
  delay(300);
  }

void setDit() {
  digitalWrite(postled, 1);
  digitalWrite(postled, 0);
  delay(300);
  digitalWrite(postled, 1);
  delay(300);
  return;
  }

void setCharSpace(){
  digitalWrite(postled, 1);
  delay(700);
  return;
}

void setWordSpace(){
  digitalWrite(postled, 1);
  delay(1400);
  return;
}

void setWordOK() {
  //display K in CW
  //setup postled
  //display OK in CW
  delay(2000);
  //display "O"
  setDah();
  setDah();
  setDah();
  setCharSpace();
  //display "K"
  setDah();
  setDit();
  setDah();
  digitalWrite(postled, 1);
  return;
   
}

//TODO add function to convert test to char byte and process one char at a time.
void setWordPostLED (char words[]) {

for (int i = 0; i < sizeof(words) - 1; i++){
  char xchar;

//TODO chars to array 
 
//TODO Get Chars, while more chars

//TODO process enums for each char
  
 switch(words[i]) {
   case 'a':
     setDit();  setDah();
     break;
   case 'b':
     setDah(); setDit(); setDit(); setDit();
     break;
   case 'c':
     setDah(); setDit(); setDah(); setDit();
     break;
   case 'd':
     setDah(); setDit(); setDit();
     break;
   case 'e':
     setDit();
     break;
   case 'f':
     setDit(); setDit(); setDah(); setDit();
     break;
   case 'g':
     setDah(); setDah(); setDit();
     break;
   case 'h':
     setDit(); setDit(); setDit(); setDit();
     break;
   case 'i':
     setDit(); setDit();
     break;
   case 'j':
     setDit(); setDah(); setDah(); setDah();
     break;
   case 'k':
     setDah(); setDit(); setDah();
     break;
   case 'l':
     setDit(); setDit(); setDah(); setDit();
     break;
   case 'm':
     setDah(); setDah();
     break;
   case 'n':
     setDah(); setDit();
     break;
   case 'o':
     setDah(); setDah(); setDah();
     break;
   case 'p':
     setDit(); setDah(); setDah(); setDit();
     break;
   case 'q':
     setDah(); setDah(); setDit(); setDah();
     break;
   case 'r':
     setDit(); setDah(); setDit();
     break;
   case 's':
     setDit(); setDit(); setDit();
     break;
   case 't':
     setDah();
     break;
   case 'u':
     setDit(); setDit(); setDah();
     break;
   case 'v': 
     setDit(); setDit(); setDit(); setDah();
     break;
   case 'w':
     setDit(); setDit(); setDah();
     break;
   case 'x':
     setDah(); setDit(); setDit(); setDah();
     break;
   case 'y':
     setDit(); setDit(); setDah(); setDit();
     break;
   case 'z':
     setDah(); setDah(); setDit(); setDit();
     break;
   case 1:
   break;
   case 2:
   break;
   case 3:
   break;
   case 4:
   break;
   case 5:
   break;
   case 6:
   break;
   case 7:
   break;
   case 8:
   break;
   case 9:
   break;
   case 0:
   break;
 }
} 
 }
  
void buildUrlString() {
  Serial.println("Building url for ThingSpeak server.");
  thingSpeakURL = "/update?api_key=";
  thingSpeakURL += api_key;
  thingSpeakURL += "&field1=";
  thingSpeakURL += f;
  thingSpeakURL += "&field2=";
  thingSpeakURL += h;
  thingSpeakURL += "&field3=";
  thingSpeakURL += ESP.getVcc();
  thingSpeakURL += "&field4=";
  thingSpeakURL += millis()/1000;
  Serial.println(thingSpeakURL);
}

void postThingServer() {
  digitalWrite(postled, 0);
  Serial.println("\nStarting connection to ThingSpeak server...");
   // if you get a connection, report back via serial:
   //WiFiClientSecure tsclient;
   WiFiClient tsclient;
   
   if (tsclient.connect(thingServer, 80)) {
     Serial.println("connected to ThingSpeak server");
     // Make a HTTP request:
     //GET https://api.thingspeak.com/update?api_key=SNS7JHC9YZTLH37W&field1=0
     Serial.println("Calling buildUrlString function...");
     getDht();
     buildUrlString();
     tsclient.print(String("GET ") + thingSpeakURL + " HTTP/1.1\r\n" +
                  "Host: " + thingServer + "\r\n" +
                  "Connection: close\r\n\r\n");
       Serial.println("request sent");
         while (tsclient.connected()) {
              String line = tsclient.readStringUntil('\n');
                  if (line == "\r") {
                          Serial.println("headers received");
                                break;
                  }  //close if
         } //close while
         
   }//close if client.connect
digitalWrite(postled, 1 );
setWordOK();
}//close function postThingServer

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  
  //configure LEDs
  pinMode(led, OUTPUT);
  pinMode(postled, OUTPUT);
  digitalWrite(postled, 1);
  digitalWrite(led, 0);
  
  //configure serial for console output
  Serial.begin(115200);
  
  //configured WiFi
  WiFi.begin(ssid, password);
  Serial.println("");
  dht.begin();
  Serial.println("Started DHT Sensor!");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");   
  }
  
   Serial.println(String("VCC Voltage is: ") + String(ESP.getVcc()));
 
   server.on("/", [](){
    handleRoot();
  });

  server.on("/setWordOK", [](){
    setWordOK();
  });

  server.on("/temp", [](){
    getDht();
    server.send(200, "text/plain", ("The latest sensor temp is: " + String(f)));
  });

   //seperate http url call to ../getvcc
   server.on("/getvcc", [](){
    //stringOne = String("VCC Voltage is: ");
    //stringOne += ESP.getVcc();
    server.send(200, "text/plain", (String("VCC Voltage is: ") + String(ESP.getVcc())));
  });

   //seperate http url call to ../getdht
   server.on("/getdht", [](){
      getDht();
      stringOne = String("Humidity is: ");
      stringOne += h;
      stringOne += "\n";
      stringOne += String("Temperature is: ");
      stringOne += f;
      stringOne += "\n";
      stringOne += String("Cycle id: ");
      stringOne += intgetDht;
      stringOne += "\n";
      stringOne += String("Uptime seconds is: ");
      stringOne += millis()/1000;
      stringOne += "\n";
    
      server.send(200, "text/plain", stringOne);
  });

   server.on("/getstatus", [](){
      stringOne = "";
      // print the SSID of the network you're attached to:
          stringOne = ("SSID: " + String(WiFi.SSID()) + "\n");
  
      // print your WiFi shield's IP address:
         IPAddress wifiip;
         wifiip = WiFi.localIP();
         stringOne += ("IP Address: " + String(wifiip) + " \n");

      // print the received signal strength:
          stringOne += ("Signal strength (RSSI): " + String(WiFi.RSSI()) + " dbm \n");

          stringOne += ("Free Heap: " + String(ESP.getFreeHeap()) + " \n");
          stringOne += ("Flash Chip Size: " + String(ESP.getFlashChipSize()) + " \n");

          getMem();

          getUptime();
          
    server.send(200, "text/plain", stringOne);
    });

   //seperate http url call to ../postts
   server.on("/postts", [](){
    postThingServer();
    server.send(200, "text/plain", "Posting to ThingSpeak server...");
  });
  
   //seperate http url call to ../online
   server.on("/help", [](){
    server.send(200, "text/plain", "Available cmds are:  /; /temp; /getvcc; /getdht; /getstatus; /postts; /setWordOk; /restart; /help");
  });

   server.on("/restart", [](){
    server.send(200, "text/plain", "Restarting....");
    delay(5000);
    ESP.restart();
  });
  
  server.onNotFound(handleNotFound);

  server.begin();
  
  Serial.println("HTTP server started.");

 //ArduinoOTA Code begins here...

  ArduinoOTA.onStart([]() {
    Serial.println("Start ArduioOTA.onStart Function...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("End ArduioOTA.onStart Function!");
    //setWordOK();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  
  ArduinoOTA.begin();
  //Serial.println("Ready");
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());

//ArduinoOTA Code end here...
  
}

void loop(void){
  
  for(int x = 0; x < 600; x ++) { 
      server.handleClient();
      ArduinoOTA.handle();
      //ESP.deepSleep(300000, WAKE_RF_DEFAULT);
      delay(1000);
  }
      
    postThingServer();
    x=0;
  
}



