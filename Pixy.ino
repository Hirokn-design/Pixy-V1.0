#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <U8g2lib.h>

#include "Config.h"
#include "src/display.h"  
#include "src/batterie.h"
#include "src/system.h" 
#include "src/touch.h"   
#include "src/sound.h"        
#include "src/recalibration.h" 
#include "src/interaction.h"
#include "src/emotion.h"

// --- VARIABLES GLOBALES (EXTERN) ---
float lastX = 0, lastY = 0, lastZ = 0;
float offX = DEFAULT_OFF_X;
float offY = DEFAULT_OFF_Y;
float offZ = DEFAULT_OFF_Z;
int currentX, currentY, currentZ;
int currentFPS = 30;

// --- LOGIQUE ÉMOTIONNELLE ---
Emotion emotionActuelle = NEUTRE;
contextualEmotion contexteActuel = C_NORMAL;
userEmotion utilisateurEmotionActuelle = U_NEUTRE;
bool estEtourdi = false;       // État "Spirales"
bool enAttenteDeCalme = false; // État "KO / Douleur"
unsigned long dernierMouvementSignificatif = 0;

// --- INSTANTIATION DES OBJETS ---
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // 0. Initialisation I2C forcée sur tes pins 17/18
  Wire.begin(17, 18); 
  Wire.setClock(I2C_SPEED_STABLE); 

  // Initialisation de l'écran en premier pour pouvoir afficher les erreurs
  if (!u8g2.begin()) {
     Serial.println("Erreur Écran !");
  }

   // 1. Initialisation buzzer
  pinMode(BUZZER_PIN, OUTPUT); // <--- INDISPENSABLE
  digitalWrite(BUZZER_PIN, LOW);

  // 2. Initialisation Tactile (TTP223B)
  pinMode(PIN_TACTILE_1, INPUT); 

  // 3. Initialisation OLED 
  if (u8g2.begin()) {
    // Utilisation de ecrireM pour un démarrage "Pro"
    const char* bootMsg[] = {"PIXY v1.0", "IAB OS"};
    ecrireM(10, 20, FONT_TECH, bootMsg, 3, 12);
    delay(1500);
  }

  // --- INITIALISATION MPU6050 ---
  bool mpuOk = false;
  for (int i = 0; i < 5; i++) {
    if (mpu.begin(0x68, &Wire, false)) { 
      mpuOk = true;
      break;
    }
    const char* retryMsg[] = {"MPU6050 introuvable", "Nouvelle tentative..."};
    ecrireM(10, 30, FONT_TECH, retryMsg, 2, 10);
    delay(500); 
  }

  if (!mpuOk) {
    const char* compatMsg[] = {"MPU: MODE CLONE", "Donnees: OK", "Systeme: PRET"};
    ecrireM(10, 25, FONT_INFO, compatMsg, 3, 15);
    delay(1000); 
} else {
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    bip(1, 1, 0.01); 
  }
} 



void loop() {
  unsigned long debutBoucle = millis();

  refresh(); // Gère les FPS et la batterie
  tactile(); // Gère les caresses sur la tête

  sensors_event_t a, g, temp;
  if (mpu.getEvent(&a, &g, &temp)) {
    
    // 1. CALCUL DU REGARD (Indépendant de l'émotion pour le suivi)
    int moveX = constrain((int)((a.acceleration.y - offX) * 4), -10, 10);
    int moveY = constrain((int)((a.acceleration.z - offY) * -4), -8, 8);

    // 2. LOGIQUE DE DÉTECTION VIA INTERACTION.H
    // detecterSecousse() utilise déjà la magnitude bivariable sqrt(x²+y²)
    if (detecterSecousse() && currentFPS > SLEEP_FPS) {
      if (emotionActuelle != CHOC) {
          emotionActuelle = CHOC;
          enAttenteDeCalme = true;
          estEtourdi = false;
          dernierMouvementSignificatif = millis();
          bip(1, 1, 0.02); // Petit cri de surprise
      }
    }

    // 3. GESTION DU CALME (Anti-triche main)
    if (!estAuRepos()) {
      dernierMouvementSignificatif = millis();
    }

    // 4. TRANSITION VERS LE VERTIGE
    if (enAttenteDeCalme && (millis() - dernierMouvementSignificatif > 2500)) {
      emotionActuelle = ETOURDI;
      estEtourdi = true;
      enAttenteDeCalme = false;
    }

    // 5. GESTION DU SOMMEIL
    if (currentFPS == SLEEP_FPS) {
        emotionActuelle = SOMMEIL;
    } else if (emotionActuelle == SOMMEIL && currentFPS > SLEEP_FPS) {
        emotionActuelle = NEUTRE;
    }

    // 6. MOTEUR ÉMOTIONNEL (Rendu final)
    emotionMotor(moveX, moveY);
  }

  // 7. GESTION DES FPS
  int tempsCible = 1000 / currentFPS; 
  int tempsEcoule = millis() - debutBoucle;
  int delaiAttente = tempsCible - tempsEcoule;
  if (delaiAttente > 0) delay(delaiAttente);
}