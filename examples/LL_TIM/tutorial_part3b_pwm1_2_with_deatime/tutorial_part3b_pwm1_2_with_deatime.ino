#include <Arduino.h>

HardwareTimer *timer;
int duty = 50;

HardwareSerial Serial1(PA3,PA2);

byte dead_percent = 10;

/**
 * Example: Changing the deadtime of a separate channels on same timer
 */
void setup()
{
  Serial1.begin(115200);

  timer = new HardwareTimer(TIM1);
  //ordering is impotant! Overflow first, LL_TIM* last.
  timer->setOverflow(40000, HERTZ_FORMAT); 

  timer->setMode(1, TIMER_OUTPUT_COMPARE_PWM1, PE_9);
  timer->setMode(2, TIMER_OUTPUT_COMPARE_PWM2, PE_11);
  timer->setCaptureCompare(1, duty, PERCENT_COMPARE_FORMAT);
  timer->setCaptureCompare(2, duty + dead_percent, PERCENT_COMPARE_FORMAT);

  LL_TIM_SetCounterMode(timer->getHandle()->Instance, LL_TIM_COUNTERMODE_CENTER_UP_DOWN);
  timer->resume();
}

void loop()
{
  delay(100);
  Serial1.println(dead_percent);
  dead_percent++;
  if (dead_percent >= 100 - duty) {
    dead_percent = 1;
  }
  timer->setCaptureCompare(2, duty + dead_percent, PERCENT_COMPARE_FORMAT);
}
