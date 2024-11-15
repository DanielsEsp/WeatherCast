



void current_datas_load() {
  
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
                     const char* datetime = doc["current"]["time"];
                     Serial.println(String(doc["current"]["time"])); Serial.println();
                     temperature = String(doc["current"]["temperature_2m"]);          Serial.print("Temperature    "); Serial.print(temperature);    Serial.println(" \u00B0C");
                     ressenti = String(doc["current"]["apparent_temperature"]);       Serial.print("Ressenti       "); Serial.print(ressenti);       Serial.println(" \u00B0C");
                     humidity = String(doc["current"]["relative_humidity_2m"]);       Serial.print("Humidite       "); Serial.print(humidity);       Serial.println(" %");
                     pression = String(doc["current"]["surface_pressure"]);           Serial.print("Pression       "); Serial.print(pression);       Serial.println(" hPa");
                     is_day = String(doc["current"]["is_day"]).toInt();               Serial.print("Flag jour      "); Serial.print(is_day);         Serial.println(" 1=jour 0=nuit");
                     vent_vitesse = String(doc["current"]["wind_speed_10m"]);         Serial.print("Vent vitesse   "); Serial.print(vent_vitesse);   Serial.println(" kmh");       
                     vent_rafale = String(doc["current"]["wind_gusts_10m"]);          Serial.print("Vent rafales   "); Serial.print(vent_rafale);    Serial.println(" kmh");
                     vent_direction = String(doc["current"]["wind_direction_10m"]);   Serial.print("Vent direction "); Serial.print(vent_direction); Serial.println(" \u00B0");
                     weather_code = String(doc["current"]["weather_code"]).toInt();   Serial.print("Meteo code     "); Serial.print(weather_code);          
                                    for (int pointeur = 0; pointeur <= 27; pointeur ++) {
                                         if (String(weather_code) == dataIcones[pointeur]) {
                                             description = dataDescription[pointeur]; Serial.print(" > "); Serial.println(description);
                                            }                            
                                        }  
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
