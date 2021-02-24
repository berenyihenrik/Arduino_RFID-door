#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h> 

Servo Servo1;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9

int x = 0;
boolean masterMode = false;
int count = 1;

MFRC522 mfrc522(SS_PIN, RST_PIN);  

String kartyak[20] = {"C4 93 71 DC"};                 // Regisztrált tagek
String MasterCard = "3A C4 0C C5";                    // "FB D9 64 55"
String Id;
 
void setup() 
{
  lcd.begin(16,2);
  lcd.noBacklight();

  Servo1.attach(3);

  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Erintsd a kartyat az olvasohoz...");
  pinMode(7, OUTPUT); //Zöld LED
  pinMode(6, OUTPUT); // Piros LED
  pinMode(8, OUTPUT); // Csipogó
  pinMode(3, OUTPUT); // Servo motor

}
void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) //Van-e új kártya
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) //Azonosító beolvasása
  {
    return;
  }

  Serial.print("Kartyaazonosito:");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();


Id = content.substring(1);

    
   if (isMaster())
  { 

 

    if(masterMode){
      masterMode = false;
     Serial.println("Mastermode kikapcsolva");
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("MASTERMODE KI");
     delay(1000);
     lcd.clear();
     lcd.noBacklight();
     delay(3000);
      }

     else{
      masterMode = true;
      Serial.println("Mastermode bekapcsolva");
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("MASTERMODE BE");
      delay(3000);
      
     }
 
  }


else{
  if(arrayIncludeElement(kartyak, Id) == true && masterMode == false){                  // Engedélyezett belépés
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Belepes");
    lcd.setCursor(0,1);
    lcd.print("Engedelyezve");
    Serial.println("Belepes engedelyezve");
    Servo1.write(0); // motor kinyit
    Serial.println();
    digitalWrite(7, HIGH);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(50);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(1500);
    lcd.clear();
    lcd.noBacklight();
    digitalWrite(7, LOW);
    Servo1.write(90); //motor becsuk
  }

   else                                                                 //Megtagadott belépés
 {  if(masterMode == false){
    lcd.setCursor(0, 0);
    lcd.backlight();
    lcd.print("Belepes");
    lcd.setCursor(0,1);
    lcd.print("Megtagadva");                                   
    Serial.println("Belepes megtagadva");
    digitalWrite(6, HIGH);
    tone(8, 1000);
    delay(1000);
    noTone(8);
    delay(1000);
    tone(8, 1000);
    delay(1000);
    noTone(8);
    delay(1500);
    lcd.clear();
    lcd.noBacklight();
    digitalWrite(6, LOW);
 }
  }
}
  

 
Mastermode();
}




void Mastermode(){


if(masterMode){
  if(arrayIncludeElement(kartyak, Id) == false && isMaster() == false){
    Serial.println("Beleirja a kartyat a listaba");
    lcd.setCursor(0, 1);
    lcd.print("Hozzaadva");
    digitalWrite(7, HIGH);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(50);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(50);
    tone(8, 1000);
    delay(50);
    noTone(8);
    addCard();
    delay(1500);
    lcd.clear();
    digitalWrite(7, LOW);
    lcd.setCursor(0, 0);
    lcd.print("MASTERMODE BE");
  }
  else{
    if(arrayIncludeElement(kartyak, Id) == true && isMaster() == false){
    removeCard();
    Serial.println("A kartyat kivettem a listabol");
    lcd.setCursor(0, 1);
    lcd.print("Kiveve");
    digitalWrite(6, HIGH);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(50);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(50);
    tone(8, 1000);
    delay(50);
    noTone(8);
    delay(1500);
    lcd.setCursor(0,0);
    lcd.print("MASTERMODE BE");
    digitalWrite(6, LOW);
    }
  }

}
 
}


boolean arrayIncludeElement(String array[], String element) {
  for (int i = 0; i < (sizeof(array)+1); i++) {
    if (array[i] == element) {
      return true;
    }
  }
  return false;
  }



  boolean isMaster(){
    if (Id == MasterCard){
      return true;
    }

    else{
      return false;
    }
  }


  void addCard(){
    kartyak[count] = Id;
    count++;
    
    return;
  }

  void removeCard(){
        for (int j = 0; j < sizeof((kartyak)+1); j++){
            if (kartyak[j] == Id){
                kartyak[j] = "";
              
            }
          
        }
      return;
  }
