# pragma once
# include "libraries.h"

class Ligge
{
    private:
        sensors_event_t a;
        sensors_event_t g;
        sensors_event_t t;
        
        const int time_limit = 120000;         // 120 000 millisec = 2 min 
        int current_pos = 0;                   //current position: right = 1, left = 2, back = 3, sitting = 4, other = 0
        int current_pos_ts;                    //timestamp for time in current position

        // private funksjoner
        int check_current_pos ();
        bool right_side ();
        bool left_side ();
        bool back_side ();
        bool sitting ();
        void send_pos ();
        void send_alarm ();
        
    public:
        Ligge () {};         // inititalisering av klassen
        void loop(sensors_event_t accel, sensors_event_t gyro, sensors_event_t temp);
};