#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include "Config.h"
#include "batterie.h"
#include "recalibration.h" 
#include "display.h"     

// Variables persistantes pour la machine à états du tactile
static unsigned long lastTapTime = 0;
static bool waitingForSecondTap = false;
const int doubleTapDelay = 350; // Fenêtre de temps pour la 2ème tape (ms)

void tactile() {
    bool tactileState = digitalRead(PIN_TACTILE_1); 
    unsigned long currentTime = millis();

    if (tactileState == HIGH) {
        unsigned long pressStartTime = millis();
        
        // --- LOGIQUE D'APPUI PROLONGÉ (3 SECONDES) ---
        while(digitalRead(PIN_TACTILE_1) == HIGH) {
            if (millis() - pressStartTime > 3000) { 
                int v = lireNiveauBatterie(); // On vérifie le niveau réel

                if (currentFPS <= SLEEP_FPS) {
                    if (v >= 15) {
                        // --- CAS 1 : RÉVEIL AUTORISÉ ---
                        u8g2.clearBuffer();
                        ecrire(30, 35, FONT_INFO, "REVEIL...");
                        bip(2, 1, 0.05);
                        currentFPS = ECO_FPS; // On repasse en mode actif
                    } else {
                        // --- CAS 2 : ÉNERGIE INSUFFISANTE ---

                        ecrire(40, 35, FONT_PIXEL, "JE DORS...");
                        bip(1, 1, 0.2); // Un bip long et grave pour dire "non"
                        delay(2000);   // On laisse le message 2s
                        // La loop suivante repassera automatiquement à l'animation sommeil()
delay(10);                    
}
                }
                return; // On sort pour ne pas déclencher de tape simple ou double
            }
        }

        // --- LOGIQUE DE TAPE CLASSIQUE (Seulement si Pixy ne dort pas) ---
        if (currentFPS > SLEEP_FPS) {
            if (currentTime - lastTapTime < 50) return; 

            if (waitingForSecondTap && (currentTime - lastTapTime < doubleTapDelay)) {
                int v = lireNiveauBatterie();
                batterie(v); 
                delay(2000); 
                waitingForSecondTap = false;
            } else {
                waitingForSecondTap = true;
            }
            lastTapTime = currentTime;
        }
    }

    // Validation de la tape simple (Calibration) - seulement en mode actif
    if (currentFPS > SLEEP_FPS && waitingForSecondTap && (millis() - lastTapTime > doubleTapDelay)) {
        attendreStabilite();
        autorecalibration(); 
        waitingForSecondTap = false;
    }
}
#endif