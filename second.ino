// Foot traffic sound sensor

// libraries
#include <FileIO.h>
#include <Bridge.h>

int soundSensor = A2; //assign to pin A2
 
void setup() 
{
  Bridge.begin();

  FileSystem.begin();

  Serial.begin(9600); //begin Serial Communication
}
 
void loop()
{
  int soundValue = 0; //create variable to store many different readings
  for (int i = 0; i < 32; i++) //create a for loop to read 
  { soundValue += analogRead(soundSensor);  } //read the sound sensor
 
  soundValue >>= 5; //bitshift operation 
  Serial.println(soundValue); //print the value of sound sensor
 
 
//if a value higher than 500 is registered, we will print the following
//this is done so that we can clearly see if the threshold is met
  if (soundValue > 500) { 
    Serial.println("OVER 500");
  

// saves data to .csv file
File dataFile = FileSystem.open("/mnt/sda1/SoundLog.csv", FILE_APPEND); // sda1 / sd
if (dataFile) 
  {
    unsigned long secondsElapsed = millis() / 1000; 
    dataFile.print(secondsElapsed);
    dataFile.print(",");
    dataFile.println(soundValue);
    dataFile.close();
  } 
else 
  {
    Serial.println("Error opening soundlog"); // error message if the file system doesn't work
  } 
  }
  delay(200); //a shorter delay between readings
}
