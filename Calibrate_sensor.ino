#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

// Dirección del MPU6050 (0x68 o 0x69 dependiendo del estado de AD0)
MPU6050 sensor;

// Valores RAW del acelerómetro y giroscopio
int16_t ax, ay, az;
int16_t gx, gy, gz;

// Variables para el filtro pasa bajos
long f_ax, f_ay, f_az;
int p_ax, p_ay, p_az;
long f_gx, f_gy, f_gz;
int p_gx, p_gy, p_gz;
int counter = 0;

// Offsets
int ax_o, ay_o, az_o;
int gx_o, gy_o, gz_o;

void setup() {
  Serial.begin(57600);
  Wire.begin(21,22);
  sensor.initialize();

  if (sensor.testConnection()) {
    Serial.println("Sensor iniciado correctamente");
  }

  // Leer offsets actuales
  ax_o = sensor.getXAccelOffset();
  ay_o = sensor.getYAccelOffset();
  az_o = sensor.getZAccelOffset();
  gx_o = sensor.getXGyroOffset();
  gy_o = sensor.getYGyroOffset();
  gz_o = sensor.getZGyroOffset();

  Serial.println("Offsets:");
  Serial.print(ax_o); Serial.print("\t");
  Serial.print(ay_o); Serial.print("\t");
  Serial.print(az_o); Serial.print("\t");
  Serial.print(gx_o); Serial.print("\t");
  Serial.print(gy_o); Serial.print("\t");
  Serial.println(gz_o);
  Serial.println("\n\nEnvíe cualquier caracter para empezar la calibración\n\n");

  while (!Serial.available()) {}
  Serial.println("Calibrando, no mover IMU");
}

void loop() {
  // Leer acelerómetro y giroscopio
  sensor.getAcceleration(&ax, &ay, &az);
  sensor.getRotation(&gx, &gy, &gz);

  // Filtro pasa bajos
  f_ax = f_ax - (f_ax >> 5) + ax;
  p_ax = f_ax >> 5;

  f_ay = f_ay - (f_ay >> 5) + ay;
  p_ay = f_ay >> 5;

  f_az = f_az - (f_az >> 5) + az;
  p_az = f_az >> 5;

  f_gx = f_gx - (f_gx >> 3) + gx;
  p_gx = f_gx >> 3;

  f_gy = f_gy - (f_gy >> 3) + gy;
  p_gy = f_gy >> 3;

  f_gz = f_gz - (f_gz >> 3) + gz;
  p_gz = f_gz >> 3;

  // Cada 100 lecturas, ajustar offset
  if (counter == 100) {
    Serial.print("Promedio:\t");
    Serial.print(p_ax); Serial.print("\t");
    Serial.print(p_ay); Serial.print("\t");
    Serial.print(p_az); Serial.print("\t");
    Serial.print(p_gx); Serial.print("\t");
    Serial.print(p_gy); Serial.print("\t");
    Serial.println(p_gz);

    // Calibrar acelerómetro (1g en Z)
    ax_o += (p_ax > 0) ? -0.1 : 0.1;
    ay_o += (p_ay > 0) ? -0.1 : 0.1;
    az_o += ((p_az - 16384) > 0) ? -0.1 : 0.1;

    sensor.setXAccelOffset(ax_o);
    sensor.setYAccelOffset(ay_o);
    sensor.setZAccelOffset(az_o);

    // Calibrar giroscopio (0 en todos los ejes)
    gx_o += (p_gx > 0) ? -0.1 : 0.1;
    gy_o += (p_gy > 0) ? -0.1 : 0.1;
    gz_o += (p_gz > 0) ? -0.1 : 0.1;

    sensor.setXGyroOffset(gx_o);
    sensor.setYGyroOffset(gy_o);
    sensor.setZGyroOffset(gz_o);

    counter = 0;
  }

  counter++;
}
