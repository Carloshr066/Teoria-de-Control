#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

MPU6050 sensor;

// Definiciones de pines de motores
const int pinPWMA = 23;
const int pinAIN2 = 4;
const int pinAIN1 = 0;
const int pinPWMB = 16;
const int pinBIN1 = 5;
const int pinBIN2 = 17;
const int pinSTBY = 18;

// Variables del sensor MPU6050
int16_t ax, ay, az;
int16_t gx, gy, gz;
long tiempo_prev;
float dt;
float ang_x, ang_y;
float ang_x_prev, ang_y_prev;

// Variables PID
float Kp = 5; // Ajusta estos valores según sea necesario
float Ki = 10;
float Kd = 0.1;
float integral = 0.0;
float derivative = 0.0;
float previous_error = 0.0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Pines SDA = 32, SCL = 33
  delay(500);//Evitar errores en el arranque
  sensor.initialize();
  
  if (!sensor.testConnection()) {
  Serial.println("Error: No se pudo conectar con el MPU6050");
  while (1); // Detiene el programa si no hay conexión
  }


  tiempo_prev = millis();

  // Configurar pines de motores
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
  pinMode(pinSTBY, OUTPUT);
}

void loop() {
  // Obtener datos del MPU6050
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  // Calcular ángulos con el acelerómetro
  float accel_ang_x = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * (180.0 / PI);
  float accel_ang_y = atan(-ax / sqrt(pow(ay, 2) + pow(az, 2))) * (180.0 / PI);

  // Calcular ángulo de rotación con giroscopio y filtro complementario
  dt = (millis() - tiempo_prev) / 1000.0;
  if (dt <= 0) return;

  tiempo_prev = millis();
  ang_x = 0.98 * (ang_x_prev + (gx / 131.0) * dt) + 0.02 * accel_ang_x;
  ang_y = 0.98 * (ang_y_prev + (gy / 131.0) * dt) + 0.02 * accel_ang_y;

  ang_x_prev = ang_x;
  ang_y_prev = ang_y;

  // Control del péndulo invertido usando PID
  float desired_angle = 0.0;
  float error = desired_angle - ang_x;

  integral += error * dt;
  derivative = (error - previous_error) / dt;

  float motor_speed = Kp * error + Ki * integral + Kd * derivative;
  
  motor_speed = constrain(motor_speed, -200, 200);

  // Verificar si motor_speed es NaN y establecerlo en 0 si lo es
  if (isnan(motor_speed)) {
    motor_speed = 0;
  }


  // Controlar los motores
  enableMotors();
  moveMotor(pinPWMA, pinAIN1, pinAIN2, motor_speed);
  moveMotor(pinPWMB, pinBIN1, pinBIN2, motor_speed);

  // Mostrar los ángulos y la velocidad de los motores
  Serial.print("Rotación en X: ");
  Serial.print(ang_x);
  Serial.print(", Error: ");
  Serial.print(error);
  Serial.print(", Velocidad de los motores: ");
  Serial.println(motor_speed);

  previous_error = error;
  enableMotors();
  delay(1); // Aumentar frecuencia de muestreo
  enableMotors();
}

// Funciones adicionales
void moveMotor(int pinPWM, int pinIN1, int pinIN2, float speed) {
  if (speed > 0) {
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);
    analogWrite(pinPWM, speed);
  } else {
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);
    analogWrite(pinPWM, -speed);
  }
}

void enableMotors() {
  digitalWrite(pinSTBY, HIGH);
}
