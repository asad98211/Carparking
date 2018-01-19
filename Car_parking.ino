//Servo control pin=2
//irentry pin 13, irexit pin=12, slot1=11,slot2=10,slot3=9
//lcd I2C bus sda=A4,scl=A5
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo myservo;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
int pos = 0,irentry=13,irexit=12,slot1=11,slot2=10,slot3=9;
void Down(){
     for(pos=0;pos<=90;pos++){
       myservo.write(pos);
       delay(10);
     }
}
void Up(){
    for(pos=90;pos>=0;pos--){
       myservo.write(pos);
       delay(10);
     }
}
void setup(){
  Serial.begin(9600);
  myservo.attach(2);  // attaches the servo on pin 2 to the servo object
  lcd.begin();
  lcd.backlight();
  pinMode(irentry,INPUT);
  pinMode(irexit,INPUT);
  pinMode(slot1,INPUT);
  pinMode(slot2,INPUT);
  pinMode(slot3,INPUT);
}

void loop() {
  static int count=0,inflag=0,exflag=0;
  int signalentry,signalexit,sig_slot1,sig_slot2,sig_slot3;
  signalentry=digitalRead(irentry);
  signalexit=digitalRead(irexit);
  sig_slot1=digitalRead(slot1);
  sig_slot2=digitalRead(slot2);
  sig_slot3=digitalRead(slot3);
  Serial.println(signalentry);
  Serial.println(signalexit);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Available Slot");
  lcd.setCursor(0,1);
  if(sig_slot1==LOW){
    lcd.print("1 ");
   }
  if(sig_slot2==LOW){
    lcd.print("2 ");
  }
  if(sig_slot3==LOW){
    lcd.print("3 ");
  }
  if(signalentry==HIGH){
    count++;
    if(inflag==0){
      inflag=1; 
      Up();
    }
    if(exflag==1){
      Down();
      exflag=0;
    }
  }
  if(signalexit==HIGH){
    
    count--;
    if(inflag==1){
      inflag=0; 
      Down();
    }
    if(exflag==0){
      Up();
      exflag=1;
    }
  }
  delay(1000);
}
