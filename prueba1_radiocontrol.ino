#define CH1 3  
#define CH2 5  
#define MOTOR_IN1 9 
#define MOTOR_IN2 8 
#define MOTOR_PWM 10 

int ch2Value;

int readRawPulse(int channelInput) {
  return pulseIn(channelInput, HIGH, 30000);
}

int readMappedChannel(int channelInput, int minLimit, int maxLimit) {
  int pulse = readRawPulse(channelInput);

  if (pulse < 1000 || pulse > 2000) return 0;

  //Toleracia para el punto muerto
  if (pulse >= 1490 && pulse <= 1510) return 0;

  return map(pulse, 1000, 2000, minLimit, maxLimit);
}

void controlMotor(int speed) {
  if (speed > 0) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_PWM, speed);
  } 
  else if (speed < 0) {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
    analogWrite(MOTOR_PWM, -speed); 
  } 
  else {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_PWM, 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);

  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  controlMotor(0);
}

void loop() {
  ch2Value = readMappedChannel(CH2, -255, 255); 

  controlMotor(ch2Value);

  Serial.print("CH2 Value: ");
  Serial.println(ch2Value);

  delay(50); 
}
