#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "IoT-Lab";  // Enter SSID here
const char* password = "77778888";  //Enter Password here

/* Put IP Address details */
ESP8266WebServer server(80);

uint8_t LED1pin = D0;
bool LED1status = HIGH;

uint8_t LED2pin = D1;
bool LED2status = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);

Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password); // Connecting to WiFi network
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP()); // Printing the ESP IP address

  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1OFF);
  server.on("/led1off", handle_led1ON);
  server.on("/led2on", handle_led2OFF);
  server.on("/led2off", handle_led2ON);
  server.onNotFound(handle_NotFound);
  
 
}
void loop() {
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);}
  else
  {digitalWrite(LED2pin, LOW);}
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO0 Status: OFF | GPIO1 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status)); 
}

void handle_led1OFF() {
  LED1status = HIGH;
  Serial.println("GPIO0 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status)); 
}

void handle_led1ON() {
  LED1status = LOW;
  Serial.println("GPIO0 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status)); 
}

void handle_led2OFF() {
  LED2status = HIGH;
  Serial.println("GPIO1 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,true)); 
}

void handle_led2ON() {
  LED2status = LOW;
  Serial.println("GPIO1 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{ background-image: url(\"https://images4.alphacoders.com/886/thumb-1920-886518.jpg\"); margin-top: 50px;} h1 {color: white;margin: 50px auto 30px;} h3 {color: white;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #FFD700;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>welcome to control your device (^ _ ^) </h1>\n";
  ptr +="<h3>desgin by : kareem ghazi</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-off\" href=\"/led1off\">ON</a>\n";}
  else
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-on\" href=\"/led1on\">OFF</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-off\" href=\"/led2off\">ON</a>\n";}
  else
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-on\" href=\"/led2on\">OFF</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
