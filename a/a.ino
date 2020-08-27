#include "LiquidCrystal.h"
#include "Wire.h"  // Comes with Arduino IDE
#include <TimeLib.h>
#include <EEPROM.h>         //Include the EEPROM library to score the highscore
 unsigned char Re_buf[11],counter=0;
 char sign=0;
float TO=0,TA=0;
void serialEvent();
const int swich_time=50;
const byte OK_SW_Pin=0;
const byte HET_key_Pin=11;

const byte HET_output_Pin=13;
const byte Mot_output_Pin=12;
const byte BUZZ_output_Pin=3;
const byte UP_SW_Pin=1;
const byte DW_SW_Pin=4;
const byte swich_time2=100;

bool oldstate_3;
int ledPin = 7;   // choose the input pin (for a pushbutton)
// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(23, 22,18, 19,20,21);
bool tt=0,k_wile;
int i;
byte address=0;

int lastDay = 0;
int lastMonth = 0;
int lastYear = 0;
int lastHour = 0;
int lastMinute = 0;
int lastSecond=0;
int lastSecond_alarm=0;
int lastSecond_alarm_pluss=5;
int movementTimer = 0;
int menuOptions = 4;
int menuOption = 0;
int alarmHours = 0;
//int Heater_alarmMinutes = 0;
//int Heater_alarmSecond=10;
//int Motor_alarmSecond=10;
//int Motor_alarmMinutes=0;

int jj;
int IR_Temp_Treshhold=40;
int Heater_alarmMinutes_end ;
int Heater_alarmSecond_end;
int Motor_alarmSecond_end;
int Motor_alarmMinutes_end;
bool state,state2,temp_situation=1;
byte state1,score;
bool heater_key = 0;//0 for tempmode, 1 for no temp mode
// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES, EXCEPT FROM "A" 
//THAT IS CALLED WITH THE ITALIAN NAME "LA" BECAUSE A0,A1...ARE THE ANALOG PINS ON ARDUINO.
// (Ab IS CALLED Ab AND NOT LAb)
#define  C0 16.35
#define Db0 17.32
#define D0  18.35
#define Eb0 19.45
#define E0  20.60
#define F0  21.83
#define Gb0 23.12
#define G0  24.50
#define Ab0 25.96
#define LA0 27.50
#define Bb0 29.14
#define B0  30.87
#define C1  32.70
#define Db1 34.65
#define D1  36.71
#define Eb1 38.89
#define E1  41.20
#define F1  43.65
#define Gb1 46.25
#define G1  49.00
#define Ab1 51.91
#define LA1 55.00
#define Bb1 58.27
#define B1  61.74
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define LA2 110.00
#define Bb2 116.54
#define B2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define LA3 220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define LA4 440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define LA5 880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define LA6 1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define LA7 3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03
// DURATION OF THE NOTES 
#define BPM 30    //  you can change this value changing all the others
//#define BPM_MAIN 120    //  you can change this value changing all the others

#define H 2*Q //half 2/4
#define Q 3000/BPM //quarter 1/4 
#define Q2 3*Q/2   //eighth 3/4
#define E Q/2   //eighth 1/8
#define E2 3*E/2   
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4
const byte buzz_pin=3;
unsigned long startTime;
 
bool Button(byte buttonPin,unsigned int  Switch_Time, bool state1c){
  // variables will change:
  int buttonState = 0;         // variable for reading the pushbutton status
  
// unsigned long Switch_Time = 100000; // 1 seconds
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  startTime = millis();
  
   if ((state1c ==0)&& (buttonState == LOW)){
   while((millis() - startTime < Switch_Time)){
         buttonState = digitalRead(buttonPin);
         if ((buttonState == HIGH)&& (millis() - startTime < Switch_Time)) {
             return 0;  
          }  
     }
     return 1;
  }
  else if ((state1c == 1)&& (buttonState == HIGH)) {
     while((millis() - startTime < Switch_Time)){
         buttonState = digitalRead(buttonPin);
         if ((buttonState == LOW)&& (millis() - startTime < Switch_Time)) {
             ; return 0; 
            }  
     }
     return 1;
     }
  else{
    return 0;
  }
}


// Create a set of new characters
byte smiley[8] = {
  B00000,  
  B01010,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

byte heart_h[8] = {
  B00000,
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,  
  B00000
}; 
byte heart_f[8] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,  
  B00000
}; 
byte ohm[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B01010,  
  B11011
}; 
byte rect[8] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111
};
byte arrow_u[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100,  
  B00100
}; 
byte arrow_d[8] = {  
  B00100,
  B00100,
  B00100,
  B00100,  
  B00100,  
  B11111,
  B01110,
  B00100
}; 
byte diamond[8] = {
  B00000,
  B00100,
  B01010,
  B10001,  
  B01010,
  B00100,
  B00000,
  B00000  
}; 

byte alef[8] = {
  B00000,
  B00100,
  B00100,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000
};

