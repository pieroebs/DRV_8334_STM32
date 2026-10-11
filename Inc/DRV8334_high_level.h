/* DRV8334_high_level.h */
#ifndef DRV_8334_HIGH_LEVEL_H
#define DRV_8334_HIGH_LEVEL_H
#include "DRV8334.h"
#include <stdbool.h>

/* (NOMBRE): el tipo DRV8334_<NOMBRE>_t y la direccion DRV8334_<NOMBRE> */
#define DRV8334_STATUS_REGS(X)                                                 \
  X(IC_STAT1) X(IC_STAT2) X(IC_STAT3) X(IC_STAT4) X(IC_STAT5) X(IC_STAT6)

#define DRV8334_CTRL_REGS(X)                                                   \
  X(IC_CTRL1)                                                                  \
  X(IC_CTRL2) X(IC_CTRL3) X(GD_CTRL1) X(GD_CTRL2) X(GD_CTRL3) X(GD_CTRL3B)     \
      X(GD_CTRL4) X(GD_CTRL5) X(GD_CTRL6) X(GD_CTRL7) X(CSA_CTRL) X(MON_CTRL1) \
          X(MON_CTRL2) X(MON_CTRL3) X(MON_CTRL4) X(MON_CTRL5) X(MON_CTRL6)     \
              X(DIAG_CTRL1)

/* Registros de config.
 * IC_CTRL2 e IC_CTRL3 van aparte porque mezclan configs con modos y esas cosas
 * (CLR_FLT, LOCK, ENABLE_DRV) y con el modo CRC del SPI SPI_CRC_EN */
#define DRV8334_CONFIG_REGS(X)                                                 \
  X(IC_CTRL1)                                                                  \
  X(GD_CTRL1) X(GD_CTRL2) X(GD_CTRL3) X(GD_CTRL3B) X(GD_CTRL4) X(GD_CTRL5)     \
  X(GD_CTRL6) X(GD_CTRL7) X(CSA_CTRL) X(MON_CTRL1) X(MON_CTRL2) X(MON_CTRL3)   \
  X(MON_CTRL4) X(MON_CTRL5) X(MON_CTRL6)

/* lectura para todos los registros */
#define DRV8334_DEFINE_READ(NAME)                                              \
  static inline HAL_StatusTypeDef DRV8334_read_##NAME(                         \
      DRV8334_t *drv, DRV8334_##NAME##_t *out) {                               \
    return DRV8334_ReadRegister(drv, DRV8334_##NAME, &out->raw);               \
  }

/* escritura solo para los de control (los de estado son de solo lectura) */
#define DRV8334_DEFINE_WRITE(NAME)                                             \
  static inline HAL_StatusTypeDef DRV8334_write_##NAME(                        \
      DRV8334_t *drv, DRV8334_##NAME##_t val) {                                \
    return DRV8334_WriteRegister(drv, DRV8334_##NAME, val.raw);                \
  }

DRV8334_STATUS_REGS(DRV8334_DEFINE_READ)
DRV8334_CTRL_REGS(DRV8334_DEFINE_READ)
DRV8334_CTRL_REGS(DRV8334_DEFINE_WRITE)

/* Un campo por registro: f.IC_STAT1, cfg.MON_CTRL2...*/
#define DRV8334_DEFINE_FIELD(NAME) DRV8334_##NAME##_t NAME;

/* Todos los registros de estado */
typedef struct {
  DRV8334_STATUS_REGS(DRV8334_DEFINE_FIELD)
} DRV8334_faults_t;

/* Configuracion completa. Rellenar con una funcion de init DRV8334_config_init_default() y
 * cambiar solo lo necesario, ej cfg.MON_CTRL2.bits.VDS_MODE = 1 */
typedef struct {
  DRV8334_IC_CTRL2_t IC_CTRL2; /* CLR_FLT, LOCK y ENABLE_DRV se ignoran */
  DRV8334_IC_CTRL3_t IC_CTRL3; /* SPI_CRC_EN se ignora */
  DRV8334_CONFIG_REGS(DRV8334_DEFINE_FIELD)
} DRV8334_config_t;

/* Valores de reset del datasheet. Ojo: con ellos casi todas las
 * protecciones estan en modo warning (no apagan los MOSFETs) por lo que si no las activas y la lias no me jodas */
void DRV8334_config_init_default(DRV8334_config_t *cfg);

/* Desbloquea, escribe todo, relee y compara, y bloquea. Deja el driver
 * deshabilitado. HAL_ERROR si algun registro no se ha quedado como se pidio */
HAL_StatusTypeDef DRV8334_configure(DRV8334_t *drv, const DRV8334_config_t *cfg);

HAL_StatusTypeDef DRV8334_read_faults(DRV8334_t *drv, DRV8334_faults_t *f);
bool DRV8334_faults_ok(const DRV8334_faults_t *f);
HAL_StatusTypeDef DRV8334_clear_faults(DRV8334_t *drv);

/* HAL_ERROR si ENABLE_DRV no se queda a 1 (fallo activo o DRVOFF alto) */
HAL_StatusTypeDef DRV8334_enable(DRV8334_t *drv);
HAL_StatusTypeDef DRV8334_disable(DRV8334_t *drv);

/* Arranque completo: comprueba el SPI, configura, limpia fallos, habilita
 * y comprueba que no queda ningún fallo. Llamar antes de pwm_init() */
HAL_StatusTypeDef DRV8334_start(DRV8334_t *drv, const DRV8334_config_t *cfg);

#endif
