# WeatherCast

OpenMeteo-WeatherCast

![OpenMeteo_Screen](https://github.com/user-attachments/assets/9d547d44-8e36-4f34-917e-a340da5bc95e)

Current and 3 days weather cast from OpenMeteo API

Suite au changement des conditions d'utilisation de l'API OpenWeatherMap càd enregistrement d'un mode de paiement même pour l'option free (ce que je ne souhaitais pas, je suis tombé sur un tutoriel du très bon site Random Nerd
qui utilise l'API du serveur OpenMeteo dont l'accès et l'utilisation restent gratuits (pour le moment).

[](https://github.com/HaroleDev/Airycons/tree/main)

De plus ce site permet l'obtention des données de plusieurs services météo.
Les données peuvent êtres récupérées au format XLSX, CSV et pour ce qui nous intéresse au format Json.
Pour le mode current, l'extraction ne pose aucun problème, mais avec les datas daily et hourly je n'ai pas réussi l'extracion en mode [indice], j'ai donc écrit une courte routine pour lire les datas pour chaque jour afin de les exploiter dans le programme.

https://open-meteo.com/en/docs

Le projet actuel permet l'affichage des données actuelles rafraîchies toutes les 15 minutes.
De l'icone météo selon le weather code reçu, la température, le ressenti, l'humidité et la pression.
Et pour les 3 jours à venir, l'icone météo et les températures maxi, mini prévues.
Tout cela sur un écran TFT ILI9488 de résolution 480 x 320 pixels servi par un Esp32.
le sketch est composé de:
- OpenMeteo_Current_-_3_days.ino     programme de base
- current_datas_load.ino             récupération datas du moment
- daily_datas_load.ino               récupération datas pour les 3 jours
- datas_extractions.ino              extraction des datas daily de la chaîne
- temp_format.ino                    mise au format de la température pour l'affichage
                                     car de temps à autres une chaine de type 8.40000001 apparait
                                     et aussi pour le format une décimale.
Je n'ai pas réussi à 'uploader' le fichier data des images (sûrement trop volumineux), il faut donc le créer et y placer le contenu des quatres fichiers 'iconess'

Un grand merci HaroleDev pour le partage de ses icones, dont je publie le lien ci-dessous

https://github.com/HaroleDev/Airycons/tree/main

et Bodmer pour ses librairies

https://github.com/Bodmer/TFT_eSPI
https://github.com/Bodmer/TJpg_Decoder

Autres bases acquises sur le site Randomnerdtutorials

https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
https://randomnerdtutorials.com/esp32-tft-lvgl-weather-station/

