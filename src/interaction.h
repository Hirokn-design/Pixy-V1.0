#ifndef INTERACTION_H
#define INTERACTION_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include "emotion.h"

// Paramètres de sensibilité
const float SEUIL_SECOUSSE = 9.0;    // Seuil bivariable (X, Y)
const float POND_Z = 0.2;           // On réduit l'impact du Z (chocs verticaux)
const int CONFIRMATION_FRAMES = 2;  // Nb de frames consécutives pour valider

extern Adafruit_MPU6050 mpu;
extern float lastX, lastY, lastZ;

/**
 * Analyse les vecteurs d'accélération pour détecter une secousse
 * Utilise une magnitude bivariable pondérée : sqrt(dx² + dy² + (k*dz²))
 */
bool detecterSecousse() {
    sensors_event_t a, g, temp;
    if (!mpu.getEvent(&a, &g, &temp)) return false;

    // Calcul du Jerk (différentiel d'accélération)
    float dx = a.acceleration.x - lastZ; 
    float dy = a.acceleration.y - lastX;
    float dz = a.acceleration.z - lastY;

    // Mise à jour des registres pour le prochain cycle
    lastX = a.acceleration.y; 
    lastY = a.acceleration.z; 
    lastZ = a.acceleration.x;

    // MAGNITUDE BIVARIABLE : On privilégie X et Y
    // Mathématiquement : Norme du vecteur de Jerk projeté
    float magnitudeJerk = sqrt((dx * dx) + (dy * dy) + (POND_Z * dz * dz));

    // Système de confirmation statistique pour filtrer le bruit
    static int compteurConfirmation = 0;
    if (magnitudeJerk > SEUIL_SECOUSSE) {
        compteurConfirmation++;
    } else {
        compteurConfirmation = 0;
    }

    return (compteurConfirmation >= CONFIRMATION_FRAMES);
}

/**
 * Détecte si Pixy est "au repos" dans la main ou sur une table
 */
bool estAuRepos() {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    float dx = a.acceleration.x - lastZ;
    float dy = a.acceleration.y - lastX;
    float dz = a.acceleration.z - lastY;
    
    float stabilite = sqrt((dx * dx) + (dy * dy) + (dz * dz));
    return (stabilite < 1.2); // Seuil de micro-mouvements
}

#endif