

CHSV GetLEDSpreadPallet(CHSVPalette16 palette, uint16_t i, byte shift = 0) { //spreads a palette across a strip of leds
  byte colorIndex = (uint32_t)i*255/NUM_LEDS; //find the palette location index
  return ColorFromPalette(palette, colorIndex + shift, 255, LINEARBLEND); //find the base color for that pixel from palette
}

void HSVBlendTowardPalette(CHSVPalette16& current, CHSVPalette16& target, uint8_t maxChanges) {
  uint8_t* p1;
  uint8_t* p2;
  uint8_t changes = 0;

  p1 = (uint8_t*)current.entries;
  p2 = (uint8_t*)target.entries;

  const uint8_t totalChannels = sizeof(CHSVPalette16);
  for( uint8_t i = 0; i < totalChannels; i++) {
    
      // if we've hit the maximum number of changes, exit
      if( changes >= maxChanges) { break; }
    
      // if the values are equal, no changes are needed
      if( p1[i] == p2[i] ) { continue; }

      // if the current value is less than the target, increase it by one
      if( p1[i] < p2[i] ) {p1[i]++; changes++;}

      // if the current value is greater than the target,
      if( p1[i] > p2[i] ) {p1[i]--; changes++;}
  }
}

void CheckInterface(){
  if (digitalRead(7)==LOW) {
    if ((ms - lastButtonPress) > 250) {
      if (digitalRead(8)==LOW){
        //way1
        hue1 += 32;
        Serial.print("hue1: ");
        Serial.println(hue1);
        basePalette = CustomPalette();
      }else{//not way1
        if (digitalRead(9)==LOW){
          //way2
          hue2 += 32;
          Serial.print("hue2: ");
          Serial.println(hue2);
          basePalette = CustomPalette();
        }else{
          //not way2
          brightness-=32;
          Serial.print("brightness: ");
          Serial.println(brightness);
          //brightness
        }//end sw2
        
      }//end sw1
    }//end debounce
  lastButtonPress = ms;
  }//end button   
}

