#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define RST_PIN 9  // Configurable, see typical pin layout above
#define SS_PIN 10  // Configurable, see typical pin layout above

#define Buzzer 3

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


#define NEW_UID \
  { 0xDE, 0xAD, 0xBE, 0xEF }

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);  // Initialize serial communications with the PC
  pinMode(Buzzer, OUTPUT);
  while (!Serial)
    ;                  // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522 card
  //Serial.println(F("Warning: this example overwrites the UID of your UID changeable card, use with care!"));
  myservo.attach(8);

  lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	


}

void loop() {
 lcd.clear();
 lcd.setCursor(4,0);
 lcd.print("Welcome!");
   

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Dump UID

  int ID = mfrc522.uid.uidByte[0];
  //Serial.print(F("Card UID:"));
  Serial.println(int(ID));
  if (ID == 227) {
    Serial.println("Maethas");
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Card UID:");
    lcd.setCursor(11,0);
    lcd.print(ID);
    lcd.setCursor(0,1);
    lcd.print("Welcome to class");
    myservo.write(180);
    delay(5000);
    myservo.write(90);
    
  }

  if (ID == 131) {
    Serial.println("Benyapa");
    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    lcd.clear();
     lcd.setCursor(0,0);
   lcd.print("Card UID:");
    lcd.setCursor(11,0);
    lcd.print(ID);
    lcd.setCursor(0,1);
    lcd.print("Welcome to class");
    myservo.write(180);
    delay(5000);
    myservo.write(90);
    
  }




  
  
}