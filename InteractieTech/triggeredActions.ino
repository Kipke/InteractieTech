int pulses = 0;
int pulseElapsed = shotDelay / 10;;
void triggeredActions(){
  // light is flashing color of shots remaining
  // degradation timer and shots to fire magic :-)
  // if no movement
  if(shotsToFire == 0){
     state = STANDBY;
     pulses = 1;
     shotTime = -1;
     pulseElapsed = shotDelay / 10;
     return; 
  }
  if(shotsToFire == 1){
     // light is yellow
     lightColor(255,255,0); 
  }
  //   start shot countdown
  if(shotTime == -1){
     shotTime = millis();
  }
  // flip the light
  if(timeElapsed(shotTime,pulseElapsed)){     
     flipLight(); 
     int pulseSpeed = shotDelay / (10 + 3 * pulses); 
     pulses++;     
     if(pulseSpeed < 50){
        pulseSpeed = 50;
     }
     pulseElapsed += pulseSpeed;
  }
  //  float temp2 = temp / shotDelay;  
  //  lightIntensity(temp2);
  //  int lightIntensity = temp2 * 255;
  //  lightColor(lightIntensity,lightIntensity,lightIntensity);
  
  // fire the shot if neccesary
  if (timeElapsed(shotTime,shotDelay) && shotTime != (-1)){    
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    shotsToFire--;
    shotTime = millis();
    pulses = 1;
    pulseElapsed = shotDelay / 10;
    lightIntensity(1);
  }
}
