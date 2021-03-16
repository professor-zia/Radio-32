Blue Pill STM32-F103-C8 Rotary Encoder Test Circuit and Code
* Ref: https://deepbluembedded.com/stm32-timer-encoder-mode-stm32-rotary-encoder-interfacing/


Circuit Connections:
Generic Rotary Encoder + Push Switch Module with integrated pull up 10k resistors
```
* CLK ->
* DT  ->
* SW  -> 
* +V  -> +3.3V 
* GND -> GND
```
* Set up timer2 to operate in encoder mode with 2 input channels (combined)
* Set up a GPIO input pin to be connected to encoder’s SW switch button pin
* Set up UART1 module to operate in async mode @ 9600bps
* Read the timer2 counter register value and print the number via serial port as well as the button state

