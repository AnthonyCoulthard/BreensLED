//Possible to add buttons to control colour of each strip individually?

//Outer right start = Pin 2
//Inner right start = Pin 0
//Outer left start = Pin 3
//Inner left start = Pin 15

#include <Adafruit_NeoPixel.h>

//Define output pins
#define pin_01 11 //Outer right is pin 11
#define pin_02 5 //Outer left is pin 5
#define pin_03 9  //Inner right is pin 9
#define pin_04 2 //Inner left is pin 2

//Initialize pixel strips
Adafruit_NeoPixel strip_01 = Adafruit_NeoPixel(24, pin_01); //Outer right strip
Adafruit_NeoPixel strip_02 = Adafruit_NeoPixel(24, pin_02); //Outer left strip
Adafruit_NeoPixel strip_03 = Adafruit_NeoPixel(16, pin_03); //Inner right strip
Adafruit_NeoPixel strip_04 = Adafruit_NeoPixel(16, pin_04); //Inner left strip

//Initial conditions
uint8_t mode = 0; //Tracks operating mode
uint8_t wait = 50; //Initial delay
uint32_t colour = 0xFF0000; //Colour is initially set to red
uint32_t redBlue = 0xFF00FF;
uint32_t greenBlue = 0x00FFFF;
uint32_t redGreen = 0xFFFF00;
uint32_t fullWhite = 0xFFFFFF;

//Begin data output on all strips, and set their brightness
void setup() {
  strip_01.begin(); //Begin data output
  strip_01.setBrightness(50); //Brightness, 255 = max
  
  strip_02.begin(); //Begin data output
  strip_02.setBrightness(50); //Half brightness

  strip_03.begin(); //Begin data output
  strip_03.setBrightness(50); //Half brightness

  strip_04.begin(); //Begin data output
  strip_04.setBrightness(50); //Half brightness
}

void loop() {
  //uint32_t currentTime;
  //Fade all colours up to white then off in between modes
  /*
  for (int i = 0; i < 256; i++){
    for (int j = 0; j < 24; j++){
      strip_01.setPixelColor(j, changeRed(changeGreen(changeBlue(strip_01.getPixelColor(j), 1), 1), 1));
      strip_02.setPixelColor(j, changeRed(changeGreen(changeBlue(strip_02.getPixelColor(j), 1), 1), 1));
      if (j < 16){
        strip_03.setPixelColor(j, changeRed(changeGreen(changeBlue(strip_03.getPixelColor(j), 1), 1), 1));
        strip_04.setPixelColor(j, changeRed(changeGreen(changeBlue(strip_04.getPixelColor(j), 1), 1), 1));
      }
    }
    strip_01.show();
    strip_02.show();
    strip_03.show();
    strip_04.show();
    delay(2);
  }
  int brightness = 123;
  for (int i = 0; i < 123; i++){
    brightness--;
    if (brightness < 0){
      brightness = 0;
    }
    strip_01.setBrightness(brightness);
    strip_02.setBrightness(brightness);
    strip_03.setBrightness(brightness);
    strip_04.setBrightness(brightness);
    strip_01.show();
    strip_02.show();
    strip_03.show();
    strip_04.show();
    delay(4);
  }
  strip_01.setBrightness(123);
  strip_02.setBrightness(123);
  strip_03.setBrightness(123);
  strip_04.setBrightness(123);
  */
  //Case statement to switch between modes
  switch(mode){
    case 0:
      colour = 0xFF0000;
      opposingSpiralSolid();
      break;

    case 1:
      colour = 0x00FF00;
      opposingSpiralSolid();
      break;

    case 2:
      colour = 0x0000FF;
      opposingSpiralSolid();
      break;

    case 3:
      rainbowSpiral_01();
      break;

    case 4:
      rainbowSpiral_02();
      break;

    case 5:
      rainbowSpiral_03();
      break;

/*
    case 5:
      colour = 0xFF0000;
      figureEightSolid();
      break;

    case 6:
      colour = 0x00FF00;
      figureEightSolid();
      break;

    case 7:
      colour = 0x0000FF;
      figureEightSolid();
      break;

    case 8:
      figureEightRainbow();
      break;
*/
  }

  mode++;
  if (mode > 4){
    mode = 0;
  }
}

