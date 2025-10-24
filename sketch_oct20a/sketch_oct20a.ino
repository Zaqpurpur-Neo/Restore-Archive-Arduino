#include "SevSeg.h"
#include "string.h"
SevSeg sevseg; 

const char* name = "aku";
int size = 0;

void setup(){
  size = strlen(name);
  byte numDigits = 1;
  byte digitPins[] = {};
  byte segmentPins[] = {6, 5, 2, 3, 4, 7, 8, 9};
  bool resistorsOnSegments = true;

  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

int count = 0;
void loop(){
  if(count >= size) count = 0;

  char temp[2] = {name[count], '\0'};
  sevseg.setChars(temp);
  sevseg.refreshDisplay();

  delay(500);

  sevseg.setChars("");
  sevseg.refreshDisplay();

  delay(500);
  count++;
}