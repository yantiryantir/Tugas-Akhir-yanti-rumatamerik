 #include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CTBot.h>


CTBot myBot;

 String ssid = "Masukan Nama Wifi";
 String pass = "Masukan Pass";
 String token = "6249397233:AAGiLt0zqTK4iOhtv-4_Hd46o5i8swxDwr8";
 const int id = 6132143257;

const int analogPin = A0; // Pin analog untuk sensor kelembapan tanah

LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat LCD I2C dan ukuran karakter (disesuaikan dengan LCD yang Anda gunakan)

int brightness = 0; // Nilai kecerahan layar LCD (0 hingga 255)

void setup() {
  
  Serial.begin(115200);
  Serial.println("Memulai Telegram Bot");
  Serial.println("Memulai...");
  Wire.begin();

  lcd.begin(16, 2);  // Menginisialisasi LCD
  lcd.clear();  // Membersihkan tampilan LCD
     
  
  myBot.wifiConnect(ssid, pass);       
  myBot.setTelegramToken(token);   

  if (myBot.testConnection())  { 
     Serial.println("\nKoneksi Ke Telegram BOT Berhasil!"); 
  }  else {
     Serial.println("\nTidak Terkoneksi Ke Telegram BOT");
 }
}

void loop() {
  int kelembapan = analogRead(analogPin); // Membaca nilai analog dari sensor
  String statusKelembapan;

  Serial.print("Kelembapan Tanah: ");
  Serial.println(kelembapan);

  lcd.setCursor(0, 0);
  lcd.print("Kelembapan Tanah:");
  lcd.setCursor(0, 1);
  lcd.print(kelembapan);

  if (kelembapan > 500) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Kering     ");
    statusKelembapan = "Tanah Kering";
  } else if (kelembapan <= 500 && kelembapan > 400) {
    lcd.setCursor(0, 1);
    lcd.print("Status: Normal     ");
    statusKelembapan = "Tanah Normal";
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Status: Lembap     ");
    statusKelembapan = "Tanah Lembap";
  }
  
 delay(1000); // Jeda 1 detik sebelum membaca lagi
 
  // Mengatur kecerahan layar LCD berdasarkan nilai kelembapan
  brightness = map(kelembapan, 0, 1023, 0, 255);
  lcd.setBacklight(brightness);

TBMessage msg;

 if (myBot.getNewMessage(msg)) {                                                         
    if (msg.text.equalsIgnoreCase("status")){                                  
          myBot.sendMessage(msg.sender.id, "Status saat ini : " + statusKelembapan);
          Serial.println("pesan terkirim");
          
  } else {  
          myBot.sendMessage(msg.sender.id, "ERROR : Perintah Tidak Dikenali");
          Serial.println("\nUser mengirim perintah yang tidak dikenal\n");
        }
 }


}
