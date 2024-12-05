#define CH1 3    // Canal 1 - Adelante / Atrás
#define CH2 5    // Canal 2 - Izquierda / Derecha
#define MOTOR_IN1 9 
#define MOTOR_IN2 8 
#define MOTOR_PWM 10 

#define SERVO1 6   // Servo 1
#define SERVO2 7   // Servo 2
#define SERVO3 11  // Servo 3
#define SERVO4 12  // Servo 4

int ch1Value, ch2Value;

int readRawPulse(int channelInput) {
  return pulseIn(channelInput, HIGH, 30000);
}

int readMappedChannel(int channelInput, int minLimit, int maxLimit) {
  int pulse = readRawPulse(channelInput);

  if (pulse < 1000 || pulse > 2000) return 0;

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

void controlServo(int servoPin, int position) {
  analogWrite(servoPin, position);
}

void setup() {
  Serial.begin(115200);

  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(MOTOR_PWM, OUTPUT);

  pinMode(SERVO1, OUTPUT);
  pinMode(SERVO2, OUTPUT);
  pinMode(SERVO3, OUTPUT);
  pinMode(SERVO4, OUTPUT);

  controlMotor(0);
  controlServo(SERVO1, 0);
  controlServo(SERVO2, 0);
  controlServo(SERVO3, 0);
  controlServo(SERVO4, 0);
}

void loop() {
  ch1Value = readMappedChannel(CH1, -255, 255); 
  ch2Value = readMappedChannel(CH2, -255, 255); 

  // Movimiento de los motores
  controlMotor(ch1Value);

  // Control de servos
  controlServo(SERVO1, ch2Value);
  controlServo(SERVO2, ch2Value);
  controlServo(SERVO3, ch2Value);
  controlServo(SERVO4, ch2Value);

  Serial.print("CH1 Value: ");
  Serial.println(ch1Value);
  Serial.print("CH2 Value: ");
  Serial.println(ch2Value);

  delay(50); 
}
