// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

int motor1Pin1 = 33;
int motor1Pin2 = 25;
int enable1Pin = 32;

int motor2Pin1 = 26;
int motor2Pin2 = 27;
int enable2Pin = 14;

const int trigPin = 13;
const int echoPin = 12;
const int buzzer = 35;
const int led = 2;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

// Setting PWM properties
//const int freq = 30000;
const int pwmChannel = 0;
//const int resolution = 8;
int dutyCycle = 220;

// Replace with your network credentials
const char* ssid = "Sam";
const char* password = "Ayushete";

const int output = 2;
String sliderValue = "0";

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

const char* PARAM_INPUT = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
  
  
  <!DOCTYPE html>
  <html>
  
  <head>
      <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no">
      <style>
          .arrows {
              font-size: 70px;
              color: red;
          }
  
          .circularArrows {
              font-size: 80px;
              color: blue;
          }
  
          td {
              background-color: black;
              border-radius: 25%;
              box-shadow: 5px 5px #888888;
          }
  
          td:active {
              transform: translate(5px, 5px);
              box-shadow: none;
          }
  
          .noselect {
              -webkit-touch-callout: none;
              /* iOS Safari */
              -webkit-user-select: none;
              /* Safari */
              -khtml-user-select: none;
              /* Konqueror HTML */
              -moz-user-select: none;
              /* Firefox */
              -ms-user-select: none;
              /* Internet Explorer/Edge */
              user-select: none;
              /* Non-prefixed version, currently
                                        supported by Chrome and Opera */
          }
      </style>
  </head>
  
  <body class="noselect" align="center" style="background-color:white">
  
      <h1 style="color: teal;text-align:center;">Robo Car</h1>
      <h2 style="color: teal;text-align:center;">Wi-Fi &#128663; Control</h2>
  
      <table id="mainTable" style="width:400px;margin:auto;table-layout:fixed" CELLSPACING=10>
          <tr>
              <td onclick=onTouchStartAndEnd(5) ontouchstart='onTouchStartAndEnd("5")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#11017;</span></td>
              <td onclick=onTouchStartAndEnd(1) ontouchstart='onTouchStartAndEnd("1")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#8679;</span></td>
              <td onclick=onTouchStartAndEnd(6) ontouchstart='onTouchStartAndEnd("6")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#11016;</span></td>
          </tr>
  
          <tr>
              <td onclick=onTouchStartAndEnd(3) ontouchstart='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#8678;</span></td>
              <td onclick=onTouchStartAndEnd(0) ontouchstart='onTouchStartAndEnd("0")' ontouchend='onTouchStartAndEnd("0")'></td>
              <td onclick=onTouchStartAndEnd(4) ontouchstart='onTouchStartAndEnd("4")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#8680;</span></td>
          </tr>
  
          <tr>
              <td onclick=onTouchStartAndEnd(7) ontouchstart='onTouchStartAndEnd("7")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#11019;</span></td>
              <td onclick=onTouchStartAndEnd(2) ontouchstart='onTouchStartAndEnd("2")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#8681;</span></td>
              <td onclick=onTouchStartAndEnd(8) ontouchstart='onTouchStartAndEnd("8")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="arrows">&#11018;</span></td>
          </tr>
  
          <tr>
              <td onclick=onTouchStartAndEnd(3) ontouchstart='onTouchStartAndEnd("3")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="circularArrows">&#8634;</span></td>
              <td style="background-color:white;box-shadow:none"></td>
              <td onclick=onTouchStartAndEnd(4) ontouchstart='onTouchStartAndEnd("4")' ontouchend='onTouchStartAndEnd("0")'><span
                      class="circularArrows">&#8635;</span></td>
          </tr>
      </table>
      <script>
          var webSocketUrl = "ws:\/\/" + window.location.hostname + "/ws";
          var websocket;
  
          function initWebSocket() {
              websocket = new WebSocket(webSocketUrl);
              websocket.onopen = function (event) { };
              websocket.onclose = function (event) { setTimeout(initWebSocket, 2000); };
              websocket.onmessage = function (event) { };
          }
          function onTouchStartAndEnd(value) {
              // websocket.send(value);
              // alert(value)
              var xhr = new XMLHttpRequest();
              xhr.open("GET", "/slider?value=" + value, true);
              xhr.send();
          }
  
          window.onload = initWebSocket;
          document.getElementById("mainTable").addEventListener("touchend", function (event) {
              event.preventDefault()
          });      
      </script>
  
  </body>
  
  </html>
  
  
  )rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var) {
  //Serial.println(var);
  if (var == "SLIDERVALUE") {
    return sliderValue;
  }
  return String();
}
void ToMotor(int motor_value) {
  if (motor_value == 1) {
    //  UP
    
//    if (distanceCm >= 10) {
    
      Serial.println("forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
//    }
  }
  else if (motor_value == 2) {
    //    DOWN
    Serial.println("Backward");
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  }
  else if (motor_value == 3) {
    //        LEFT
    Serial.println("Left Turn");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  }
  else if (motor_value == 4) {
    //RIGHT
    Serial.println("Right Turn");
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
  }
  else if (motor_value == 5) {
    //    UPLEFT
  }
  else if (motor_value == 6) {
    //    UPRIGHT
  }
  else if (motor_value == 7) {
    //    DOWNLEFT
  }
  else if (motor_value == 8) {
    //    DOWNRIGHT
  }
  else if (motor_value == 9) {
    //    TURNLEFT
  }
  else if (motor_value == 10) {
    //    TURNRIGHT
  }
  else if (motor_value == 0) {
    //    STOP
    Serial.println("Stop");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }

}


void setup() {

  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  ledcAttachPin(enable2Pin, pwmChannel);
  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
  // Serial port for debugging purposes
  Serial.begin(115200);

  // configure LED PWM functionalitites
  //  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  //  ledcAttachPin(output, ledChannel);

  //  ledcWrite(ledChannel, sliderValue.toInt());
  ledcWrite(pwmChannel, dutyCycle);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      //      ledcWrite(ledChannel, sliderValue.toInt());
    }
    else {
      inputMessage = 999;
    }
//    Serial.println(inputMessage);
    ToMotor(inputMessage.toInt());
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void beepbeep(int timedelay) {
  //  for (int i = 2; i > 0 ; --i)
  //  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);  
  delay(timedelay);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  delay(timedelay);
  //  }
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Prints the distance in the Serial Monitor
  //  Serial.print("Distance (cm): ");
  //  Serial.println(distanceCm);
  if (distanceCm > 800) {
    beepbeep(100);
  }
  else if (distanceCm <= 10) {
    beepbeep(100);
  }
}
