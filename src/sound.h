// src/sound.h

#ifndef SOUND_H
#define SOUND_H

#include <Arduino.h>
#include "../Config.h"

/**
 * @brief Émet un signal sonore avec Pixy
 * @param nombre : Nombre de répétitions
 * @param intensite : 1 (bas/haché), 2 (fort/continu)
 * @param duree_s : Durée du son en secondes (ex: 0.1 pour 100ms)
 * @param repos_s : Temps de silence entre les bips en secondes (par défaut 0.5)
 */
inline void bip(int nombre, int intensite, float duree_s, float repos_s = 0.5) {
  int duree_ms = (int)(duree_s * 1000);
  int repos_ms = (int)(repos_s * 1000);

  for (int i = 0; i < nombre; i++) {
    if (intensite == 2) {
      // SON FORT
      digitalWrite(BUZZER_PIN, HIGH);
      delay(duree_ms);
      digitalWrite(BUZZER_PIN, LOW);
    } 
    else if (intensite == 1) {
      // SON BAS (Hachage manuel pour diminuer le volume perçu)
      unsigned long start = millis();
      while (millis() - start < (unsigned long)duree_ms) {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(400); 
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(600); // On laisse plus de temps à LOW pour baisser le volume
      }
    }

    // Silence entre deux bips
    if (i < nombre - 1) {
      delay(repos_ms);
    }
  }
}

#endif