int CiPin = 4;          // Container Sensor Pin
int CcPin = 5;          // Capping station sensor Pin
int CapPin = 6;         // Cap Sensor Pin
int HeadDwPin = 7;      // Cap Screwing Head Up, Pneumatic Forward Pin
int HeadUpPin =8;       // Pneumatic Reverse Pin
int MotorPin = 10;      // Stepping Motor drive Pin  
int CapAlarm = 11;      // No cap Alarm Pin
int Cap = 0;
int Cc = 0;
int Ci = 0;
int A = 0;

void setup() {
Serial.begin(9600);
pinMode(4, INPUT);
pinMode(5, INPUT);
pinMode(6, INPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
 
}

void loop() {
  Cap = digitalRead(CapPin);
  if (Cap == HIGH)                        // Cap detector HIGH = Capready, LOW = No Cap.
  {
    for (int i = 0; i <= 400; i++)       // Motor Move 90 degrees
      {
        digitalWrite(MotorPin, LOW);     // Pule generation 50% dutycycle 20 Milisec. Pulse Repletiontion time 
        delay(10);
        digitalWrite(MotorPin, HIGH);
        delay(10); 
      }
    if (digitalRead(CcPin) == HIGH)                       // Container in the capping position.
      {
        int A;
        A = CappingFunction();              // Call Capping Function
      }
    else 
      {
        for (int i = 0; i <= 50; i++)       // Motor Move 90 degrees
          {
          digitalWrite(MotorPin, LOW);     // Pule generation 50% dutycycle 20 Milisec. Pulse Repletiontion time 
          delay(10);
          digitalWrite(MotorPin, HIGH);
          delay(10); 
          }
      }
  }
  else {
        Serial.println(" No Cap!!!");
        digitalWrite(CapAlarm, HIGH);       // No Cap Alarm.
        delay(500);
      }
}
int CappingFunction()
  {
    digitalWrite(MotorPin, LOW);        // Stop Motor
    digitalWrite(HeadDwPin, HIGH);      // Pneumatic pistol Forward On, Capping Screw Head downward.
    digitalWrite(HeadUpPin, LOW);       // Pneumatic pistoal Reverse Off. 
    delay(2000);                        // Screwing the Cap, 2 sec. Time Interval.
    digitalWrite(HeadDwPin, LOW);       // Pneumatic pistal Forward Off,
    digitalWrite(HeadUpPin, HIGH);      // Pneumatic pistoal Reverse ON, Secure the Capping Head.
    delay(500);                         // Interval 500 milisec.
  }