#include <Keyboard.h>
#include <Mouse.h>
#include <SPI.h>    // RFID를 위한 SPI 라이브러리
#include <MFRC522.h>// RFID 라이브러리
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //I2C LCD 라이브러리
#include <SoftwareSerial.h> //블루투스 연결을 위한 라이브러리

LiquidCrystal_I2C lcd (0x3F,16,2);  //I2C LCD 객체인 lcd를 설정합니다.

#define BT_RXD 8
#define BT_TXD 7
SoftwareSerial bluetooth(8, 7); //블루투스 세팅
#define SS_PIN 10   //RFID SS(SDA:ChipSelect) PIN
#define RST_PIN 9   //RFID Reset PIN
MFRC522 rfid(SS_PIN, RST_PIN); //RFID 라이브러리
 
/* 등록된 RF CARD ID */ 
#define PICC_0 0x10
#define PICC_1 0x49
#define PICC_2 0x93
#define PICC_3 0xA6

#define PICC_00 0x2A
#define PICC_11 0xFF
#define PICC_22 0x4B
#define PICC_33 0x79

#define USERNAME ""
#define PASSWORD ""
 
void setup() { 
  
  //시리얼 모니터 시작
  bluetooth.begin(9600);  //블루투스 시작
  Serial.begin(9600);
  SPI.begin(); // SPI 시작
  rfid.PCD_Init(); // RF 모듈 시작
  Mouse.begin();

  //lcd 시작
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcdclear();
}
 
void loop() {

  if (bluetooth.available()) {  //블루투스에서 넘어온 데이터가 있다면 
    int bt;
    bt = bluetooth.read();
    Serial.write(bt);
    if(bt == '1')
      login(1);
    else if(bt == '2')
      login(2);
  }
  
  //카드가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_IsNewCardPresent())
    return;
 
  //RF카드의 ID가 인식 안되었다면 더이상 진행하지 말고 빠져나감
  if ( ! rfid.PICC_ReadCardSerial())
    return;
 
 
  Serial.print(F("PICC type: "));
  //PICC 타입 읽어오기
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));
 
 
  //MIFARE 방식이 아니라면 더이상 진행하지 말고 빠져나감
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
 
 
  //ID가 등록된 첫 번째 카드 ID와 같다면
  if (rfid.uid.uidByte[0] == PICC_0 || 
      rfid.uid.uidByte[1] == PICC_1 || 
      rfid.uid.uidByte[2] == PICC_2 || 
      rfid.uid.uidByte[3] == PICC_3 ) {
      
      Serial.println(F("카드1 접속 허가"));
      lcdprint(1);
         
      delay(100);
      Mouse.click();
      delay(100);
      Keyboard.print(USERNAME); //아이디
      delay(100);
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.print(PASSWORD); //비밀번호
      delay(100);
      Keyboard.write (KEY_RETURN);
      delay(100);

      for(int i = 5; i>=0; i--){
        lcd.setCursor(15, 1);
        lcd.print(i);
        delay(1000);
       }
       lcdclear();
  }

  //ID가 등록된 두 번째 카드 ID와 같다면
  else if(rfid.uid.uidByte[0] == PICC_00 || 
      rfid.uid.uidByte[1] == PICC_11 || 
      rfid.uid.uidByte[2] == PICC_22 || 
      rfid.uid.uidByte[3] == PICC_33) {

        
      Serial.println(F("카드 2 접속 허가"));
      lcdprint(2);
         
      delay(100);
      Mouse.click();
      delay(100);
      Keyboard.print(USERNAME); //아이디
      delay(250);
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.write(KEY_TAB);
      Keyboard.write (KEY_RETURN);
      delay(2500);
      Keyboard.print(PASSWORD); //비밀번호
      delay(250);
      Keyboard.write (KEY_RETURN);
      delay(250);

      for(int i = 5; i>=0; i--){
        lcd.setCursor(15, 1);
        lcd.print(i);
        delay(1000);
       }
      lcdclear();
   }
  
  else{
    //등록된 카드가 아니라면 시리얼 모니터와 lcd 로 ID 표시
    Serial.println(F("경고! 등록되지 않은 카드입니다."));
    Serial.print(F("In hex: "));
    lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Login Failed...");
      lcd.setCursor(0, 1); 
      lcd.print("Unknown Card");
    printHex(rfid.uid.uidByte, rfid.uid.size);

    for(int i = 5; i>=0; i--){
        lcd.setCursor(15, 1);
        lcd.print(i);
        delay(1000);
       }
     lcdclear();
  }
  
  //종료
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
 
  //다시 시작
}






void login(int card){
  if(card == 1){
    
    Serial.println(F("카드1 접속 허가"));
      lcdprint(1);
         
      delay(100);
      Mouse.click();
      delay(100);
      Keyboard.print(USERNAME); //아이디
      delay(100);
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.print(PASSWORD); //비밀번호
      delay(100);
      Keyboard.write (KEY_RETURN);
      delay(100);

      for(int i = 5; i>=0; i--){
        lcd.setCursor(15, 1);
        lcd.print(i);
        delay(1000);
       }
       lcdclear();
       
  }

  else if(card == 2){

    Serial.println(F("카드 2 접속 허가"));
      lcdprint(2);
         
      delay(100);
      Mouse.click();
      delay(100);
      Keyboard.print("*****"); //아이디
      delay(100);
      Keyboard.write(KEY_TAB);
      delay(100);
      Keyboard.print("*****"); //비밀번호
      delay(100);
      Keyboard.write (KEY_RETURN);
      delay(100);

      for(int i = 5; i>=0; i--){
        lcd.setCursor(15, 1);
        lcd.print(i);
        delay(1000);
       }
      lcdclear();
    
  }
}

//로그인 성공 or 실패 시 출력.
void lcdprint(int card){
  
  if(card == 1){
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Login Colpleted!");
      lcd.setCursor(0, 1); 
      lcd.print("Card 1");
  }
  
  
  else if(card == 2){
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Login Colpleted!");
      lcd.setCursor(0, 1); 
      lcd.print("Card 2");
  }

  else{
      lcd.clear();
      lcd.setCursor(0, 0); 
      lcd.print("Login Failed...");
      lcd.setCursor(0, 1); 
      lcd.print("Unknown Card");
  }
  
}

//시작 화면 lcd 출력
void lcdclear(void){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Auto");
  lcd.setCursor(0, 1);
  lcd.print("Log-In System!");
}
 
//16진수 표시
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
