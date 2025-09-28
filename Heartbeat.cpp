/*
  Heartbeat Monitoring System
  Counts BPM from pulse sensor
*/

const int pulsePin = A0;
const int buzzer = 8;
const int led = 9;
int signal = 0;
int beatCount = 0;
unsigned long startTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  startTime = millis();
  Serial.println("Heartbeat Monitor Started...");
}

void loop() {
  signal = analogRead(pulsePin);

  if (signal > 550) {   // Pulse detected
    beatCount++;
    delay(10); // Debounce
  }

  if (millis() - startTime >= 60000) { // Every 1 min
    Serial.print("Heart Rate: ");
    Serial.print(beatCount);
    Serial.println(" BPM");

    if (beatCount > 100) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      Serial.println("⚠️ High Heart Rate!");
    } else {
      digitalWrite(buzzer, LOW);
      digitalWrite(led, LOW);
    }

    beatCount = 0;
    startTime = millis();
  }
}
