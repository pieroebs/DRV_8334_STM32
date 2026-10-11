/*Author: PEBS
High level library for DRV8334, currently untested as of 10 OCT 2026
*/

#include "DRV8334_high_level.h"

/* Campo LOCK de IC_CTRL2 */
#define DRV8334_LOCK_UNLOCK 0x3 /* 011b */
#define DRV8334_LOCK_LOCK 0x6   /* 110b */

/* Si SPI peta cortar */
#define DRV8334_TRY(call)                                                      \
  do {                                                                         \
    HAL_StatusTypeDef st_ = (call);                                            \
    if (st_ != HAL_OK) {                                                       \
      return st_;                                                              \
    }                                                                          \
  } while (0)

/* Bits de IC_CTRL2 que son control y no config */
static uint16_t ic_ctrl2_cmd_mask(void) {
  DRV8334_IC_CTRL2_t m = {.raw = 0};
  m.bits.CLR_FLT = 1;
  m.bits.LOCK = 0x7;
  m.bits.ENABLE_DRV = 1;
  return m.raw;
}

void DRV8334_config_init_default(DRV8334_config_t *cfg) {
  cfg->IC_CTRL2.raw = DRV8334_IC_CTRL2_RESET;
  cfg->IC_CTRL3.raw = DRV8334_IC_CTRL3_RESET;
#define DRV8334_SET_RESET(NAME) cfg->NAME.raw = DRV8334_##NAME##_RESET;
  DRV8334_CONFIG_REGS(DRV8334_SET_RESET)
#undef DRV8334_SET_RESET
}

HAL_StatusTypeDef DRV8334_configure(DRV8334_t *drv,
                                    const DRV8334_config_t *cfg) {
  /*1) desbloquear y deshabilitar el driver*/
  DRV8334_IC_CTRL2_t ctrl2;
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &ctrl2));
  ctrl2.bits.CLR_FLT = 0;
  ctrl2.bits.ENABLE_DRV = 0;
  ctrl2.bits.LOCK = DRV8334_LOCK_UNLOCK;
  DRV8334_TRY(DRV8334_write_IC_CTRL2(drv, ctrl2));

  /* 2 Escribir la configuracion */
  ctrl2 = cfg->IC_CTRL2;
  ctrl2.bits.CLR_FLT = 0;
  ctrl2.bits.ENABLE_DRV = 0;
  ctrl2.bits.LOCK = DRV8334_LOCK_UNLOCK;
  DRV8334_TRY(DRV8334_write_IC_CTRL2(drv, ctrl2));

  /* ojo que el crc hay que tocarlo bien */
  DRV8334_IC_CTRL3_t ctrl3 = cfg->IC_CTRL3;
  ctrl3.bits.SPI_CRC_EN = drv->crc_enabled ? 1 : 0;
  DRV8334_TRY(DRV8334_write_IC_CTRL3(drv, ctrl3));

#define DRV8334_WRITE_CFG(NAME)                                                \
  DRV8334_TRY(DRV8334_write_##NAME(drv, cfg->NAME));
  DRV8334_CONFIG_REGS(DRV8334_WRITE_CFG)
#undef DRV8334_WRITE_CFG

  /* 3. relectura y comparar garantia d q (jaja ejes dq) las protecciones estan puestas */
  DRV8334_IC_CTRL2_t rd2;
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &rd2));
  uint16_t mask = (uint16_t)~ic_ctrl2_cmd_mask();
  if ((rd2.raw & mask) != (ctrl2.raw & mask)) {
    return HAL_ERROR;
  }

  DRV8334_IC_CTRL3_t rd3;
  DRV8334_TRY(DRV8334_read_IC_CTRL3(drv, &rd3));
  if (rd3.raw != ctrl3.raw) {
    return HAL_ERROR;
  }

