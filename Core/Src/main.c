/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DC_MOTOR.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t count[4];
uint16_t t1[4];
uint16_t t2[4];
uint16_t diff[4];
uint16_t d[4];
uint16_t trig_flag=0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)	// ISR for timer1
{
	//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	if (htim->Instance == TIM2) {
		// Check if the callback is triggered by the correct timer (TIMx)
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			// Check if the callback is triggered by the correct channel (x)
			if(count[0] == 0)
			{
				t1[0]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[0]=1;
			}
			else if(count[0] == 1)
			{
				t2[0]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[0]=0;
				if(t2[0]>t1[0])
				{
					diff[0]=t2[0]-t1[0];
				}
				else if(t1[0]>t2[0])
				{
					diff[0] = ((0xffff-t1[0])+t2[0])+1;
				}
				d[0]=diff[0]/58;
			}
			// Your code here for handling the IC event on the specified timer and channel
		}
	}
	else if (htim->Instance == TIM3) {
		// Check if the callback is triggered by the correct timer (TIMx)

		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			// Check if the callback is triggered by the correct channel (x)
			if(count[1] == 0)
			{
				t1[1]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[1]=1;
			}
			else if(count[1] == 1)
			{
				t2[1]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[1]=0;
				if(t2[1]>t1[1])
				{
					diff[1]=t2[1]-t1[1];
				}
				else if(t1[1]>t2[1])
				{
					diff[1] = ((0xffff-t1[1])+t2[1])+1;
				}
				d[1]=diff[1]/58;
			}
			// Your code here for handling the IC event on the specified timer and channel
		}
	}
	else if (htim->Instance == TIM4) {
		// Check if the callback is triggered by the correct timer (TIMx)
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			// Check if the callback is triggered by the correct channel (x)
			if(count[2] == 0)
			{
				t1[2]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[2]=1;
			}
			else if(count[2] == 1)
			{
				t2[2]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[2]=0;
				if(t2[2]>t1[2])
				{
					diff[2]=t2[2]-t1[2];
				}
				else if(t1[2]>t2[2])
				{
					diff[2] = ((0xffff-t1[2])+t2[2])+1;
				}
				d[2]=diff[2]/58;
			}
			// Your code here for handling the IC event on the specified timer and channel
		}
	}
	else if (htim->Instance == TIM15) {
		// Check if the callback is triggered by the correct timer (TIMx)

		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			// Check if the callback is triggered by the correct channel (x)
			if(count[3] == 0)
			{
				t1[3]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[3]=1;
			}
			else if(count[3] == 1)
			{
				t2[3]=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
				count[3]=0;
				if(t2[3]>t1[3])
				{
					diff[3]=t2[3]-t1[3];
				}
				else if(t1[3]>t2[3])
				{
					diff[3] = ((0xffff-t1[3])+t2[3])+1;
				}
				d[3]=diff[3]/58;
			}
			// Your code here for handling the IC event on the specified timer and channel
		}
	}

	//	c++;
	//	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
	//	if(count == 0)
	//	{
	//		t1=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
	//		count=1;
	//	}
	//	else if(count == 1)
	//	{
	//		t2=HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
	//		count=0;
	//		if(t2>t1)
	//		{
	//			diff=t2-t1;
	//		}
	//		else if(t1>t2)
	//		{
	//			diff = ((0xffff-t1)+t2)+1;
	//		}
	//		d[3]=diff/58;
	//		//d[0]=diff/58;
	//		trig_flag++;
	//	}
}

void Ultrasonic_Runable(void)
{
	if(trig_flag==0)
	{
		HAL_GPIO_WritePin(TRIGGER1_GPIO_Port,TRIGGER1_Pin , GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIGGER1_GPIO_Port,TRIGGER1_Pin, GPIO_PIN_RESET);
		trig_flag=1;
	}
	else if(trig_flag==1)
	{
		HAL_GPIO_WritePin(TRIGGER2_GPIO_Port,TRIGGER2_Pin , GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIGGER2_GPIO_Port,TRIGGER2_Pin, GPIO_PIN_RESET);
		trig_flag=2;
	}
	else if(trig_flag==2)
	{
		HAL_GPIO_WritePin(TRIGGER3_GPIO_Port,TRIGGER3_Pin , GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIGGER3_GPIO_Port,TRIGGER3_Pin, GPIO_PIN_RESET);
		trig_flag=3;
	}
	else if(trig_flag==3)
	{
		HAL_GPIO_WritePin(TRIGGER4_GPIO_Port,TRIGGER4_Pin , GPIO_PIN_SET);
		HAL_Delay(1);
		HAL_GPIO_WritePin(TRIGGER4_GPIO_Port,TRIGGER4_Pin, GPIO_PIN_RESET);
		trig_flag=0;
	}
	HAL_Delay(15);
}
uint16_t Ultrasonic_Getter(uint8_t ultrasonic_N)
{
	if(ultrasonic_N<4)
	{
		return d[ultrasonic_N];
	}
	return 0;
}

