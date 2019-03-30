void Ripple() {
  random16_add_entropy( random());

  static int wavePos[NUM_LEDS]; //position (0=zero)
  static int waveVel[NUM_LEDS]; //speed direction (-127=down 0=still 127=up)
  
    for(int i = 0; i < NUM_LEDS; i++) { //for each led
      int left = 0; //assume its attached to the side wall
      int right = 0;
      if (i > 0) { //if not attached to side
        left = wavePos[i-1]; //attach to left node
      }
      if (i < NUM_LEDS-1) {// same for right
        right = wavePos[i+1];
      }
      int differance = (left + right) - (wavePos[i]*2); //(left + right) - wavepos * 2 [<<1] //find differance
      waveVel[i] += (differance / rippleForceDamp); //apply force
    }

    if ((ms - lastRippleDamp) > 250) {
      lastRippleDamp = ms;
      for( int i = 0; i < NUM_LEDS; i++) {
        waveVel[i] = ((long)waveVel[i]*(rippleVelocityDamp-1))/rippleVelocityDamp;
      }
    }

    if (pulse>0){
      pulse -=1;
      wavePos[ripplepos] = wavePos[ripplepos] + 1000;
    }else{
      if ((ms - lastRipplePulse) > rippleInterval) {
        lastRipplePulse = ms;
        pulse = scale8(random8(),8)+20;
        ripplepos = random8(NUM_LEDS);
      }
    }
    
    for(int i = 0; i < NUM_LEDS; i++) {
      int pos = wavePos[i];
      pos += (waveVel[i] / rippleSpeedDamp);
      if (pos < -16000) {pos = -16000;}
      if (pos > 16000) {pos = 16000;}
      wavePos[i] = pos;

      //byte scale = 255-map(pos,-16000,16000,minBright,maxBright);
      //nblend(leds[i],CRGB::Black,scale);
      
      if (pos > 0) {
        byte scale = map(pos,0,16000,0,255);
        nblend(leds[i],GetLEDSpreadPallet(ripplePalette,i,ms/250),scale);
        //nblend(leds[i],CHSV(0,0,255),255-scale);
      }else{
        byte scale = map(pos,-16000,0,255-rippleMinBrightness,0);
        nblend(leds[i],CHSV(leds[i].h,0,0),scale);
      }

    }//end loop
}//end ripple

//CRGB color = ColorFromPalette(rippleBasePalette, (pos + 16000) / 125);
//nblend(leds[i],color,(byte)(min(abs(pos)/30,255)));
//leds[i].nscale8_video(scale);

