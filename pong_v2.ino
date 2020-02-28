#include "LedControl.h"   //include the library ledcontrol from this site : https://github.com/wayoda/LedControl


//CREDITS  




/* 

  https://howtomechatronics.com/tutorials/arduino/8x8-led-matrix-max7219-tutorial-scrolling-text-android-control-via-bluetooth/
  by Dejan Nedelkovski, www.HowToMechatronics.com

  https://labs.bsoares.com/ping-pong-com-matriz-de-leds-8x8-ee13cce39007
  @author Bruno Soares

  https://randomnerdtutorials.com/guide-for-8x8-dot-matrix-max7219-with-arduino-pong-game/
  Play pong on an 8x8 matrix - project from itopen.it

  Take on me
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
  Robson Couto, 2019
*/

LedControl lc=LedControl(12,11,10,2);
unsigned long delaytime=500;


const int leftJoy= 4;
const int rightJoy= 5;
int leftracket = 3;
int rightracket = 3;
int data = 500;
int data2 = 500;
int scoreleft =0;
int scoreright = 0;
int x = 1;
byte rightscore;
byte leftscore;

int xball;
int yball;
int angle = 180;
int racketheight=2;



int screen=0;
byte smile01[] = {    //happy
    B00111100,
    B01000010,
    B10010101,
    B10100001,
    B10100001,
    B10010101,
    B01000010,
    B00111100
  };
byte smile02[] = {    //neutral
    B00111100,
    B01000010,
    B10010101,
    B10010001,
    B10010001,
    B10010101,
    B01000010,
    B00111100
  };
byte smile03[] = {    //sad
    B00111100,
    B01000010,
    B10100101,
    B10010001,
    B10010001,
    B10100101,
    B01000010,
    B00111100
  };