//////////////////////////////////////////////////////////
//Function to change the red colour by a given integer////
//Takes in a hex colour and an integer, returns a colour//
//////////////////////////////////////////////////////////
uint32_t changeRed(uint32_t initialColour, int change){
  //Isolate the red hex digits
  int32_t newColour = initialColour >> 16;
  //Add or subtract the change
  newColour += change;
  //Bounded at 0
  if (newColour < 0){
    newColour = 0;
  }
  //Bounded at 0xFF
  if (newColour > 255){
    newColour = 255;
  }
  //Shift the new hex digits back into position
  newColour = newColour << 16;
  //Turn the old hex digits into 0s
  initialColour = initialColour << 8;
  initialColour = initialColour >> 8;
  //Add the new red colour with the old blue and green
  initialColour = (uint32_t)newColour + initialColour;
  return initialColour;
}

//////////////////////////////////////////////////////////
//Function to change the green colour by a given integer//
//Takes in a hex colour and an integer, returns a colour//
//////////////////////////////////////////////////////////
uint32_t changeGreen(uint32_t initialColour, int change){
  //Isolate the green hex digits
  int32_t newColour = initialColour & 0x00FF00;
  newColour = newColour >> 8;
  //Add or subtract the change
  newColour += change;
  //Bounded at 0
  if (newColour < 0){
    newColour = 0;
  }
  //Bounded at 0xFF
  if (newColour > 255){
    newColour = 255;
  }
  //Shift the new hex digits back into position
  newColour = newColour << 8;
  //Turn the old hex digits into 0s
  initialColour = initialColour & 0xFF00FF;
  //Add the new green colour with the old blue and red
  initialColour = (uint32_t)newColour + initialColour;
  return initialColour;
}

