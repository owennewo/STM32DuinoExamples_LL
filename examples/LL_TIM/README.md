# LOW LEVEL TIMER API

Timers can seem a bit intimidating.  These examples aim to show some of the stm32 features that are not possible using standard "Arduino APIs"

As mentioned on main README these LL_* macros are not always supported on all boards and quite often are only possible on certain timers (e.g. on my `stm32g431` board I can do dead time on TIM1 but not TIM4)

## countermode
The default counter mode is `up`.  This means that the counter will typically start at zero and countup until it hits your overflow value and reset to zero and resume counting.  Each of your timer channels have a change register value that might cause a gpio pin to go high/low or for an interrups (callback) to fire.
There are other countermodes that are commonly used but require LL_TIM macros/registers:
  - LL_TIM_COUNTERMODE_UP
  - LL_TIM_COUNTERMODE_DOWN
  - LL_TIM_COUNTERMODE_CENTER_UP_DOWN -> this one is particularly useful for motor applications
  - LL_TIM_COUNTERMODE_CENTER_DOWN
  - LL_TIM_COUNTERMODE_CENTER_UP

You may also wish to change the repition counter using LL_TIM_SetRepetitionCounter.  This can be used to control how often an `update event` occurs.  e.g. if you set it to 1 then it'll skip one `update event` and the timer scoped interrupt will fire every other counter reset.  You might use a value of 1 for an updown counter where you only want an update event on an `underflow` reset (after down) not at `overflow` (after up).

## PWM2
By default `Arduino APIs` will be using `LL_TIM_OCMODE_PWM` - this basically will make the gpio go from low to high at the timer channels change count.  What happens if you want it to go from high to low?  You should use `LL_TIM_OCMODE_PWM2`.  A typical application for this is where you have 2 pins which you want to do PWM on but one must be off when the other is on.  Each pin would need to be on the same timer but use different channels.

Note, perhaps a better way to do this is using complementary channels (`CH1 CH1N`) where multiple gpios are managed on the same channel.

## Complementary channels CH1 CH1N and dead time
I'm still not 100% sure I understand complementaty channels and timers but I have an example that works for me!  

So I'm wanting two pins that are the opposite of each other and with deadtime in between so that only one is ever on.  I did this by enabling the CH1N channel and setting the deadtime
```
LL_TIM_OC_SetDeadTime(timer->getHandle()->Instance, dead_time);
LL_TIM_CC_EnableChannel(timer->getHandle()->Instance, LL_TIM_CHANNEL_CH1 | LL_TIM_CHANNEL_CH1N);
```

There seems to be ordering magic to how these commands need to be executed, so I suspect other `Arduino APIs` commands overwrite some of the registers.  See example.


# Using STM32Cube Device Configuration tool
I don't code using STM32Cube (I use platformio / stm32duino boards) but I do use their Device Configuration Tool

A lot of the above is super difficult to do without this tool.  You'd need to study the datasheets it would take hours.  I'm sort of lying - some of it can be achieved using introspection but I think you should still use the tool!
Example 1.  I want to know which timer and chanbel should be used with pin PA6?

So you can use introspection (note this doesn't use LL_TIM_*)
```
IM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(PA6), PinMap_PWM); // give me the timer instance associated with PA6
uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(PA6), PinMap_PWM)); // give me the channel # within this timer associated with PA6
HardwareTimer *MyTim = new HardwareTimer(Instance); // create the timer
MyTim->setPWM(channel, PA6, 20000, 50); //configure PA6 as PWM 

```
But it gets a whole load more confusing if you want to select pins that purposely use different timers or the same timers.  

More importantly some timers don't support all the features.  e.g. if you need dead time you may need to use a specific timer and need to use gpio bound to this timer.  This is where this graphical tool will show you association between pins and timers.