#define DRV8334_VERIFY_CFG(NAME)                                               \
  {                                                                            \
    DRV8334_##NAME##_t rd;                                                     \
    DRV8334_TRY(DRV8334_read_##NAME(drv, &rd));                                \
    if (rd.raw != cfg->NAME.raw) {                                             \
      return HAL_ERROR;                                                        \
    }                                                                          \
  }
  DRV8334_CONFIG_REGS(DRV8334_VERIFY_CFG)
#undef DRV8334_VERIFY_CFG

  /* 4. Bloqueo, a partir de aqui se ignoran las escrituras de configuraciin */
  rd2.bits.CLR_FLT = 0;
  rd2.bits.LOCK = DRV8334_LOCK_LOCK;
  DRV8334_TRY(DRV8334_write_IC_CTRL2(drv, rd2));
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &rd2));
  if (rd2.bits.LOCK != DRV8334_LOCK_LOCK) {
    return HAL_ERROR;
  }
  return HAL_OK;
}

HAL_StatusTypeDef DRV8334_read_faults(DRV8334_t *drv, DRV8334_faults_t *f) {
#define DRV8334_READ_STAT(NAME) DRV8334_TRY(DRV8334_read_##NAME(drv, &f->NAME));
  DRV8334_STATUS_REGS(DRV8334_READ_STAT)
#undef DRV8334_READ_STAT
  return HAL_OK;
}

bool DRV8334_faults_ok(const DRV8334_faults_t *f) {
  return f->IC_STAT1.bits.SPI_OK && !f->IC_STAT1.bits.FAULT;
}

HAL_StatusTypeDef DRV8334_clear_faults(DRV8334_t *drv) {
  DRV8334_IC_CTRL2_t ctrl2;
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &ctrl2));
  ctrl2.bits.CLR_FLT = 1; /* se pone a 0 solo */
  return DRV8334_write_IC_CTRL2(drv, ctrl2);
}

/* CLR_FLT y ENABLE_DRV deben ir en tramas separadas (leete el datasheet prro) */
HAL_StatusTypeDef DRV8334_enable(DRV8334_t *drv) {
  DRV8334_IC_CTRL2_t ctrl2;
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &ctrl2));
  ctrl2.bits.CLR_FLT = 0;
  ctrl2.bits.ENABLE_DRV = 1;
  DRV8334_TRY(DRV8334_write_IC_CTRL2(drv, ctrl2));

  /* el chip lo fuerza a 0 si hay un fallo activo o DRVOFF es high */
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &ctrl2));
  return ctrl2.bits.ENABLE_DRV ? HAL_OK : HAL_ERROR;
}

HAL_StatusTypeDef DRV8334_disable(DRV8334_t *drv) {
  DRV8334_IC_CTRL2_t ctrl2;
  DRV8334_TRY(DRV8334_read_IC_CTRL2(drv, &ctrl2));
  ctrl2.bits.CLR_FLT = 0;
  ctrl2.bits.ENABLE_DRV = 0;
  return DRV8334_write_IC_CTRL2(drv, ctrl2);
}

HAL_StatusTypeDef DRV8334_start(DRV8334_t *drv, const DRV8334_config_t *cfg) {
  DRV8334_IC_STAT1_t stat1;
  DRV8334_TRY(DRV8334_read_IC_STAT1(drv, &stat1));
  if (!stat1.bits.SPI_OK) {
    return HAL_ERROR;
  }

  DRV8334_TRY(DRV8334_configure(drv, cfg));
  DRV8334_TRY(DRV8334_clear_faults(drv));
  HAL_Delay(
      1); /* el datasheet pide >= 5 us con nFAULT alto antes de ENABLE_DRV */
  DRV8334_TRY(DRV8334_enable(drv));

  DRV8334_faults_t f;
  DRV8334_TRY(DRV8334_read_faults(drv, &f));
  if (!DRV8334_faults_ok(&f)) {
    DRV8334_disable(drv);
    return HAL_ERROR;
  }
  return HAL_OK;
}