byte alef_kolahdar[8] = {
  B00001,
  B11111,
  B10100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte Mim_chasban[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B10100,
  B11100,
  B00000
};

byte dal[8] = {
  B00000,
  B00000,
  B00000,
  B00010,
  B00100,
  B01000,
  B00100,
  B00010
};

byte he_tak_cheshm[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01010,
  B01010,
  B01110,
  B00000
};

byte box[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000
};
byte blank[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};


void setup() {
 Wire.begin();
 pinMode(ledPin, OUTPUT);  // declare LED as output
 pinMode(OK_SW_Pin, INPUT);    // declare pushbutton as input
 pinMode(UP_SW_Pin, INPUT);    // declare pushbutton as input
 pinMode(DW_SW_Pin, INPUT);    // declare pushbutton as input
 pinMode(HET_output_Pin, OUTPUT);  // declare LED as output
 pinMode(Mot_output_Pin, OUTPUT);  // declare LED as output 
 pinMode(buzz_pin, OUTPUT);   
// digitalWrite(ledPin, HIGH);  // turn LED ON
lcd.begin(16,2);

// set cursor position to start of first line on the LCD
lcd.setCursor(0,0);
//text to print
lcd.print("   16x2 LCD");
// set cusor position to start of next line
lcd.setCursor(0,1);
lcd.print("   DISPLAY");


//Amadeh(0,3);
delay(500);

//lcd.createChar (0, smiley);    // load smiley to memory 0
//  lcd.createChar (1, heart_h);    // load  heart_h to memory 1
//  lcd.createChar (2, heart_f);  // load heart_f to memory 2
//  lcd.createChar (3, ohm);     // load  ohm to memory 3
//lcd.createChar (4, rect);     // load rect to memory 4
//  lcd.createChar (7, diamond);     // load diamond to memory 7
lcd.createChar (0, box);
lcd.createChar (1, arrow_u);     // load arrow_u to memory 5
lcd.createChar (2, arrow_d);     // load arrow_d to memory 6
lcd.createChar (3, blank);
//12 11 8 10 9 (amadeh)
//
//lcd.createChar (12, alef);    // load smiley to memory 0
//  lcd.createChar (11, alef_kolahdar);    // load  heart_h to memory 1
//  lcd.createChar (8, Mim_chasban);  // load heart_f to memory 2
//  lcd.createChar (10, dal);     // load  ohm to memory 3
//lcd.createChar (9, he_tak_cheshm);     // load rect to memory 4
//  lcd.createChar (5, arrow_u);     // load arrow_u to memory 5
//  lcd.createChar (6, arrow_d);     // load arrow_d to memory 6
//  lcd.createChar (7, diamond);     // load diamond to memory 7


//lcd.print(char(0));    //display a smiley
// lcd.print(char(1));  //display a  hollow heart
// lcd.print(char(2));   //display a  filled heart
// lcd.print(char(3));   //display a ohm
// lcd.print(char(4));//display a rectangle
// lcd.print(char(5)); //display a arrow
// lcd.print(char(6)); //display a rectangle
// lcd.print(char(7)); //display a arrow
//delay (500);

//lcd.clear();
//lcd.print(char(0));    //display a smiley
//lcd.print(char(9));    //display a smiley
// lcd.print(char(10));  //display a  hollow heart
// lcd.print(char(8));   //display a  filled heart
// lcd.print(char(11));   //display a ohm
//lcd.print(char(12));    //display a smiley
//lcd.print(char(0));    //display a smiley
delay (100); 

//lcd.clear();         //clear the screen
//  lcd.backlight(); // turn on back light
  
   Serial.begin(115200);
  delay(1);
  Serial.write(0XA5);
  Serial.write(0X45);
  Serial.write(0XEA);
//for (i=0;i<100;i++){
//  lcd.setCursor(0,0);
//       lcd.print(i);delay(100);
//}
//  address=1;
//  EEPROM.write(address,11); 
  score=29;
  if (EEPROM.read(1)==score){
  address=2;
  lcd.setCursor(0,0);
  lcd.clear();lcd.print("eeprom writed beffor");delay(1000);
  Heater_alarmSecond_end = EEPROM.read(address);
  Heater_alarmMinutes_end= EEPROM.read(address+1);
  Motor_alarmSecond_end = EEPROM.read(address+2);
  Motor_alarmMinutes_end = EEPROM.read(address+3);
  IR_Temp_Treshhold=EEPROM.read(address+4);
  temp_situation=1;//EEPROM.read(address+5);
  }
  else{
  lcd.setCursor(0,0);
  lcd.print("new eeprom");delay(500);
  address=1;
  EEPROM.write(address,29);
  EEPROM.write(address+1,10);
  EEPROM.write(address+2,0);
  EEPROM.write(address+3,10);
  EEPROM.write(address+4,0);
  EEPROM.write(address+5,IR_Temp_Treshhold);
  EEPROM.write(address+6,temp_situation);
  address=2;
  
  Heater_alarmSecond_end = EEPROM.read(address);
  Heater_alarmMinutes_end= EEPROM.read(address+1);
  Motor_alarmSecond_end = EEPROM.read(address+2);
  Motor_alarmMinutes_end = EEPROM.read(address+3);
  IR_Temp_Treshhold=EEPROM.read(address+4);
  temp_situation=EEPROM.read(address+5);
  }
  lcd.clear();    
}
//
//void Amadeh(int j, int i) // Farsi text = 'Amadeh'
//
//{ // i column , j row
////  lcd.print(char(0));    //display a smiley
//// lcd.home();
//
//delay(100);
//
//
//
//  
//  lcd.write(int(5));lcd.setCursor(j,i+1);
//    lcd.write(int(4));lcd.setCursor(j,i+2);
//      lcd.write(int(1));lcd.setCursor(j,i+3);
//        lcd.write(int(3));lcd.setCursor(j,i+4);
//          lcd.write(int(2));lcd.setCursor(j,i+5);
////  
////lcd.print(char(9));    //display a smiley
//// lcd.print(char(10));  //display a  hollow heart
//// lcd.print(char(8));   //display a  filled heart
//// lcd.print(char(11));   //display a ohm
////lcd.print(char(12));    //display a smiley
//////lcd.print(char(0));    //display a smiley
//}

void start(){
  lcd.clear();
   
//   lastHour = hour();
   state=1;tt=0; jj=0;
          //check for heater key pressed
   while(state){
   if (Button(HET_key_Pin,100, 1)) {
    
      for (int ii = 0; ii <= 255; ii++) {
         delay(10);jj=jj+1;
      }
      
      if (jj>=200) 
      {
         state = 0;                     // Update flag
         digitalWrite(ledPin, HIGH);  // turn LED OFF
         break;
        }
      }
//   else if (tt==0)  {
//      
//       digitalWrite(ledPin, LOW);  // turn LED ON
//       lcd.setCursor(0,0);
//       lcd.print("Wating for :");
//       lcd.setCursor(0,1);
//       lcd.print(" Going UP");
//       tt=1;
//       }
       
       digitalWrite(ledPin, LOW);  // turn LED ON
       lcd.clear();
//     lcd.print(char(7)); //display a arrow
       lcd.setCursor(0,0); 
       lcd.print("    Wating for :");
       lcd.setCursor(0,1);
       lcd.print(" Going UP   "); 
       if (tt==0){
       lcd.write(int(1)); lcd.write(int(1)); 
//     lcd.print(char(7)); //display a arrow
       tt=1;
       }
       else{
       lcd.write(int(3)); lcd.write(int(3)); tt=0;
       }
//       if (Button(HET_key_Pin,100, 1)) break; 
//       delay(300);
//       if (Button(HET_key_Pin,100, 1)) break; 


//lcd.clear();lcd.setCursor(0,1);lcd.home();
//lcd.print("  ");
//lcd.write(int(0)); lcd.write(int(0));    //display a smiley
////Amadeh(0,3);
//lcd.write(int(0)); lcd.write(int(0)); 
//lcd.print("  ");   //display a smiley
delay (200);
if (Button(HET_key_Pin,100, 1)) break;       
Buzzer();
   }

   
   lcd.clear();setTime(0, 0, 1, 20, 1, 2013); // hour, min, sec, day, month, year
   state =1;tt=0;
   if (temp_situation==1){
    heater_key=1;
   }else{
    heater_key=0;
   }

   
   lastSecond_alarm=second();
   while (state==1){

    
      if ( lastSecond!=second())
     {

 if (lastMinute != minute()) 
          {
          lastSecond_alarm= 0;lastMinute = minute() ; 
          }
          
          
          if (second()>=lastSecond_alarm+lastSecond_alarm_pluss){
           
           if (lastMinute == minute()) lastSecond_alarm= second();
           
           Buzzer_During_Heating();
                    
          }
          
      
        lastMinute = minute();
        lastSecond=second();
        
        
        //text to print
        if (tt==0)  {lcd.setCursor(0,0); lcd.print("Heater Time:"); tt=1;}
        lcd.setCursor(0,1);
        lcd.print(lastMinute);
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(lastSecond);
       
       //delay(1000);
     }    
   if (heater_key==1)
    {
      if (Button(HET_key_Pin,100, 0)) break;
      // alarm set
      if ((Heater_alarmSecond_end <= lastSecond) && (Heater_alarmMinutes_end == lastMinute))
      {
         state=0;
         digitalWrite(HET_output_Pin, LOW);

     }
      
      
      }
       if ((Heater_alarmSecond_end >= lastSecond) || (Heater_alarmMinutes_end >= lastMinute))
         {
          //sound alarm
          digitalWrite(HET_output_Pin, HIGH);
          //setOffAlarm();

    }

     if (heater_key==0){
      state=1;lcd.clear();
      while(state==1){
         mlx90615();
         lcd.clear();//lcd.setCursor(0,0); lcd.print("TA:");lcd.setCursor(5,0); lcd.print(TA);delay(300);
         lcd.setCursor(0,1);lcd.print("Temp:");lcd.setCursor(5,1); lcd.print(TO);delay(300);
         digitalWrite(HET_output_Pin, HIGH);
         if ( (int(TO)>=IR_Temp_Treshhold) ){ //(int(TA)>=40) or
          delay(1000);state=0;digitalWrite(HET_output_Pin, LOW);
          lcd.clear();lcd.setCursor(0,0); lcd.print("Temprature over heated");delay(500);
          
         }
      }
     
     }
   } 

   
   digitalWrite(HET_output_Pin, LOW);
   state=1;tt=0;
   
   lastSecond_alarm=second();
   tt=0;
   while(state){
        
   if (Button(HET_key_Pin,100, 0)) {
      state = 0;                     // Update flag
      digitalWrite(ledPin, HIGH);  // turn LED OFF
      }
      
   else if (tt==0)  {
       digitalWrite(ledPin, LOW);  // turn LED ON
       lcd.setCursor(0,0);
       lcd.print("Wating for :");
       lcd.setCursor(0,1);
       lcd.print("Downing Pad    ");
       
       if (tt==0){
       lcd.write(int(2));   lcd.write(int(2)); 
//     lcd.print(char(7)); //display a arrow
       tt=1;
       }
       else{
       lcd.write(int(3));   lcd.write(int(3)); 
       tt=0;
       }
       
       }
       if (Button(HET_key_Pin,100, 1)) Buzzer_3door();
       
   }
     tt=0;lcd.clear();
    state =1;
    setTime(0, 0, 0, 20, 1, 2013); // hour, min, sec, day, month, year
    
     while (state ){

    if ( lastSecond!=second()){
          
          if (lastMinute != minute()) 
          {
          lastSecond_alarm= second();lastMinute = minute() ; 
          }
          if (second()>=lastSecond_alarm+lastSecond_alarm_pluss){
           lastSecond_alarm= second();
           Buzzer_During_Heating();
          }
         }

      if ( lastSecond!=second())
     {
        lastMinute = minute();
        lastSecond=second();
        
        //text to print
        if (tt==0)  {lcd.setCursor(0,0); lcd.print("Motor Time:"); tt=1;}
        lcd.setCursor(0,1);
        lcd.print(lastMinute);
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(lastSecond);
       
       //delay(1000);
     }    
   if (1)
    {
      // alarm set
      if ((Motor_alarmSecond_end <= lastSecond) && (Motor_alarmMinutes_end == lastMinute))
      {
         state=0;
         digitalWrite(Mot_output_Pin, LOW);
   
       }
       if ((Motor_alarmSecond_end >= lastSecond) || (Motor_alarmMinutes_end >= lastMinute))
         {
          //sound alarm
          digitalWrite(Mot_output_Pin, HIGH);
         
         }
     }
   }
digitalWrite(Mot_output_Pin, LOW);lcd.clear();
//########### MLX90615 @#############
//   char i=0,sum=0;
// 
////  for (i=0;i<100;i++){
//   score=1;
//    while(score==1){
//    serialEvent();
//    if(sign)
//    {
//       sign=0;
//       for(i=0;i<8;i++)
//        sum+=Re_buf[i];
//       if(sum==Re_buf[i] )
//       {
//             TO=(float)(Re_buf[4]<<8|Re_buf[5])/100;
//             if ((int)TO>=30){
//              score=0;
//             }
//            lcd.setCursor(0,0);
//            lcd.print("Temprature :"); 
//            TA=(float)(Re_buf[6]<<8|Re_buf[7])/100;
//            lcd.setCursor(0,1); lcd.print("TA: "); lcd.print(TA);
//            
//             
//             Serial.print("TA:");
//             Serial.println(TA);
//             delay(100);
//     }
//    }
//  }
////####################
//   delay(100);
   
   return;
   
}


//void Buzzer() {
//  //tone(pin, note, duration)
//   tone(buzz_pin,C5,E); 
//    
//    delay(1+E);//delay duration should always be 1 ms more than the note in order to separate them.
//    tone(buzz_pin,G4,E);
////    delay(1+E);
//    delay(1+E);
//    tone(buzz_pin,E4,Q);
//    delay(1);
//    tone(buzz_pin,LA4,Q); 
//    delay(1); //delay duration should always be 1 ms more than the note in order to separate them.
//    tone(buzz_pin,B4,Q);
//    delay(1);
//    tone(buzz_pin,LA4,Q);
//    delay(1);
//    tone(buzz_pin,G4,E);
//    
//    tone(buzz_pin,Ab4,Q); 
//    delay(1); //delay duration should always be 1 ms more than the note in order to separate them.
//    tone(buzz_pin,Bb4,Q);
//    delay(1);
//    tone(buzz_pin,Ab4,Q);
//    delay(1);
//    
//    
//    tone(buzz_pin,E4,E); 
//    delay(1); //delay duration should always be 1 ms more than the note in order to separate them.
//    tone(buzz_pin,D4,E);
//    delay(1);
//}
void Buzzer() {
  
  //tone(pin, note, duration)
   if (Button(HET_key_Pin,100, 0)) tone(buzz_pin,0,Q);
   if (Button(HET_key_Pin,100, 0)) delay(Q);
   if (Button(HET_key_Pin,100, 0)) tone(buzz_pin,E6,5*Q/16); 
    
   if (Button(HET_key_Pin,100, 0))  delay(5*Q/16);//delay duration should always be 1 ms more than the note in order to separate them.
   if (Button(HET_key_Pin,100, 0)) tone(buzz_pin,0,S/2); 
    
   if (Button(HET_key_Pin,100, 0))  delay(S/2);
   if (Button(HET_key_Pin,100, 0)) tone(buzz_pin,E6,S); 
   if (Button(HET_key_Pin,100, 0))  delay(S);
   if (Button(HET_key_Pin,100, 0)) tone(buzz_pin,0,W);
   if (Button(HET_key_Pin,100, 0)) delay(W);    
   
}

void Buzzer_During_Heating() {
  
  //tone(pin, note, duration)
    tone(buzz_pin,0,Q);
    delay(Q);
    tone(buzz_pin,E6,5*Q/16); 
    
    delay(5*Q/16);//delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,0,S/2); 
    
    delay(S/2);
    tone(buzz_pin,E6,S); 
    delay(S);
    tone(buzz_pin,0,W);
    delay(W);    
   
}

void Buzzer_3door() {
  
  //tone(pin, note, duration)
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,D4,E);
   if (Button(HET_key_Pin,100, 1))  delay(E);
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,LA4,E); 
    
   if (Button(HET_key_Pin,100, 1))  delay(E);//delay duration should always be 1 ms more than the note in order to separate them.
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,D5,E);
   if (Button(HET_key_Pin,100, 1))  delay(E);
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,E5,E2);
   if (Button(HET_key_Pin,100, 1))  delay(E2);
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,0,S);
//   if (Button(HET_key_Pin,100, 1))  delay(S);
//   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,E5,Q);
//   if (Button(HET_key_Pin,100, 1))  delay(Q);
//   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,0,S);
//   if (Button(HET_key_Pin,100, 1))  delay(S);
    
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,E5,E);
   if (Button(HET_key_Pin,100, 1))  delay(E);
   if (Button(HET_key_Pin,100, 1))  tone(buzz_pin,F5,Q);
   if (Button(HET_key_Pin,100, 1))  delay(Q);
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,E5,E);
   if (Button(HET_key_Pin,100, 1))  delay(E);
   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,0,S);
