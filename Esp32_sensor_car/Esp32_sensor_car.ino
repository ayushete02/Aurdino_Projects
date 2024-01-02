// Import required libraries
//#include <AsyncTCP.h>

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
const int pwmChannelA = 0;
const int pwmChannelB = 0;
//const int resolution = 8;
int dutyCycle = 255;

const int output = 2;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
void beepbeep(int timedelay) {
  //  for (int i = 2; i > 0 ; --i)
  //  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(led, HIGH);
  delay(timedelay);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
  delay(timedelay);
}

void ToMotor(int motor_value) {

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
  else if (distanceCm <= 20) {
    beepbeep(100);
  }

  if (motor_value == 1) {
    //  UP

    if (distanceCm >= 20 && distanceCm <= 800 ) {
      Serial.println("forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    }
    else {
      Serial.println("Stop");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }
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
  ledcSetup(pwmChannelA, freq, resolution);
  ledcSetup(pwmChannelB, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannelA);
  ledcAttachPin(enable2Pin, pwmChannelB);

  Serial.print("Testing DC Motor...");
  ledcWrite(pwmChannelA, dutyCycle);
  ledcWrite(pwmChannelB, dutyCycle);
  Serial.begin(115200);


}

void loop() {
  ToMotor(1);
}
