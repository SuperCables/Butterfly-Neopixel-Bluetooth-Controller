void Twinkle() {
  static byte flicker[NUM_LEDS];
  static byte flickBoost[NUM_LEDS];
  
  if (random8()<twinkleChance) {
    int pos = random8(NUM_LEDS);
    flickBoost[pos] = 1;
  }
  
  for(int i = 0; i < NUM_LEDS; i++) {
    byte tmp = flicker[i];
    byte dir = flickBoost[i];
    if (dir == 1) { //if go up
       if (tmp < 230) { //if low
        tmp = tmp + 8; //go up
      }else{ //if high (and should go up)
        tmp = 240; //max out
        flickBoost[i] = 0; //start going down
      }
    }else{//if go down
      if (tmp > 0) { //if high
        tmp = tmp -1;//go down
      }//end if high (and go down)
    }//end go down
    
    flicker[i] = tmp;

    nblend(leds[i],CHSV(0,0,255),tmp);
  }//end loop

}

