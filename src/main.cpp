#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Adafruit_NeoPixel.h>

// Helper untuk Firebase
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

// --- Konfigurasi Hardware ---
#define BUTTON_PIN D1
#define LED_PIN    D0
#define NUM_LEDS   8
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Konfigurasi WiFi & Firebase ---
#define WIFI_SSID "NAMA_WIFI"
#define WIFI_PASSWORD "PASSWORD_WIFI"
#define API_KEY "FIREBASE_API_KEY"
#define DATABASE_URL "URL_DATABASE.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variabel untuk manajemen tombol
unsigned long buttonTimer = 0;
bool buttonActive = false;

// --- Fungsi Deep Sleep (OFF) ---
void enterDeepSleep() {
    Serial.println("System Powering Off (Deep Sleep)...");
    pixels.fill(pixels.Color(0, 0, 0)); // Matikan LED
    pixels.show();
    
    // Bangunkan ESP32-C3 jika D1 ditekan (LOW)
    esp_deep_sleep_enable_gpio_wakeup(1ULL << BUTTON_PIN, ESP_GPIO_WAKEUP_GPIO_LOW);
    
    delay(1000);
    esp_deep_sleep_start();
}

// --- Callback Firebase (IoT Capture Logic) ---
void streamCallback(FirebaseStream data) {
    // App mengirim angka 1-4 untuk ganti warna saat capture
    int state = data.intData();
    Serial.printf("IoT Command Received: State %d\n", state);

    switch (state) {
        case 1: pixels.fill(pixels.Color(255, 255, 255)); break; // White
        case 2: pixels.fill(pixels.Color(255, 0, 0));   break; // Red
        case 3: pixels.fill(pixels.Color(0, 255, 0));   break; // Green
        case 4: pixels.fill(pixels.Color(0, 0, 255));   break; // Blue
        default: pixels.fill(pixels.Color(3, 126, 243)); break; // Standby Blue
    }
    pixels.show();
}

void streamTimeoutCallback(bool timeout) {
    if (timeout) Serial.println("Firebase Stream timeout...");
}

void setup() {
    Serial.begin(115200);
    pixels.begin();
    pixels.setBrightness(50); // Set kecerahan agar tidak overheat
    
    // Cek apakah baru saja bangun dari tidur
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO) {
        Serial.println("Woke up from Deep Sleep!");
    }

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Koneksi WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");

    // Inisialisasi Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    // Setup Path Stream: /devices/[MAC_ADDRESS]/led_state
    String path = "/devices/";
    path.concat(WiFi.macAddress());
    path.concat("/led_state");
    if (!Firebase.RTDB.beginStream(&fbdo, path)) {
        Serial.print("Stream Error: ");
        Serial.println(fbdo.errorReason());
    }
    Firebase.RTDB.setStreamCallback(&fbdo, streamCallback, streamTimeoutCallback);

    // Indikator menyala: AIRPLAS Blue
    pixels.fill(pixels.Color(3, 126, 243));
    pixels.show();
}

void loop() {
    // Logika Tombol ON/OFF (Tahan 2 detik untuk masuk Deep Sleep)
    if (digitalRead(BUTTON_PIN) == LOW) {
        if (!buttonActive) {
            buttonActive = true;
            buttonTimer = millis();
        }
        
        // Indikator visual saat menahan tombol (opsional)
        if (millis() - buttonTimer > 2000) {
            enterDeepSleep();
        }
    } else {
        buttonActive = false;
    }

    // Firebase Stream berjalan secara asinkron di background.
    // Loop ini tetap kosong untuk menjaga responsivitas CPU.
}