void send_distance(void)
{
	uint8_t x10='1';
	HAL_UART_Transmit(&huart4,&x10,sizeof(x10),20);
	uint8_t x11='.';
	HAL_UART_Transmit(&huart4,&x11,sizeof(x11),20);
	uint16_t N=55;
	N=d[0];
	while(N)
	{
		uint8_t d=(N%10)+'0';
		HAL_UART_Transmit(&huart4, &d,sizeof(d),20);
		N=N/10;
	}
	uint8_t x='_';
	HAL_UART_Transmit(&huart4, &x,sizeof(x),20);
	/////////////////////////////////////
	uint8_t x2='2';
	HAL_UART_Transmit(&huart4,&x2,sizeof(x),20);
	uint8_t x3='.';
	HAL_UART_Transmit(&huart4,&x3,sizeof(x),20);
	uint16_t N1=55;
	N1=d[1];
	while(N1)
	{
		uint8_t d1=(N1%10)+'0';
		HAL_UART_Transmit(&huart4, &d1,sizeof(d1),20);
		N1=N1/10;
	}
	uint8_t x1='_';
	HAL_UART_Transmit(&huart4, &x1,sizeof(x),20);

	////////////////////////////////////////////////
	uint8_t x4='3';
	HAL_UART_Transmit(&huart4,&x4,sizeof(x),20);
	uint8_t x5='.';
	HAL_UART_Transmit(&huart4,&x5,sizeof(x),20);
	uint16_t N2=55;
	N2=d[2];
	while(N2)
	{
		uint8_t d2=(N2%10)+'0';
		HAL_UART_Transmit(&huart4, &d2,sizeof(d2),20);
		N2=N2/10;
	}
	HAL_UART_Transmit(&huart4, &x1,sizeof(x),20);
	////////////////////////////////////////////////
	uint8_t x6='4';
	HAL_UART_Transmit(&huart4,&x6,sizeof(x),20);
	uint8_t x7='.';
	HAL_UART_Transmit(&huart4,&x7,sizeof(x),20);
	uint16_t N3=55;
	N3=d[3];
	while(N3)
	{
		uint8_t d3=(N3%10)+'0';
		HAL_UART_Transmit(&huart4, &d3,sizeof(d3),20);
		N3=N3/10;
	}
	HAL_UART_Transmit(&huart4, &x1,sizeof(x),20);
	////////////////////////////////////////////////
}
uint8_t Data;
void control_car(void)
{
	if(Data == 'R'){
		Set_motor_RL_direction(Right);
	}else if(Data == 'L'){
		Set_motor_RL_direction(Left);
	}else if(Data == 'F'){
		Set_motor_FR_direction(Forward);
	}else if(Data == 'B'){
		Set_motor_FR_direction(Reverse);
	}else if(Data == 'G'){
		Set_motor_FR_direction(Forward);
		Set_motor_RL_direction(Left);
	}else if(Data == 'I'){
		Set_motor_FR_direction(Forward);
		Set_motor_RL_direction(Right);
	}else if(Data == 'H'){
		Set_motor_FR_direction(Reverse);
		Set_motor_RL_direction(Left);
	}else if(Data == 'J'){
		Set_motor_FR_direction(Reverse);
		Set_motor_RL_direction(Right);
	}
	else{
		Stop_motor_FR();
		Stop_motor_RL();
	}
}
uint8_t Mode_Flag=0;
void find_park(void)
{
	static uint8_t count=0;
	static uint8_t park_not_found=0;
	//	static uint8_t park_found=0;
	//	if((d[1]>=20)&&(d[2]>=20) )
	//	{
	//
	//		park_found=1;
	//		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1, 40, 0.85);
	//
	//	}
	//	else if(park_found==1 && (d[1]<20) && (d[2]>20))
	//	{
	//
	//		park_not_found=1;
	//		Stop_motor_FR();
	//		Stop_motor_RL();
	//		Mode_Flag=2;
	//	}
	//	else if(park_not_found==0	||	(d[1]<20)	||	(d[2]<20)	)
	//	{
	//		park_not_found=1;
	//		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1, 40, 0.96);
	//		Set_motor_FR_direction(Forward);
	//		HAL_Delay(5);
	//		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,40, 0.90);
	//	}
	if((d[1]>=20)&&(d[2]>=20))
	{
		count++;
	}
	else if(park_not_found==0	&&(	(d[1]<20)	||	(d[2]<20)	))
	{
		park_not_found=1;
		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1, 100, 1);
		Set_motor_FR_direction(Forward);
		HAL_Delay(5);
		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.93);
		count=0;
	}
	if(count>=50||(d[1]<=12&&count>5)) //45 is a good value //
	{
		//park_not_found=0;
		//HAL_Delay(120);
		Stop_motor_FR();
		Stop_motor_RL();
		Mode_Flag=2;
	}
}

