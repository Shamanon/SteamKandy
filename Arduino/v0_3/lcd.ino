// clear the LCD
void lcdClear(){
  Serial3.print("$GO 1 1\r\n");
  Serial3.print("$CLEAR\r\n");
}


// move the cursor to the home position
void lcdHome(){
  Serial3.print("$GO 1 1\r\n");
}

// move the cursor to a specific place
// e.g.: cursorSet(3,2) sets the cursor to x = 3 and y = 2
void cursorSet(int ypos, int xpos){     
  Serial3.print("$GO ");
  Serial3.print(String(ypos));
  Serial3.print(" ");
  Serial3.print(String(xpos));
  Serial3.print("\r\n"); //Row position 
}

void lcdLine2(){
  Serial3.print("$GO 2 0\r\n");
}

void printLCD(String text){
  Serial3.print("$PRINT ");
  Serial3.print(text);
  Serial3.print("\r\n");
}
