void readKnobs(){
  for(int i=0;i<4;i++){
    int x = analogRead(i);
    if(abs(pots[i]- x) > 5){
      usbMIDI.sendControlChange(i+50,map(abs(x/8),1,126,126,1),channel);
      pots[i] = x;
    }
  }
}

void OnNoteOn(byte channel, byte note, byte velocity){
  
  int i = note - 60;
  if(ledState[i] == 0){ 
    shiftVal += led[i];
    ledState[i] = 1;
  } 

}

void OnNoteOff(byte channel, byte note, byte velocity){
  
  int i = note - 60;
  if(ledState[i] == 1){ 
    shiftVal -= led[i];
    ledState[i] = 0;
  }
 
}
