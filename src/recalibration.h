#ifndef RECALIBRATION_H
#define RECALIBRATION_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include "display.h" 
#include "sound.h"  

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2; 
extern Adafruit_MPU6050 mpu;

// Variables partagées
extern float lastX, lastY, lastZ;
extern float offX, offY, offZ;
extern int currentX, currentY, currentZ;

const float MARGE_TOLERANCE = 0.15; 

void attendreStabilite() {
  bool estPret = false;
  unsigned long debutStabilite = 0;
  int dernierSecondeAffichee = -1;

  while (!estPret) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // On surveille les 3 axes physiques pour une stabilité totale
    bool stableMaintenant = (abs(a.acceleration.y - lastX) < MARGE_TOLERANCE && 
                             abs(a.acceleration.z - lastY) < MARGE_TOLERANCE &&
                             abs(a.acceleration.x - lastZ) < MARGE_TOLERANCE);

    if (!stableMaintenant) {
      debutStabilite = 0; 
      dernierSecondeAffichee = -1;
      ecrire(15, 35, FONT_TECH, "STABILISEZ PIXY...");
      delay(2000);
    } 
    else {
      if (debutStabilite == 0) debutStabilite = millis();
      long tempsEcoule = millis() - debutStabilite;
      int secondesRestantes = 5 - (tempsEcoule / 1000);

      if (secondesRestantes != dernierSecondeAffichee) { 
        char buf[2];
        sprintf(buf, "%d", (secondesRestantes < 0 ? 0 : secondesRestantes));
        ecrire(55, 45, FONT_COUNT, buf);
        dernierSecondeAffichee = secondesRestantes;
        bip(1, 1, 0.01); // Petit bip de décompte
      }
      if (secondesRestantes <= 0) estPret = true;
    }
    // Mise à jour des 3 axes de référence
    lastX = a.acceleration.y;
    lastY = a.acceleration.z;
    lastZ = a.acceleration.x;
    delay(50); 
  }
}

void autorecalibration() {
  sensors_event_t a, g, temp;
  double sumH = 0, sumV = 0, sumG = 0; // H:Horizontal, V:Vertical, G:Gravité
  int echantillons = 500; 

  ecrire(25, 30, FONT_TECH, "CALIBRATION...");
  delay(1000);

  for(int i=0; i < echantillons; i++) {
    mpu.getEvent(&a, &g, &temp);
    
    // MAPPAGE SELON TA THÉORIE :
    sumH += a.acceleration.y; // Y physique -> Horizontal
    sumV += a.acceleration.z; // Z physique -> Vertical regard
    sumG += a.acceleration.x; // X physique -> Gravité (Verticale réelle)
    
    if(i % 20 == 0) { 
      u8g2.clearBuffer();
      u8g2.setFont(FONT_TECH);
      u8g2.drawStr(25, 30, "CALIBRATION..."); // ne pas utiliser ecrire()
      
      u8g2.setFont(FONT_INFO);
      u8g2.drawStr(20, 35, "NE PAS BOUGER"); // Pas besoin de ecrire() ici
      
      // Barre de progression
      u8g2.drawFrame(10, 40, 104, 7); 
      u8g2.drawBox(12, 42, (i * 104 / echantillons), 3); 
      u8g2.sendBuffer();
    }
    delay(10); 
  }
  
  // Calcul des moyennes finales
  offX = (float)(sumH / echantillons);
  offY = (float)(sumV / echantillons);
  offZ = (float)(sumG / echantillons);

  // Affichage final des résultats sur l'OLED
  char res[40];
  sprintf(res, "X:%.1f Y:%.1f Z:%.1f", offX, offY, offZ);
  ecrire(20, 25, FONT_TECH, "OFFSETS OK :");
  delay(1500);
  ecrire(10, 45, FONT_TECH, res, false); // false pour ne pas effacer le titre

  delay(2000); // A  remplacer par une commande ( vocale, tactile ou par bouton) plus tard
  ecrire(35, 35, FONT_INFO, "PIXY PRET !");
  bip(2, 2, 0.08, 0.04); 
  delay(1000);

  
  unsigned long timerTest = millis();
  while(millis() - timerTest < 5000) { // Test visuel pendant 3s
      sensors_event_t a, g, temp;
      if (mpu.getEvent(&a, &g, &temp)) {
          float netHoriz = a.acceleration.y - offX;
          float netVerti = a.acceleration.z - offY;

          currentX = CENTER_X - (int)(netHoriz * 5); 
          currentY = CENTER_Y - (int)(netVerti * 5); 

          currentX = constrain(currentX, 15, 113);
          currentY = constrain(currentY, 15, 49);

          dessinerOeilInteractif(currentX, currentY);
      }
      delay(10); // Fluidité
  }
 
}

#endif