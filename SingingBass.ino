
#define BUFFERSIZE 100
int sensorPin = A0;    // select the input pin for the potentiometer
int buzzerPin = 8;      // select the pin for the LED
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

    tone(buzzerPin, 440, 100);

    for(int i=0; i<BUFFERSIZE; i++)
    {
      lightHistory[i] = lightLevel;
    }
  }

  lightHistory[loopNum%BUFFERSIZE - 1] = lightLevel;




  loopNum++;

  delay(100);
}


