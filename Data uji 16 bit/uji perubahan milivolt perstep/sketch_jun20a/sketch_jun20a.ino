#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!ads.begin()) {
    Serial.println("ADS1115 tidak terdeteksi!");
    while(1);
  }
  
  ads.setGain(GAIN_TWOTHIRDS); // ±6.144V
  Serial.println("=== TEST RESOLUSI ADS1115 ===");
  Serial.println("Range: ±6.144V, Resolusi teoritis: 0.1875mV");
  Serial.println("ADC_Value\tVoltage(V)\tVoltage(mV)");
}

void loop() {
  // Ambil multiple reading untuk melihat noise
  long sum = 0;
  int samples = 100;
  
  for(int i = 0; i < samples; i++) {
    sum += ads.readADC_SingleEnded(0);
    delay(1);
  }
  
  float avgADC = sum / (float)samples;
  float voltage = (avgADC * 6.144) / 32767.0;
  float voltageMillis = voltage * 1000.0;
  
  Serial.print(avgADC, 1);
  Serial.print("\t\t");
  Serial.print(voltage, 6);
  Serial.print("\t\t");
  Serial.println(voltageMillis, 3);
  
  delay(500);
}