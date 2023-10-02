// Konstanta untuk keanggotaan fuzzy
const int DRY_THRESHOLD = 20;
const int WET_THRESHOLD = 40;

// Pin LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address LCD I2C dan ukuran (16x2)

void setup() {
  lcd.begin(16, 2);  // Inisialisasi LCD
  lcd.print("Soil Humidity");  // Tampilkan judul

  pinMode(A0, INPUT);  // Pin A0 sebagai input dari sensor kelembaban tanah
}

void loop() {
  int moistureValue = analogRead(A0);  // Baca nilai kelembaban tanah

  // Mengecek keanggotaan fuzzy berdasarkan tingkat kelembaban tanah
  float membershipDry = getMembershipDry(moistureValue);
  float membershipMoist = getMembershipMoist(moistureValue);
  float membershipWet = getMembershipWet(moistureValue);

  // Menampilkan hasil pada LCD
  lcd.setCursor(0, 1);  // Posisi cursor pada baris ke-2
  lcd.print("Moisture: ");

  if (moistureValue < DRY_THRESHOLD) {
    lcd.print("Dry");
  } else if (moistureValue > WET_THRESHOLD) {
    lcd.print("Wet");
  } else {
    lcd.print("Moist");
  }

  delay(1000);  // Delay 1 detik
}

// Fungsi keanggotaan untuk himpunan fuzzy
float getMembershipDry(int value) {
  if (value <= DRY_THRESHOLD) {
    return 1.0;
  } else if (value > DRY_THRESHOLD && value < WET_THRESHOLD) {
    return (WET_THRESHOLD - value) / (WET_THRESHOLD - DRY_THRESHOLD);
  } else {
    return 0.0;
  }
}

float getMembershipMoist(int value) {
  if (value > DRY_THRESHOLD && value < WET_THRESHOLD) {
    return (value - DRY_THRESHOLD) / (WET_THRESHOLD - DRY_THRESHOLD);
  } else {
    return 0.0;
  }
}

float getMembershipWet(int value) {
  if (value >= WET_THRESHOLD) {
    return 1.0;
  } else if (value > DRY_THRESHOLD && value < WET_THRESHOLD) {
    return (value - DRY_THRESHOLD) / (WET_THRESHOLD - DRY_THRESHOLD);
  } else {
    return 0.0;
  }
}
