void CheckSerial() { //Remaining letters -> acefghijklnopqtuvwy ACEFGIJKLMPQUVWXYZ
  while (Serial.available()) {
    BluetoothData=Serial.read(); //Get next character from bluetooth

    //==================Noise==================
    //Speed
    if(BluetoothData=='S') {
      timeScale = Serial.parseInt();
      if (Respond) {
        Serial.print(F("TimeScale: "));
        Serial.println(timeScale);
      }
    }
    //Scale
    if(BluetoothData=='s') {
      spaceScale = Serial.parseInt();
      if (Respond) {
        Serial.print(F("SpaceScale: "));
        Serial.println(spaceScale);
      }
    }
    //Bias
    if(BluetoothData=='b') {
      tmpSpeedDampThingyBiasWhatever = Serial.parseInt();
      uint16_t baseSpeed = tmpSpeedDampThingyBiasWhatever/timeScale; //arbitrayy and needs tweeking

      if (Respond) {
        Serial.print(F("tmpSpeedDampThingyBiasWhatever: "));
        Serial.println(tmpSpeedDampThingyBiasWhatever);
        
        Serial.print(F("Base Speed (<50 for damping) : "));
        Serial.println(baseSpeed);
      }
      uint8_t dataSmoothing = 0;
      if( baseSpeed < 50) {
        dataSmoothing = 200 - (baseSpeed * 4);
        if (Respond) {
          Serial.print(F("dataSmoothing : "));
          Serial.println(dataSmoothing);
        }
      }else{
        if (Respond) {
          Serial.println(F("dataSmoothing : None"));
        }
      }
    }
    //==================Primary==================
    //Brightness
    if(BluetoothData=='B') {
      brightness = Serial.parseInt();
      if (Respond) {
       Serial.print(F("Brightness: "));
        Serial.println(brightness);
      }
    }
    //Scale
    if(BluetoothData=='H') {
      HueSpread = Serial.parseInt();
      if (Respond) {
        Serial.print(F("HueSpread: "));
        Serial.println(HueSpread);
      }
    }
    //Next Pal Speed
    if(BluetoothData=='N') {
      nextPaletteSpeed = (byte)Serial.parseInt();
      if (Respond) {
        Serial.print(F("nextPaletteSpeed: "));
        Serial.println(nextPaletteSpeed);
      }
    }
    //==================Ripple==================
    //Damp
    if(BluetoothData=='D') {
      rippleVelocityDamp = Serial.parseInt();
      if (rippleVelocityDamp < 2) {rippleVelocityDamp = 2;}
      if (Respond) {
        Serial.print(F("rippleVelocityDamp: "));
        Serial.println(rippleVelocityDamp);
      }
    }
    //Damp
    if(BluetoothData=='r') {
      rippleForceDamp = Serial.parseInt();
      if (rippleForceDamp < 1) {rippleForceDamp = 1;}
      if (Respond) {
       Serial.print(F("rippleForceDamp: "));
       Serial.println(rippleForceDamp);
      }
    }
    //Damp
    if(BluetoothData=='R') {
      rippleSpeedDamp = Serial.parseInt();
      if (rippleSpeedDamp < 1) {rippleSpeedDamp = 1;}
      if (Respond) {
        Serial.print(F("rippleSpeedDamp: "));
        Serial.println(rippleSpeedDamp);
      }
    }
    //Interval
    if(BluetoothData=='d') {
      rippleInterval = Serial.parseInt() * 1000;
      if (Respond) {
        Serial.println(F("rippleInterval Set"));
      }
    }
    //
    if(BluetoothData=='m') {
      rippleMinBrightness = Serial.parseInt() * 1000;
      if (Respond) {
        Serial.print(F("rippleMinBrightness: "));
        Serial.println(rippleMinBrightness);
      }
    }
    //==================Twinkle==================
    //Ammount (chance)
    if(BluetoothData=='T') {
      twinkleChance = Serial.parseInt();
      if (Respond) {
        Serial.print(F("twinkleChance: "));
        Serial.println(twinkleChance);
      }
    }
    //==================z==================
    //Debug
    if(BluetoothData=='z') {
      int index = Serial.parseInt();
      Serial.read();
      int val = Serial.parseInt();
      if (index >=0 && index <=9) {
        Debug[index] = val;
        Serial.print(F("Set Debug["));
        Serial.print(index);
        Serial.print(F("] to <"));
        Serial.print(val);
        Serial.println(F(">"));
      }else{
        if (index == 3234 && val == 7546) {
          Respond = 1-Respond;
          Serial.println(F(">_<"));
        }else{
          Serial.println(F("!Out of range!"));
        }
      }
    }
    //==================x==================
    //recive palette
    if(BluetoothData=='O') {
      byte pos = 0;
      byte t = 0; //time scence last recive
      byte channel = 0;
      byte in[3];
      while (pos < 16 && t < 100) {
        if (Serial.available() > 0) {
          byte chr = Serial.read();
          in[channel] = chr;
          t = 0;
          if (channel == 2) {//if end of line
            incomingPalette[pos] = CHSV(in[0],in[1],in[2]); //assign this position
            pos++; //new line
            channel = 0; 
          }else{//if not end on line
            channel+=1; //continue
          }
        }else{//not available
          delay(1);
          t++;
        }//end available
        //incomingPalette[pos] = CHSV(in[0],in[1],in[2]);
      }//end of loop

      t = 0;
      while (Serial.available() == 0 && t < 100) {
        t++;
        delay(1);
      }
      
      byte chr = Serial.read();
      for (byte i=0; i<16; i++) {
        if (chr == 1) {basePalette[i] = incomingPalette[i];}
        if (chr == 2) {nextBasePalette[i] = incomingPalette[i];}
        if (chr == 3) {ripplePalette[i] = incomingPalette[i];}
        if (chr == 4) {nextRipplePalette[i] = incomingPalette[i];}
      }
      if (Respond) {
        Serial.print(F("Recive Pal -> slot: "));
        Serial.println(chr);
      }
    }//end of recive
    //==================x==================
    //New Random
    if(BluetoothData=='x') {
      hue1 = random8();
      hue2 = random8();
      nextBasePalette = CustomPalette();
      
      Serial.print(F("New Rand Base-> a:"));
      Serial.print(hue1);
      Serial.print(F(" b:"));
      Serial.print(hue2);
      Serial.println(F(" <"));
      
      hue1 = random8();
      hue2 = random8();
      nextRipplePalette = CustomPalette();
      
      Serial.print(F("New Rand Ripp-> a:"));
      Serial.print(hue1);
      Serial.print(F(" b:"));
      Serial.print(hue2);
      Serial.println(F(" <"));
    }
  }//End input data
}