//////////////////////////////////////////////////////////
//Function to change the blue colour by a given integer///
//Takes in a hex colour and an integer, returns a colour//
//////////////////////////////////////////////////////////
uint32_t changeBlue(uint32_t initialColour, int change){
  //Isolate the blue hex digits
  int32_t newColour = initialColour & 0x0000FF;
  //Add or subtract the change
  newColour += change;
  //Bounded at 0
  if (newColour < 0){
    newColour = 0;
  }
  //Bounded at 0xFF
  if (newColour > 255){
    newColour = 255;
  }
  //Turn the old hex digits into 0s
  initialColour = initialColour >> 8;
  initialColour = initialColour << 8;
  //Add the new blue colour with the old red and green
  initialColour = (uint32_t)newColour + initialColour;
  return initialColour;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//Function to make the goggles spin in opposing directions in a single colour (defined globally)//
//////////////////////////////////////////////////////////////////////////////////////////////////
void opposingSpiralSolid(){
  for (int iterations = 0; iterations < 24; iterations++){
    uint8_t i; //Pixel i tracks the outer right strip's position
    uint8_t n = 0; //Pixel n tracks the inner right strip's position
    uint8_t j = 23; //Pixel j is the reflection of pixel i in the outer left strip
    uint8_t k = 15; //Pixel k is the reflection of pixel n in the inner left strip
    
    //Change 2 pixels on each of the outer strips before refreshing
    for (i = 0; i < 24; i++){
      if (i == 21){
        strip_01.setPixelColor(i+2, colour);
      }
      if (i == 22){
        strip_01.setPixelColor(0, colour);
      }
      else if (i == 23){
        strip_01.setPixelColor(1, colour);
      }
      else {
        strip_01.setPixelColor(i+2, colour);  //Colour pixel i on the right outer strip
      }
      strip_02.setPixelColor(j, colour);  //Colour pixel j on the left outer strip
      //Clear the pixel 4 positions behind pixel i
      if (i == 0){
        strip_01.setPixelColor(22, 0);
      }
      else if (i == 1){
        strip_01.setPixelColor(23, 0);
      }
      else if (i > 1){
        strip_01.setPixelColor(i-2, 0);
      }
      //Clear the pixel 4 positions ahead of pixel j
      if (j >= 20){
        strip_02.setPixelColor(j-20, 0);
      }
      else if (j < 20){
        strip_02.setPixelColor(j+4, 0);
      }
  
      //Change 2 pixels on each of the inner strips before refreshing
      //Do not refresh the inner strips every third refresh of the outer strips for timing
      if ((i % 3) != 0){
        strip_03.setPixelColor(n, colour); //Colour pixel n on the right inner strip
        strip_04.setPixelColor(k, colour); //Colour pixel k on the left inner strip
        //Clear the pixel 3 positions behind pixel n
        if (n <= 2){
          strip_03.setPixelColor(n+13, 0);
        }
        else if (n > 2){
          strip_03.setPixelColor(n-3, 0);
        }
        //Clear the pixel 3 positions ahead of pixel k
        if (k >= 13){
          strip_04.setPixelColor(k-13, 0);
        }
        else if (k < 13){
          strip_04.setPixelColor(k+3, 0);
        }
        //Change what position n and k point to
        n++;
        if (n > 15){
          n = 0;
        }
        k--;
        if (k < 0){
          k = 15;
        }
      }
  
      //Show all the pixel changes on the 4 strips
      strip_01.show();
      strip_02.show();
      strip_03.show();
      strip_04.show();
      
      //Change what pixel j points to
      j--;
      if (j < 0){
        j = 23;
      }
      delay(wait);
    }
    wait -=1;
  }
  wait = 50;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to make the goggles spin in opposing directions while changing a single colour, then two colours at a time//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rainbowSpiral_01(){
  uint32_t outerColour, outerReverse, innerColour, innerReverse; //Variables to hold the different colours of the strips
  for (int iterations = 0; iterations < 6; iterations++){
    outerColour = outerReverse = innerColour = innerReverse = 0xFFFFFF; //Initialize all colours to fullWhite
    uint8_t i; //Pixel i tracks the outer right strip's position
    uint8_t n = 0; //Pixel n tracks the inner right strip's position
    uint8_t j = 23; //Pixel j is the reflection of pixel i in the outer left strip
    uint8_t k = 15; //Pixel k is the reflection of pixel n in the inner left strip
    
    //Change 2 pixels on each of the outer strips before refreshing
    for (i = 0; i < 24; i++){
      strip_01.setPixelColor(i, outerColour);  //Colour pixel i on the right outer strip
      strip_02.setPixelColor(j, outerReverse);  //Colour pixel j on the left outer strip
      //Clear the pixel 4 positions behind pixel i
      if (i <= 3){
        strip_01.setPixelColor(i+20, 0);
      }
      else if (i > 3){
        strip_01.setPixelColor(i-4, 0);
      }
      //Clear the pixel 4 positions ahead of pixel j
      if (j >= 20){
        strip_02.setPixelColor(j-20, 0);
      }
      else if (j < 20){
        strip_02.setPixelColor(j+4, 0);
      }
  
      //Change 2 pixels on each of the inner strips before refreshing
      //Do not refresh the inner strips every third refresh of the outer strips for timing
      if ((i % 3) != 0){
        strip_03.setPixelColor(n, innerColour); //Colour pixel n on the right inner strip
        strip_04.setPixelColor(k, innerReverse); //Colour pixel k on the left inner strip
        //Clear the pixel 3 positions behind pixel n
        if (n <= 2){
          strip_03.setPixelColor(n+13, 0);
        }
        else if (n > 2){
          strip_03.setPixelColor(n-3, 0);
        }
        //Clear the pixel 3 positions ahead of pixel k
        if (k >= 13){
          strip_04.setPixelColor(k-13, 0);
        }
        else if (k < 13){
          strip_04.setPixelColor(k+3, 0);
        }
        //Change what position n and k point to
        n++;
        if (n > 15){
          n = 0;
        }
        k--;
        if (k < 0){
          k = 15;
        }
      }
  
      //Show all the pixel changes on the 4 strips
      strip_01.show();
      strip_02.show();
      strip_03.show();
      strip_04.show();
      
      //Change what pixel j points to
      j--;
      if (j < 0){
        j = 23;
      }
      
      //Change the colour the next pixel on each strip will show
      //Decrease colour for first half of rotation
      if (i < 12){
        //First iteration changes red
        if (iterations == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x150000;
        }
        //Second iteration changes green
        else if (iterations == 1){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x001500;
        }
        //Third iteration changes blue
        else if (iterations == 2){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000015;
        }
        //Fourth iteration changes to red
        else if (iterations == 3){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x001515;
        }
        //Fifth iteration changes to green
        else if (iterations == 4){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x150015;
        }
        //Sixth iteration changes to blue
        else if (iterations == 5){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x151500;
        }
      }
      //Increase colour for next half of rotation (back to fullWhite)
      else {
        //First iteration changes red
        if (iterations == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x150000;
        }
        //Second iteration changes green
        else if (iterations == 1){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x001500;
        }
        //Third iteration changes blue
        else if (iterations == 2){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000015;
        }
        //Fourth iteration changes to red
        else if (iterations == 3){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x001515;
        }
        //Fifth iteration changes to green
        else if (iterations == 4){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x150015;
        }
        //Sixth iteration changes to blue
        else if (iterations == 5){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x151500;
        }
      }
      delay(wait);
    }
  }
  wait = 50;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function to make the goggles spin in opposing directions while fading between colours//
/////////////////////////////////////////////////////////////////////////////////////////
void rainbowSpiral_02(){
  uint32_t outerColour, outerReverse, innerColour, innerReverse; //Variables to hold the different colours of the strips
  for (int iterations = 0; iterations < 19; iterations++){
    outerColour = outerReverse = innerColour = innerReverse = 0xFFFFFF; //Initialize all colours to fullWhite
    uint8_t i; //Pixel i tracks the outer right strip's position
    uint8_t n = 0; //Pixel n tracks the inner right strip's position
    uint8_t j = 23; //Pixel j is the reflection of pixel i in the outer left strip
    uint8_t k = 15; //Pixel k is the reflection of pixel n in the inner left strip
    
    //Change 2 pixels on each of the outer strips before refreshing
    for (i = 0; i < 24; i++){
      strip_01.setPixelColor(i, outerColour);  //Colour pixel i on the right outer strip
      strip_02.setPixelColor(j, outerReverse);  //Colour pixel j on the left outer strip
      //Clear the pixel 4 positions behind pixel i
      if (i <= 3){
        strip_01.setPixelColor(i+20, 0);
      }
      else if (i > 3){
        strip_01.setPixelColor(i-4, 0);
      }
      //Clear the pixel 4 positions ahead of pixel j
      if (j >= 20){
        strip_02.setPixelColor(j-20, 0);
      }
      else if (j < 20){
        strip_02.setPixelColor(j+4, 0);
      }
  
      //Change 2 pixels on each of the inner strips before refreshing
      //Do not refresh the inner strips every third refresh of the outer strips for timing
      if ((i % 3) != 0){
        strip_03.setPixelColor(n, innerColour); //Colour pixel n on the right inner strip
        strip_04.setPixelColor(k, innerReverse); //Colour pixel k on the left inner strip
        //Clear the pixel 3 positions behind pixel n
        if (n <= 2){
          strip_03.setPixelColor(n+13, 0);
        }
        else if (n > 2){
          strip_03.setPixelColor(n-3, 0);
        }
        //Clear the pixel 3 positions ahead of pixel k
        if (k >= 13){
          strip_04.setPixelColor(k-13, 0);
        }
        else if (k < 13){
          strip_04.setPixelColor(k+3, 0);
        }
        //Change what position n and k point to
        n++;
        if (n > 15){
          n = 0;
        }
        k--;
        if (k < 0){
          k = 15;
        }
      }
  
      //Show all the pixel changes on the 4 strips
      strip_01.show();
      strip_02.show();
      strip_03.show();
      strip_04.show();
      
      //Change what pixel j points to
      j--;
      if (j < 0){
        j = 23;
      }
      
      //Change the colour the next pixel on each strip will show
      //First iteration fades to red
      if (iterations == 0){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = changeGreen(outerColour, -11);
          outerColour = outerReverse = innerColour = innerReverse = changeBlue(outerColour, -11);
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = changeGreen(outerColour, -10);
          outerColour = outerReverse = innerColour = innerReverse = changeBlue(outerColour, -10);
        }
      }
      //Second iteration fades red out and green in
      else if (iterations == 1){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Third iteration fades green out and red in
      else if (iterations == 2){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0000;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0000;
        }
      }
      //Fourth iteration fades red out and green in
      else if (iterations == 3){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Fifth iteration fades green out and blue in
      else if (iterations == 4){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Sixth iteration fades blue out and green in
      else if (iterations == 5){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000B;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000A;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Seventh iteration fades green out and blue in
      else if (iterations == 6){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Eighth iteration fades blue out and red in
      else if (iterations == 7){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000B;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0000;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000A;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0000;
        }
      }
      //Ninth iteration fades red out and blue in
      else if (iterations == 8){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Tenth iteration fades blue out and green in
      else if (iterations == 9){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000B;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000A;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Eleventh iteration fades green out and red in
      else if (iterations == 10){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0000;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0000;
        }
      }
      //Twelfth iteration fades red out and green in
      else if (iterations == 11){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Thirteenth iteration fades green out and red in
      else if (iterations == 12){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0000;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0000;
        }
      }
      //Fourteenth iteration fades red out and blue in
      else if (iterations == 13){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Fifteenth iteration fades blue out and red in
      else if (iterations == 14){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000B;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0000;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000A;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0000;
        }
      }
      //Sixteenth iteration fades red out and blue in
      else if (iterations == 15){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0B0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x0A0000;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Seventeenth iteration fades blue out and green in
      else if (iterations == 16){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000B;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x00000A;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x000A00;
        }
      }
      //Eighteenth iteration fades green out and blue in
      else if (iterations == 17){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000B00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000B;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour - 0x000A00;
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x00000A;
        }
      }
      //Nineteenth iteration fades to fullWhite
      else if (iterations == 18){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0B0B00;
        }
        else{
          outerColour = outerReverse = innerColour = innerReverse = outerColour + 0x0A0A00;
        }
      }
      delay(wait);
    }
  }
  wait = 50;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function to make the goggles spin in opposing directions while meeting colours at red//
/////////////////////////////////////////////////////////////////////////////////////////
void rainbowSpiral_03(){
  uint32_t outerColour, outerReverse, innerColour, innerReverse; //Variables to hold the different colours of the strips
  for (int iterations = 0; iterations < 17; iterations++){
    outerColour = innerReverse = 0x00FF00; //Outer right and inner left initially green
    outerReverse = innerColour = 0x0000FF; //Outer left and inner right initially blue
    uint8_t i; //Pixel i tracks the outer right strip's position
    uint8_t n = 0; //Pixel n tracks the inner right strip's position
    uint8_t j = 23; //Pixel j is the reflection of pixel i in the outer left strip
    uint8_t k = 15; //Pixel k is the reflection of pixel n in the inner left strip
    
    //Change 2 pixels on each of the outer strips before refreshing
    for (i = 0; i < 24; i++){
      strip_01.setPixelColor(i, outerColour);  //Colour pixel i on the right outer strip
      strip_02.setPixelColor(j, outerReverse);  //Colour pixel j on the left outer strip
      //Clear the pixel 4 positions behind pixel i
      if (i <= 3){
        strip_01.setPixelColor(i+20, 0);
      }
      else if (i > 3){
        strip_01.setPixelColor(i-4, 0);
      }
      //Clear the pixel 4 positions ahead of pixel j
      if (j >= 20){
        strip_02.setPixelColor(j-20, 0);
      }
      else if (j < 20){
        strip_02.setPixelColor(j+4, 0);
      }
  
      //Change 2 pixels on each of the inner strips before refreshing
      //Do not refresh the inner strips every third refresh of the outer strips for timing
      if ((i % 3) != 0){
        strip_03.setPixelColor(n, innerColour); //Colour pixel n on the right inner strip
        strip_04.setPixelColor(k, innerReverse); //Colour pixel k on the left inner strip
        //Clear the pixel 3 positions behind pixel n
        if (n <= 2){
          strip_03.setPixelColor(n+13, 0);
        }
        else if (n > 2){
          strip_03.setPixelColor(n-3, 0);
        }
        //Clear the pixel 3 positions ahead of pixel k
        if (k >= 13){
          strip_04.setPixelColor(k-13, 0);
        }
        else if (k < 13){
          strip_04.setPixelColor(k+3, 0);
        }
        //Change what position n and k point to
        n++;
        if (n > 15){
          n = 0;
        }
        k--;
        if (k < 0){
          k = 15;
        }
      }
  
      //Show all the pixel changes on the 4 strips
      strip_01.show();
      strip_02.show();
      strip_03.show();
      strip_04.show();
      
      //Change what pixel j points to
      j--;
      if (j < 0){
        j = 23;
      }
      
      //Change the colour the next pixel on each strip will show
      //No change on first iteration, next read OuterRight/InnerLeft (RtG, RtB, BtG), OuterLeft/InnerRight
      if (iterations == 0){

      }
      //GtR, BtR
      else if (iterations == 1){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeGreen(outerColour, -11);
          outerColour = innerReverse = changeRed(outerColour, 11);
          outerReverse = innerColour = changeBlue(outerReverse, -11);
          outerReverse = innerColour = changeRed(outerReverse, 11);
        }
        else{
          outerColour = innerReverse = changeGreen(outerColour, -10);
          outerColour = innerReverse = changeRed(outerColour, 10);
          outerReverse = innerColour = changeBlue(outerReverse, -10);
          outerReverse = innerColour = changeRed(outerReverse, 10);
        }
      }
      //No change
      else if (iterations == 2){
        
      }
      //RtB, RtG
      else if (iterations == 3){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeBlue(outerColour, 11);
          outerColour = innerReverse = changeRed(outerColour, -11);
          outerReverse = innerColour = changeGreen(outerReverse, 11);
          outerReverse = innerColour = changeRed(outerReverse, -11);
        }
        else{
          outerColour = innerReverse = changeBlue(outerColour, 10);
          outerColour = innerReverse = changeRed(outerColour, -10);
          outerReverse = innerColour = changeGreen(outerReverse, 10);
          outerReverse = innerColour = changeRed(outerReverse, -10);
        }
      }
      //No change
      else if (iterations == 4){
        
      }
      //BtR, GtR
      else if (iterations == 5){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeBlue(outerColour, -11);
          outerColour = innerReverse = changeRed(outerColour, 11);
          outerReverse = innerColour = changeGreen(outerReverse, -11);
          outerReverse = innerColour = changeRed(outerReverse, 11);
        }
        else{
          outerColour = innerReverse = changeBlue(outerColour, -10);
          outerColour = innerReverse = changeRed(outerColour, 10);
          outerReverse = innerColour = changeGreen(outerReverse, -10);
          outerReverse = innerColour = changeRed(outerReverse, 10);
        }
      }
      //No change
      else if (iterations == 6){
        
      }
      //RtG, RtB
      else if (iterations == 7){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeGreen(outerColour, 11);
          outerColour = innerReverse = changeRed(outerColour, -11);
          outerReverse = innerColour = changeBlue(outerReverse, 11);
          outerReverse = innerColour = changeRed(outerReverse, -11);
        }
        else{
          outerColour = innerReverse = changeGreen(outerColour, 10);
          outerColour = innerReverse = changeRed(outerColour, -10);
          outerReverse = innerColour = changeBlue(outerReverse, 10);
          outerReverse = innerColour = changeRed(outerReverse, -10);
        }
      }
      //No change
      else if (iterations == 8){
        
      }//GtR, BtR
      else if (iterations == 9){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeGreen(outerColour, -11);
          outerColour = innerReverse = changeRed(outerColour, 11);
          outerReverse = innerColour = changeBlue(outerReverse, -11);
          outerReverse = innerColour = changeRed(outerReverse, 11);
        }
        else{
          outerColour = innerReverse = changeGreen(outerColour, -10);
          outerColour = innerReverse = changeRed(outerColour, 10);
          outerReverse = innerColour = changeBlue(outerReverse, -10);
          outerReverse = innerColour = changeRed(outerReverse, 10);
        }
      }
      //No change
      else if (iterations == 10){
        
      }
      //RtB, RtG
      else if (iterations == 11){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeBlue(outerColour, 11);
          outerColour = innerReverse = changeRed(outerColour, -11);
          outerReverse = innerColour = changeGreen(outerReverse, 11);
          outerReverse = innerColour = changeRed(outerReverse, -11);
        }
        else{
          outerColour = innerReverse = changeBlue(outerColour, 10);
          outerColour = innerReverse = changeRed(outerColour, -10);
          outerReverse = innerColour = changeGreen(outerReverse, 10);
          outerReverse = innerColour = changeRed(outerReverse, -10);
        }
      }
      //No change
      else if (iterations == 12){
        
      }
      //BtR, GtR
      else if (iterations == 13){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeBlue(outerColour, -11);
          outerColour = innerReverse = changeRed(outerColour, 11);
          outerReverse = innerColour = changeGreen(outerReverse, -11);
          outerReverse = innerColour = changeRed(outerReverse, 11);
        }
        else{
          outerColour = innerReverse = changeBlue(outerColour, -10);
          outerColour = innerReverse = changeRed(outerColour, 10);
          outerReverse = innerColour = changeGreen(outerReverse, -10);
          outerReverse = innerColour = changeRed(outerReverse, 10);
        }
      }
      //No change
      else if (iterations == 14){
        
      }
      //RtG, RtB
      else if (iterations == 15){
        //Change by 11 on even pixels, 10 on odd pixels
        if (i%2 == 0){
          outerColour = innerReverse = changeGreen(outerColour, 11);
          outerColour = innerReverse = changeRed(outerColour, -11);
          outerReverse = innerColour = changeBlue(outerReverse, 11);
          outerReverse = innerColour = changeRed(outerReverse, -11);
        }
        else{
          outerColour = innerReverse = changeGreen(outerColour, 10);
          outerColour = innerReverse = changeRed(outerColour, -10);
          outerReverse = innerColour = changeBlue(outerReverse, 10);
          outerReverse = innerColour = changeRed(outerReverse, -10);
        }
      }
      //No change
      else if (iterations == 16){
        
      }
      delay(wait);
    }
  }
  wait = 50;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function to make the goggles double spin in opposing directions in a single colour (defined globally)//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//NEED TO ADD THE GENERIC LED TO BE TURNED ON FOR THE HALFWAY SNAKE
