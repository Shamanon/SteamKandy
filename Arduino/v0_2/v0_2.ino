
//#include <Bounce.h>

// alpha version of MIDI controller

// potentiometers
int pots[4];

//Mux control pins
int s0 = 0;
int s1 = 1;
int s2 = 2;
int s3 = 3;
int controlPin[] = {s0, s1, s2, s3};

//Mux in "SIG" pin
int SIG_pin = 4;

//pin states for chatter
byte pinState[16];

//byte
int muxChannel[16][4]={
  {0,0,0,0}, //channel 0
  {1,0,0,0}, //channel 1
  {0,1,0,0}, //channel 2
  {1,1,0,0}, //channel 3
  {0,0,1,0}, //channel 4
  {1,0,1,0}, //channel 5
  {0,1,1,0}, //channel 6
  {1,1,1,0}, //channel 7
  {0,0,0,1}, //channel 8
  {1,0,0,1}, //channel 9
  {0,1,0,1}, //channel 10
  {1,1,0,1}, //channel 11
  {0,0,1,1}, //channel 12
  {1,0,1,1}, //channel 13
  {0,1,1,1}, //channel 14
  {1,1,1,1}  //channel 15
};

// LEDS and buttons
int led[16];
byte but[16];

// shift register 74HC595
int latchPin = 6; //ST_CP
int clockPin = 12; //SH_CP
int dataPin = 11; //DS
int shiftVal = 0; //current value of register
int shiftLast = 0; //Last value of register

// RGB
int redPin = 10;
int greenPin = 9;
int bluePin = 5;
String rgbData;
String space = " ";
int r = 0;
int g = 0;
int b = 256;
int rd = 1;

// MIDI
int channel = 1;

void setup()
{
  
    // init serial
  Serial.begin(9600);
  
  //initialize LCD
  Serial3.begin(9600);
  lcdClear();
  delay(10);
  lcdHome();
  delay(10);
  
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  delay(10);

  printLCD("Light Check");
  delay(10);
  
  // set decimal values of LEDs for shifting
  int x = 65536; // number of LED 15 (2^16) to shift register
  shifty(x);
  delay(200);
  for(int i=16;i>-1;i--){
    int y = i;
    pinState[y] = false;
    but[y] = false;
    led[y] = x;
    x = x/2;
    shifty(x);
    delay(200);
  }
  
  lcdLine2();
  printLCD("Setup: *");
  
  // set MUX outputs
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  pinMode(SIG_pin, INPUT_PULLUP);
  printLCD("*");
  delay(1000);
  
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  printLCD("*");
  delay(1000);
  
  // reset shift register
  shifty(shiftVal);
  printLCD("*");
  
  lcdClear();
  lcdHome();
  printLCD("SteamKandy v0.2");
  
  //setup MIDI
  usbMIDI.setHandleNoteOn(OnNoteOn);
}

void loop() 
{ 
  
  readButtons();
  usbMIDI.read();
  
  // light LEDs
  if(shiftVal != shiftLast){
    shifty(shiftVal);
    shiftLast = shiftVal;
  }
  
  // do something with RGB126126
  setColor(map(pots[0]/8,1,126,126,1),map(pots[1]/8,1,126,126,1),map(pots[2]/8,1,126,126,1));
  
  readKnobs();
  
} 
