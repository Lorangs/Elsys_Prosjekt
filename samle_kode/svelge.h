//Author
//Denne koden sender data via internett
//den printer ingenting!! all serial er tatt ut
//Helene og Nikolai eier koden 
//Sist fungerende: 04.04 kl 15:05

# pragma once
# include "libraries.h"

#define ARRAY_LENGTH 1000                               // Må trolig endres
#define PIEZO_SENSOR A0                                 // the piezo is connected to analog pin 0
#define PIEZO_THRESHOLD 3000                            //must be set through testing
#define GYRO_THRESHOLD 0.1                              //must be set through testing

const char* ssid = "NN14Max";
const char* password = "12345678";
const char* serverAddress = "172.20.10.12";
const int serverPort = 5000;                            // Change to your server's port

class Svelge 
{
    private:
        sensors_event_t a;
        sensors_event_t g;
        sensors_event_t t;

        int piezo_reading = 0;                          // variable to store the value read from the sensor pin
        unsigned long time_now = 0;                     //setter nåværende tid til 0
        unsigned long swallow_times[ARRAY_LENGTH];      //lag en array som skal holde alle svelgetidspunkt
        int s_index = 0;                                // Index for the swallow_times array
        int piezo[ARRAY_LENGTH] ={0};                   //Making an array for Piezo values
        int p_index = 0;                                // Initialize the piezo index tracker
        unsigned long time_values[ARRAY_LENGTH]={0};    // Define the time array
        float gyro_values[ARRAY_LENGTH]={0};            //Make array for gyro values of rotation in y-axis

        // private funksjoner
        void append_data();
        void detect_swallows();
        void send_swallow_data();

    public:
        Svelge(){};
        void loop(sensors_event_t accel, sensors_event_t gyro, sensors_event_t temp);
};