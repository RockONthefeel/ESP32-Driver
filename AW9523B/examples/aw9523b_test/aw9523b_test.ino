/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : aw8523b_test.ino
  * @version        : v1.0 Drizzt
  * @brief          : 
  ******************************************************************************
  * @attention
  *
  * Copyright (c) Drizzt
  * All rights reserved.
  *
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
/* USER CODE BEGIN Includes */
#include <Wire.h>
#include <AW9523B.h>
/* USER CODE END Includes */


/* Private class prototypes---------------------------------------------------*/
/* USER CODE BEGIN PCP */
AW9523B aw9523b;
/* USER CODE END PCP */


/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
GPIO_InitTypeDef GPIO_InitStruct;
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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 0 */
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  aw9523b.begin();
  if(aw9523b.state == true)
  {
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Work_Mode = GPIO_MODE;
    GPIO_InitStruct.Pin_Mode = GPIO_INPUT;
    GPIO_InitStruct.Port0_Mode = PP;
    aw9523b.gpioInit(GPIO_P0, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Work_Mode = GPIO_MODE;
    GPIO_InitStruct.Pin_Mode = GPIO_OUTPUT;
    aw9523b.gpioInit(GPIO_P1, &GPIO_InitStruct);

    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_0, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_1, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_2, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_3, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_4, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_5, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_6, GPIO_PIN_SET);
    aw9523b.GPIO_WritePin(GPIO_P1, GPIO_PIN_7, GPIO_PIN_SET);
  }
  else Serial.println("AW9523B Init Failed");
}
/* USER CODE END 0 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
void loop()
{
  if(aw9523b.state == true)
  {
    Serial.printf("GPIO_PIN_0 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_0));
    Serial.printf("GPIO_PIN_1 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_1));
    Serial.printf("GPIO_PIN_2 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_2));
    Serial.printf("GPIO_PIN_3 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_3));
    Serial.printf("GPIO_PIN_4 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_4));
    Serial.printf("GPIO_PIN_5 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_5));
    Serial.printf("GPIO_PIN_6 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_6));
    Serial.printf("GPIO_PIN_7 state:[%d]\n", aw9523b.GPIO_ReadPin(GPIO_P0, GPIO_PIN_7));
  }
  delay(1000);
}
/* USER CODE END 1 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 2 */

/* USER CODE END 2 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 3 */

/* USER CODE END 3 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 5 */

/* USER CODE END 5 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 6 */

/* USER CODE END 6 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 7 */

/* USER CODE END 7 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 8 */

/* USER CODE END 8 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 9 */

/* USER CODE END 9 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 10 */

/* USER CODE END 10 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 11 */

/* USER CODE END 11 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 12 */

/* USER CODE END 12 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 13 */

/* USER CODE END 13 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 14 */

/* USER CODE END 14 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 15 */

/* USER CODE END 15 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 16 */

/* USER CODE END 16 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 17 */

/* USER CODE END 17 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 18 */

/* USER CODE END 18 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 19 */

/* USER CODE END 19 */


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Drizzt *****END OF FILE****/
