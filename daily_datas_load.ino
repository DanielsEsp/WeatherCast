

    
     
void daily_datas_load() {    
     
     if (WiFi.status() == WL_CONNECTED) {
         HTTPClient http; 
         http.begin(url);
         int httpCode = http.GET(); 

         if (httpCode > 0) {
             if (httpCode == HTTP_CODE_OK) {
                 String payload = http.getString();
                 Serial.println("Request information:");
                 Serial.println(payload); Serial.println();
                 StaticJsonDocument<1024> doc;
                 DeserializationError error = deserializeJson(doc, payload);
                 if (!error) {
                     const char* datetime = doc["daily"]["time"];
                     Serial.println(String(doc["daily"]["time"])); Serial.println();
                     tempMax = String(doc["daily"]["temperature_2m_max"]); Serial.print("Temperature maxi    "); Serial.print(tempMax);    Serial.println(" \u00B0C");
                     tempMin = String(doc["daily"]["temperature_2m_min"]); Serial.print("Temperature mini    "); Serial.print(tempMin);       Serial.println(" \u00B0C");
                     weather_code_txt = String(doc["daily"]["weather_code"]); Serial.print("Meteo code     "); Serial.println(weather_code_txt);          
                     Serial.print("Time zone "); Serial.println(String(timezone));
                     String datetime_str = String(datetime);
                     int splitIndex = datetime_str.indexOf('T');
                     current_date = datetime_str.substring(0, splitIndex);
                     last_weather_update = datetime_str.substring(splitIndex + 1, splitIndex + 9); // Extract time portion
                     Serial.print("Derniere mise a jour "); Serial.println(last_weather_update); Serial.println();
                    } else {
                     Serial.print("deserializeJson() failed: ");
                     Serial.println(error.c_str());
                    }
                }
           } else {
            Serial.printf("GET request failed, error: %s\n", http.errorToString(httpCode).c_str());
            delay(9999);
            Serial.printf("Reset !");           
            esp_restart(); delay(100);
           }
       http.end(); // Close connection
      } else {
       Serial.println("Not connected to Wi-Fi");
      }
  
}