void start_parking()
{
	static uint8_t phase=0;
	static  uint8_t TimerToStop=0;
	static  uint8_t t5mesa_timer=0;
	static  uint8_t IR_handle_flag=0;
	//static  uint8_t phase_6_time_out=0;
	static  uint8_t kareem_counter=0;
	static  uint8_t kareem_flag=0;

	TimerToStop++;
	if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)==1))
	{
		IR_handle_flag=1;
	}
	if(TimerToStop>=60)
	{
		if(phase==0)
		{
			Set_motor_RL_direction(Right);
			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.75);//795
			Set_motor_FR_direction(Reverse);
			phase=1;
		}
		else if(	( phase== 1 )   && (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5)==0) && IR_handle_flag==1)
		{
			Stop_motor_FR();
			Stop_motor_RL();
			//Set_motor_FR_direction(Forward);
			phase=2;
		}
		else if(phase==2)
		{
			HAL_Delay(100);
			Set_motor_RL_direction(Right);
			HAL_Delay(50);
			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.978);//0.98
			Set_motor_FR_direction(Forward);
			HAL_Delay(900);
			Stop_motor_FR();
			Stop_motor_RL();
			phase=3;
		}
		else if(phase==3)
		{
			HAL_Delay(100);
			Set_motor_RL_direction(Left);
			HAL_Delay(50);
			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.83);
			Set_motor_FR_direction(Reverse);

			phase=4;
		}
		else if(phase==4&&((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)==0)||t5mesa_timer>=28))//35
		{
			Stop_motor_RL();
			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 1);
			Set_motor_FR_direction(Forward);
			Set_motor_RL_direction(Right);
			HAL_Delay(150);
			Stop_motor_FR();
			Stop_motor_RL();
			phase=5;

		}
		else if(phase==4)
		{
			t5mesa_timer++;
		}
		else if(phase==5)
		{
			if(kareem_flag==0)
			{

				phase = 2 ;
				kareem_flag=1;
			}
			else if(kareem_counter !=1)
			{
				if(d[1]>8 && d[2]>8 )
				{
					phase =3;
					kareem_counter++;
				}
				else {
								phase=6;
					}
			}

			//			HAL_Delay(50);
			//			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.94);
			//			Set_motor_RL_direction(Right);
			//			Set_motor_FR_direction(Forward);


		}
		else if(phase==6)//&&(phase_6_time_out>=20))
		{
			Stop_motor_FR();
			Stop_motor_RL();
			Mode_Flag=3;
		}
		//		else if(phase==6)
		//		{
		//			phase_6_time_out++;
		//		}
		TimerToStop=100;
	}



	//else if(phase==2)
	//{
	//	Set_motor_RL_direction(Left);
	//	Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,40, 0.9);
	//	Set_motor_FR_direction(Reverse);
	//	phase=3;
	//	HAL_Delay(50);
	//}
	//else if(phase==3 && d[0]<16)
	//{
	//	Stop_motor_FR();
	//	Stop_motor_RL();
	//	phase=4;
	//}




}
void ta7deen(){
	while(d[1]>5 && d[2]>5){
		Ultrasonic_Runable();
		//phase 2  [right&forward]

		HAL_Delay(50);
		Set_motor_RL_direction(Right);
		HAL_Delay(50);
		Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1,100, 0.97);
		Set_motor_FR_direction(Forward);
		HAL_Delay(500);
		Stop_motor_FR();
		Stop_motor_RL();
		HAL_Delay(50);
		if(d[1]<=5 && d[2]<=5){
			break;
		}

	}
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM1_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();
	MX_TIM15_Init();
	MX_UART4_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim4, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1, 40, 1);
	//	Mode_Flag=2;
	while (1)
	{
		Ultrasonic_Runable();
		send_distance();
		//		uint8_t IR=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)+'0';
		//		HAL_UART_Transmit(&huart4,&IR,sizeof(IR),20);
		//		uint8_t IR=HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)+'0';
		//		HAL_UART_Transmit(&huart4,&IR,sizeof(IR),20);
		HAL_UART_Receive(&huart4, &Data, sizeof(Data), 10);
		if(Data=='V')
		{
			//			Set_pwm_duty_FR_motor(&htim1, TIM_CHANNEL_1, 40, 0.93 );
			Mode_Flag=1;
		}
		else if(Data=='v')
		{
			Mode_Flag=0;
		}

		//-----------------------------------

		if(Mode_Flag==0)
		{
			control_car();
		}
		if(Mode_Flag==1)
		{
			find_park();
		}
		else if(Mode_Flag==2)
		{
			start_parking();

		}	/*else if(Mode_Flag==3)
		{
			ta7deen();
		}
		 */

		//HAL_Delay(1000);
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_UART4
			|RCC_PERIPHCLK_TIM1|RCC_PERIPHCLK_TIM15
			|RCC_PERIPHCLK_TIM2|RCC_PERIPHCLK_TIM34;
	PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
	PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
	PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
	PeriphClkInit.Tim15ClockSelection = RCC_TIM15CLK_HCLK;
	PeriphClkInit.Tim2ClockSelection = RCC_TIM2CLK_HCLK;
	PeriphClkInit.Tim34ClockSelection = RCC_TIM34CLK_HCLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
