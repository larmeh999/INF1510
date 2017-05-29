
char msg = ' '; //Inneholder beskjed fra Ardoino senderen 
const int buttonPinG = 2; //Knapp grønn 
const int buttonPinR = 7; //Knapp rød
int buttonStateR = 0; // Tilstand til knappene 
int buttonStateG = 0;
int ledpinG = 13; // LED grønn
int ledpinR = 9; // LED rød 
int lastButtonStateG = 0;//Forrige tilstand til knapp, debounce
int lastButtonStateR = 0;

void setup() {
 pinMode(9, OUTPUT); 
 pinMode(13, OUTPUT);
  
 pinMode(buttonPinG, INPUT);
 pinMode(buttonPinR, INPUT);
Serial.begin(9600);//Baud rate må være samme for begge Arduinos
}
void loop() {

  buttonStateG = digitalRead(buttonPinG); //Leser om knapp er trykket 
  digitalWrite(ledpinR, HIGH); // Setter rod LED til aa lyse
  digitalWrite(ledpinG, LOW);
   if (buttonStateG != lastButtonStateG) {
 
    if (buttonStateG == HIGH) {// Hvis gronn knapp er trykket, send bokstav "K" til serial. 
    Serial.print("K");
    
    } 
    delay(50);
  }           
  lastButtonStateG = buttonStateG;

   buttonStateR = digitalRead(buttonPinR);
  
   if (buttonStateR != lastButtonStateR) {
 //Hvis rod kanpp er trykket, send bokstav "E" til serial
    if (buttonStateR == HIGH) {
    Serial.print("E");
    
    } 
    delay(50);
  }           
  lastButtonStateR = buttonStateR;
 // Hvis bokstaven "H" blir mottatt, sett led gronn til HIGH og led rod til LOW 
  while(Serial.available()>0) {
           msg=Serial.read();
           if(msg=='H') {
              
               digitalWrite(ledpinR, LOW);
               digitalWrite(ledpinG, HIGH); 
               delay(2000);
   
           }
                
delay(500);
    
  }
}
