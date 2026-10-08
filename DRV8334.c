/* DRV8334.c
Author: PEBS
DRV8334 motor driver IC library for stm32cubemx HAL
Will be used in PBSESC, and future proyects such as PEBS_X LV inverter.
Im spanish so you will find some comments in spanish, sorry for that.
*/

#include "DRV8334.h"
/* I love macro expansions*/
#define DRV8334_CS_LOW(drv)                                                    \
  HAL_GPIO_WritePin((drv)->DRV8334_CS_GPIO_Port, (drv)->DRV8334_CS_Pin,        \
                    GPIO_PIN_RESET)
#define DRV8334_CS_HIGH(drv)                                                   \
  HAL_GPIO_WritePin((drv)->DRV8334_CS_GPIO_Port, (drv)->DRV8334_CS_Pin,        \
                    GPIO_PIN_SET)
#define MAX_SPI_TIMEOUT 1000 // Define a maximum timeout for SPI operations
#define DRV8334_W0_WRITE 0x00 // W0 = 0b for write command
#define DRV8334_W0_READ 0x01  // W0 = 1b for read command

typedef struct {
  uint8_t regAddress;
  uint16_t data;
  uint8_t is_write; // 1 for write, 0 for read
} DRV8334_SPI_FRAME_t;

static HAL_StatusTypeDef DRV8334_SPI_Transmit(DRV8334_t *drv, uint8_t *data,
                                              uint16_t size) {
  return HAL_SPI_Transmit(drv->hspi, data, size, MAX_SPI_TIMEOUT);
}
static HAL_StatusTypeDef DRV8334_SPI_TransmitReceive(DRV8334_t *drv,
                                                     uint8_t *txData,
                                                     uint8_t *rxData,
                                                     uint16_t size) {
  return HAL_SPI_TransmitReceive(drv->hspi, txData, rxData, size,
                                 MAX_SPI_TIMEOUT);
}
/* CRC8: poly 0x2F, init 0xFF, no final XOR, MSB first.
   Covers command + data (3 bytes): 38 00 09 -> 6E */
static uint8_t DRV8334_CalculateCRC(const uint8_t *data, uint16_t length) {
  uint8_t crc = 0xFF; // Initial value
  for (uint16_t i = 0; i < length; i++) {
    crc ^= data[i];                   // XOR byte into the crc
    for (uint8_t j = 0; j < 8; j++) { // Loop over each bit
      if (crc & 0x80) {
        crc = (crc << 1) ^ 0x2F;
      } else {
        crc <<= 1;
      }
    }
  }
  return crc;
}
/* serialize func */
static void DRV8334_Serialize_Frame(const DRV8334_SPI_FRAME_t *frame,
                                    uint8_t *buffer) {
  buffer[0] = (uint8_t)(frame->regAddress << 1) |
              (frame->is_write ? DRV8334_W0_WRITE : DRV8334_W0_READ);
  buffer[1] = (frame->data >> 8) & 0xFF;          // MSB
  buffer[2] = frame->data & 0xFF;                 // LSB
  buffer[3] = DRV8334_CalculateCRC(buffer, 3);    // only sent if crc_enabled
}

HAL_StatusTypeDef DRV8334_WriteRegister(DRV8334_t *drv, uint8_t regAddress,
                                        uint16_t data) {
  uint8_t size = drv->crc_enabled ? 4 : 3; // tamaño frame, si crc -> 4 bytes, sino 3
                                           // is enabled, otherwise 3 bytes
  DRV8334_SPI_FRAME_t frame = {
      .regAddress = regAddress, .data = data, .is_write = 1};
  uint8_t txData[4] = {0};
  DRV8334_Serialize_Frame(&frame, txData); // serializamos frame
  DRV8334_CS_LOW(drv);
  HAL_StatusTypeDef status = DRV8334_SPI_Transmit(drv, txData, size);
  DRV8334_CS_HIGH(drv);
  return status;
}
HAL_StatusTypeDef DRV8334_ReadRegister(DRV8334_t *drv, uint8_t regAddress,
                                       uint16_t *data) {
  uint8_t size = drv->crc_enabled ? 4 : 3; // tamaño frame, si crc -> 4 bytes, sino 3
                                           // is enabled, otherwise 3 bytes
  uint8_t txData[4] = {0};
  uint8_t rxData[4] = {0};
  DRV8334_SPI_FRAME_t frame = {
      .regAddress = regAddress, .data = 0, .is_write = 0};
  DRV8334_Serialize_Frame(&frame, txData);
  DRV8334_CS_LOW(drv);
  HAL_StatusTypeDef status =
      DRV8334_SPI_TransmitReceive(drv, txData, rxData, size);
  DRV8334_CS_HIGH(drv);
  if (status != HAL_OK) {
    return status;
  }
  /* CRC over status + data + crc must leave a zero residue */
  if (drv->crc_enabled && DRV8334_CalculateCRC(rxData, 4) != 0) {
    return HAL_ERROR;
  }
  drv->last_status = rxData[0];                   // FAULT bit + address echo
  *data = ((uint16_t)rxData[1] << 8) | rxData[2]; // MSB first, byte by byte
  return HAL_OK;
}
/* Writes IC_CTRL3 = 0x0009 (SPI_CRC_EN = 0). With CRC still enabled the
   serializer produces exactly the datasheet frame 38 00 09 6E. */
HAL_StatusTypeDef DRV8334_Disable_CRC(DRV8334_t *drv) {
  HAL_StatusTypeDef status =
      DRV8334_WriteRegister(drv, DRV8334_IC_CTRL3, 0x0009);
  if (status == HAL_OK) {
    drv->crc_enabled = 0; // from now on frames are 24 bits
  }
  return status;
}

/* Inicializar estructura del driver */
/*TODO: no me gusta que confie en que el spi esta correctamente configurado
eso en si es responsabildiad del caller pero le dare una vuelta*/
void DRV8334_Init(DRV8334_t *drv, uint16_t csPin, GPIO_TypeDef *csPort,
                  SPI_HandleTypeDef *hspi) {
  drv->DRV8334_CS_Pin = csPin;
  drv->DRV8334_CS_GPIO_Port = csPort;
  drv->hspi = hspi;
  drv->crc_enabled = 1; // SPI CRC is enabled by default after power-up
  drv->last_status = 0;
  DRV8334_CS_HIGH(drv); // Ensure CS is high at initialization
}
