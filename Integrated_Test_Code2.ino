#include <SPI.h>
#include <MFRC522.h>
#include <Stepper.h>

//RFID-SS Pin is same as SDA
#define SS_PIN 10
#define RST_PIN 9

// Stepper Driver pin connections 
const int dirPin = 2;
const int stepPin = 3;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance (MFRC522 is the RFID Reader)

//Stepper
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, stepPin, dirPin, 10, 11);


void setup() {
 Serial.begin(9600);        // Initialize serial communications with the PC
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card

  // set the speed at 60 rpm:
myStepper.setSpeed(150);
  // initialize the serial port:
Serial.begin(9600);
  
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
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
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "32 B1 FF 21") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(500);

    // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step((stepsPerRevolution*12));
  delay(5000);
    

    
  }
 
 else   {
    Serial.println(" Access denied");
    delay(3000);
  }
} 
