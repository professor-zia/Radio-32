/*
  BluePillBlink.ino
  STM32-F103-C8 Blue Pill Board
  Arduino IDE v1.8.13
  STM32 Cores by STMicroelectronics v1.9.0 / HAL/LL API
  https://github.com/stm32duino/Arduino_Core_STM32
  
  Blink PC13 LED once per second

  F.Zia / K2FZZ 2021_0316
*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
  HAL_Delay(10);                    // wait for 0.01 second
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED off
  HAL_Delay(990);                   // wait for 0.99 second
}
