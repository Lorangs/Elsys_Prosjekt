// Dokumentasjon i github:      https://github.com/adafruit/Adafruit_MPU6050
// klassebeskrivelse og opcode: https://adafruit.github.io/Adafruit_MPU6050/html/class_adafruit___m_p_u6050.html
// referanse kode:              https://maker.pro/arduino/tutorial/how-to-build-a-fall-detector-with-arduino

# pragma once
# include "libraries.h"
# define RESET_BUTTON_PIN 4
# define LED_BUILTIN 2 

class Falle 
{
    private:
        sensors_event_t angle_acc1;
        sensors_event_t angle_acc2;
        float abs_accel = 0;
        float abs_gyro = 0;
        const int lower_threshold = 7;          // 0.5g m/s**2
        const int upper_threshold = 10;         // 1g   m/s**2
        const int rotation_threshold = 50;      // 50 grader rotering fra vertikal akse
        bool fall = 0;                          // Variabel for fall er detektert eller ikke
        bool reset = 0;                         // Tilbakestillingsknapp
        bool trigger1 = 0;                      // Fall i akselerasjonsverdier
        bool trigger2 = 0;                      // økning tilbake til normal av akselerasjonsverdier
        bool trigger3 = 0;                      // Rotering av personen i forhold til orientering før fall
        int trigger1count = 0;
        int trigger2count = 0;
        int trigger3count = 0;

        // private funksjoner
        float abs_acceleration (sensors_event_t accel);
        float abs_gyroscope (sensors_event_t gyro);
        void handel_trigger1 (sensors_event_t accel, sensors_event_t gyro);
        void handel_trigger2 (sensors_event_t gyro);
        void handel_trigger3 ();
        void reset_values();
        void read_reset_button();

    public:
        Falle();
        void loop();
}