HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  while (1)
  {
  for(int i=0;i<100;i++)
		{
			__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1 ,i);
			HAL_Delay (50);
		}
		for(int i=99;i>=0;i--)
		{
			__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1 ,i);
			HAL_Delay (50);
		}
  }