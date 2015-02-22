String currentText[2];

void print(int line, String text){
  if(currentText[line] != text){
     currentText[line] = text;
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(currentText[0]);
     lcd.setCursor(0,1);
     lcd.print(currentText[1]);
  }
}
