
#include "pitches.h"

#define BUFFERSIZE 300
#define WHOLENOTE 900


// notes in the melody:
int melody[] = {NOTE_G5, NOTE_FS5, NOTE_DS5, NOTE_A5, NOTE_GS4, NOTE_E5, NOTE_GS5, NOTE_C6};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {8,8,8,8,8,8,8,8};


int sensorPin = A0;    // select the input pin for the potentiometer
int buzzerPin = 12;      // select the pin for the LED
double lightLevel = 0;  // variable to store the value coming from the sensor
double lightHistory[BUFFERSIZE];
int loopNum = 1;
double lightAverage = 0;

void setup() 
{
  pinMode(buzzerPin, OUTPUT);  
  for(int i=0; i<BUFFERSIZE; i++)
  {
    lightHistory[i] = analogRead(sensorPin);
  }
  // Serial.begin(9600);
}

void loop() 
{
  // read in the light level
  lightLevel = analogRead(sensorPin);
  // done reading


  // compute the average of the light level history
  lightAverage = 0;
  for(int i=0; i<BUFFERSIZE; i++)
  {
    lightAverage = lightAverage+lightHistory[i];
  }
  lightAverage = lightAverage/BUFFERSIZE;
  // done computing average


  // check for large difference in level
  if(lightLevel < lightAverage*0.7 || lightLevel > lightAverage*1.3)
  {
    for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take whole note 
    // divided by the note type.
    int noteDuration = WHOLENOTE/noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.10;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  
    // int a = millis();
    for(int i=0; i<BUFFERSIZE; i++)
    {
      lightHistory[i] = analogRead(sensorPin);
    }
    // int b = millis();
    // Serial.println(b-a);
  }
  

  



  lightHistory[loopNum%BUFFERSIZE - 1] = lightLevel;



// keep track of which loop number it's on
  loopNum++;

// wait
  delay(200);
}


