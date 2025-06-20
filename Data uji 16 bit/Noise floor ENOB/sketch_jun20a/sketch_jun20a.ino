#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  
  Serial.println("=== UJI NOISE & ENOB ===");
  Serial.println("Hubungkan input ke GND atau tegangan stabil");
}

void loop() {
  int samples = 1000;
  long sum = 0;
  long sumSquares = 0;
  int16_t minVal = 32767;
  int16_t maxVal = -32768;
  
  // Ambil banyak sample
  for(int i = 0; i < samples; i++) {
    int16_t val = ads.readADC_SingleEnded(0);
    sum += val;
    sumSquares += (long)val * val;
    
    if(val < minVal) minVal = val;
    if(val > maxVal) maxVal = val;
    delay(1);
  }
  
  float mean = sum / (float)samples;
  float variance = (sumSquares / (float)samples) - (mean * mean);
  float stdDev = sqrt(variance);
  float peakToPeak = maxVal - minVal;
  
  // Hitung ENOB (simplified)
  float rms_noise_voltage = (stdDev * 6.144) / 32767.0;
  float enob = log2(6.144 / (rms_noise_voltage * sqrt(12)));
  
  Serial.println("--- HASIL STATISTIK ---");
  Serial.print("Mean ADC: "); Serial.println(mean, 2);
  Serial.print("Std Dev: "); Serial.println(stdDev, 2);
  Serial.print("Min-Max: "); Serial.print(minVal); Serial.print(" to "); Serial.println(maxVal);
  Serial.print("Peak-to-Peak: "); Serial.println(peakToPeak);
  Serial.print("RMS Noise: "); Serial.print(rms_noise_voltage * 1000, 3); Serial.println(" mV");
  Serial.print("Estimated ENOB: "); Serial.println(enob, 1);
  Serial.println("========================");
  
  delay(5000);
}