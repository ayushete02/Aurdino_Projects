#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "Sam";
const char* password = "Ayushete";

const int led_pin = 2;
String slider_value = "0";

const int frequency = 5000;
const int led_channel = 0;
const int resolution = 8;

const char* input_parameter = "value";

AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>

<body>
    <style>
        @import url(https://fonts.googleapis.com/css?family=Dosis:700);

        body {
            font-family: "Dosis", Helvetica, Arial, sans-serif;
            background: #ecf0f1;
            color: #34495e;
            padding-top: 40px;
            text-shadow: white 1px 1px 1px;
        }

        .value {
            border-bottom: 4px dashed #bdc3c7;
            text-align: center;
            font-weight: bold;
            font-size: 10em;
            width: 300px;
            height: 100px;
            line-height: 60px;
            margin: 40px auto;
            letter-spacing: -.07em;
            text-shadow: white 2px 2px 2px;
        }

        input[type="range"] {
            display: block;
            -webkit-appearance: none;
            background-color: #bdc3c7;
            width: 300px;
            height: 5px;
            border-radius: 5px;
            margin: 0 auto;
            outline: 0;
        }

        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            background-color: #e74c3c;
            width: 30px;
            height: 30px;
            border-radius: 50%;
            border: 2px solid white;
            cursor: pointer;
            transition: .3s ease-in-out;
        }

        ​input[type="range"]::-webkit-slider-thumb:hover {
            background-color: white;
            border: 2px solid #e74c3c;
        }

        input[type="range"]::-webkit-slider-thumb:active {
            transform: scale(1.6);
        }
    </style>
    <div class="value">0</div>
    <input type="range" min="0" max="100" step="1" value="0">
    <script>
        var elem = document.querySelector('input[type="range"]');

        var rangeValue = function () {
            var newValue = elem.value;
            var target = document.querySelector('.value');
            target.innerHTML = newValue;
            var xhr = new XMLHttpRequest();
            xhr.open("GET", "/slider?value=" + newValue, true);
            xhr.send();
        }

        elem.addEventListener("input", rangeValue);
    </script>
</body>

)rawliteral";

String processor(const String& var){
  if (var == "SLIDERVALUE"){
    return slider_value;
  }
  return String();
}

void setup(){
  Serial.begin(115200);

  ledcSetup(led_channel, frequency, resolution);
  ledcAttachPin(led_pin, led_channel);
  ledcWrite(led_channel, slider_value.toInt());

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String message;
    if (request->hasParam(input_parameter)) {
      message = request->getParam(input_parameter)->value();
      slider_value = message;
      ledcWrite(led_channel, slider_value.toInt());
    }
    else {
      message = "No message sent";
    }
    Serial.println(message);
    request->send(200, "text/plain", "OK");
  });
  
  server.begin();
}
  
void loop() {
  
}
