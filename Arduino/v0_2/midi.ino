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
  shiftVal += led[i];
  
  
  /*
  if(but[i]){
    but[i] = false;
    shiftVal -= led[i];
  }else{
    but[i] = true;
    shiftVal += led[i];
  }
  */
  //lcdLine2();
  printLCD(note);
  printLCD(" on|");
  

}

void OnNoteOff(byte channel, byte note, byte velocity){
  int i = note - 60;
  shiftVal -= led[i];
  
  printLCD(note);
  printLCD(" off|");
  /*
  lcdHome();
  printLCD("Recd OFF: ");
  printLCD(channel);
  printLCD(" | ");
  printLCD(note);
  printLCD(" | ");
  printLCD(velocity);
  */
}
