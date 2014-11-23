void readButtons(){
  //Loop through and read all 16 values using bounce
  for(int i = 0; i < 16; i++){
    pinState[i] = readMux(i);
    //double reed to prevent crosstalk & set timer
    if(pinState[i] == readMux(i) && pinState[i] == readMux(i)){
      // has the state changed since last time?
      if(pinState[i] != pinStateHold[i]){ 
        if(!pinState[i]){
          usbMIDI.sendNoteOn(i+60, 127, channel);
         }else{
          usbMIDI.sendNoteOn(i+60, 0, channel);
        }
        pinStateHold[i] = pinState[i];
      }
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
