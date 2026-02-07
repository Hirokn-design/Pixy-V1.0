#ifndef SYSTEM_H
#define SYSTEM_H

#include "Config.h"
#include "batterie.h"

void refresh() {
    int niveau = lireNiveauBatterie();

    // LOGIQUE DESCENDANTE STRICTE
    if (niveau <= BATT_LIMIT_CRITICAL) {
        currentFPS = SLEEP_FPS; // Bloqué à 1 FPS
    } 
    else if (niveau <= BATT_LIMIT_LOW) {
        currentFPS = LOW_FPS;   // Bloqué à 7 FPS
    } 
    else if (niveau <= BATT_LIMIT_PERF) {
        // Limitation à 15 FPS si on demande trop
        if (currentFPS > ECO_FPS) {
            currentFPS = ECO_FPS; 
        }
    }
    // Note : Si niveau > 30, currentFPS garde sa valeur 
    // (soit ECO par défaut, soit PERF via une commande vocale)
}

void afficherStatutSysteme() {
    char fBuf[15], bBuf[15], mBuf[20];
    sprintf(fBuf, "FPS : %d", currentFPS);
    sprintf(bBuf, "BATT: %d%%", lireNiveauBatterie());
    
    // Déterminer le mode selon le FPS
    const char* mode = (currentFPS == SLEEP_FPS) ? "MODE: CRITIQUE" : 
                       (currentFPS == LOW_FPS)   ? "MODE: ECO" : "MODE: NORMAL";

    const char* systemData[] = {"--- SYSTEM ---", fBuf, bBuf, mode};
    
    // On utilise ecrireM pour tout afficher proprement
    // Saut de 10px car on veut que les 4 lignes rentrent sur 64px
    ecrireM(0, 12, FONT_TECH, systemData, 4, 12);
}

void debugBatterie() {
    float vRaw = (analogRead(BATT_ADC_PIN) * 3.3 / 4095.0) * 2.0;
    int pourcent = lireNiveauBatterie();

    char pBuf[15], vBuf[15];
    sprintf(pBuf, "Niveau: %d%%", pourcent);
    sprintf(vBuf, "Tension: %.2fV", vRaw);

    const char* debugBatt[] = {"ETAT BATTERIE", pBuf, vBuf};

    // On utilise ecrireM pour afficher ces infos techniques
    ecrireM(10, 15, FONT_TECH, debugBatt, 3, 12);
}

#endif