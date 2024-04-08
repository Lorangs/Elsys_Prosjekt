# include "ligge.h"

//checking if pasient has switched position
void Ligge::loop(sensors_event_t accel, sensors_event_t gyro, sensors_event_t temp) {
  a = accel; g = gyro; t = temp;    // oppdatering av nye verdier fra gyroskop

  int new_pos = check_current_pos(accel);
  if (current_pos != new_pos) {
    current_pos = new_pos;
    current_pos_ts = millis();
    send_pos_laying();
  }
  //sending alarm if pasient has layed too long on same side
  else {
    if ((millis() - current_pos_ts) > time_limit) {
      current_pos_ts = 0;
      send_alarm ();
    }
  }
}

int Ligge::check_current_pos () {
  if      (right_side()) { return 1; }
  else if (left_side())  { return 2; }
  else if (back_side())  { return 3; }
  else if (sitting())    { return 4; }
  else                   { return 0; }
}

// true if pasient is laying on this side
bool Ligge::right_side () {
  if (a.acceleration.x >= -8    && a.acceleration.x <= -2   &&
      a.acceleration.y >= -8.5  && a.acceleration.y <= -2.5 &&
      a.acceleration.z >= 2.5   && a.acceleration.z <= 8.5) { return 1; }
  else { return 0; }
}

bool Ligge::left_side () {
  if (a.acceleration.x >= 2.5   && a.acceleration.x <= 8.5   &&
      a.acceleration.y >= -5    && a.acceleration.y <= 1    &&
      a.acceleration.z >= -12   && a.acceleration.z <= -6) { return 1; }
  else { return 0; }
}

bool Ligge::back_side (){ 
  if (a.acceleration.x >= 3     && a.acceleration.x <= 9    &&
      a.acceleration.y >= -11    && a.acceleration.y <= -4.5 &&
      a.acceleration.z >= -0.5   && a.acceleration.z <= 5.5) { return 1; }
  else { return 0; }
}

bool Ligge::sitting (){
  if (a.acceleration.x >= -2.5  && a.acceleration.x <= 4    &&
      a.acceleration.y >= -13   && a.acceleration.y <= -7   &&
      a.acceleration.z >= -5     && a.acceleration.z <= 2) { return 1; }
  else { return 0; }
}

//send functions for position and alarm
void Ligge::send_pos () {
  Serial.print("pos "); 
  Serial.println(current_pos);
}

void Ligge::send_alarm () {
  Serial.println(1);
}