//NEED TO REMOVE THE SECOND SPIRAL'S LEDs THAT HAVE BEEN TURNED ON
void doubleSpiralSolid(){
  for (int iterations = 0; iterations < 24; iterations++){
    uint8_t i; //Pixel i tracks the outer right strip's position
    uint8_t n = 0; //Pixel n tracks the inner right strip's position
    uint8_t j = 23; //Pixel j is the reflection of pixel i in the outer left strip
    uint8_t k = 15; //Pixel k is the reflection of pixel n in the inner left strip
    
    //Change 2 pixels on each of the outer strips before refreshing
    for (i = 0; i < 24; i++){
      //RIGHT OUTER STRIP//
      if (i == 8){
        strip_01.setPixelColor(10, colour);
        strip_01.setPixelColor(22, colour);
      }
      if (i == 9){
        strip_01.setPixelColor(11, colour);
        strip_01.setPixelColor(23, colour);
      }
      if (i == 10){
        strip_01.setPixelColor(12, colour);
        strip_01.setPixelColor(0, colour);
      }
      else if (i == 21){
        strip_01.setPixelColor(i+2, colour);
        strip_01.setPixelColor(11, colour);
      }
      else if (i == 22){
        strip_01.setPixelColor(0, colour);
        strip_01.setPixelColor(12, colour);
      }
      else if (i == 23){
        strip_01.setPixelColor(1, colour);
        strip_01.setPixelColor(13, colour);
      }
      else {
        strip_01.setPixelColor(i+2, colour);  //Colour pixel i on the right outer strip
        if (i <= 9){
          strip_01.setPixelColor(i+14, colour);
        }
        else if (i > 9){
          strip_01.setPixelColor(i-10, colour);
        }
      }
      //LEFT OUTER STRIP//
      strip_02.setPixelColor(j, colour);  //Colour pixel j on the left outer strip
      //Clear the pixel 4 positions behind pixel i
      if (i == 0){
        strip_01.setPixelColor(22, 0);
      }
      else if (i == 1){
        strip_01.setPixelColor(23, 0);
      }
      else if (i > 1){
        strip_01.setPixelColor(i-2, 0);
      }
      //Clear the pixel 4 positions ahead of pixel j
      if (j >= 20){
        strip_02.setPixelColor(j-20, 0);
      }
      else if (j < 20){
        strip_02.setPixelColor(j+4, 0);
      }
      //INNER STRIPS//
      //Change 2 pixels on each of the inner strips before refreshing
      //Do not refresh the inner strips every third refresh of the outer strips for timing
      if ((i % 3) != 0){
        strip_03.setPixelColor(n, colour); //Colour pixel n on the right inner strip
        strip_04.setPixelColor(k, colour); //Colour pixel k on the left inner strip
        //Clear the pixel 3 positions behind pixel n
        if (n <= 2){
          strip_03.setPixelColor(n+13, 0);
        }
        else if (n > 2){
          strip_03.setPixelColor(n-3, 0);
        }
        //Clear the pixel 3 positions ahead of pixel k
        if (k >= 13){
          strip_04.setPixelColor(k-13, 0);
        }
        else if (k < 13){
          strip_04.setPixelColor(k+3, 0);
        }
        //Change what position n and k point to
        n++;
        if (n > 15){
          n = 0;
        }
        k--;
        if (k < 0){
          k = 15;
        }
      }
  
      //Show all the pixel changes on the 4 strips
      strip_01.show();
      strip_02.show();
      strip_03.show();
      strip_04.show();
      
      //Change what pixel j points to
      j--;
      if (j < 0){
        j = 23;
      }
      delay(wait);
    }
    wait -=1;
  }
  wait = 50;
}
