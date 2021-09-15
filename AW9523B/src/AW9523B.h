/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : AW9523B.h
  * @version        : v1.0 Drizzt
  * @brief          : Header for AW9523B.cpp file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AW9523B__H__
#define __AW9523B__H__

/* Includes ------------------------------------------------------------------*/
#include <Arduino.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */


/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/** AW9523B Port work mode select */
typedef enum __GPIO_WorkMode
{
  LED_MODE    = 0U, // LED_MODE
  GPIO_MODE   = 1U, // GPIO_MODE
}GPIO_WorkMode;

/** AW9523B Port0 mode select, only port0 can be changed*/
typedef enum __AW9523B_Port0_Mode
{
  OD  = 0x00, // P0 open drain mode
  PP  = 0x10, // P0 push pull mode
}AW9523B_Port0_Mode;

/** AW9523B Pin work mode select */
typedef enum __GPIO_Pin_Mode
{
  GPIO_OUTPUT = 0U,
  GPIO_INPUT  = 1U,
}GPIO_Pin_Mode;

typedef enum __GPIO_PinNum
{
  GPIO_PIN_0 = 0x01,
  GPIO_PIN_1 = 0x02,
  GPIO_PIN_2 = 0x04,
  GPIO_PIN_3 = 0x08,
  GPIO_PIN_4 = 0x10,
  GPIO_PIN_5 = 0x20,
  GPIO_PIN_6 = 0x40,
  GPIO_PIN_7 = 0x80,
}GPIO_PinNum;

typedef enum __GPIO_PinState
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET   = 1U,
  GPIO_PIN_ERR   = 2U,
}GPIO_PinState;

/** AW9523B Port constants */
typedef enum __AW9523B_Port
{
  GPIO_P0 = 0U, // Port 0
  GPIO_P1 = 1U, // Port 1
}AW9523B_Port;

/** AW9523B Port0 LED dimmer constants: 256 step dimming range select*/
typedef enum __AW9523B_Led_MaxDim
{
  DIM_MAX = 0x00, // 0~IMAX:37mA(typical)
  DIM_MED = 0x01, // 0~(IMAX×3/4)
  DIM_LOW = 0x02, // 0~(IMAX×2/4)
  DIM_MIN = 0x03, // 0~(IMAX×1/4)
}AW9523B_Led_MaxDim;

/** AW9523B LED dimm current control registers*/
typedef enum __AW9523B_LedDimCtrl
{
  P1_0 = 0x20, // DIM0
  P1_1 = 0x21, // DIM1
  P1_2 = 0x22, // DIM2
  P1_3 = 0x23, // DIM3
  P0_0 = 0x24, // DIM4
  P0_1 = 0x25, // DIM5
  P0_2 = 0x26, // DIM6
  P0_3 = 0x27, // DIM7
  P0_4 = 0x28, // DIM8
  P0_5 = 0x29, // DIM9
  P0_6 = 0x2A, // DIM10
  P0_7 = 0x2B, // DIM11
  P1_4 = 0x2C, // DIM12
  P1_5 = 0x2D, // DIM13
  P1_6 = 0x2E, // DIM14
  P1_7 = 0x2F, // DIM15
}AW9523B_LedDimCtrl;

typedef struct __GPIO_InitTypeDef
{
  uint8_t Pin;        /* Specifies the GPIO pins to be configured.*/
  uint8_t Work_Mode;  /* GPIO or LED */
  uint8_t Pin_Mode;   /* Specifies the operating mode(Input or Output) for the selected pins.*/
  AW9523B_Port0_Mode Port0_Mode;  /* If Port0, select port mode(OD or PP);Port1 only have PP mode */
  AW9523B_Led_MaxDim max_dim; 
}GPIO_InitTypeDef;

typedef void (*AW9523B_Event)(void);
/* USER CODE END ET */


