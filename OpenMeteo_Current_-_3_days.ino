



#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "############";
const char* password = "@@@@@@@@";


   String  timezone = "Europe/Paris";
   #define TEMP_CELSIUS 1
   String  temperature_unit = "";
const char degree_symbol[] = "\u00B0C";
       int oneCall = (15*60)*1000;// pour 15 minutes en microsecondes
       int lastCall;
      bool firstCall = true;
      
//        Varialbles WEATHER DATAS LOAD
   String current = ("https://api.open-meteo.com/v1/forecast?latitude=48.477&longitude=7.6788&current=temperature_2m,relative_humidity_2m,apparent_temperature,is_day,precipitation,weather_code,surface_pressure,wind_speed_10m,wind_direction_10m,wind_gusts_10m&timezone=auto");    
   String daily = ("https://api.open-meteo.com/v1/forecast?latitude=48.477&longitude=7.6788&daily=weather_code,temperature_2m_max,temperature_2m_min,apparent_temperature_max,precipitation_probability_max,wind_speed_10m_max,wind_gusts_10m_max,wind_direction_10m_dominant&timezone=auto&forecast_days=4&models=meteofrance_seamless");
   String url;
   String current_date;
   String last_weather_update;
   String temperature;
   String ressenti;
   String humidity;
   String pression;
   String vent_vitesse;
   String vent_rafale;
   String vent_direction;
      int is_day;
     bool grande_icone = true;
      int weather_code, weather_description, temp_icone;
   String weather_code_txt;

   String tempMax;   
   String tempMin;
   String appTempMax;
   String appTempMin;      
   String prevPluieMax;   


//        Varialbles DATAS EXTRACTION   
   String dataReceve;                   //chaine brute reçue
      int lengthDataReceve;             //longueur de la chaine reçue
      int boucle;                       //indice compteur lecture chaine
      int pointeur;                     //indice pointeur tableau de reception
   String extract;                      //carractère extrait de la chaine
   String dataExtract;                  //donnée isolée extraite de la chaine  
const int dimMaxTableau = 5;            //indice nombre maxi de donées tableau
   String dataTableau[dimMaxTableau];   //tableau de reception des données
      int dimTableau;   
    float decimal, decimalTemp, integerTemp;


#include <SPI.h>
#include <TFT_eSPI.h>
          TFT_eSPI tft = TFT_eSPI();
#define   TFT_LED 33
#include "Free_Fonts.h"

#define   FS_NO_GLOBALS
#include <FS.h>
#include "SPIFFS.h"

#include <TJpg_Decoder.h>
          uint16_t w = 0, h = 0;
          int x, y = 0;
          bool tft_output (int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap) {
                           if (y >= tft.height() ) return 0;
                               tft.pushImage(x, y, w, h, bitmap);
                               return 1;    
                              }
          String icone, description;
          String dataIcones[28] = { "0", "1", "2", "3", "45", "48", "51", "53",
                                    "55","56", "57", "61", "63", "65", "66", "67",
                                    "71", "73", "75", "77", "80", "81", "82", "85",
                                    "86", "95", "96", "99" };
          String dataDescription[28] = { "Ciel clair", "Principalement clair", "Partiellement nuageux", "Couvert",
                                         "Brouillard", "Brouillard givrant",
                                         "Legere bruine", "Bruine moderee", "Bruine dense",
                                         "Bruine verglacante", "Forte bruine verglacante",
                                         "Legere pluie", "Pluie moderee", "Forte pluie",
                                         "Legere pluie verglacante", "Forte pluie verglacante",
                                         "Legeres chutes de neige", "Chutes de neige moderees", "Fortes chutes de neige",
                                         "Neige", "Faibles averses", "Averses moderees", "Violentes averses",
                                         "Legeres averses de neige", "Fortes averses de neige", "Orage faible ou modere",
                                         "Orage faible risque de grele", "Orage et risque de grele" };
             int pointIcone = 0;



void icone_display() {

     TJpgDec.getFsJpgSize(&w, &h, "/" + icone + ".jpg");
     TJpgDec.drawFsJpg(x, y, "/" + icone + ".jpg");
  
}


void setup() {

     Serial.begin(115200); Serial.println(); Serial.println();

     WiFi.begin(ssid, password);
     Serial.print("Connecting");
     while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
           }
     Serial.print("\nConnected to Wi-Fi network with IP Address: ");
     Serial.println(WiFi.localIP()); Serial.println(); Serial.println();

     if (!SPIFFS.begin()) {
         Serial.println("SPIFFS initialisation failed!");
         while (1) yield();
     }
     
     tft.init();
     tft.setRotation(3);
     pinMode(TFT_LED, OUTPUT);
     digitalWrite(TFT_LED, HIGH);
     tft.fillScreen(TFT_BLACK);

     tft.setSwapBytes(true);
     TJpgDec.setJpgScale(1);
     TJpgDec.setCallback(tft_output);
 
     tft.setTextColor(TFT_WHITE, TFT_BLACK);
         
}


