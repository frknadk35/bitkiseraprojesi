#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define toprakNemPin A1 // Toprak nem sensörü için su seviyesi pinini kullanıyoruz
#define suSeviyePin A0 // Su seviyesi sensörü için toprak nem pinini kullanıyoruz
#define ledPin 6 // LED'i kontrol etmek için kullanacağımız pin
#define buzzerPin 9 // Buzzer'ı kontrol etmek için kullanacağımız pin

void setup() {
  lcd.begin(16, 2);
  lcd.print("Toprak Nem: ");
  lcd.setCursor(0, 1);
  lcd.print("Su Seviyesi:");
  
  pinMode(ledPin, OUTPUT); // LED pinini çıkış olarak ayarla
  pinMode(buzzerPin, OUTPUT); // Buzzer pinini çıkış olarak ayarla
}

void loop() {
  // Toprak nem sensöründen okunan değeri al
  int toprakNem = analogRead(toprakNemPin);
  // Su seviye sensöründen okunan değeri al
  int suSeviyesi = analogRead(suSeviyePin);

  // Su seviyesi sensörünün okuma değerini tersine çevir
  suSeviyesi = map(suSeviyesi, 0, 1023, 0, 100);
  toprakNem = map(toprakNem, 0 ,1023, 1000, 0);

  lcd.setCursor(12, 0);
  lcd.print(toprakNem);

  lcd.setCursor(12, 1);
  lcd.print(suSeviyesi);

  // Eğer toprak nem düşükse, farklı bir ötüş ve LED deseni kullan
  if (toprakNem < 30) {
    for(int i = 0; i < 5; i++){ // 5 kere dönecek
      digitalWrite(ledPin, HIGH); // LED'i yak
      digitalWrite(buzzerPin, HIGH); // Buzzer'ı yak
      delay(50); // 50 milisaniye boyunca yüksek
      digitalWrite(ledPin, LOW); // LED'i söndür
      digitalWrite(buzzerPin, LOW); // Buzzer'ı söndür
      delay(50); // 50 milisaniye boyunca düşük
    }
    delay(500); // Desenler arası 500 milisaniye bekleme
  } 
  // Eğer su seviyesi düşükse, farklı bir ötüş ve LED deseni kullan
  else if (suSeviyesi < 30) {
    for(int i = 0; i < 5; i++){ // 5 kere dönecek
      digitalWrite(ledPin, HIGH); // LED'i yak
      digitalWrite(buzzerPin, HIGH); // Buzzer'ı yak
      delay(100); // 100 milisaniye boyunca yüksek
      digitalWrite(ledPin, LOW); // LED'i söndür
      digitalWrite(buzzerPin, LOW); // Buzzer'ı söndür
      delay(100); // 100 milisaniye boyunca düşük
    }
    delay(500); // Desenler arası 500 milisaniye bekleme
  } 
  else {
    digitalWrite(ledPin, LOW); // LED'i söndür
    digitalWrite(buzzerPin, LOW); // Buzzer'ı söndür
  }
  
  delay(100); // Tekrar okumayı saniyede bir kez yap
}
