/* DRV8334.h
Author: PEBS
*/

#ifndef DRV8334_H
#define DRV8334_H
#include "main.h"
#include "DRV8334_regs.h"

/* Register addresses (datasheet) */
#define DRV8334_IC_STAT1   0x00
#define DRV8334_IC_STAT2   0x01
#define DRV8334_IC_STAT3   0x02
#define DRV8334_IC_STAT4   0x03
#define DRV8334_IC_STAT5   0x04
#define DRV8334_IC_STAT6   0x05
#define DRV8334_IC_CTRL1   0x1A
#define DRV8334_IC_CTRL2   0x1B
#define DRV8334_IC_CTRL3   0x1C
#define DRV8334_GD_CTRL1   0x1E
#define DRV8334_GD_CTRL2   0x1F
#define DRV8334_GD_CTRL3   0x21
#define DRV8334_GD_CTRL3B  0x22
#define DRV8334_GD_CTRL4   0x23
#define DRV8334_GD_CTRL5   0x24
#define DRV8334_GD_CTRL6   0x25
#define DRV8334_GD_CTRL7   0x26
#define DRV8334_CSA_CTRL   0x29
#define DRV8334_MON_CTRL1  0x2B
#define DRV8334_MON_CTRL2  0x2C
#define DRV8334_MON_CTRL3  0x2D
#define DRV8334_MON_CTRL4  0x2E
#define DRV8334_MON_CTRL5  0x2F
#define DRV8334_MON_CTRL6  0x30
#define DRV8334_DIAG_CTRL1 0x33
#define DRV8334_SPI_TEST   0x36
#define DRV8334_OTP_USR    0x48

typedef struct{
    uint16_t DRV8334_CS_Pin;
    GPIO_TypeDef* DRV8334_CS_GPIO_Port;
    SPI_HandleTypeDef* hspi;
    uint8_t crc_enabled;  // 1 after power-up (SPI_CRC_EN reset value is 1)
    uint8_t last_status;  // first SDO byte: bit7 = FAULT, bits 6..0 = address echo
} DRV8334_t;


void DRV8334_Init(DRV8334_t *drv, uint16_t csPin, GPIO_TypeDef *csPort,
                  SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef DRV8334_WriteRegister(DRV8334_t *drv, uint8_t regAddress,
                                        uint16_t data);
HAL_StatusTypeDef DRV8334_ReadRegister(DRV8334_t *drv, uint8_t regAddress,
                                       uint16_t *data);
HAL_StatusTypeDef DRV8334_Disable_CRC(DRV8334_t *drv);

#endif
