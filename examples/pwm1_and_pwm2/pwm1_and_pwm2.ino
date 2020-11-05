#include <Arduino.h>
// Example uses the disco_f407vg which has 4 LEDs

void setup()
{

  // TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(LED_RED), PinMap_PWM); 
  // uint32_t channelBlue = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LED_BLUE), PinMap_PWM));
  // uint32_t channelRed = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LED_RED), PinMap_PWM));
  // uint32_t channelOrange = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LED_ORANGE), PinMap_PWM));
  // uint32_t channelGreen = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(LED_GREEN), PinMap_PWM));
  
  /* 
    The above 5 lines are identical to the next 5 lines.  
    But the next 5 lines requires you to read datasheet or use stm32 pinout config tool to discover mappings between pins and timers.
    On my board the LEDs can only be used with timer 4
    Note Timer4 cannot do 'dead time' (see other example)
  */
  TIM_TypeDef *Instance = TIM4;
  uint32_t channelBlue = 4;
  uint32_t channelRed = 3;
  uint32_t channelOrange = 2;
  uint32_t channelGreen = 1;

  HardwareTimer *timer = new HardwareTimer(Instance);
  timer->setOverflow(1, HERTZ_FORMAT); 

  timer->setCaptureCompare(channelRed, 50, PERCENT_COMPARE_FORMAT);
  timer->setCaptureCompare(channelBlue, 50, PERCENT_COMPARE_FORMAT);
  timer->setCaptureCompare(channelGreen, 75, PERCENT_COMPARE_FORMAT);
  timer->setCaptureCompare(channelOrange, 75, PERCENT_COMPARE_FORMAT);
  
  timer->setMode(channelRed, TIMER_OUTPUT_COMPARE_PWM1, LED_RED);
  timer->setMode(channelBlue, TIMER_OUTPUT_COMPARE_PWM2, LED_BLUE);
  timer->setMode(channelGreen, TIMER_OUTPUT_COMPARE_PWM1, LED_GREEN);
  timer->setMode(channelOrange, TIMER_OUTPUT_COMPARE_PWM2, LED_ORANGE);
  
  timer->resume();

  
  LL_TIM_COUNTERMODE_UP
  LL_TIM_COUNTERMODE_DOWN
  LL_TIM_COUNTERMODE_CENTER_UP_DOWN
  LL_TIM_COUNTERMODE_CENTER_DOWN
  LL_TIM_GetR
  LL_TIM_CC
}

void loop()
{
}