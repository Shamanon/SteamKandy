void shifty(int data)
{
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, MSBFIRST, (data >> 8));  
  shiftOut(dataPin, clockPin, MSBFIRST, data); 
  digitalWrite(latchPin, HIGH);
}
