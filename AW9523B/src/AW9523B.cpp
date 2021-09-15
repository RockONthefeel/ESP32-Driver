/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : AW9523B.cpp
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
#include "AW9523B.h"
/* USER CODE BEGIN Includes */
#include <Wire.h>
/* USER CODE END Includes */


/* Private class prototypes---------------------------------------------------*/
/* USER CODE BEGIN PCP */

/* USER CODE END PCP */


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
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 0 */
uint8_t AW9523B::readI2C(uint8_t Reg)
{
  Wire.beginTransmission(this->_addr);
  Wire.write(Reg);
  Wire.endTransmission();
  Wire.requestFrom(this->_addr, (byte)1);
  return Wire.read();
}
/* USER CODE END 0 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */
uint8_t AW9523B::writeI2C(uint8_t Reg, uint8_t Val)
{
  Wire.beginTransmission(this->_addr);
  Wire.write(Reg);
  Wire.write(Val);
  return Wire.endTransmission();
}
/* USER CODE END 1 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 2 */
bool AW9523B::begin(void)
{
  AW9523B::Solf_Reset();
  delay(10);
  this->_addr = AW9523B_I2C_ADDRESS;
  this->_id = AW9523B::readI2C(AW9523B_ID_REG);
  if(this->_id == AW9523B_ID)
    this->state = true;
  else
    this->state = false;
  return this->state;
}

bool AW9523B::begin(bool AD0, bool AD1)
{
  AW9523B::Solf_Reset();
  delay(10);
  this->_addr = (AW9523B_I2C_ADDRESS | (AD1 << 1)) | AD0;
  this->_id = AW9523B::readI2C(AW9523B_ID_REG);
  if(this->_id == AW9523B_ID)
    this->state = true;
  else
    this->state = false;
  return this->state;
}

