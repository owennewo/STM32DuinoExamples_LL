#include <Arduino.h>

int dead_time = 220;  //non linear and clock speed dependent!
int duty = 50;

void setup()
{

  HardwareTimer *timer = new HardwareTimer(TIM1);

  //ordering is impotant! Overflow first, LL_TIM* last.

  timer->setOverflow(20000, HERTZ_FORMAT); 
  timer->setCaptureCompare(1, duty, PERCENT_COMPARE_FORMAT);
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE8);
  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE9);
  LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
  LL_TIM_CC_EnableChannel(timer->getHandle()->Instance, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH1N);
  timer->resume();
}

void loop()
{

}