//   if (Button(HET_key_Pin,100, 1))  delay(S);
//   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,E5,E);
//   if (Button(HET_key_Pin,100, 1))  delay(E);
//   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,G5,E);
//   if (Button(HET_key_Pin,100, 1))  delay(E);
//   if (Button(HET_key_Pin,100, 1)) tone(buzz_pin,F5,E);
//   if (Button(HET_key_Pin,100, 1))  delay(E);

//    tone(buzz_pin,E5,E);
//    delay(E);
//    tone(buzz_pin,D5,E);
//    delay(E);
//    tone(buzz_pin,LA3,E);
//    delay(E);
//    tone(buzz_pin,E4,E);
//    delay(E);
//    tone(buzz_pin,LA4,E);
//    delay(E);
//    tone(buzz_pin,0,S);
//    delay(S);
//    tone(buzz_pin,LA4,E);
//    delay(E);
//    tone(buzz_pin,C4,Q);
//    delay(Q);

//    tone(buzz_pin,LA4,Q);
//    delay(Q);
//    tone(buzz_pin,LA5,Q);
//    delay(Q);
//    tone(buzz_pin,C5,Q);
//    delay(Q);
//    tone(buzz_pin,G5,Q);
//    delay(Q);
//    tone(buzz_pin,C5,Q);
//    delay(Q);
//    tone(buzz_pin,F5,Q);
//    delay(Q);
//    tone(buzz_pin,C5,Q);
//    delay(Q);
//    
//    tone(buzz_pin,E5,Q);
//    delay(Q);
//    tone(buzz_pin,C5,Q);
//    delay(Q);
    if (Button(HET_key_Pin,100, 1))  tone(buzz_pin,0,2*Q);
    if (Button(HET_key_Pin,100, 1))  delay(2*Q);
    
}
void Buzzer_CRUPTED() {

   //tone(pin, note, duration)
    tone(buzz_pin,0,2*Q);
    delay(2*Q);
    tone(buzz_pin,E4,E2); 
    
    delay(E2);//delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,E4,Q2);
    delay(Q2);
    
    tone(buzz_pin,E4,E);
    delay(E);
    tone(buzz_pin,F4,Q);
    delay(Q);
    tone(buzz_pin,E4,Q);
    delay(Q);
    tone(buzz_pin,E4,S);
    delay(S);
    tone(buzz_pin,0,S);
    delay(S);
    tone(buzz_pin,E4,Q);
    delay(Q);
    tone(buzz_pin,F4,E);
    delay(E);
    tone(buzz_pin,F4,E);
    delay(E);
    tone(buzz_pin,0,E);
    delay(E);
    tone(buzz_pin,0,Q);
    delay(Q);
    tone(buzz_pin,C4,E2);
    delay(E2);
    tone(buzz_pin,C4,E2);
    delay(E2);
    tone(buzz_pin,C4,E2);
    delay(E2);
    
    
}
void Buzzer_papion() {
    //tone(pin, note, duration)
    tone(buzz_pin,D4,E); 
    
    delay(E);//delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,E4,E);
    //delay(E);
    delay(E);
    tone(buzz_pin,F4,E);
    delay(E);
    tone(buzz_pin,F4,Q);
    delay(Q);
    tone(buzz_pin,E4,S); 
    delay(S); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,D4,S);
    delay(S);
    tone(buzz_pin,F4,Q2);
    delay(Q2);
    tone(buzz_pin,LA4,E);
    delay(E);
    tone(buzz_pin,E4,E); 
    delay(E); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,D4,E);
    delay(E);
    
    tone(buzz_pin,E4,E);
    delay(E); 
    tone(buzz_pin,LA3,E); 
    delay(E); //delay duration should always be 1 ms more than the note in order to separate them.
    //tone(buzz_pin,C4,E);
    //delay(1);
    tone(buzz_pin,Db4,E);
    delay(E);
    tone(buzz_pin,E4,Q2);
    delay(Q2);
    tone(buzz_pin,F4,E);
    delay(E);
    tone(buzz_pin,E4,E);
    delay(E);
    
    tone(buzz_pin,Db4,Q2);
    delay(Q2);
    //tone(buzz_pin,0,E);
