String currentText[2];

void print(int line, String text){  
  if(currentText[line] != text){
    bool t = false;
     if(text.endsWith("D-C")){
         text.remove(text.length() - 3);
         t = true;
     }
     currentText[line] = text;

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(currentText[0]);
     if(t) { 
       lcd.write(byte(0));
       lcd.write("C");
     }
     lcd.setCursor(0,1);
     lcd.print(currentText[1]);
     //lcd.write(byte(0));
  }
}

void lightColor(int red, int green, int blue){
  analogWrite(redPin,255 - red);
  analogWrite(greenPin,255 - green);
  analogWrite(bluePin,255 - blue);  
}

void writeToEEPROM(int number){
  // a base 256 number system is used to write to the EEPROM, because each EEPROM index can hold 256 values(it is a byte).
  // if the number is smaller than 256  
  if(number < 256){
     // write a 0 at index 0 for safety 
     EEPROM.write(0,0);
     // and write the number at index 1
     EEPROM.write(1,number); 
  }
  int mod = number % 256;
  if(mod == 0){
     // write the number divided by 256 at index 0
     EEPROM.write(0,number / 256);
     // write a 0 at index 1 for safety
     EEPROM.write(1,0);
     return; 
  }
  number - mod;
  // write what remains of the number, divided by 256 at index 0
  EEPROM.write(0,number / 256);
  // write what was left over at index 1
  EEPROM.write(1,mod);
}

int readFromEEPROM(){
  // read both values
  int a = EEPROM.read(0);
  int b = EEPROM.read(1);
  // combine the 2 using the base 256 system
  return 256 * a + b; 
}

int checkButtons()
{
  int buttons = analogRead(buttonPin) / 100;
  switch (buttons)
  { 
   case 10:
     //No buttons
     doorClosed = false;
     button1Pressed = false;
     button2Pressed = false;
     button3Pressed = false;
     break;
   case 7:
     //Door closed
     doorClosed = true;
     button1Pressed = false;
     button2Pressed = false;
     button3Pressed = false;
     break;
   case 6:
     //Button3
     button3Pressed = true;
     button1Pressed = false;
     button2Pressed = false;
     break;
   case 5:
     //Button2
     button2Pressed = true;
     button1Pressed = false;
     break;
   case 0:
     //Button1
     button1Pressed = true;
     break;
  } 
  return buttons;
}

bool timeElapsed(int since, int elapsed)
{
  return (millis() - since > elapsed);
}