byte zero[]={      // Used to display a '0' for when displaying the score
  B00000000,
  B00000000,
  B00111100,
  B01000010,
  B01000010,
  B01000010,
  B00111100,
  B00000000  
   };
 byte one[]={       // Used to display a '1' for when displaying the score
  B00000000,
  B00000000,
  B10001000,
  B10000100,
  B11111110,
  B10000000,
  B10000000,
  B00000000
 };
 byte two[]={        // Used to display a '2' for when displaying the score
  B00000000,
  B01100010,
  B01010001,
  B01010001,
  B01001001,
  B01000110,
  B00000000,
  B00000000
};
byte three[]={      // Used to display a '3' for when displaying the score
  B00000000,
  B00100110,
  B01000001,
  B01001001,
  B00110110,
  B00000000,
  B00000000,
  B00000000
};
byte four[]={        // Used to diplay a '4' for when displaying the score
  B00000000,
  B00000000,
  B00001111,
  B00001000,
  B00001000,
  B11111111,
  B00000000,
  B00000000
};
byte five[]={        // Used to diplay a '5' for when displaying the score
  B00000000,
  B00100111,
  B00100101,
  B00011001,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 140;

// change this to whichever pin you want to use
int buzzer = 2;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Take on me, by A-ha
  // Score available at https://musescore.com/user/190926/scores/181370
  // Arranged by Edward Truong

  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  NOTE_FS5,8, NOTE_FS5,8,NOTE_D5,8, NOTE_B4,8, REST,8, NOTE_B4,8, REST,8, NOTE_E5,8, 
  REST,8, NOTE_E5,8, REST,8, NOTE_E5,8, NOTE_GS5,8, NOTE_GS5,8, NOTE_A5,8, NOTE_B5,8,
  
  NOTE_A5,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, REST,8, NOTE_D5,8, REST,8, NOTE_FS5,8, 
  REST,8, NOTE_FS5,8, REST,8, NOTE_FS5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8,
  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setSprite(byte *sprite){     //used todisplay all the rows correctly when calling score
    
    for(int r = 0; r < 16; r++){
        lc.setRow(screen, r, sprite[r]);
    }
}
void marioStart(){
  tone(2,660,100);
  delay(150);
  tone(2,660,100);
  delay(300);
  tone(2,510,100);
  delay(100);
  tone(2,660,100);
  delay(300);
  tone(2,770,100);
  delay(550);
  noTone(2);
}
void start(){
  marioStart();
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  setSprite(three);
  tone(2,600,400);
  delay(600);
  screen = 1;
  setSprite(two);
  tone(2,600,400);
  lc.clearDisplay(0);
  delay(600);
  lc.clearDisplay(1);
  screen = 0;
  setSprite(one);
  tone(2,600,400);
  delay(600);
  screen = 1;
  setSprite(zero);
  tone(2,800,400);
  lc.clearDisplay(0);
  delay(600);
  lc.clearDisplay(1);
  
}

void ballPosition(){      //moving the ball in x,y
  if (xball<=7){
    lc.setLed(0,xball,yball,true);
  delay(125);
  lc.setLed(0,xball,yball,false);
  }
  else if (xball>7){
    lc.setLed(1,xball-8,yball,true);
  delay(125);
  lc.setLed(1,xball-8,yball,false);
  }

  
}
void ballStarting(){    //random placement of the ball (4 dots at the center of the matrix)
  yball = rand() % 2+3;
  xball = rand() % 2+7;
  if (xball<=7){
    lc.setLed(0,xball,yball,true);
    delay(125);
    
  }
  else {
    lc.setLed(1,xball-8,yball,true);
    delay(125);
    
  }
  lc.setLed(1,xball-8,yball,false);
  lc.setLed(0,xball,yball,false);
  
  
}
void calcAngleIncrement(){    //it checks the angle of the ball and in function of it it orders to move the ball
  
  if (angle==0 || angle == 360|| angle==-360){
     xball+=1;
  }
  else if (angle == 45|| angle==-315)  {
     xball += 1;
     yball += 1;
  }
  else if (angle == 135|| angle==-225)  {
     xball -= 1;
     yball += 1;
  }
  else if (angle == 180|| angle==-180)  {
     xball -= 1;
  }
  else if (angle == 225|| angle==-135)  {
     xball -= 1;
     yball -= 1;
  }
  else if (angle == 315|| angle==-45)  {
     xball += 1;
     yball -= 1;
  }
  else if (angle == 90|| angle ==-270)  {
     yball += 1;
  }
  else if (angle == 270|| angle == -90)  {
     yball -= 1;
  }
}
void wallCollisons(){   
  
  if(yball==0||yball==7){   //vertical walls
    angle = -1*angle;
  }
  else if(xball<0||xball>15){    //horizontal walls
    tone(2,600,150);
    delay(100);
    tone(2,200,300);
    delay(100);
    noTone(2);
    leftracket = 3;
    rightracket = 3;

    
    if (yball<=0||yball>=15){
      angle = 180;
    }
    if (xball<0){     //rightside wins
      angle = 0;
      scoreright++;
      screen =1;
      switch (scoreright){
        case 0:
          setSprite(zero);
          break;
        case 1:
          setSprite(one);
          break;
        case 2:
          setSprite(two);
          break;
        case 3:
          setSprite(three);
          break;
        case 4:
          setSprite(four);
          break;
        case 5:
          setSprite(five);
          break;
      }
      //delay(2);
      screen = 0;
      switch (scoreleft){
        case 0:
          setSprite(zero);
          break;
        case 1:
          setSprite(one);
          break;
        case 2:
          setSprite(two);
          break;
        case 3:
          setSprite(three);
          break;
        case 4:
          setSprite(four);
          break;
        case 5:
          setSprite(five);
          break;
      }
      delay(1000);
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      ballStarting();
      Rackleft();
      Rackright();
    }
    else if (xball>15){      //leftside wins
      angle = 180;
      scoreleft++;
      screen = 0;
      switch (scoreleft){
        case 0:
          setSprite(zero);
          break;
        case 1:
          setSprite(one);
          break;
        case 2:
          setSprite(two);
          break;
        case 3:
          setSprite(three);
          break;
        case 4:
          setSprite(four);
          break;
        case 5:
          setSprite(five);
          break;
      }
      screen =1;
      switch (scoreright){
        case 0:
          setSprite(zero);
          break;
        case 1:
          setSprite(one);
          break;
        case 2:
          setSprite(two);
          break;
        case 3:
          setSprite(three);
          break;
        case 4:
          setSprite(four);
          break;
        case 5:
          setSprite(five);
          break;
      }
      delay(1000);
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      ballStarting();
      Rackleft();
      Rackright();
    }
    if (scoreleft ==5 || scoreright ==5){   //it means a win
      delay(300);
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      if (scoreleft == 5){
        screen = 0;
        setSprite(smile01);
        screen = 1;
        setSprite(smile03);
      }
      else if(scoreright==5){
        screen = 1;
        setSprite(smile01);
        screen = 0;
        setSprite(smile03);
      }
      takeOnMe();
      delay(2000);
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      setup();
      scoreleft =0;
      scoreright = 0;
    }
    delay(1000);
  }
  if (-360>=angle){     //used to keep the angle between 360 and -360
      angle = 360+angle;
    }
  else if(angle>=360){
    angle = angle-360;
  }  
  
}
void takeOnMe(){
 // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }
}

void Rackleft(){    //moving the left racket with a joystick
  data = analogRead(leftJoy);
  if (data>=600){     //analogRead is between 0 and 1020 stg like that, and 511 is the middle
    if(7>leftracket+1){
      lc.setLed(0,0,leftracket++,false);// turning off the previous led and then turning on the led further
      for (int i =0; i<racketheight;i++){
        lc.setLed(0,0,leftracket+i,true);
        
        }
        
    }
    
  }
  else if (data<= 400){   // doing the same but when moving the joystick the other way
    if(0<leftracket){
      lc.setLed(0,0,1+leftracket--,false);
      
      for (int i =0; i<racketheight;i++){
        
        lc.setLed(0,0,leftracket+i,true);
        
        
        }
        
      }

  }
  else{     //when we still haven't touche the joystick, it will be position at "leftracket pos"
    for (int i =0; i<racketheight;i++){
      lc.setLed(0,0,leftracket+i,true);
    }
    
  }


}
void Rackright(){     //same but for the right racket
  data2 = analogRead(rightJoy);
  if (data2>=600){
    if(7>rightracket+1){
      lc.setLed(1,7,rightracket++,false);
      for (int i =0; i<racketheight;i++){
        lc.setLed(1,7,rightracket+i,true);
        
        }
        delay(2);
    }
    
  }
  else if (data2<= 400){
    if(0<rightracket){
      lc.setLed(1,7,1+rightracket--,false);
      
      for (int i =0; i<racketheight;i++){
        
        lc.setLed(1,7,rightracket+i,true);
        
        
        }
        delay(2);
      }

  }
  else{
    for (int i =0; i<racketheight;i++){
      lc.setLed(1,7,rightracket+i,true);
    }
    delay(2);
  }
 
  
}
void racketCollisions(){
  if (xball ==1){   //collision for leftracket
    if (yball == leftracket+2 && angle == 225 || yball == leftracket+2 && angle == -135 ){    //top left corner
      angle = 45;
    }
    else if (yball == leftracket+1 ){   //collisions for top left
      if ( angle == 225 || angle == -135){
        angle = 0;
      }
      else{
        angle = 45;
      }
    }
    else if(yball == leftracket ){    //bottom
      if(angle==135||angle==-225){
        angle = 0;
      }
      else{
        angle=-45;
      }
    }
    else if (yball == leftracket-1 && angle == 135 || yball == leftracket-1 && angle == -225){ //bottom corner
      angle = -45;
    }
  }
  else if (xball==14){   //collsion for rightracket
    if (yball == rightracket+2 && angle == 315 || yball == rightracket+2 && angle == -45 ){    //top left corner
      angle = 135;
    }
    else if (yball == rightracket+1 ){   //top right
      if ( angle == 315 || angle == -45){
        angle = 180;
      }
      else{
        angle = 135;
      }
    }
    else if(yball == rightracket ){   //bottom right
      if(angle==45||angle==-315){
        angle = 180;
      }
      else{
        angle=-135;
      }
    }
    else if (yball == rightracket-1 && angle == 45 || yball == rightracket-1 && angle == -315){
      angle = 225;    //bottom corner
    }
  }
  
 
  
}


void setup() {
  lc.shutdown(0,false);
  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,4);
  lc.setIntensity(1,4);
  
  start();
  ballStarting();
}

void loop() {
  racketCollisions();
  wallCollisons();
  ballPosition();
  calcAngleIncrement(); 
  Rackleft();
  Rackright();
}

