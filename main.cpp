#include "svelge.h"
#include "ligge.h"
#include "falle.h"


// deklarasjon av globale variable
sensors_event_t a, g, t;
Adafruit_MPU6050 mpu;
Ligge ligge;
Svelge svelge;
Fall falle;

void setup() {
  //starting terminal for testing
  Serial.begin(115200);
  while (!Serial){
    delay(10);
  }
  Serial.print(F("Adafruit MPU6050 test!"));
  //initializing, error if not
  mpu.begin();
  if (!mpu.begin()) {
      Serial.print(F("Failed to find MPU6050 chip"));
      }

  //range of accelerometer
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

  //range of gyroscope
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  //bandwith of digital anti aliasing low pass filter
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop () {
    // oppdaterer variable fra gyroskop
    mpu.getEvent(&a, &g, &t);

    ligge.loop();
    svelge.loop();
    falle.loop();

}