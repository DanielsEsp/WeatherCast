



void temp_format() {

     lengthDataReceve = dataReceve.length();
 
     for (boucle = 0; boucle <= lengthDataReceve; boucle ++) {
          extract = dataReceve.substring(boucle, boucle + 1);

          if (extract != ".") {
              dataExtract = dataExtract + extract;
          } else {
              extract = dataReceve.substring(boucle, boucle + 2);
              dataExtract = dataExtract + extract;              
              boucle = lengthDataReceve;          
          }
     
     }

     decimalTemp = dataExtract.toFloat();
     integerTemp = int(decimalTemp);
     decimal = decimalTemp - integerTemp;
     if (decimal == 0) { dataExtract = dataExtract + ".0"; }

}
