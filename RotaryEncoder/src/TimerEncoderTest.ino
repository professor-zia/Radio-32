// https://www.stm32duino.com/viewtopic.php?f=62&t=828

HardwareSerial Serial(PA3, PA2);

void setup() {
   Serial.begin(115200);
   Serial.println("Hello Stm32Duino world!");
   EncoderInit();
}

void loop() {
   Serial.print(LL_TIM_GetCounter(TIM4));
   Serial.print(' ');
   Serial.println(LL_TIM_GetCounter(TIM2));
   delay(1000);
}

//-----------------------------------------------------------------------------
// pinModeAF - configure Arduino pin for given alternate-function
//-----------------------------------------------------------------------------
// Alternate values: see LL_GPIO_SetAFPin_8_15()
// example call: pinModeAF(PD12, GPIO_AF2_TIM4);
//-----------------------------------------------------------------------------
void pinModeAF(int ulPin, uint32_t Alternate)
{
   int pn = digitalPinToPinName(ulPin);

   if (STM_PIN(pn) < 8) {
      LL_GPIO_SetAFPin_0_7( get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn), Alternate);
   } else {
      LL_GPIO_SetAFPin_8_15(get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn), Alternate);
   }

   LL_GPIO_SetPinMode(get_GPIO_Port(STM_PORT(pn)), STM_LL_GPIO_PIN(pn), LL_GPIO_MODE_ALTERNATE);
}

void EncoderInit(void)
{
   // use standaard Arduino function for basic setup
   pinMode(PD12, INPUT_PULLUP);  // TIM4
   pinMode(PD13, INPUT_PULLUP);  // TIM4
   pinMode(PA15, INPUT_PULLUP);  // TIM2
   pinMode(PB3 , INPUT_PULLUP);  // TIM2

   // use custom function to switch to AlternateFuction.
   pinModeAF(PD12, GPIO_AF2_TIM4);
   pinModeAF(PD13, GPIO_AF2_TIM4);
   pinModeAF(PA15, GPIO_AF1_TIM2);
   pinModeAF(PB3 , GPIO_AF1_TIM2);

   TIM_HandleTypeDef       Encoder_Handle;
   TIM_Encoder_InitTypeDef sEncoderConfig;

   Encoder_Handle.Init.Period             = 65535;
   Encoder_Handle.Init.Prescaler          = 0;
   Encoder_Handle.Init.ClockDivision      = 0;
   Encoder_Handle.Init.CounterMode        = TIM_COUNTERMODE_UP;
   Encoder_Handle.Init.RepetitionCounter  = 0;
   Encoder_Handle.Init.AutoReloadPreload  = TIM_AUTORELOAD_PRELOAD_DISABLE;

   sEncoderConfig.EncoderMode             = TIM_ENCODERMODE_TI12;

   sEncoderConfig.IC1Polarity             = TIM_ICPOLARITY_RISING;
   sEncoderConfig.IC1Selection            = TIM_ICSELECTION_DIRECTTI;
   sEncoderConfig.IC1Prescaler            = TIM_ICPSC_DIV1;
   sEncoderConfig.IC1Filter               = 0;

   sEncoderConfig.IC2Polarity             = TIM_ICPOLARITY_RISING;
   sEncoderConfig.IC2Selection            = TIM_ICSELECTION_DIRECTTI;
   sEncoderConfig.IC2Prescaler            = TIM_ICPSC_DIV1;
   sEncoderConfig.IC2Filter               = 0;

   Encoder_Handle.Instance = TIM4;
   enableTimerClock(&Encoder_Handle);
   if(HAL_TIM_Encoder_Init(&Encoder_Handle, &sEncoderConfig) != HAL_OK) Serial.println("Init error of TIM4");
   HAL_TIM_Encoder_Start(&Encoder_Handle, TIM_CHANNEL_ALL);

   Encoder_Handle.Instance = TIM2;
   enableTimerClock(&Encoder_Handle);
   if(HAL_TIM_Encoder_Init(&Encoder_Handle, &sEncoderConfig) != HAL_OK) Serial.println("Init error of TIM2");
   HAL_TIM_Encoder_Start(&Encoder_Handle, TIM_CHANNEL_ALL);
}
