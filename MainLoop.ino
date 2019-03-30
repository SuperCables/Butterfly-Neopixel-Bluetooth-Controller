void loop()
{
  ms = millis();
  ts = (ms*50)/timeScale;

  if (brightness){ //if on
    if ((ms - lastFrame) > 25) {
      lastFrame = ms;
      fillnoise8();
  
      if ((ms - lastPaletteFade) > 100) { //fade to next base palette
        lastPaletteFade = ms;
        HSVBlendTowardPalette(basePalette,nextBasePalette,nextPaletteSpeed);
        HSVBlendTowardPalette(ripplePalette,nextRipplePalette,nextPaletteSpeed);
      }
      
      for( int i = 0; i < NUM_LEDS; i++) { //fill leds from palette
        leds[i] = GetLEDSpreadPallet(basePalette,i,ms/250);
      }

      if (rippleInterval > 0){
        Ripple();
      }

      if (twinkleChance > 0){
        Twinkle();
      }
      
  
      for( int i = 0; i < NUM_LEDS; i++) {//spread hue and assign rgb result
        int hue = leds[i].h;
        hue = hue - HueSpread + (noise[i]*HueSpread/128); //spread
        leds[i].h = hue;
        
        rgbOutput[i] = leds[i]; //HSV -> RGB convert
      }
  
      blur1d(rgbOutput, NUM_LEDS,1); //blur the result a little bit
      
      nscale8_video(rgbOutput,NUM_LEDS,brightness); //dim the display
      FastLED.show();
    }//end next frame
  }else{//is off
    fill_solid(rgbOutput,NUM_LEDS,CHSV(0,0,0)); //if bright is 0 then show black and take a nap
    FastLED.show();
    delay(50);
  }//end is on
  CheckSerial();
  //CheckInterface();
}


