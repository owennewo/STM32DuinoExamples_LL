#include <Arduino.h>

// WATCH VIDEO: https://youtu.be/HOCXhLaX4Kk

HardwareTimer *timer;
byte dead_time = 220;  //non linear and clock speed dependent!
int duty = 50;

HardwareSerial Serial1(PA3,PA2);

/**
 * Example: Changing the deadtime of a complementary CH1 CH1N channel
 */
void setup()
{
  pinMode(LED_BLUE,OUTPUT);
  Serial1.begin(115200);

  timer = new HardwareTimer(TIM1);
  //ordering is impotant! Overflow first, LL_TIM* last.
  timer->setOverflow(40000, HERTZ_FORMAT); 
  timer->setCaptureCompare(1, duty, PERCENT_COMPARE_FORMAT);
  // I expect calling this is 'not the proper way'.  I should probably be configuring TIM_OC by hand, but this works!
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_8);
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_9);

  LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
  LL_TIM_CC_EnableChannel(timer->getHandle()->Instance, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH1N);
  // LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
  timer->resume();
}

void loop()
{
  delay(20);
  Serial1.println(dead_time);
  dead_time++; // a byte will naturally flip from 255 to 0
  LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
}

