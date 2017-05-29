#include <Servo.h> // Inkluderer Servo biblotek
Servo myservo;// Definerer Servo som "myservo"
#include <SPI.h>//inkluderer SPI biblotek 
#include <MFRC522.h> //inkluderer MFRC522 bibliotek
 char msg = ' '; // BEskjed som kommer i serial
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Lager instanse av MFRC522
 int pos = 90; //Setter servo til 90 grader ved oppstart.
void setup() 
{
  Serial.begin(9600);   // Initialiserer Serial
  SPI.begin();      // Initialiserer SP bus 
  mfrc522.PCD_Init();   // initialiserer MFRC522
  myservo.attach(3); //Initialiserer servo til pin 3
myservo.write(0);//Setter servo til 0 grader, altsaa aapen
}
void loop() 

{

delay(1000);
// Naar serial er tilgjengelig, les og hvis bokstaven "K" blir mottat og servo staar i 0 grader, så skal servo snu 90 grader. 
       while(Serial.available()>0) {
           msg=Serial.read();
           if(msg=='K' && myservo.read() == 0) {
              myservo.write(90);
              delay(100);
        
           }
           //Hvis bokstaven "E" blir mottatt og servo staar i 90 grader, snu servo til 0 grader
           else if(msg=='E' && myservo.read() == 90) {
              myservo.write(0);
              delay(100);
        
           }
//Hvis ikke sett servo til 0 grader.            
         else {
            myservo.write(0);
            delay(100);
           }
           
         
delay(1000);
}
  // Leter etter nye RFID kort for å lese
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // FInner et kort. 
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

 //Skriver ut dataen til kortet som er funnet 
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  
  content.toUpperCase();
  //Hvis UID til kortet er riktig, send bokstaven "H" til serial
  if (content.substring(1) == "56 2F 50 06") //change here the UID of the card/cards that you want to give access
  {
 
    Serial.print("H"); 
     
    delay(2000);

  }
 

}
