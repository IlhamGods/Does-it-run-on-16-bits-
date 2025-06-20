# Does-it-run-on-16-bits-
Apakah ADS1115 kamu beroperasi pada 16-bit? Uji cobakan dahulu disini

# Teoritis ADS1115
Secara teori, ADS1115 dapat membaca perubahan data analog ke digital dengan resolusi 16-bit. Jika kamu memakai _differential mode_, maka jumlah kuantisasinya adalah 2^16 = 65536. Berbeda dengan _single ended mode_, jumlah kuantisasi adalah 32767. 

Pada pembahasan ini menggunakan _single ended mode_ karena mode tersebut umum dipakai. Dengan memakai mode tegangan referensi 5V, maka tepat untuk menggunakan GAIN_TWOTHIRDS : ±6,144V. Resolusi 6,144V/32,767 = 0,1875 mV. Artinya, ADS1115 dapat membaca perubahan tegangan sekecil 0,1875 mV. 

Untuk membuktikan hal tersebut, gunakan kode program uji dengan voltage reference. 

# Uji Step Response dengan Potentiometer presisi
    Setup Hardware:
    1. Gunakan potensiometer multiturn presisi (10-turn, 10kΩ)
    2. Supply dengan voltage reference stabil (misal LM4040-5.0 atau battery)
    3. Hubungkan wiper potensiometer ke AIN0 ADS1115

Yang harus diperhatikan:
  1. Apakah ADC berubah 1 step saat tegangan berubah minimal?
  2. Apakah bisa mendeteksi perubahan sub-milivolt?

# Uji dengan Voltage Divider Presisi
    Setup hardware:
    1. Gunakan resistor presisi 0.1% untuk pembagi tegangan
    2. Buat beberapa titik tegangan berbeda (misal 1V, 2V, 3V, 4V)
    3. Ukur dengan multimeter 6.5 digit sebagai referensi

# Kriteria Membuktikan Resolusi 16-bit 
 A. ADS1115 benar-benar 16-bit jika:
    1. Step size konsisten ~0.1875mV (dengan GAIN_TWOTHIRDS)
    2. ENOB minimal 14-15 bit (karena noise selalu ada)
    3. Linearitas bagus di seluruh range
    4. Noise RMS < 1-2 LSB (< 0.375mV)
    5. Dapat membedakan perubahan sub-millivolt

Tanda-tanda resolusi tidak mencapai 16-bit:
    1. Noise tinggi (>5-10 LSB)
    2. Missing codes (ada nilai ADC yang tidak pernah muncul)
    3. Non-linearitas signifikan
