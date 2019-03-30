// Fill the array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on speed.
  uint16_t baseSpeed = tmpSpeedDampThingyBiasWhatever/timeScale; //arbitrayy and needs tweeking
  uint8_t dataSmoothing = 0;
  if(baseSpeed < 50) {
    dataSmoothing = 200 - (baseSpeed * 4);
  }
  
  for(int i = 0; i < NUM_LEDS; i++) {
    uint8_t data = inoise8(spaceScale * i, 234, ts);
    data = qsub8(data,16); // The range of the inoise8 function is roughly 16-238.
    data = qadd8(data,scale8(data,39)); // These two operations expand those values out to roughly 0..255
    
    if( dataSmoothing ) {
      uint8_t olddata = noise[i];
      uint8_t newdata = scale8(olddata, dataSmoothing) + scale8(data, 256 - dataSmoothing);
      data = newdata;
    }
    
      noise[i] = data;
  }

}