//    delay(E);
//     tone(buzz_pin,G4,E);
//    delay(E);
//     tone(buzz_pin,LA4,E);
//     delay(E);
     
//     tone(buzz_pin,B4,Q2);
//    delay(Q2);
//    tone(buzz_pin,G4,E);
//    delay(E);
//    tone(buzz_pin,F4,E);
//    delay(E);
//    tone(buzz_pin,E4,E);
//    delay(E);
//    
//    tone(buzz_pin,LA4,Q2);
//    delay(Q2);
//    tone(buzz_pin,F4,E);
//    delay(E);
//    tone(buzz_pin,D4,E);
//    delay(E);
//    tone(buzz_pin,F4,E);
//    delay(E);
//    
//    tone(buzz_pin,G4,Q2);
//    delay(Q2);
//    tone(buzz_pin,G4,E);
//    delay(E);
//    tone(buzz_pin,B4,E);
//    delay(E);
//    tone(buzz_pin,LA4,E);
//    delay(E);
//
//    tone(buzz_pin,F4,Q);
//    delay(Q);
//    tone(buzz_pin,D4,E);
//    delay(E);
//     tone(buzz_pin,Gb4,E);
//    delay(E);
//     tone(buzz_pin,G4,E);
//    delay(E);
//    tone(buzz_pin,LA4,E);
//    delay(E);
//
//    tone(buzz_pin,B4,Q2);
//    delay(Q2);
//    tone(buzz_pin,C5,E);
//    delay(E);
//    tone(buzz_pin,B4,3*Q/2);
//    delay(3*Q/2);
//    tone(buzz_pin,E4,E);
//    delay(E);
//    tone(buzz_pin,G4,Q);
//    delay(Q);
    
    //delay(1000);
   
}


