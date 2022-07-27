int CiPin = 4;          // Container Sensor Pin
int CcPin = 5;          // Capping station sensor Pin
int CapPin = 6;         // Cap Sensor Pin
int HeadDwPin = 7;      // Cap Screwing Head Up, Pneumatic Forward Pin
int HeadUpPin =8;       // Pneumatic Reverse Pin
int MotorPin = 10;      // Main Stepping Motor drive Pin  
int CapMotorPin = 11;  // Cap Insert Stepping Motor
int DirPin = 12;        // Direction Pin to set the motor direction , clockwise or anti-clockwise
int CapAlarm = 13;      // No cap Alarm Pin
int DirPin2 = 14;       // Cap Insert Motor Direction control  
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
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
 
}

void loop() {
  Cap = digitalRead(CapPin);
  if (Cap == HIGH)                          // Cap detector HIGH = Capready, LOW = No Cap.
  {
    digitalWrite(DirPin, HIGH);             // Set motor move clockwise
    for (int i = 0; i <= 20000; i++)        // Main Motor Move 100 turns
      {
        for (int n = 0; n <= 200; n++)      // Cap Insert: Cap Insert Motor move 1 turn
          {
          digitalWrite(DirPin2, HIGH);      // Set Cap Insert motor move clockwise
          digitalWrite(CapMotorPin, LOW);   // Pulse generator for Cap Insert Motor
          delay(10);
          digitalWrite(CapMotorPin, HIGH);
          }
        digitalWrite(MotorPin, LOW);        // Pule generator: 50% dutycycle 20 Milisec. Pulse Repletiontion time 
        delay(10);
        digitalWrite(MotorPin, HIGH);
        delay(10);
          if (digitalRead(CcPin) == HIGH)   // Container in the capping position.
              {
                int A;
                A = CappingFunction();      // Call Capping Function
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