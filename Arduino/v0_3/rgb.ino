void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  /*
  lcdLine2();
  rgbData = red + space + green + space + blue + space + space + space + space;
  printLCD(rgbData);
  */
} 

void cycleColor()
{
  if(rd==1){
    r++;
    b--;
    if(r==256) rd = 2;
  }else if(rd==2){
    r--;
    g++;
    if(g==256) rd = 3;
  }else if(rd==3){
    g--;
    b++;
    if(b==256) rd = 1;
  }
}
