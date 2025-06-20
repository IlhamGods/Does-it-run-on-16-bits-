#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  
  Serial.println("=== UJI LINEARITAS ===");
  Serial.println("Ukur berbagai tegangan referensi");
  Serial.println("Expected(V)\tMeasured(V)\tADC\tError(mV)");
}

void loop() {
  // Input tegangan referensi dari user via Serial
  if(Serial.available()) {
    float expectedVoltage = Serial.parseFloat();
    
    // Rata-rata 100 sample
    long sum = 0;
    for(int i = 0; i < 100; i++) {
      sum += ads.readADC_SingleEnded(0);
      delay(1);
    }
    
    float avgADC = sum / 100.0;
    float measuredVoltage = (avgADC * 6.144) / 32767.0;
    float error = (measuredVoltage - expectedVoltage) * 1000.0; // dalam mV
    
    Serial.print(expectedVoltage, 4);
    Serial.print("\t\t");
    Serial.print(measuredVoltage, 6);
    Serial.print("\t");
    Serial.print((int)avgADC);
    Serial.print("\t");
    Serial.println(error, 3);
  }
}