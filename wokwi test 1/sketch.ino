
#include <WiFi.h>
#include <WiFiClient.h>

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 5
#define DHTTYPE DHT22
#define lampu 13 // Pin relay terhubung ke pin 13 pada ESP32
#define kipas 12   // Pin kipas terhubung ke pin 12 pada ESP32


DHT dht(DHTPIN, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C LCD dapat bervariasi, gunakan alamat yang benar

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  dht.begin();
 
  pinMode(lampu, OUTPUT);
  pinMode(kipas, OUTPUT); 
}

void loop() {

  float kelembapan = dht.readHumidity();
  float suhu = dht.readTemperature();

  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(suhu) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Humi: " + String(kelembapan) + " %");

  //kontrol lampu berdasarkan suhu
    if (suhu <= 35) {digitalWrite(lampu, HIGH); // Aktifkan lampu 
    lcd.print(" LAMPU NYALA");//tampilkan pesan di LCD
    Serial.println("LAMPU SEDANG NYALA");  // Menampilkan pesan di Serial Monitor
    //Blynk.virtualWrite(V0, "Lampu : ON"); // Kirim status ke Blynk
    } 
    else if (suhu >= 40) {digitalWrite(lampu, LOW); // Matikan lampu 
    lcd.print(" LAMPU MATI");
    Serial.println("LAMPU SEDANG MATI");  // Menampilkan pesan di Serial Monitor
    //Blynk.virtualWrite(V0, "Lampu : OFF"); // Kirim status ke Blynk
    }

  // Kontrol kipas berdasarkan kelembapan
    if (kelembapan <= 55) { digitalWrite(kipas, HIGH); // Aktifkan kipas
    lcd.print(" KIPAS NYALA");//tampilkan pesan di LCD
    Serial.println("KIPAS SEDANG NYALA");  // Menampilkan pesan di Serial Monitor
    //Blynk.virtualWrite(V1, "Kipas: ON"); // Kirim status ke Blynk
    } 
    else if (kelembapan >= 65) {digitalWrite(kipas, LOW); // Matikan kipas
    lcd.print(" KIPAS MATI");//tampilkan pesan di LCD
    Serial.println("KIPAS SEDANG MATI");  // Menampilkan pesan di Serial Monitor
   // Blynk.virtualWrite(V1, "Kipas: OFF"); // Kirim status ke Blynk
    }
  lcd.scrollDisplayLeft();//tulisan berjalan  
  delay(100);//jeda 
}