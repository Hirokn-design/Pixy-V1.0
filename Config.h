// Config.h

#ifndef CONFIG_H
#define CONFIG_H

// ==========================================
// 1. CONFIGURATION MATÉRIELLE (PINS)
// ==========================================

// Buzzer actif
#define BUZZER_PIN 21       

// BUS I2C UNIQUE (Stable sur ESP32-S3)
#define I2C_SDA    17        
#define I2C_SCL    18   

// Tous les composants partagent les mêmes pins
#define OLED_SDA   I2C_SDA
#define OLED_SCL   I2C_SCL
#define MPU_SDA    I2C_SDA
#define MPU_SCL    I2C_SCL

// ==========================================================
// 2. RÉGLAGES PAR DÉFAUT DE L'EQILIBRE (MPU6050 VERTICAL)
// ==========================================================
// Ces offsets serviront à remettre Pixy à "zéro" quand il est droit (avec recalibration.h)
#define DEFAULT_OFF_X 0
#define DEFAULT_OFF_Y 0
#define DEFAULT_OFF_Z 9.81

// On déclare ces variables pour qu'elles soient accessibles partout
extern float offX; 
extern float offY; 
extern float offZ;


// =====================================================
// 3. CONFIGURATION DU CAPTEUR TACTILE (TTP223/TTP223B)
// =====================================================

#define PIN_TACTILE_1 4      // Pin SIG du TTP223B branché sur GPIO 4
// Note : Pas de TOUCH_THRESHOLD ici car c'est un signal numérique (HIGH/LOW)


// ==========================================
// 4. CONFIGURATION DE LA BATTERIE
// ==========================================
#define BATT_ADC_PIN 1

// ==========================================
// 5. PARAMÈTRES DE L'AFFICHAGE
// ==========================================
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define CENTER_X      64
#define CENTER_Y      32

// ===============================================
// 6. GESTION DE L'ÉNERGIE (FPS et I2C)
// ===============================================

#define PERF_FPS  30  // Mode Démo / Interaction fluide
#define ECO_FPS   15  // Mode Standard (démarrage)
#define LOW_FPS   7   // Mode Survie / Recherche de station
#define SLEEP_FPS 1   // Mode veille (1 image par seconde suffit largement)

#define BATT_LIMIT_PERF    30 // Batterie à 30%
#define BATT_LIMIT_LOW     15 // Batterie à 15%
#define BATT_LIMIT_CRITICAL 7 // Batterie à 7%

extern int currentFPS;

// --- I2C BUS SPEEDS ---
#define I2C_SPEED_LOW      50000   // 50kHz  (Mode Survie/Batterie < 5%)
#define I2C_SPEED_STABLE   100000  // 100kHz (Standard/Sécurité)
#define I2C_SPEED_FAST     400000  // 400kHz (Performance/Animation fluide)

// ==============================================
// 7. BIBLIOTHÈQUE DE POLICES (16MB FLASH POWER)
// ==============================================

#define FONT_TECH    u8g2_font_6x10_tf          // Debug technique précis
#define FONT_GAME    u8g2_font_pressstart2p_8f // Style rétro SonicDraft
#define FONT_COUNT   u8g2_font_fub20_tn         // Gros chiffres décompte
#define FONT_INFO    u8g2_font_7x13_mf          // Messages status
#define FONT_DATA    u8g2_font_4x6_tf           // Ultra-mini pour logs réseau
#define FONT_LOGO    u8g2_font_logisoso26_tf    // Police énorme et élégante pour "PIXY"
#define FONT_SYMB    u8g2_font_unifont_t_symbols // Icônes (Batterie, WiFi, etc.)
#define FONT_PIXEL  u8g2_font_haxrcorp4089_tr   // Message de retour haptique

// ===============================================
// 8. RECONNAISSANCE VOCALE
// ===============================================

// --- Configuration du Module Vocal (SU-O3T) ---
#define VOICE_RX_PIN 15  // Connecté au TX du module vocal
#define VOICE_TX_PIN 16  // Connecté au RX du module vocal
#define VOICE_BAUD 115200  // Vitesse standard du SU-O3T

// --- États de la reconnaissance ---
#define VOICE_IDLE 0     // Pixy attend le mot de réveil
#define VOICE_HEARD 1    // Pixy a reconnu une commande


#endif