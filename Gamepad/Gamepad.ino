// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

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

    <h1 style="color: teal;text-align:center;">Hash Include Electronics</h1>
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
            <td onclick=onTouchStartAndEnd(5) ontouchstart='onTouchStartAndEnd("4")' ontouchend='onTouchStartAndEnd("0")'><span
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
            <td onclick=onTouchStartAndEnd(9) ontouchstart='onTouchStartAndEnd("9")' ontouchend='onTouchStartAndEnd("0")'><span
                    class="circularArrows">&#8634;</span></td>
            <td style="background-color:white;box-shadow:none"></td>
            <td onclick=onTouchStartAndEnd(10) ontouchstart='onTouchStartAndEnd("10")' ontouchend='onTouchStartAndEnd("0")'><span
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
String processor(const String& var){
  //Serial.println(var);
  if (var == "SLIDERVALUE"){
    return sliderValue;
  }
  return String();
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(output, ledChannel);
  
  ledcWrite(ledChannel, sliderValue.toInt());

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ledcWrite(ledChannel, sliderValue.toInt());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  
  // Start server
  server.begin();
}
  
void loop() {
  
}
