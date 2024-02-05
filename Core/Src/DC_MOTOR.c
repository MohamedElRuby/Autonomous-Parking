/*
 * DC_MOTOR.c
 *
 *  Created on: Sep 24, 2023
 *      Author: Kareem
 */
#include "main.h"
#include "DC_MOTOR.h"

void Set_motor_RL_direction(unsigned char dir)
{
	if(dir==Right)
	{
		HAL_GPIO_WritePin(DC_PORT,IN1_PIN,1);
		HAL_GPIO_WritePin(DC_PORT, IN2_PIN,0);
	}
	else if(dir==Left) {
		HAL_GPIO_WritePin(DC_PORT,IN1_PIN,0);
		HAL_GPIO_WritePin(DC_PORT, IN2_PIN,1);
	}
	else{
		Stop_motor_RL();
	}
}
void Set_motor_FR_direction(unsigned char dir)
{
	if(dir==Forward)
	{


		HAL_GPIO_WritePin(DC_PORT, IN3_PIN,0);
		HAL_GPIO_WritePin(DC_PORT, IN4_PIN,1);
	}
	else if(dir==Reverse) {
		HAL_GPIO_WritePin(DC_PORT, IN3_PIN,1);
		HAL_GPIO_WritePin(DC_PORT, IN4_PIN,0);
	}
	else{
		Stop_motor_FR();
	}
}

void Stop_motor_RL()
{
	HAL_GPIO_WritePin(DC_PORT,IN1_PIN, 0);
	HAL_GPIO_WritePin(DC_PORT,IN2_PIN, 0);
}
void Stop_motor_FR()
{
	HAL_GPIO_WritePin(DC_PORT, IN3_PIN, 0);
	HAL_GPIO_WritePin(DC_PORT, IN4_PIN, 0);


}

//void Set_pwm_duty_FR_motor(int duty)
//{
//	/*PRESCALER 16*/
//	/*FREQ PWM = 1KHZ*/
//	/*ARR = 1000 */
//	/*duty 50%= CCR1=500*/
//	/*factor==10*/
//	//duty*=250;
//	//TIM1->CCR1=duty;
//
//}




/* @param  Channel TIM Channels to be enabled
  *          This parameter can be one of the following values:
  *            @arg TIM_CHANNEL_1: TIM Channel 1 selected
  *            @arg TIM_CHANNEL_2: TIM Channel 2 selected
  *            @arg TIM_CHANNEL_3: TIM Channel 3 selected
  *            @arg TIM_CHANNEL_4: TIM Channel 4 selected
  *
  *
  *   Set_pwm_duty__motor(htim1, TIM_CHANNEL_1, 40, 0.65);
  */
void Set_pwm_duty_FR_motor(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t period, float duty)
{
//	/*PRESCALER 8*/
//	/*FREQ PWM = 25KHZ*/
//	/*ARR = 1000 */
//	/*duty 50%= CCR1=500*/
//	/*factor==10*/
//	//duty*=250;
//	//TIM1->CCR4=duty;
////40//.5//.2

	htim->Instance->ARR = period;
	htim->Instance->CCR1 = (uint32_t)(period * duty);
	HAL_TIM_PWM_Start(htim, Channel);


}



