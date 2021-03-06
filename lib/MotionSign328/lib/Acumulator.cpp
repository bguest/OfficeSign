#include "Acumulator.h"

Acumulator::Acumulator(){
  lastStep = 0;
  this->resetPts();
}

void Acumulator::resetPts(){
  nextPt = 0;
  lastPixel = millis();
  for(uint8_t i=0; i<LED_WIDTH; i++){
    pts[i] = -2;
  }
}

void Acumulator::run(Sign &sign, Data &data){
  unsigned long currMillis = millis();

  unsigned long STEP_TIME = 60;

  if(currMillis - lastStep < STEP_TIME){ return; }
  lastStep = currMillis;

  unsigned long pixelStep = TIME_OUT / LED_WIDTH;

  if( data.motion.isMotion() ){
    this->resetPts();
  }else if(nextPt < LED_WIDTH && currMillis - lastPixel > pixelStep ){
    lastPixel = currMillis;
    pts[nextPt] = -1;
    nextPt++;
  }
  this->pushMotion(sign, data);

  //Calculate point locations
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] <= -2){ continue; }
    if(pts[i] < LED_WIDTH-1-i ){ pts[i]++; }
  }

  //Color Green
  uint16_t hue = data.isReserved ? HUE_BLUE : HUE_GREEN;
  for(uint8_t i=0; i<LED_WIDTH; i++){
    if(pts[i] >= 0){
      // Empty Color Variation
      ColorHSV color = sign.colorAt(pts[i]);
      if(color.val == 0xFF){
        color.val = (color.hue >> 8) + 0x6D;
      }
      color.hue = hue;
      //ColorHSV color = ColorHSV(hue,0xFF,0xFF);
      sign.setColor(color, pts[i]);
    }
  }
}

void Acumulator::pushMotion(Sign &sign, Data &data){
    uint16_t hue = data.motion.avgMapU16(0,0xFFFF) - 0x6D00;
    ColorHSV color = ColorHSV(hue, 0xFF, 0xFF);
    sign.pushRight(color);
}

