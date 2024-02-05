/*
 * DC_MOTOR.h
 *
 *  Created on: Sep 24, 2023
 *      Author: Kareem
 */

#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_
#include "main.h"
#include "../../Drivers/STM32F3xx_HAL_Driver/Inc/stm32f3xx_hal.h"

#define Forward 0
#define Reverse 1
#define Right 0
#define Left 1

#define DC_PORT 	GPIOC

#define IN1_PIN 	 GPIO_PIN_6
#define IN2_PIN		 GPIO_PIN_7
#define IN3_PIN		 GPIO_PIN_8
#define IN4_PIN		 GPIO_PIN_9

void RL_motor_init();
void FR_motor_init();
void Set_motor_RL_direction(unsigned char dir);
void Set_motor_FR_direction(unsigned char dir);
void Stop_motor_RL();
void Stop_motor_FR();
//void Set_pwm_duty_FR_motor(int duty);
void Set_pwm_duty_FR_motor(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t period, float duty);



#endif /* INC_DC_MOTOR_H_ */
