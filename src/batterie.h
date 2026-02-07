#ifndef BATTERIE_H
#define BATTERIE_H

#include <Arduino.h>
#include "Config.h"

int lireNiveauBatterie() {
    /* // Lissage : on fait la moyenne de 10 lectures
    long sum = 0;
    for(int i=0; i<20; i++) { // Augmenté à 20 pour plus de stabilité
        sum += analogRead(BATT_ADC_PIN);
    }
    int raw = sum / 20;
    
    // 3.3 * 2 = 6.6V max théorique. ADC 12 bits = 4095
    float tension = (raw * 6.6) / 4095.0;

    // Mapping plus sécurisé : 3.5V (0%) à 4.15V (100%) 
    // On prend 4.15V au lieu de 4.2V car les chargeurs TP4056 s'arrêtent souvent un peu avant.
    int pourcentage = map(tension * 100, 350, 415, 0, 100);
    
    return constrain(pourcentage, 0, 100); */

    return 80; // test
}

#endif