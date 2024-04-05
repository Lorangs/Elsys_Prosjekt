# include "svelge.h"

void Svelgesensor::loop() {
    piezo_reading = analogRead(PIEZO_SENSOR);
    append_data();
    detect_swallows();
}

void Svelgesensor::append_data(){
  if (p_index >= ARRAY_LENGTH-1) {
    p_index = 0;
  }
  // Append data to the arrays
  piezo[p_index] = piezo_reading;
  time_values[p_index] = millis()/1000;
  gyro_values[p_index] = g.gyro.y; 
  p_index++; // Increment the index tracker
}

void Svelgesensor::detect_swallows() {
  if (piezo[p_index] > PIEZO_THRESHOLD && abs(gyro_values[p_index]) < GYRO_THRESHOLD){
    if(s_index == 0){
      swallow_times[s_index] = time_values[p_index];
      send_swallow_data();
      s_index++;
    }
    //check if the time or the time one second before the time we want to append is already in swallow_times
    else if ((time_values[p_index] - swallow_times[s_index-1]) > 1){
      swallow_times[s_index] = time_values[p_index];
      send_swallow_data();
      s_index++;
    }
  }
}

void Svelgesensor::send_swallow_data(){
  //Serial.println(swallow_times[s_index]);
  int data = swallow_times[s_index];
  WiFiClient client;
  if (client.connect(serverAddress, serverPort)) {
    String postData = "data=" + String(data); // Adjust payload as needed
    client.println("POST /receiver_path HTTP/1.1");
    client.println("Host: " + String(serverAddress) + ":" + String(serverPort));
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(postData.length()));
    client.println();
    client.println(postData);
  }
  client.stop();
}
