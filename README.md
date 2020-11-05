# STM32DuinoExamples_LL
Contains examples of using stm32duino core low level (`LL_*`)APIs.

For when the `Arduino APIs` are not enough!

## Background
There are some great/official stm32duino examples over at: https://github.com/stm32duino/STM32Examples

That repo sticks to `Arduino APIs`.  The benefit here is portability i.e. those examples will likely work on most stm32 boards.

However the `Arduino APIs` are sometimes not enough and you have to write code that is non portable that makes use of the LL_* libraries.  These libraries don't need to be installed, they are just hiding waiting to be explored!

I'm currently interested in LL_TIM_* (timers) but there are quite a few other areas!

The Low Level libraries consist of:
 - LL_TIM_* - macros/registers relating to stm32 timers.  If you want to use countermode (down or up/down counters) or complementary timers (two pins sharing the same timer channel, one the negative of the other) with deadtime (useful for motor drivers where a dead time needs to be introduced to avoid high/low mosfet short circuiting). I think there are some DMA macros here too.
 - LL_RTC_* - macros/registers for doing clever things with the real time clock
 - LL_GPIO_* - e.g. to set an alternative function on a GPIO pin, locking a pin, or changing pin output speed
