// src/display.h

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8g2lib.h>
#include "../Config.h" // Pour accéder à la bibliothèque centrale de polices, SCREEN_WIDTH et SCREEN_HEIGHT

// --- RÉFÉRENCE EXTERNE ---
extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2; // Change SW en HW

// --- BITMAPS ---
// Visage souriant généré pour écran OLED 128x64
static const unsigned char oeil_sourire_bitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfc, 0x01, 0x00, 0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// --- FONCTIONS ---

/**
 * @brief Affiche une ligne de texte unique sur l'OLED.
 * @details Utilise le buffer de l'écran U8g2 et rafraîchit l'affichage immédiatement.
 * * @param x       Position horizontale (0 à 127).
 * @param y       Position verticale (ligne de base du texte, 0 à 64).
 * @param police  La police U8g2 à utiliser (ex: FONT_INFO, FONT_GAME).
 * @param message La chaîne de caractères à afficher.
 * @param effacer Si true (défaut), vide l'écran avant d'écrire. 
 * Mettre à false pour superposer du texte sur un dessin.
 */
inline void ecrire(int x, int y, const uint8_t *police, const char* message, bool effacer = true) {
  if (effacer) {
    u8g2.clearBuffer(); // On n'efface que si demandé
  }
  
  u8g2.setFont(police);
  u8g2.setDrawColor(1);
  u8g2.drawStr(x, y, message);
  
  u8g2.sendBuffer(); // On rafraîchit l'écran pour afficher le nouveau texte
}

/**
 * @brief Affiche plusieurs lignes de texte sur l'OLED.
 * @param x Coordonnée horizontale (0-127).
 * @param y Coordonnée verticale de la 1ère ligne (ligne de base).
 * @param police Alias de la police (ex: FONT_TECH).
 * @param messages Tableau de chaînes (ex: const char* m[] = {"A", "B"}).
 * @param nbMessages Nombre de lignes à afficher (défaut: 1).
 * @param space Espacement vertical entre les lignes (défaut: 12).
 * @param effacer Si true, vide l'écran avant d'écrire (défaut: true).
 */
inline void ecrireM(int x, int y, const uint8_t *police, const char* messages[], int nbMessages = 1, int space = 12, bool effacer = true) {
  if (effacer) {
    u8g2.clearBuffer(); 
  }
  
  u8g2.setFont(police);
  u8g2.setDrawColor(1);

  for (int i = 0; i < nbMessages; i++) {
    // On décale chaque ligne de 12 pixels vers le bas
    u8g2.drawStr(x, y + (i * space), messages[i]);
  }
  
  u8g2.sendBuffer(); 
}

void face(int moveX, int moveY) {
  u8g2.clearBuffer();

  // --- PARAMÈTRES DES YEUX EMO ---
  int largeurOeil = 36;
  int hauteurOeil = 30;
  int arrondi = 8; // Bords incurvés
  
  // OEIL GAUCHE (Positionné à 15, 10)
  u8g2.drawRFrame(15, 10, largeurOeil, hauteurOeil, arrondi);
  u8g2.drawRFrame(16, 11, largeurOeil-2, hauteurOeil-2, arrondi-1); // Double épaisseur
  
  // Pupille gauche (contrainte à l'intérieur du rectangle)
  u8g2.drawDisc(33 + moveX, 25 + moveY, 4);

  // OEIL DROIT (Positionné à 77, 10)
  u8g2.drawRFrame(77, 10, largeurOeil, hauteurOeil, arrondi);
  u8g2.drawRFrame(78, 11, largeurOeil-2, hauteurOeil-2, arrondi-1); // Double épaisseur
  
  // Pupille droite
  u8g2.drawDisc(95 + moveX, 25 + moveY, 4);

  // Pas de bouche pour le style EMO pur, ou une toute petite
  // u8g2.drawDisc(64, 50, 2); 

  u8g2.sendBuffer();
}

void afficherSourire() {
    u8g2.clearBuffer();
    // Dessine l'image en 128x64 à partir du point (0,0)
    u8g2.drawXBMP(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, oeil_sourire_bitmap);
    u8g2.sendBuffer();
}

void dessinerOeilInteractif(int targetX, int targetY) {
    u8g2.clearBuffer();
    
    // Dessin des axes (Dynamique)
    u8g2.drawHLine(0, CENTER_Y, SCREEN_WIDTH); 
    u8g2.drawVLine(CENTER_X, 0, SCREEN_HEIGHT);  

    // Dessin de l'iris
    int r = 16; 
    for (int i = -r; i <= r; i += 2) { 
        int len = sqrt(r * r - i * i); 
        u8g2.drawHLine(targetX - len, targetY + i, len * 2);
    }
    
    // Pupille
    u8g2.setDrawColor(0); 
    u8g2.drawDisc(targetX, targetY, 3); 
    u8g2.setDrawColor(1);
    
    // Point de précision central
    if(targetX == CENTER_X && targetY == CENTER_Y) {
      u8g2.drawPixel(CENTER_X, CENTER_Y); 
    }

    u8g2.sendBuffer();
}


void batterie(int niveau) {
    u8g2.clearBuffer();
    
    // --- DESSIN DU CORPS ---
    // Centré horizontalement (128 - 60) / 2 = 34
    u8g2.drawFrame(34, 15, 60, 30);      // Contour
    u8g2.drawBox(94, 22, 5, 15);          // Borne +
    
    // --- REMPLISSAGE DYNAMIQUE ---
    int barWidth = map(niveau, 0, 100, 0, 56);
    u8g2.drawBox(36, 17, barWidth, 26);
    
    // --- TEXTE ---
    char buf[10];
    sprintf(buf, "%d%%", niveau); // Correction : niveau au lieu de v
    
    // On centre le texte sous la batterie
    // FONT_GAME est imposante, on descend un peu le Y à 60 si besoin
    ecrire(45, 60, FONT_GAME, buf, false); 
    
    u8g2.sendBuffer();
}
void sommeil() {
  u8g2.clearBuffer(); 

  // --- DESSIN DES YEUX ---
  int largeurOeil = 36;
  int hauteurTrait = 6; 
  int arrondi = 3;      
  int yPos = 22; 
  u8g2.setDrawColor(1);
  u8g2.drawRBox(15, yPos, largeurOeil, hauteurTrait, arrondi);
  u8g2.drawRBox(77, yPos, largeurOeil, hauteurTrait, arrondi);

  // --- SUPERPOSITION DES Zzz AVEC ecrireM ---
  const char* zzz[] = {"z", "Z"};
  // On commence à x=115, y=10. Le 'Z' sera 6px plus bas (10 + 6 = 16)
  // On met effacer = false pour garder les yeux !
  ecrireM(115, 10, FONT_DATA, zzz, 2, 6, false); 
}
#endif