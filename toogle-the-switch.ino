#include <Servo.h>

Servo myServo;

int trigPin = 5;
int echoPin = 6;

long duration;
int distance;  

bool switchState = false;   // false = OFF, true = ON
bool sudahTrigger = false;
       

// int kembali = 50;  // My code,    

int posisiOff = 28-29;   // sesuaikan dengan mekanikmu        
// int posisiOff = 28-29;   // sesuaikan dengan mekanikmu
int posisiOn  = 73;  // sesuaikan dengan mekanikmu //80 to 90 
// int posisiOn  = 63;  // sesuaikan dengan mekanikmu //80 to 90 

void setup() {
  myServo.attach(3);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);

  myServo.write(50);  // mulai dari OFF   
}

void loop() {

  // Trigger ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  // Jika tangan terdeteksi
  if (distance > 0 && distance < 10 && !sudahTrigger) {

    switchState = !switchState;  // toggle status

    if (switchState) {
      myServo.write(posisiOn);   // nyalakan
      delay(500);
      myServo.write(50);
    } else {
      myServo.write(posisiOff);  // matikan
      delay(500);
      myServo.write(50);

    }

    delay(600);  // waktu servo dorong sakelar

    sudahTrigger = true;
  }

  // Reset setelah tangan menjauh
  if (distance > 20) {
    sudahTrigger = false;
  }

  delay(100);
}