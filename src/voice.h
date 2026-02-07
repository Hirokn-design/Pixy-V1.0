#ifndef VOICE_H
#define VOICE_H

#include <Arduino.h>
#include "Config.h"

// Codes hypothétiques (à vérifier lors de tes tests)
#define CODE_WAKE_UP 0x01  // Le code envoyé quand tu dis "Pixy"

extern int pixyState;
bool isPixyAwake = false; // Le Guard
unsigned long lastWakeTime = 0;
const unsigned long WAKE_TIMEOUT = 5000; // Pixy écoute pendant 5 secondes

void initVoice() {
    Serial1.begin(VOICE_BAUD, SERIAL_8N1, VOICE_RX_PIN, VOICE_TX_PIN);
    Serial.println(">>> Pixy : Système auditif avec Guard activé.");
}

void updateVoice() {
    if (Serial1.available()) {
        byte incomingByte = Serial1.read();
        
        // --- ÉTAPE 1 : Le Réveil ---
        if (incomingByte == CODE_WAKE_UP) {
            isPixyAwake = true;
            lastWakeTime = millis();
            pixyState = VOICE_HEARD;
            Serial.println("OUI ? (Pixy est réveillé)");
            return; // On attend la commande suivante
        }

        // --- ÉTAPE 2 : Le Guard ---
        if (isPixyAwake) {
            // On vérifie si on n'a pas dépassé le temps d'écoute (5s)
            if (millis() - lastWakeTime < WAKE_TIMEOUT) {
                Serial.print("Commande reçue après 'Pixy' : 0x");
                Serial.println(incomingByte, HEX);
                
                // Ici tu placeras tes actions (Avance, Danse, etc.)
                
                // Une fois la commande exécutée, on peut rendormir le guard
                isPixyAwake = false; 
            } else {
                isPixyAwake = false;
                Serial.println("Trop tard, Pixy s'est rendormi.");
            }
        } else {
            Serial.println("Commande ignorée : vous devez dire 'Pixy' d'abord.");
        }
        
        pixyState = VOICE_IDLE;
    }
}

#endif