#ifndef DPADCPP
#define DPADCPP

#include <Arduino.h>

#ifndef KEYPAD_PIN
#define KEYPAD_PIN  A0
#endif

const int dpad[5][2] = {
  {540, 580}, //KEY_MIDDLE 0
  
  {200, 240}, //KEY_LEFT 1
  {430, 470}, //KEY_RIGHT 2
  {320, 360}, //KEY_DOWN 3
  {770, 810}  //KEY_ROTATE 4
};

static int dpadwarp[5] = { 0,0,0,0,0 };
static volatile int Debounce = 0;
static volatile bool processKey = true;
static volatile int currentPos;


class Dpad
{

  static const int DebounceMax = 10;
  
  public:

    static int getPos() {
      
      currentPos = getPosition(KEYPAD_PIN)*1;
      delay(100);
      
      for(int i=0;i<5;i++) {
        if(currentPos > dpad[i][0] && currentPos < dpad[i][1]) {
          return i;  
        }
      }
      return -1;
    }

    static boolean DoDebounce() {
      Debounce++;
      if(Debounce > DebounceMax) {
        return true;
      }
      return false;
    }

    static int setAccel(int acceleration, int offset) {
      if(processKey) {
        dpadwarp[currentPos] = millis();
      }
      if(millis() < dpadwarp[currentPos] + offset) {
        processKey = false;
      } else {
        processKey = true;
        acceleration = acceleration + 70;
        if (acceleration > offset) {
          acceleration = offset;
        }
      }
      return acceleration;
    }

  private:
  
    static int getPosition(int pin) {
      return analogRead(pin);
    }
};

#endif



 
