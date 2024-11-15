



void datas_extraction() {

     lengthDataReceve = dataReceve.length();
     pointeur = 0;
 
     for (boucle = 1; boucle <= lengthDataReceve; boucle ++) {
          extract = dataReceve.substring(boucle, boucle + 1);

          if (extract != "," & extract != "]") {
              dataExtract = dataExtract + extract;
          } else {
              pointeur ++; 
              dataTableau[pointeur] = dataExtract;           
              dataExtract = "";
          }

     dimTableau = pointeur;      
     }

}