/* Exported define ------------------------------------------------------------*/
/* USER CODE BEGIN ED */
#define AW9523B_I2C_ADDRESS         0x58  // I2C base address for AW9523B
#define AW9523B_ID                  0x23  // id value
/** Registers */
#define AW9523B_P0_IN_REG           0x00  // P0 port input register
#define AW9523B_P1_IN_REG           0x01  // P1 port input register
#define AW9523B_P0_OUT_REG          0x02  // P0 port output register
#define AW9523B_P1_OUT_REG          0x03  // P1 port output register
#define AW9523B_P0_CONF_REG         0x04  // P0 port config register
#define AW9523B_P1_CONF_REG         0x05  // P1 port config register
#define AW9523B_P0_INT_CONF_REG     0x06  // P0 input interrupt config register
#define AW9523B_P1_INT_CONF_REG     0x07  // P1 input interrupt config register
#define AW9523B_ID_REG              0x10  // id register
#define AW9523B_GLOB_CTR_REG        0x11  // Global control register
#define AW9523B_P0_LED_MODE         0x12  // P0 port led mode switch register
#define AW9523B_P1_LED_MODE         0x13  // P1 port led mode switch register
#define AW9523B_SOFT_RST_REG        0x7F  // Soft reset register
/* USER CODE END ED */


/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */


/* Exported variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */


/* Exported class prototypes---------------------------------------------------*/
/* USER CODE BEGIN ECP */
class AW9523B
{
  private:
    uint8_t _addr;
    uint8_t _id;
    uint8_t _port0Mode;
    uint8_t _maxDim;
    int32_t _int_pin = -1;
    
    uint8_t GPIO_P0_workMode  = 0xFF; // GPIO:bit=1;LED:bit=0
    uint8_t GPIO_P1_workMode  = 0xFF;
    uint8_t GPIO_P0_pinMode   = 0xFF; // Input:bit=1;Output:bit=0
    uint8_t GPIO_P1_pinMode   = 0xFF;
    uint8_t GPIO_P0_IN_Data   = 0x00; // HIGH:bit=1;LOW:bit=0
    uint8_t GPIO_P1_IN_Data   = 0x00;
    uint8_t GPIO_P0_OUT_Data  = 0x00; // HIGH:bit=1;LOW:bit=0
    uint8_t GPIO_P1_OUT_Data  = 0x00;
    uint8_t GPIO_P0_INT_CONF  = 0xFF; // EN:bit=1;DISEN:bit=0
    uint8_t GPIO_P1_INT_CONF  = 0xFF;
    uint8_t readI2C(uint8_t Reg);
    uint8_t writeI2C(uint8_t Reg, uint8_t Val);
  public:
    bool state;
	bool begin(void);
	bool begin(bool AD0, bool AD1);
    bool begin(uint8_t Addr, bool AD0, bool AD1);
    void gpioInit(AW9523B_Port GPIO_Port, GPIO_InitTypeDef *GPIO_Init);
    GPIO_PinState GPIO_ReadPin(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin);
    void GPIO_WritePin(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_PinState PinState);
    void GPIO_Set_WorkMode(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_WorkMode Work_Mode);
    void GPIO_Set_PinMode(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, GPIO_Pin_Mode Pin_Mode);
    void GPIO_Set_Port0Mode(AW9523B_Port0_Mode Port0_Mode);
    void GPIO_INTPIN_Enable(AW9523B_Port GPIO_Port, uint8_t GPIO_Pin);
    void GPIO_INTPIN_Disable(AW9523B_Port GPIO_Port, uint8_t GPIO_Pin);
    void LED_MaxDim_Config(AW9523B_Led_MaxDim Value);
    void LED_Dim_Set(AW9523B_Port GPIO_Port, GPIO_PinNum GPIO_Pin, uint8_t Value);
    void onEvent(AW9523B_Event aw9523b_event, int32_t EXTI_PIN);
    void removeEvent(void);
    uint8_t readData(uint8_t Reg);
    void writeData(uint8_t Reg, uint8_t Data);
    void Solf_Reset(void);
};
/* USER CODE END ECP */


/*
 * -- Insert exported functions declaration here --
 */
/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* __AW9523B__H__ */

/************************ (C) COPYRIGHT Drizzt *****END OF FILE****/