bool AW9523B::begin(uint8_t Addr, bool AD0, bool AD1)
{
  AW9523B::Solf_Reset();
  delay(10);
  this->_addr = (Addr | (AD1 << 1)) | AD0;
  this->_id = AW9523B::readI2C(AW9523B_ID_REG);
  if(this->_id == AW9523B_ID)
    this->state = true;
  else
    this->state = false;
  return this->state;
}
/* USER CODE END 2 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 3 */
void AW9523B::gpioInit(AW9523B_Port GPIO_Port, GPIO_InitTypeDef *GPIO_Init)
{
  switch (GPIO_Init->Work_Mode)
  {
    case LED_MODE:
      this->_maxDim = GPIO_Init->max_dim;
      writeI2C(AW9523B_GLOB_CTR_REG, ((this->_maxDim)|(this->_port0Mode))&0x13);
      if(GPIO_Port == GPIO_P0)
      {
        for(uint8_t i=0;i<8;i++)
        {
          if(((GPIO_Init->Pin)>>i)&0x01)
          {
            this->GPIO_P0_workMode &= (~(0x01<<i));
          }
        }
        writeI2C(AW9523B_P0_LED_MODE, this->GPIO_P0_workMode);
      }
      else if(GPIO_Port == GPIO_P1)
      {
        for(uint8_t i=0;i<8;i++)
        {
          if(((GPIO_Init->Pin)>>i)&0x01)
          {
            this->GPIO_P1_workMode &= (~(0x01<<i));
          }
        }
        writeI2C(AW9523B_P1_LED_MODE, this->GPIO_P1_workMode);
      }
      break;
    
    case GPIO_MODE:
      if(GPIO_Port == GPIO_P0)
      {
        this->_port0Mode = GPIO_Init->Port0_Mode;
        writeI2C(AW9523B_GLOB_CTR_REG, ((this->_maxDim)|(this->_port0Mode))&0x13);
        for(uint8_t i=0;i<8;i++)
        {
          if(((GPIO_Init->Pin)>>i)&0x01)
          {
            this->GPIO_P0_workMode |= (0x01<<i);
            if(GPIO_Init->Pin_Mode == GPIO_OUTPUT)
            {
              this->GPIO_P0_pinMode &= (~(0x01<<i));
            }
            else if(GPIO_Init->Pin_Mode == GPIO_INPUT)
            {
              this->GPIO_P0_pinMode |= (0x01<<i);
            }
          }
        }
        writeI2C(AW9523B_P0_LED_MODE, this->GPIO_P0_workMode);
        writeI2C(AW9523B_P0_CONF_REG, this->GPIO_P0_pinMode);
      }
      else if(GPIO_Port == GPIO_P1)
      {
        for(uint8_t i=0;i<8;i++)
        {
          if(((GPIO_Init->Pin)>>i)&0x01)
          {
            this->GPIO_P1_workMode |= (0x01<<i);
            if(GPIO_Init->Pin_Mode == GPIO_OUTPUT)
            {
              this->GPIO_P1_pinMode &= (~(0x01<<i));
            }
            else if(GPIO_Init->Pin_Mode == GPIO_INPUT)
            {
              this->GPIO_P1_pinMode |= (0x01<<i);
            }
          }
        }
        writeI2C(AW9523B_P1_LED_MODE, this->GPIO_P1_workMode);
        writeI2C(AW9523B_P1_CONF_REG, this->GPIO_P1_pinMode);
      }
      break;

    default:
      break;
  }
}
/* USER CODE END 3 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 4 */
GPIO_PinState AW9523B::GPIO_ReadPin(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin)
{
  if(GPIO_Port == GPIO_P0)
  {
    this->GPIO_P0_IN_Data = readI2C(AW9523B_P0_IN_REG);
    for(uint8_t i=0;i<8;i++)
    {
      if((GPIO_Pin>>i)&0x01)
      {
        if(((this->GPIO_P0_IN_Data) >> i)&0x01)
          return GPIO_PIN_SET;
        else
          return GPIO_PIN_RESET;
      }
    }
    return GPIO_PIN_ERR;
  }
  else if(GPIO_Port == GPIO_P0)
  {
    this->GPIO_P1_IN_Data = readI2C(AW9523B_P1_IN_REG);
    for(uint8_t i=0;i<8;i++)
    {
      if((GPIO_Pin>>i)&0x01)
      {
        if(((this->GPIO_P1_IN_Data) >> i)&0x01)
          return GPIO_PIN_SET;
        else
          return GPIO_PIN_RESET;
      }
    }
    return GPIO_PIN_ERR;
  }
  else return GPIO_PIN_ERR;
}
/* USER CODE END 4 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 5 */
void AW9523B::GPIO_WritePin(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_PinState PinState)
{
  if(GPIO_Port == GPIO_P0)
  {
    if(PinState = GPIO_PIN_RESET)
    {
      this->GPIO_P0_OUT_Data &= (~GPIO_Pin);
      writeI2C(AW9523B_P0_OUT_REG, this->GPIO_P0_OUT_Data);
    }
    else if(PinState = GPIO_PIN_SET)
    {
      this->GPIO_P0_OUT_Data |= GPIO_Pin;
      writeI2C(AW9523B_P0_OUT_REG, this->GPIO_P0_OUT_Data);
    }
  }
  else if(GPIO_Port == GPIO_P1)
  {
    if(PinState = GPIO_PIN_RESET)
    {
      this->GPIO_P1_OUT_Data &= (~GPIO_Pin);
      writeI2C(AW9523B_P1_OUT_REG, this->GPIO_P1_OUT_Data);
    }
    else if(PinState = GPIO_PIN_SET)
    {
      this->GPIO_P1_OUT_Data |= GPIO_Pin;
      writeI2C(AW9523B_P1_OUT_REG, this->GPIO_P1_OUT_Data);
    }
  }
}
/* USER CODE END 5 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 6 */
void AW9523B::GPIO_Set_WorkMode(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_WorkMode Work_Mode)
{
  if(Work_Mode == LED_MODE)
  {
    if(GPIO_Port = GPIO_P0)
    {
      this->GPIO_P0_workMode &= (~GPIO_Pin);
      writeI2C(AW9523B_P0_LED_MODE, this->GPIO_P0_workMode);
    }
    else if(GPIO_Port = GPIO_P1)
    {
      this->GPIO_P1_workMode &= (~GPIO_Pin);
      writeI2C(AW9523B_P1_LED_MODE, this->GPIO_P1_workMode);
    }
  }
  else if(Work_Mode == GPIO_MODE)
  {
    if(GPIO_Port = GPIO_P0)
    {
      this->GPIO_P0_workMode |= GPIO_Pin;
      writeI2C(AW9523B_P0_LED_MODE, this->GPIO_P0_workMode);
    }
    else if(GPIO_Port = GPIO_P1)
    {
      this->GPIO_P1_workMode |= GPIO_Pin;
      writeI2C(AW9523B_P1_LED_MODE, this->GPIO_P1_workMode);
    }
  }
}
/* USER CODE END 6 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 7 */
void AW9523B::GPIO_Set_PinMode(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_Pin_Mode Pin_Mode)
{
  if(Pin_Mode == GPIO_OUTPUT)
  {
    if(GPIO_Port = GPIO_P0)
    {
      this->GPIO_P0_pinMode &= (~GPIO_Pin);
      writeI2C(AW9523B_P0_CONF_REG, this->GPIO_P0_pinMode);
    }
    else if(GPIO_Port = GPIO_P1)
    {
      this->GPIO_P1_pinMode &= (~GPIO_Pin);
      writeI2C(AW9523B_P1_CONF_REG, this->GPIO_P1_pinMode);
    }
  }
  else if(Pin_Mode == GPIO_INPUT)
  {
    if(GPIO_Port = GPIO_P0)
    {
      this->GPIO_P0_pinMode |= GPIO_Pin;
      writeI2C(AW9523B_P0_CONF_REG, this->GPIO_P0_pinMode);
    }
    else if(GPIO_Port = GPIO_P1)
    {
      this->GPIO_P1_pinMode |= GPIO_Pin;
      writeI2C(AW9523B_P1_CONF_REG, this->GPIO_P1_pinMode);
    }
  }
}
/* USER CODE END 7 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 8 */
void AW9523B::GPIO_Set_Port0Mode(AW9523B_Port0_Mode Port0_Mode)
{
  uint8_t data = readI2C(AW9523B_GLOB_CTR_REG);
  this->_maxDim = data&0x03;
  this->_port0Mode = Port0_Mode&0x10;
  writeI2C(AW9523B_GLOB_CTR_REG, ((this->_maxDim)|(this->_port0Mode))&0x13);
}
/* USER CODE END 8 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 9 */
void AW9523B::GPIO_INTPIN_Enable(AW9523B_Port GPIO_Port, uint8_t GPIO_Pin)
{
  if(GPIO_Port == GPIO_P0)
  {
    this->GPIO_P0_INT_CONF &= (~GPIO_Pin);
    writeI2C(AW9523B_P0_INT_CONF_REG, this->GPIO_P0_INT_CONF);
  }
  else if(GPIO_Port == GPIO_P1)
  {
    this->GPIO_P1_INT_CONF &= (~GPIO_Pin);
    writeI2C(AW9523B_P1_INT_CONF_REG, this->GPIO_P1_INT_CONF);
  }
}
/* USER CODE END 9 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 9 */
void AW9523B::GPIO_INTPIN_Disable(AW9523B_Port GPIO_Port, uint8_t GPIO_Pin)
{
  if(GPIO_Port == GPIO_P0)
  {
    this->GPIO_P0_INT_CONF |= GPIO_Pin;
    writeI2C(AW9523B_P0_INT_CONF_REG, this->GPIO_P0_INT_CONF);
  }
  else if(GPIO_Port == GPIO_P1)
  {
    this->GPIO_P1_INT_CONF |= GPIO_Pin;
    writeI2C(AW9523B_P1_INT_CONF_REG, this->GPIO_P1_INT_CONF);
  }
}
/* USER CODE END 9 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 11 */
void AW9523B::LED_MaxDim_Config(AW9523B_Led_MaxDim Value)
{
  uint8_t data = readI2C(AW9523B_GLOB_CTR_REG);
  this->_port0Mode = data&0x10;
  this->_maxDim = Value&0x03;
  writeI2C(AW9523B_GLOB_CTR_REG, ((this->_maxDim)|(this->_port0Mode))&0x13);
}
/* USER CODE END 11 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 12 */
void AW9523B::LED_Dim_Set(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, uint8_t Value)
{
  if(GPIO_Port == GPIO_P0)
  {
    switch (GPIO_Pin)
    {
      case GPIO_PIN_0:
        writeI2C(P0_0, Value);
        break;
      case GPIO_PIN_1:
        writeI2C(P0_1, Value);
        break;
      case GPIO_PIN_2:
        writeI2C(P0_2, Value);
        break;
      case GPIO_PIN_3:
        writeI2C(P0_3, Value);
        break;
      case GPIO_PIN_4:
        writeI2C(P0_4, Value);
        break;
      case GPIO_PIN_5:
        writeI2C(P0_5, Value);
        break;
      case GPIO_PIN_6:
        writeI2C(P0_6, Value);
        break;
      case GPIO_PIN_7:
        writeI2C(P0_7, Value);
        break;
      default:
        break;
    }
  }
  else if(GPIO_Port == GPIO_P1)
  {
    switch (GPIO_Pin)
    {
      case GPIO_PIN_0:
        writeI2C(P1_0, Value);
        break;
      case GPIO_PIN_1:
        writeI2C(P1_1, Value);
        break;
      case GPIO_PIN_2:
        writeI2C(P1_2, Value);
        break;
      case GPIO_PIN_3:
        writeI2C(P1_3, Value);
        break;
      case GPIO_PIN_4:
        writeI2C(P1_4, Value);
        break;
      case GPIO_PIN_5:
        writeI2C(P1_5, Value);
        break;
      case GPIO_PIN_6:
        writeI2C(P1_6, Value);
        break;
      case GPIO_PIN_7:
        writeI2C(P1_7, Value);
        break;
      default:
        break;
    }
  }
}
/* USER CODE END 12 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 13 */
void AW9523B::onEvent(AW9523B_Event aw9523b_event, int32_t EXTI_PIN)
{
  this->_int_pin = EXTI_PIN;
  attachInterrupt(this->_int_pin, aw9523b_event, FALLING);
}
/* USER CODE END 13 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 14 */
void AW9523B::removeEvent(void)
{
  if(this->_int_pin != -1)
  {
    detachInterrupt(this->_int_pin);
  }
}
/* USER CODE END 14 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 15 */
uint8_t AW9523B::readData(uint8_t Reg)
{
  return readI2C(Reg);
}
/* USER CODE END 15 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 16 */
void AW9523B::writeData(uint8_t Reg, uint8_t Data)
{
  writeI2C(Reg, Data);
}
/* USER CODE END 16 */


/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 17 */
void AW9523B::Solf_Reset(void)
{
  writeI2C(AW9523B_SOFT_RST_REG, 0x00);
}
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