void Buzzer2() {
   //tone(pin, note, duration)
   tone(buzz_pin,LA3,2*Q); 
    
    delay(1+E);//delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,C4,2*Q);
//    delay(1+E);
    delay(1+E);
    tone(buzz_pin,E4,2*Q);
    delay(1+E);
    tone(buzz_pin,F4,2*Q);
    delay(1+E);
    tone(buzz_pin,E4,2*Q); 
    delay(1+E); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,E4,2*Q);
    delay(1+E);
    tone(buzz_pin,G4,2*Q);
    delay(1+E);
    tone(buzz_pin,F4,2*Q);
    delay(1+E); 
    tone(buzz_pin,E4,2*Q); 
    delay(1+E); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(buzz_pin,D4,2*Q);
    delay(1+E);
    
    tone(buzz_pin,C4,2*Q);
    delay(1+E); 
    tone(buzz_pin,B3,2*Q); 
    delay(1+E); //delay duration should always be 1 ms more than the note in order to separate them.
    //tone(buzz_pin,C4,2*E);
    //delay(1);
    tone(buzz_pin,0,2*E);
    delay(1+E);
    
    delay(1000);
   
}

void IR_Sensor(){
//  state1=1;oldstate_3 = 0;i=0;lcd.clear(); 
//   lcd.setCursor(0,0);
//        lcd.print("Max Temp:");lcd.print(" ");
//        lcd.setCursor(10,1);
////        lcd.print(":");
//        lcd.setCursor(10,1);
//        lcd.print("    ");
//        lcd.setCursor(10,1);
//        lcd.print(IR_Temp_Treshhold);
//  while (state1==1){
//  if (Button(UP_SW_Pin,swich_time2, 1)) {
//      oldstate_3 = 1; i=1;k_wile=0 ;                  // Update flag
//   while(k_wile==0){
//        if (Button(UP_SW_Pin,300, 1)) {
//         i=i+1;
//          if (i>=5) {
//            i=5;
//              }
//        }
//        IR_Temp_Treshhold=IR_Temp_Treshhold+i;
//            if (IR_Temp_Treshhold>150){
//                IR_Temp_Treshhold=0;
//               
//                }
//          
//           
//            
//            
//         lcd.setCursor(0,0);
//        lcd.print("Max Temp:");lcd.print(" ");
//        lcd.setCursor(10,1);
////        lcd.print(":");
//        lcd.setCursor(10,1);
//        lcd.print("    ");
//        lcd.setCursor(10,1);
//        lcd.print(IR_Temp_Treshhold);
//            if ((oldstate_3==1) &&( Button(UP_SW_Pin, swich_time2, 0))) {
//          k_wile=1;oldstate_3=0;i=1;
//        }
//        }  
//   
// 
//   }   
//    if (Button(DW_SW_Pin,swich_time2, 1)) {
////      oldstate_3 = 1;                     // Update flag
//    
//        oldstate_3 = 1; i=1;k_wile=0 ;                  // Update flag
//   while(k_wile==0){
//        if (Button(DW_SW_Pin,300, 1)) {
//         i=i+1;
//          if (i>=5) {
//            i=5;
//        }}
//        IR_Temp_Treshhold=IR_Temp_Treshhold-i;
//        if (IR_Temp_Treshhold<0){
//                IR_Temp_Treshhold=150;
//                
//               }
//        lcd.setCursor(0,0);
//        lcd.print("Max Temp:");lcd.print(" ");
//        lcd.setCursor(10,1);
////        lcd.print(":");
//        lcd.setCursor(10,1);
//        lcd.print("    ");
//        lcd.setCursor(10,1);
//        lcd.print(IR_Temp_Treshhold);
//            if ((oldstate_3==1) &&( Button(DW_SW_Pin, swich_time2, 0))) {
//          k_wile=1;oldstate_3=0;i=1;
//        }
//        }
//    }
//   if (Button(OK_SW_Pin,swich_time2, 1)) 
//    {
//      oldstate_3 = 1; tone(buzz_pin,C5,S);                    // Update flag
//    }
//   if ((oldstate_3==1) && Button(OK_SW_Pin, swich_time2, 0)) {
//       digitalWrite(ledPin, LOW);  // turn LED ON
//      i=i+1; oldstate_3 = 0;
//     if (i>=2) { address=1;lcd.clear(); lcd.setCursor(0,0); lcd.print("Saving ...");
////          EEPROM.write(address+1,Heater_alarmSecond_end);
////          EEPROM.write(address+2,Heater_alarmMinutes_end);
//          EEPROM.write(address+5,IR_Temp_Treshhold);
//          
//          lcd.clear();  k_wile=0;state1=0;state=0;oldstate_3=0;startTime = millis();
//          while(state==0){
//           lcd.setCursor(0,0); lcd.print("Control Heater ");
//          lcd.setCursor(0,1); lcd.print("by Temp:");lcd.setCursor(9,1); lcd.print(" Yes|No");
//          
//          if  (millis()-startTime>100){
//            startTime = millis();
//          if (temp_situation==0){
//             lcd.setCursor(9,1); lcd.print("    |No"); 
//          }
//          else
//          {
//             lcd.setCursor(9,1); lcd.print(" Yes|  ");
//          }
//          }
//          if (Button(DW_SW_Pin,swich_time2, 1)) {
//              oldstate_3 = 1; temp_situation=not (temp_situation);
//          }
//          if ((oldstate_3==1) &&( Button(DW_SW_Pin, swich_time2, 0))) {
//          oldstate_3=0;
//        }
//
//        if (Button(UP_SW_Pin,swich_time2, 1)) {
//              oldstate_3 = 1; temp_situation=not (temp_situation);
//          }
//          if ((oldstate_3==1) &&( Button(UP_SW_Pin, swich_time2, 0))) {
//          oldstate_3=0;
//       
//       }
//       if (Button(OK_SW_Pin,swich_time2, 1)) 
//         {
//          k_wile = 1;                    // Update flag
//         }
//       if ((k_wile==1) && Button(OK_SW_Pin, swich_time2, 0)) {
//          k_wile=0;state=1;EEPROM.write(address+6,temp_situation);
//       }
//       }
//       
//   }
//
//    }
//}
}
void loop() {
  int val = 0;
//  delay(1000);lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("   TO  ");
//  lcd.print(TO);
  tt=0;
  state1=0;
  state2 = 0;
  if (tt==0)  {lcd.setCursor(0,0); lcd.print("Ready for work"); tt=1;}
  if (Button(OK_SW_Pin,swich_time, 1)) {
      state2 = 1;state1=2;                     // Update flag
      digitalWrite(ledPin, HIGH);  // turn LED OFF
//      lcd.clear();lcd.setCursor(0,0); lcd.print("sd for work");delay(1000);
      oldstate_3 = 1; i=1;k_wile=0 ;                   // Update flag
      while(k_wile==0){
      if (Button(OK_SW_Pin,1000, 1)) {
//         lcd.clear();lcd.setCursor(0,0); lcd.print("while");delay(300);
         IR_Sensor(); state1=3;
      }
      
   if ((state2==1) &&( Button(OK_SW_Pin, swich_time, 0))) {
//       lcd.clear();lcd.setCursor(0,0); lcd.print("d for work");digitalWrite(ledPin, LOW);  // turn LED ON
       state2 = 0; k_wile=1;
       
       }
     }
   }
    if (state1==2){
      mlx90615();//IR_Sensor(); 
      start();
      state1=0;
    }
    state=0;
    if (Button(UP_SW_Pin,swich_time2, 1)){
     state1=11; lcd.clear();lcd.setCursor(0,0); lcd.print("Heater setting");
        lcd.setCursor(0,1);
        lcd.print(Motor_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Motor_alarmSecond_end);
    }

    if (Button(DW_SW_Pin,swich_time2, 1)){
     state1=22; lcd.clear();lcd.setCursor(0,0); lcd.print("Motor setting");
        lcd.setCursor(0,1);
        lcd.print(Heater_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Heater_alarmSecond_end);
    }
    oldstate_3 = 0;k_wile=1 ;
    while (state1==22){
   if (Button(UP_SW_Pin,swich_time2, 1)) {
      oldstate_3 = 1; i=1;k_wile=0 ;                   // Update flag
   while(k_wile==0){
        if (Button(UP_SW_Pin,300, 1)) {
         i=i+1;
          if (i>=5) {
            i=5;
        }}
        Motor_alarmSecond_end=Motor_alarmSecond_end+i;
            if (Motor_alarmSecond_end>59){
                Motor_alarmSecond_end=0;
                Motor_alarmMinutes_end=Motor_alarmMinutes_end+1;
                if (Motor_alarmMinutes_end>=11){
                    Motor_alarmMinutes_end=0;
                     }
                }
          
           
            
            
         lcd.setCursor(0,1);
        lcd.print(Motor_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Motor_alarmSecond_end);
            if ((oldstate_3==1) &&( Button(UP_SW_Pin, swich_time2, 0))) {
          k_wile=1;oldstate_3=0;i=1;
        }
        }  
   
 
   }   
    if (Button(DW_SW_Pin,swich_time2, 1)) {
//      oldstate_3 = 1;                     // Update flag
    
        oldstate_3 = 1; i=1;k_wile=0 ;                   // Update flag
   while(k_wile==0){
        if (Button(DW_SW_Pin,300, 1)) {
         i=i+1;
          if (i>=5) {
            i=5;
        }}
        Motor_alarmSecond_end=Motor_alarmSecond_end-i;
        if (Motor_alarmSecond_end<0){
                Motor_alarmSecond_end=59;
                Motor_alarmMinutes_end=Motor_alarmMinutes_end-1;
                if (Motor_alarmMinutes_end<0){
                    Motor_alarmMinutes_end=10;}
               }
         
           
         lcd.setCursor(0,1);
        lcd.print(Motor_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Motor_alarmSecond_end);
            if ((oldstate_3==1) &&( Button(DW_SW_Pin, swich_time2, 0))) {
          k_wile=1;oldstate_3=0;i=1;
        }
        }
    }
    
   if (Button(OK_SW_Pin,swich_time2, 1)) 
    {
      oldstate_3 = 1;                     // Update flag
    }
   if ((oldstate_3==1) && Button(OK_SW_Pin, swich_time2, 0)) {
       digitalWrite(ledPin, LOW);  // turn LED ON
       oldstate_3 = 0;state1=0;lcd.clear(); lcd.setCursor(0,0); lcd.print("Saving ...");
       address=1;
//          EEPROM.write(address+1,Heater_alarmSecond_end);
//          EEPROM.write(address+2,Heater_alarmMinutes_end);
          EEPROM.write(address+3,Motor_alarmSecond_end);
          EEPROM.write(address+4,Motor_alarmMinutes_end);
          lcd.clear();  
       }
    
    }

 oldstate_3 = 0;
 while (state1==11){
   if (Button(UP_SW_Pin,swich_time2, 1)) {
      oldstate_3 = 1; i=1;k_wile=0 ;                   // Update flag
   while(k_wile==0){
        if (Button(UP_SW_Pin,300, 1)) {
         i=i+1;
          if (i>=5) {
            i=5;
        }}
        Heater_alarmSecond_end=Heater_alarmSecond_end+i;
            if (Heater_alarmSecond_end>59){
                Heater_alarmSecond_end=0;
                Heater_alarmMinutes_end=Heater_alarmMinutes_end+1;
                if (Heater_alarmMinutes_end>=11){
                    Heater_alarmMinutes_end=0;
                     }
                }
          
         lcd.setCursor(0,1);
        lcd.print(Heater_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Heater_alarmSecond_end);
            if ((oldstate_3==1) &&( Button(UP_SW_Pin, swich_time2, 0))) {
          k_wile=1;oldstate_3=0;i=1;
        }
        }  
   
 
   }   
    if (Button(DW_SW_Pin,swich_time2, 1)) {
//      oldstate_3 = 1;                     // Update flag
    
        oldstate_3 = 1; i=1;k_wile=0 ;                   // Update flag
   while(k_wile==0){
        if (Button(DW_SW_Pin,300, 1)) {
         i=i+1;
          if (i>=5) {
            i=5;
        }}
        Heater_alarmSecond_end=Heater_alarmSecond_end-i;
        if (Heater_alarmSecond_end<0){
                Heater_alarmSecond_end=59;
                Heater_alarmMinutes_end=Heater_alarmMinutes_end-1;
                if (Heater_alarmMinutes_end<0){
                    Heater_alarmMinutes_end=10;}
               }
         
           
         lcd.setCursor(0,1);
        lcd.print(Heater_alarmMinutes_end);lcd.print(" ");
        lcd.setCursor(3,1);
        lcd.print(":");
        lcd.setCursor(5,1);
        lcd.print("  ");
        lcd.setCursor(5,1);
        lcd.print(Heater_alarmSecond_end);
            if ((oldstate_3==1) &&( Button(DW_SW_Pin, swich_time2, 0))) {
          k_wile=1;oldstate_3=0;i=1;
        }
        }
     
    } 
       
   
   if (Button(OK_SW_Pin,swich_time2, 1)) 
    {
      oldstate_3 = 1;                     // Update flag
    }
   if ((oldstate_3==1) && Button(OK_SW_Pin, swich_time2, 0)) {
       digitalWrite(ledPin, LOW);  // turn LED ON
       oldstate_3 = 0;state1=0;lcd.clear(); lcd.setCursor(0,0); lcd.print("Saving ...");
       address=1;
          EEPROM.write(address+1,Heater_alarmSecond_end);
          EEPROM.write(address+2,Heater_alarmMinutes_end);
//          EEPROM.write(address+3,Heater_alarmSecond_end);
//          EEPROM.write(address+4,Motor_alarmMinutes_end);
          lcd.clear();  
       }
    
    }

    
//    oldstate_3 = 0;
//    while (state1==11){
//   
//   if (Button(UP_SW_Pin,swich_time2, 1)) {
////      oldstate_3 = 1;                     // Update flag
//      if (Heater_alarmSecond_end==59){
//                Heater_alarmSecond_end=0;
//                if (Heater_alarmMinutes_end==10){
//                    Heater_alarmMinutes_end=0;
//                }
//                else {
//                      Heater_alarmMinutes_end=Heater_alarmMinutes_end+1;
//                }
//                }
//          else {
//            Heater_alarmSecond_end=Heater_alarmSecond_end+1;
//            }
//
//       
//        }    
//    if (Button(DW_SW_Pin,swich_time2, 1)) {
////      oldstate_3 = 1;                     // Update flag
//    if (Heater_alarmSecond_end==0){
//                Heater_alarmSecond_end=59;
//                if (Heater_alarmMinutes_end==0){
//                    Heater_alarmMinutes_end=10;}
//                else {
//                      Heater_alarmMinutes_end=Heater_alarmMinutes_end-1;
//                }
//                }
//          else {
//            Heater_alarmSecond_end=Heater_alarmSecond_end-1;
//            }
//           }
//       
//        lcd.setCursor(0,1);
//        lcd.print(Heater_alarmMinutes_end);
//        lcd.setCursor(3,1);
//        lcd.print(":");
//        lcd.setCursor(5,1);
//        lcd.print("  ");
//        lcd.setCursor(5,1);
//        lcd.print(Heater_alarmSecond_end);
//   
//   if (Button(OK_SW_Pin,swich_time2, 1)) {
//      oldstate_3 = 1;                     // Update flag
//   }
//   if ((oldstate_3==1) && Button(OK_SW_Pin, swich_time2, 0)) {
//       digitalWrite(ledPin, LOW);  // turn LED ON
//       oldstate_3 = 0;state1=0;lcd.clear(); lcd.setCursor(0,0); lcd.print("Saving ...");
//       address=1;
//          EEPROM.write(address+1,Heater_alarmSecond_end);
//          EEPROM.write(address+2,Heater_alarmMinutes_end);
//          lcd.clear(); 
//           
//       }
//    
//    }
//      val = digitalRead(HET_SW_Pin);  // read input value
//  if (val == HIGH) {         // check if the input is HIGH (button released)
//    digitalWrite(ledPin, LOW);  // turn LED OFF
//  } else {
//    digitalWrite(ledPin, HIGH);  // turn LED ON
//  }
}

void mlx90615(){
//  char i=0,sum=0;
//  serialEvent();
//  if(sign)
//  {
//     sign=0;
//     for(i=0;i<8;i++)
//      sum+=Re_buf[i];
//     if(sum==Re_buf[i] )
//     {
//           TO=(float)(Re_buf[4]<<8|Re_buf[5])/100;
////           Serial.print("TO:");
////           Serial.println(TO);
//           lcd.setCursor(1,1);
//           lcd.print("   TO  ");
//           lcd.print(TO);
//           TA=(float)(Re_buf[6]<<8|Re_buf[7])/100;
////           Serial.print("TA:");
////           Serial.println(TA);
//
//           lcd.setCursor(0,1);
//           lcd.print("   TA  ");
//           lcd.print(TA);
//           delay(300);
//   }
//  }
 
}
void serialEvent(){ 
  while (Serial.available()) {
    Re_buf[counter]=(unsigned char)Serial.read();
    if(counter==0&&Re_buf[0]!=0x5A) return;
    counter++;
    if(counter==9)
    {
       counter=0;
       sign=1;
    }
  }
}
