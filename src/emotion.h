#ifndef EMOTION_H
#define EMOTION_H

#include <Arduino.h>
#include "display.h"
#include "sound.h"

// --- 1. DÉFINITION DES ENUMS (Optimisés en taille) ---
enum Emotion : uint8_t {
    NEUTRE, SOURIANT, CHOC, ETOURDI, FACHE, SOMMEIL, JOIE,
    SURPRIS, ENNUI, TRISTESSE, CURIEUX, PEUR, SUSPICIEUX,
    FATIGUE, EPUISE, EXASPERE
};

enum contextualEmotion : uint8_t {
    C_NORMAL, INSTABLE, MALADE, NOEL, ANNIVERSAIRE,
    PACQUES, HALLOWEEN, AN, SAINT_VALENTIN
};

enum userEmotion : uint8_t {
    U_NEUTRE, U_SOURIANT, U_CHOC, U_ETOURDI, U_FACHE,
    U_SOMMEIL, U_JOIE, U_SURPRIS, U_ENNUI, U_TRISTESSE,
    U_CURIEUX, U_PEUR, U_SUSPICIEUX, U_FATIGUE, U_EPUISE, U_EXASPERE
};

// --- 2. VARIABLES GLOBALES (extern) ---
extern Emotion emotionActuelle;
extern contextualEmotion contexteActuel;
extern userEmotion utilisateurEmotionActuelle;
extern bool estEtourdi;
extern int currentFPS;

// --- 3. FONCTIONS GRAPHIQUES (avec inline pour éviter les erreurs de lien) ---

inline void dessinerYeuxSpirale(int xOffset, int yOffset, float phase) {
    const int nbPoints = 30; // Réduit de 40 à 30 : gain de calcul sans perte visuelle
    const float rayonMax = 12.0;
    int centresX[] = {33 + xOffset, 95 + xOffset};
    int centreY = 25 + yOffset;

    u8g2.setDrawColor(1);
    for (int oeil = 0; oeil < 2; oeil++) {
        int cx = centresX[oeil];
        float lastX = cx, lastY = centreY;

        for (int i = 0; i < nbPoints; i++) {
            float angle = (i * 0.5f) + phase;
            float r = (i / (float)nbPoints) * rayonMax;
            int px = cx + (int)(r * cos(angle));
            int py = centreY + (int)(r * sin(angle));

            if (i > 0) {
                u8g2.drawLine(lastX, lastY, px, py);
            }
            lastX = px; lastY = py;
        }
    }
}

inline void etourdi() {
    static float phaseAnim = 0;
    static unsigned long debutAnim = 0;
    
    if (debutAnim == 0) {
        debutAnim = millis();
        bip(3, 1, 0.05, 0.02);
    }

    u8g2.clearBuffer();
    phaseAnim -= 0.3f;
    dessinerYeuxSpirale(random(-1, 2), random(-1, 2), phaseAnim);
    u8g2.sendBuffer();

    if (millis() - debutAnim > 3000) {
        estEtourdi = false;
        emotionActuelle = NEUTRE;
        debutAnim = 0;
        bip(1, 2, 0.1);
    }
}

inline void Colere(int moveX, int moveY) {
    u8g2.clearBuffer();
    face(moveX, moveY);
    u8g2.drawLine(10, 5, 50, 20); // Sourcil G
    u8g2.drawLine(78, 20, 118, 5); // Sourcil D
    u8g2.sendBuffer();
}

// --- 4. MOTEUR ÉMOTIONNEL PRINCIPAL ---

inline void emotionMotor(int mx, int my) {
    switch (emotionActuelle) {
        case CHOC:
            u8g2.clearBuffer();
            u8g2.drawBox(25, 28, 25, 6); u8g2.drawBox(78, 28, 25, 6);
            u8g2.sendBuffer();
            if (millis() % 400 < 40) bip(1, 1, 0.01);
            break;

        case ETOURDI:
            etourdi();
            break;

        case FACHE:
            Colere(mx, my);
            break;

        case SOMMEIL:
            sommeil();
            break;

        case JOIE:
        case SOURIANT:
            u8g2.clearBuffer();
            face(mx, my);
            u8g2.drawRFrame(45, 45, 38, 10, 5); 
            u8g2.sendBuffer();
            break;

        case SURPRIS:
            u8g2.clearBuffer();
            u8g2.drawCircle(33 + mx, 25 + my, 15);
            u8g2.drawCircle(95 + mx, 25 + my, 15);
            u8g2.sendBuffer();
            break;

        default:
            face(mx, my);
            break;
    }
}

#endif