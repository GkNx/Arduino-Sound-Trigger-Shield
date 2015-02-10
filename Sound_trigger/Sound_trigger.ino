#define FLASH_PIN 4
#define SHUTTER_PIN 2
#define SOUND_TRIGGER_ANALOG_PIN 0

int soundVal;

int outputValue;
int delaytime = 0;
int delayedtime = 0;

long ilkshutter = 0;

void setup() {
  pinMode(SHUTTER_PIN, OUTPUT); 
  digitalWrite(SHUTTER_PIN, LOW); 
  pinMode(FLASH_PIN, OUTPUT); 
  digitalWrite(FLASH_PIN, LOW); 
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW); 
  soundVal = analogRead(SOUND_TRIGGER_ANALOG_PIN);
  blinkLED(4);
}

void loop() {
  int sensorValue = analogRead(A1);
  outputValue = map(sensorValue, 0, 1023, 0, 500);
  int sensorValueDelay = analogRead(A3);
  delaytime = map(sensorValueDelay, 0, 1023, 0, 300);
  int newsoundVal = analogRead(SOUND_TRIGGER_ANALOG_PIN);
  if (abs(newsoundVal - soundVal > outputValue))
  {
    unsigned long sonshutter = millis();
    if(sonshutter - ilkshutter > 1000) {
      ilkshutter = sonshutter;
      delay(delaytime);
      digitalWrite(SHUTTER_PIN, HIGH);
      digitalWrite(FLASH_PIN, HIGH);
      delay(200);
      digitalWrite(SHUTTER_PIN, LOW);
      digitalWrite(FLASH_PIN, LOW);
      digitalWrite(13, LOW);
      blinkLED(2);
    }
  }
  soundVal = newsoundVal;
}

void blinkLED(int numBlinks) {
  for (int i=0; i < numBlinks; i++) {
    delay(50);
    digitalWrite(13, HIGH);   
    delay(50);                     
    digitalWrite(13, LOW);   
  }
}
