void readButtons(){

  //Loop through and read all 16 values
  for(int i = 0; i < 16; i ++){
    int x = readMux(i);
    if(!x && !pinState[i]){
      if(x == readMux(i)){ // rereading the MUX here prevents cross-talk 
        lcdLine2();
        printLCD("S: ");
        printLCD(i);
        printLCD("|");
        printLCD(led[i]);
        // high and low kill buttons & play buttons 
        // simple, always send "on" command, store button status in but[] array
        //if(i<4||i==6||i==9||i==12||i==15){ 
          usbMIDI.sendNoteOn(i+60,127, channel);
        //}
        /*
        if(!but[i]){
          //but[i] = true;
          //shiftVal += led[i];
          usbMIDI.sendNoteOn(i+60,127, channel);
        }else{
          //but[i] = false;
          //shiftVal -= led[i];
          usbMIDI.sendNoteOff(i+60,0, channel);
        }*/
        pinState[i] = 1;
      }
    }else if(x && pinState[i]){
      pinState[i] = 0;
    }
  }

}


int readMux(int channel){

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = digitalRead(SIG_pin);

  //return the value
  return val;
}
