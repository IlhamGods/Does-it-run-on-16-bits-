#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;
int16_t lastADC = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  
  Serial.println("=== UJI STEP RESPONSE ===");
  Serial.println("Putar potensiometer PERLAHAN dan lihat perubahan ADC");
  Serial.println("ADC_Value\tChange\tVoltage(mV)");
}

void loop() {
  int16_t currentADC = ads.readADC_SingleEnded(0);
  int16_t change = currentADC - lastADC;
  float voltage = (currentADC * 6.144 * 1000.0) / 32767.0;
  
  if (abs(change) > 0) { // Hanya tampilkan jika ada perubahan
    Serial.print(currentADC);
    Serial.print("\t\t");
    Serial.print(change);
    Serial.print("\t");
    Serial.println(voltage, 3);
  }
  
  lastADC = currentADC;
  delay(50);
}