void loop() {

     if (WiFi.status() != WL_CONNECTED) {
         ESP.restart();
        }
     delay(50);
     
     
     if (((millis() - lastCall) > oneCall) || (firstCall == true)) {
         lastCall = millis();
         firstCall = false;
         tft.fillScreen(TFT_BLACK);

         url = current; current_datas_load();
         if (is_day == 1) { icone = "D_"; } else { icone = "N_"; }
     
         for (int pointeur = 0; pointeur <= 27; pointeur ++) {
              if (String(weather_code) == dataIcones[pointeur]) { 
                  x = 30, y = 5; icone = icone + dataIcones[pointeur]; icone_display();
                  tft.setFreeFont(FF18); tft.setCursor(60, 235); tft.print(description); 
                 }                            
             }      

         dataReceve = temperature; temp_format(); temperature = dataExtract; dataExtract = "";
         tft.setFreeFont(FF20); tft.drawRightString(temperature, 440, 20, 7); tft.drawString("o", 450, 17, 4);
         tft.setFreeFont(FF20); tft.drawRightString("Temperature", 325, 53, 2);

         temp_icone = temperature.toInt();
         if (temp_icone < 0) { icone = "1"; }
         if (temp_icone >= 0 && temp_icone < 10) { icone = "2"; } 
         if (temp_icone >= 10 && temp_icone < 15) { icone = "2"; }
         if (temp_icone >= 15 && temp_icone < 18) { icone = "3"; }
         if (temp_icone >= 18 && temp_icone < 20) { icone = "4"; }
         if (temp_icone >= 20 && temp_icone < 22) { icone = "5"; }
         if (temp_icone >= 22 && temp_icone < 24) { icone = "6"; }
         if (temp_icone >= 24 && temp_icone < 28) { icone = "7"; }
         if (temp_icone >= 28) { icone = "8"; }        
         x = 220, y = 23; icone_display();
                 
         dataReceve = ressenti; temp_format(); ressenti = dataExtract; dataExtract = "";
         tft.setFreeFont(FF20); tft.drawRightString(ressenti, 440, 90, 7); tft.drawString("o", 450, 87, 4);
         tft.setFreeFont(FF20); tft.drawRightString("Ressenti", 325, 123, 2);      

         tft.setFreeFont(FF20); tft.drawRightString(pression, 215, 160, 7);tft.drawString("hPa", 220, 160, 4);      
         x = 10, y = 165; icone = "pression"; icone_display();
         tft.setFreeFont(FF20); tft.drawString("Pression", 5, 193, 2);
          
         x = 275, y = 165; icone = "humide"; icone_display();
         tft.setFreeFont(FF20); tft.drawRightString(humidity, 440, 160, 7); tft.drawString("%", 450, 160, 4);
         tft.setFreeFont(FF20); tft.drawRightString("Humidite", 365, 193, 2);      

         url = daily; daily_datas_load();
         dataReceve = weather_code_txt; datas_extraction();
         for (int pointeur = 0; pointeur <= 27; pointeur ++) {
              if (dataTableau[1] == dataIcones[pointeur]) { 
                  x = 10; y = 245; icone = "P_" + dataIcones[pointeur]; icone_display();
                 } 
             }                           
         for (int pointeur = 0; pointeur <= 27; pointeur ++) {
              if (dataTableau[2] == dataIcones[pointeur]) { 
                  x = 160; y = 245; icone = "P_" + dataIcones[pointeur]; icone_display();
                 } 
             }  
         for (int pointeur = 0; pointeur <= 27; pointeur ++) {
              if (dataTableau[3] == dataIcones[pointeur]) { 
                  x = 310; y = 245; icone = "P_" + dataIcones[pointeur]; icone_display();
                 } 
             }  

         x = 90; y = 250; icone = "fleches"; icone_display(); 
         x = 237; y = 250; icone = "fleches"; icone_display();  
         x = 390; y = 250; icone = "fleches"; icone_display();  

         dataReceve = tempMax; datas_extraction();
         dataReceve =(dataTableau[1]); temp_format(); tempMax = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMax, 150, 255, 1); tft.drawString("o", 152, 250, 2);
         dataReceve =(dataTableau[2]); temp_format(); tempMax = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMax, 300, 255, 1); tft.drawString("o", 302, 250, 2);
         dataReceve =(dataTableau[3]); temp_format(); tempMax = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMax, 455, 255, 1); tft.drawString("o", 457, 250, 2);

         dataReceve = tempMin; datas_extraction();
         dataReceve =(dataTableau[1]); temp_format(); tempMin = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMin, 150, 280, 1); tft.drawString("o", 152, 275, 2);
         dataReceve =(dataTableau[2]); temp_format(); tempMin = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMin, 300, 280, 1); tft.drawString("o", 302, 275, 2);
         dataReceve =(dataTableau[3]); temp_format(); tempMin = dataExtract; dataExtract = "";
         tft.setFreeFont(FF18); tft.drawRightString(tempMin, 455, 280, 1); tft.drawString("o", 457, 275, 2);

        }

}
