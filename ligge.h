# pragma once
# include "libraries.h"

class Ligge_Saar 
{
    private:
        const int time_limit = 120000;         // 120 000 millisec - 2 min 
        int current_pos = 0;                   //current position: right = 1, left = 2, back = 3, sitting = 4, other = 0
        int current_pos_ts;                    //timestamp for time in current position

        // private funksjoner
        int check_current_pos (sensors_event_t a);
        bool right_side (sensors_event_t a);
        bool left_side (sensors_event_t a);
        bool back_side (sensors_event_t);
        bool sitting (sensors_event_t);
        void send_pos ();
        void send_alarm ();
        
    public:
        Ligge_Saar () {};
        void loop();
};