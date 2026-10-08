/* DRV8334_regs.h
Author: PEBS

Bit-field views of every DRV8334 register .
GCC on ARM (little-endian) allocates bit-fields from bit 0 upwards,the
first field declared in each struct is bit 0.
The real work is doing this .h file, too much registers :(


*/

#ifndef DRV8334_REGS_H
#define DRV8334_REGS_H
#include <stdint.h>

/* ------------------------------ STATUS registers (read only) --------------- */

/* IC_STAT1 (0x00) */
#define DRV8334_IC_STAT1_RESET 0x8000
typedef union {
  uint16_t raw;
  struct {
    uint16_t DRV_STAT        : 1;       // bit 0      (R) Indicates Driver Enable Status
    uint16_t OTW             : 1;       // bit 1      (R) Overtemperature Warning Status Bit
    uint16_t                 : 6;       // bits 2-7   reserved
    uint16_t UV              : 1;       // bit 8      (R) Logic OR of supply voltage undervoltage detection
    uint16_t OV              : 1;       // bit 9      (R) Logic OR of supply voltage overvoltage detection
    uint16_t SNS_OCP         : 1;       // bit 10     (R) Logic OR of Sense overcurrent detection
    uint16_t VGS             : 1;       // bit 11     (R) Logic OR of VGS detection
    uint16_t VDS             : 1;       // bit 12     (R) Logic OR of VDS overcurrent detection
    uint16_t WARN            : 1;       // bit 13     (R) Logic OR of WARN status, except OTW
    uint16_t FAULT           : 1;       // bit 14     (R) Logic OR of FAULT status registers
    uint16_t SPI_OK          : 1;       // bit 15     (R) No SPI Fault is detected
  } bits;
} DRV8334_IC_STAT1_t;
_Static_assert(sizeof(DRV8334_IC_STAT1_t) == 2, "DRV8334_IC_STAT1_t must be 16 bits");

/* IC_STAT2 (0x01) */
#define DRV8334_IC_STAT2_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t VDS_LC          : 1;       // bit 0      (R) VDS Overcurrent Status on the C Low-side MOSFET
    uint16_t VDS_HC          : 1;       // bit 1      (R) VDS Overcurrent Status on the C High-side MOSFET
    uint16_t VDS_LB          : 1;       // bit 2      (R) VDS Overcurrent Status on the B Low-side MOSFET
    uint16_t VDS_HB          : 1;       // bit 3      (R) VDS Overcurrent Status on the B High-side MOSFET
    uint16_t VDS_LA          : 1;       // bit 4      (R) VDS Overcurrent Status on the A Low-side MOSFET
    uint16_t VDS_HA          : 1;       // bit 5      (R) VDS Overcurrent Status on the A High-side MOSFET
    uint16_t                 : 2;       // bits 6-7   reserved
    uint16_t SNS_OCP_C       : 1;       // bit 8      (R) Overcurrent on External Sense Resistor Status Bit on phase C
    uint16_t SNS_OCP_B       : 1;       // bit 9      (R) Overcurrent on External Sense Resistor Status Bit on phase B
    uint16_t SNS_OCP_A       : 1;       // bit 10     (R) Overcurrent on External Sense Resistor Status Bit on phase A
    uint16_t                 : 4;       // bits 11-14 reserved
    uint16_t CBC_ST          : 1;       // bit 15     (R) VDS and SNS_OCP monitor Cycle By Cycle (CBC) counter activity
  } bits;
} DRV8334_IC_STAT2_t;
_Static_assert(sizeof(DRV8334_IC_STAT2_t) == 2, "DRV8334_IC_STAT2_t must be 16 bits");

/* IC_STAT3 (0x02) */
#define DRV8334_IC_STAT3_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t VGS_LC          : 1;       // bit 0      (R) Gate driver fault status on the C Low-side MOSFET
    uint16_t VGS_HC          : 1;       // bit 1      (R) Gate driver fault status on the C High-side MOSFET
    uint16_t VGS_LB          : 1;       // bit 2      (R) Gate driver fault status on the B Low-side MOSFET
    uint16_t VGS_HB          : 1;       // bit 3      (R) Gate driver fault status on the B High-side MOSFET
    uint16_t VGS_LA          : 1;       // bit 4      (R) Gate driver fault status on the A Low-side MOSFET
    uint16_t VGS_HA          : 1;       // bit 5      (R) Gate driver fault status on the A High-side MOSFET
    uint16_t                 : 10;      // bits 6-15  reserved
  } bits;
} DRV8334_IC_STAT3_t;
_Static_assert(sizeof(DRV8334_IC_STAT3_t) == 2, "DRV8334_IC_STAT3_t must be 16 bits");

/* IC_STAT4 (0x03) */
#define DRV8334_IC_STAT4_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t BSTC_UV         : 1;       // bit 0      (R) BST undervoltage on the C High-side MOSFET
    uint16_t BSTC_OV         : 1;       // bit 1      (R) BST overvoltage on the C High-side MOSFET
    uint16_t BSTB_UV         : 1;       // bit 2      (R) BST undervoltage on the B High-side MOSFET
    uint16_t BSTB_OV         : 1;       // bit 3      (R) BST overvoltage on the B High-side MOSFET
    uint16_t BSTA_UV         : 1;       // bit 4      (R) BST undervoltage on the A High-side MOSFET
    uint16_t BSTA_OV         : 1;       // bit 5      (R) BST overvoltage on the A High-side MOSFET
    uint16_t                 : 1;       // bit 6      reserved
    uint16_t                 : 1;       // bit 7      reserved
    uint16_t GVDD_UV         : 1;       // bit 8      (R) GVDD undervoltage status
    uint16_t GVDD_OV         : 1;       // bit 9      (R) GVDD overvoltage status
    uint16_t VCP_UV          : 1;       // bit 10     (R) VCP undervoltage status
    uint16_t VCP_OV          : 1;       // bit 11     (R) VCP overvoltage status
    uint16_t VDRAIN_UV       : 1;       // bit 12     (R) VDRAIN undervoltage status
    uint16_t VDRAIN_OV       : 1;       // bit 13     (R) VDRAIN overvoltage status
    uint16_t PVDD_UV         : 1;       // bit 14     (R) PVDD undervoltage status
    uint16_t PVDD_OV         : 1;       // bit 15     (R) PVDD overvoltage status
  } bits;
} DRV8334_IC_STAT4_t;
_Static_assert(sizeof(DRV8334_IC_STAT4_t) == 2, "DRV8334_IC_STAT4_t must be 16 bits");

/* IC_STAT5 (0x04) */
#define DRV8334_IC_STAT5_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t DEADT_FLT       : 1;       // bit 0      (R) Dead time violation
    uint16_t STP_FLT         : 1;       // bit 1      (R) Shoot Through Protection violation
    uint16_t                 : 1;       // bit 2      reserved
    uint16_t OTP_USR_CRC_FLT : 1;       // bit 3      (R) USER OTP CRC fault
    uint16_t OTP_CRC_FLT     : 1;       // bit 4      (R) OTP CRC fault bit
    uint16_t SPI_CLK_FLT     : 1;       // bit 5      (R) SPI Clock Framing fault bit
    uint16_t SPI_ADDR_FLT    : 1;       // bit 6      (R) SPI Address fault bit
    uint16_t SPI_CRC_FLT     : 1;       // bit 7      (R) SPI CRC fault bit
    uint16_t WDT_FLT         : 1;       // bit 8      (R) Watch dog timer fault bit
    uint16_t OTSD            : 1;       // bit 9      (R) Overtemperature shutdown status
    uint16_t GVDD_CP_LDO     : 1;       // bit 10     (R) GVDD operating mode status
    uint16_t                 : 3;       // bits 11-13 reserved
    uint16_t PVDD_UVW        : 1;       // bit 14     (R) PVDD undervoltage warning status
    uint16_t                 : 1;       // bit 15     reserved
  } bits;
} DRV8334_IC_STAT5_t;
_Static_assert(sizeof(DRV8334_IC_STAT5_t) == 2, "DRV8334_IC_STAT5_t must be 16 bits");

/* IC_STAT6 (0x05) */
#define DRV8334_IC_STAT6_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t CLK_MON_FLT     : 1;       // bit 0      (R) Clock monitor fault status
    uint16_t                 : 2;       // bits 1-2   reserved
    uint16_t DEV_MODE_FLT    : 1;       // bit 3      (R) Device mode fault status
    uint16_t ABIST_FLT       : 1;       // bit 4      (R) Analog BIST fault status
    uint16_t                 : 2;       // bits 5-6   reserved
    uint16_t DVDD_OV         : 1;       // bit 7      (R) DVDD overvoltage status
    uint16_t                 : 1;       // bit 8      reserved
    uint16_t VDDSDO_UV       : 1;       // bit 9      (R) Device internal regulator VDDSDO regulator undervoltage status
    uint16_t VREF_UV         : 1;       // bit 10     (R) VREF input undervoltage status
    uint16_t VREF_OV         : 1;       // bit 11     (R) VREF input overvoltage status
    uint16_t                 : 1;       // bit 12     reserved
    uint16_t PHCC_FLT        : 1;       // bit 13     (R) Indicates phase comparator fault of PHCC
    uint16_t PHCB_FLT        : 1;       // bit 14     (R) Indicates phase comparator fault of PHCB
    uint16_t PHCA_FLT        : 1;       // bit 15     (R) Indicates phase comparator fault of PHCA
  } bits;
} DRV8334_IC_STAT6_t;
_Static_assert(sizeof(DRV8334_IC_STAT6_t) == 2, "DRV8334_IC_STAT6_t must be 16 bits");

/* ------------------------------ CONTROL registers -------------------------- */

/* IC_CTRL1 (0x1A) */
#define DRV8334_IC_CTRL1_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t VDDSDO_SEL      : 1;       // bit 0      VDDSDO regulator output selection bit
    uint16_t                 : 15;      // bits 1-15  reserved
  } bits;
} DRV8334_IC_CTRL1_t;
_Static_assert(sizeof(DRV8334_IC_CTRL1_t) == 2, "DRV8334_IC_CTRL1_t must be 16 bits");

/* IC_CTRL2 (0x1B) */
#define DRV8334_IC_CTRL2_RESET 0x0006
typedef union {
  uint16_t raw;
  struct {
    uint16_t CLR_FLT         : 1;       // bit 0      Clear fault
    uint16_t LOCK            : 3;       // bits 1-3   Lock and unlock the register setting
    uint16_t                 : 2;       // bits 4-5   reserved
    uint16_t VCP_MODE        : 2;       // bits 6-7   VCP/TCP mode control
    uint16_t GVDD_MODE       : 1;       // bit 8      GVDD Charge pump LDO mode control
    uint16_t DIS_GVDD_SS     : 1;       // bit 9      Disable GVDD charge pump soft start
    uint16_t CSA_AZ_DIS      : 1;       // bit 10     Current Sense Amplifier Auto Zero function disable
    uint16_t CSA_EN          : 1;       // bit 11     Current Sense Amplifier Enable
    uint16_t CLKMON_EN       : 1;       // bit 12     Clock monitor enable
    uint16_t CFG_CRC_EN      : 1;       // bit 13     Enable configuration data CRC function
    uint16_t MODE_NSLEEP     : 1;       // bit 14     nSLEEP Mode
    uint16_t ENABLE_DRV      : 1;       // bit 15     Enable predriver bit
  } bits;
} DRV8334_IC_CTRL2_t;
_Static_assert(sizeof(DRV8334_IC_CTRL2_t) == 2, "DRV8334_IC_CTRL2_t must be 16 bits");

/* IC_CTRL3 (0x1C) */
#define DRV8334_IC_CTRL3_RESET 0x8009
typedef union {
  uint16_t raw;
  struct {
    uint16_t OTSD_MODE       : 2;       // bits 0-1   Overtemperature shutdown mode
    uint16_t                 : 1;       // bit 2      reserved
    uint16_t OT_LVL          : 1;       // bit 3      Overtemperature shutdown threshold selection
    uint16_t                 : 4;       // bits 4-7   reserved
    uint16_t DRVOFF_PDSEL_LS : 1;       // bit 8      DROVFF Pull-down select for low-side gate driver
    uint16_t DRVOFF_PDSEL_HS : 1;       // bit 9      DROVFF Pull-down select for high-side gate driver
    uint16_t TCP_EN_DLY      : 1;       // bit 10     Delay time to activate trickle charge pump after the device de
    uint16_t                 : 1;       // bit 11     reserved
    uint16_t DIS_SSC         : 1;       // bit 12     TI Internal design parameter: No change is required unless not
    uint16_t                 : 1;       // bit 13     reserved
    uint16_t WARN_MODE       : 1;       // bit 14     Warning nFAULT mode; Control nFAULT response for warning
    uint16_t SPI_CRC_EN      : 1;       // bit 15     SPI CRC Enable
  } bits;
} DRV8334_IC_CTRL3_t;
_Static_assert(sizeof(DRV8334_IC_CTRL3_t) == 2, "DRV8334_IC_CTRL3_t must be 16 bits");

/* GD_CTRL1 (0x1E) */
#define DRV8334_GD_CTRL1_RESET 0x0138
typedef union {
  uint16_t raw;
  struct {
    uint16_t DEADT_MODE_6X   : 2;       // bits 0-1   Dead Time Violation Response Mode for 6 PWM mode only
    uint16_t DEADT_MODE      : 1;       // bit 2      Dead Time Insertion Mode
    uint16_t DEADT           : 3;       // bits 3-5   Gate driver dead time
    uint16_t                 : 1;       // bit 6      reserved
    uint16_t STP_MODE        : 1;       // bit 7      Shoot-through protection report mode
    uint16_t SGD_TMP_EN      : 1;       // bit 8      Enable dynamic temperature control of Smart Gate Drive
    uint16_t SGD_MODE        : 2;       // bits 9-10  Smart Gate Drive mode
    uint16_t                 : 1;       // bit 11     reserved
    uint16_t PWM_MODE        : 3;       // bits 12-14 PWM mode
    uint16_t                 : 1;       // bit 15     reserved
  } bits;
} DRV8334_GD_CTRL1_t;
_Static_assert(sizeof(DRV8334_GD_CTRL1_t) == 2, "DRV8334_GD_CTRL1_t must be 16 bits");

/* GD_CTRL2 (0x1F) */
#define DRV8334_GD_CTRL2_RESET 0x0717
typedef union {
  uint16_t raw;
  struct {
    uint16_t TDRVN           : 4;       // bits 0-3   Peak sink pull down drive timing
    uint16_t TDRVN_D         : 4;       // bits 4-7   Peak sink pull down pre-discharge timing
    uint16_t TDRVP           : 4;       // bits 8-11  Peak source pull up drive timing
    uint16_t                 : 4;       // bits 12-15 reserved
  } bits;
} DRV8334_GD_CTRL2_t;
_Static_assert(sizeof(DRV8334_GD_CTRL2_t) == 2, "DRV8334_GD_CTRL2_t must be 16 bits");

/* GD_CTRL3 (0x21) */
#define DRV8334_GD_CTRL3_RESET 0x0700
typedef union {
  uint16_t raw;
  struct {
    uint16_t IDRVN_SD        : 6;       // bits 0-5   Smart shutdown drive current
    uint16_t                 : 2;       // bits 6-7   reserved
    uint16_t TDRVN_SDD       : 4;       // bits 8-11  Smart shutdown discharge timing
    uint16_t                 : 4;       // bits 12-15 reserved
  } bits;
} DRV8334_GD_CTRL3_t;
_Static_assert(sizeof(DRV8334_GD_CTRL3_t) == 2, "DRV8334_GD_CTRL3_t must be 16 bits");

/* GD_CTRL3B (0x22) */
#define DRV8334_GD_CTRL3B_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t IDRVN_D_L       : 6;       // bits 0-5   Peak sink pull down pre-discharge current for low-side gate dr
    uint16_t                 : 2;       // bits 6-7   reserved
    uint16_t IDRVN_D_H       : 6;       // bits 8-13  Peak sink pull down pre-discharge current for high-side gate d
    uint16_t                 : 2;       // bits 14-15 reserved
  } bits;
} DRV8334_GD_CTRL3B_t;
_Static_assert(sizeof(DRV8334_GD_CTRL3B_t) == 2, "DRV8334_GD_CTRL3B_t must be 16 bits");

/* GD_CTRL4 (0x23) */
#define DRV8334_GD_CTRL4_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t DRV_GLC         : 1;       // bit 0      Drive GLC by SPI command
    uint16_t DRV_GLB         : 1;       // bit 1      Drive GLB by SPI command
    uint16_t DRV_GLA         : 1;       // bit 2      Drive GLA by SPI command
    uint16_t DRV_GHC         : 1;       // bit 3      Drive GHC by SPI command
    uint16_t DRV_GHB         : 1;       // bit 4      Drive GHB by SPI command
    uint16_t DRV_GHA         : 1;       // bit 5      Drive GHA by SPI command
    uint16_t                 : 2;       // bits 6-7   reserved
    uint16_t IHOLD_SEL       : 1;       // bit 8      Select IHOLD pull-up and pull-down current
    uint16_t IDRVP_CFG       : 1;       // bit 9      IDRVP configuration mode
    uint16_t                 : 2;       // bits 10-11 reserved
    uint16_t PWM1X_BRAKE     : 2;       // bits 12-13 1x PWM output configuration
    uint16_t PWM1X_DIR       : 1;       // bit 14     1x PWM Direction
    uint16_t PWM1X_COM       : 1;       // bit 15     1x PWM Commutation Control
  } bits;
} DRV8334_GD_CTRL4_t;
_Static_assert(sizeof(DRV8334_GD_CTRL4_t) == 2, "DRV8334_GD_CTRL4_t must be 16 bits");

/* GD_CTRL5 (0x24) */
#define DRV8334_GD_CTRL5_RESET 0x0007
typedef union {
  uint16_t raw;
  struct {
    uint16_t DRVEN_C         : 1;       // bit 0      DRVEN_C = 0 enforces GHC and GLC low with active pull down
    uint16_t DRVEN_B         : 1;       // bit 1      DRVEN_B = 0 enforces GHB and GLB low with active pull down
    uint16_t DRVEN_A         : 1;       // bit 2      DRVEN_A = 0 enforces GHA and GLA low with active pull down
    uint16_t                 : 13;      // bits 3-15  reserved
  } bits;
} DRV8334_GD_CTRL5_t;
_Static_assert(sizeof(DRV8334_GD_CTRL5_t) == 2, "DRV8334_GD_CTRL5_t must be 16 bits");

/* GD_CTRL6 (0x25) */
#define DRV8334_GD_CTRL6_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t IDRVP_L         : 6;       // bits 0-5   Low-side peak source pull up current
    uint16_t                 : 2;       // bits 6-7   reserved
    uint16_t IDRVP_H         : 6;       // bits 8-13  High-side peak source pull up current
    uint16_t                 : 2;       // bits 14-15 reserved
  } bits;
} DRV8334_GD_CTRL6_t;
_Static_assert(sizeof(DRV8334_GD_CTRL6_t) == 2, "DRV8334_GD_CTRL6_t must be 16 bits");

/* GD_CTRL7 (0x26) */
#define DRV8334_GD_CTRL7_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t IDRVN_L         : 6;       // bits 0-5   Low-side peak sink pull down current
    uint16_t IDRV_RATIO_L    : 2;       // bits 6-7   Low-side IDRVP and IDRVN ratio
    uint16_t IDRVN_H         : 6;       // bits 8-13  High-side peak sink pull down current
    uint16_t IDRV_RATIO_H    : 2;       // bits 14-15 High-side IDRVP and IDRVN ratio
  } bits;
} DRV8334_GD_CTRL7_t;
_Static_assert(sizeof(DRV8334_GD_CTRL7_t) == 2, "DRV8334_GD_CTRL7_t must be 16 bits");

/* CSA_CTRL (0x29) */
#define DRV8334_CSA_CTRL_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t CSA_GAIN_C      : 4;       // bits 0-3   CSA Gain of SOC
    uint16_t CSA_GAIN_B      : 4;       // bits 4-7   CSA Gain of SOB
    uint16_t CSA_GAIN_A      : 4;       // bits 8-11  CSA Gain of SOA
    uint16_t                 : 3;       // bits 12-14 reserved
    uint16_t AREF_DIV        : 1;       // bit 15     VREF dividing ratio
  } bits;
} DRV8334_CSA_CTRL_t;
_Static_assert(sizeof(DRV8334_CSA_CTRL_t) == 2, "DRV8334_CSA_CTRL_t must be 16 bits");

/* MON_CTRL1 (0x2B) */
#define DRV8334_MON_CTRL1_RESET 0x4002
typedef union {
  uint16_t raw;
  struct {
    uint16_t PVDD_OV_MODE    : 1;       // bit 0      PVDD OV threshold monitor mode
    uint16_t PVDD_OV_LVL     : 2;       // bits 1-2   PVDD OV threshold level
    uint16_t PVDD_UVW_LVL    : 1;       // bit 3      PVDD UV Warning threshold level
    uint16_t VCP_UV_MODE     : 1;       // bit 4      VCP monitor mode of under voltage monitor
    uint16_t VCP_OV_MODE     : 1;       // bit 5      VCP monitor mode of over voltage monitor
    uint16_t GVDD_UV_MODE    : 1;       // bit 6      GVDD monitor mode of under voltage monitor
    uint16_t GVDD_OV_MODE    : 1;       // bit 7      GVDD monitor mode of over voltage monitor
    uint16_t DVDD_OV_MODE    : 1;       // bit 8      DVDD monitor mode of over voltage monitor
    uint16_t BST_UV_LVL      : 1;       // bit 9      BST pin undervoltage threshold level VBST_UV
    uint16_t BST_UV_MODE     : 1;       // bit 10     BST pin monitor mode
    uint16_t BST_UV_LATCH    : 1;       // bit 11     BST pin undervoltage latch mode
    uint16_t BST_OV_MODE     : 1;       // bit 12     BST pin overvoltage monitor mode
    uint16_t VDRAIN_MON_MODE : 1;       // bit 13     VDRAIN monitor mode for under and over voltage monitors
    uint16_t VDRAIN_OV_LVL   : 2;       // bits 14-15 VDRAIN Overvoltage threshold level
  } bits;
} DRV8334_MON_CTRL1_t;
_Static_assert(sizeof(DRV8334_MON_CTRL1_t) == 2, "DRV8334_MON_CTRL1_t must be 16 bits");

/* MON_CTRL2 (0x2C) */
#define DRV8334_MON_CTRL2_RESET 0x1101
typedef union {
  uint16_t raw;
  struct {
    uint16_t VGS_DEG         : 3;       // bits 0-2   VGS monitor deglitch time
    uint16_t VGS_BLK         : 3;       // bits 3-5   VGS monitor blanking time
    uint16_t VGS_MODE        : 2;       // bits 6-7   VGS monitor mode
    uint16_t VDS_DEG         : 3;       // bits 8-10  VDS overcurrent deglitch time
    uint16_t VDS_BLK         : 3;       // bits 11-13 VDS overcurrent blanking time
    uint16_t VDS_MODE        : 2;       // bits 14-15 VDS overcurrent mode
  } bits;
} DRV8334_MON_CTRL2_t;
_Static_assert(sizeof(DRV8334_MON_CTRL2_t) == 2, "DRV8334_MON_CTRL2_t must be 16 bits");

/* MON_CTRL3 (0x2D) */
#define DRV8334_MON_CTRL3_RESET 0x003B
typedef union {
  uint16_t raw;
  struct {
    uint16_t SNS_OCP_DEG     : 2;       // bits 0-1   Deglitch time of VSENSE overcurrent protection (Rshunt monitor
    uint16_t                 : 1;       // bit 2      reserved
    uint16_t SNS_OCP_LVL     : 3;       // bits 3-5   Threshold voltage of VSENSE overcurrent protection (Rshunt mon
    uint16_t SNS_OCP_MODE    : 2;       // bits 6-7   Monitor mode of VSENSE overcurrent protection (Rshunt monitor)
    uint16_t VGS_LVL         : 1;       // bit 8      Gate voltage monitor threshold level when INLx/INHx = High
    uint16_t                 : 7;       // bits 9-15  reserved
  } bits;
} DRV8334_MON_CTRL3_t;
_Static_assert(sizeof(DRV8334_MON_CTRL3_t) == 2, "DRV8334_MON_CTRL3_t must be 16 bits");

/* MON_CTRL4 (0x2E) */
#define DRV8334_MON_CTRL4_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t WDT_EN          : 1;       // bit 0      Watchdog Time Enable
    uint16_t WDT_W           : 2;       // bits 1-2   Watchdog Timer window tWDL (lower window) and tWDU (upper
    uint16_t WDT_MODE        : 1;       // bit 3      Watchdog Time MODE
    uint16_t WDT_CNT         : 1;       // bit 4      Watchdog Time Fault Count
    uint16_t WDT_FLT_MODE    : 1;       // bit 5      Watchdog Time Fault Mode
    uint16_t                 : 10;      // bits 6-15  reserved
  } bits;
} DRV8334_MON_CTRL4_t;
_Static_assert(sizeof(DRV8334_MON_CTRL4_t) == 2, "DRV8334_MON_CTRL4_t must be 16 bits");

/* MON_CTRL5 (0x2F) */
#define DRV8334_MON_CTRL5_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t PHC_TH          : 1;       // bit 0      Phase Comparator threshold
    uint16_t PHC_OUTEN       : 1;       // bit 1      Phase Output buffer enable
    uint16_t PHC_COMPEN      : 1;       // bit 2      Phase Comparator enable
    uint16_t PHC_MON_MODE    : 1;       // bit 3      Phase Comparator fault monitor mode
    uint16_t PHC_OUTDG_SEL   : 1;       // bit 4      Phase Comparator output (PHCx device pin) deglitch time select
    uint16_t                 : 6;       // bits 5-10  reserved
    uint16_t VREF_MON_MODE   : 1;       // bit 11     VREF monitor mode for under and over voltage monitors
    uint16_t VREF_MON_LVL    : 1;       // bit 12     VREF (CSA reference voltage) undervoltage and overvoltage
    uint16_t VDDSDO_MON_LVL  : 1;       // bit 13     VDDSDO (Power supply of SDO) undervoltage and overvoltage
    uint16_t                 : 2;       // bits 14-15 reserved
  } bits;
} DRV8334_MON_CTRL5_t;
_Static_assert(sizeof(DRV8334_MON_CTRL5_t) == 2, "DRV8334_MON_CTRL5_t must be 16 bits");

/* MON_CTRL6 (0x30) */
#define DRV8334_MON_CTRL6_RESET 0x20BB
typedef union {
  uint16_t raw;
  struct {
    uint16_t VDS_LVL_LS      : 4;       // bits 0-3   VDS overcurrent threshold for low-side MOSFETs
    uint16_t VDS_LVL_HS      : 4;       // bits 4-7   VDS overcurrent threshold for high-side MOSFETs
    uint16_t                 : 3;       // bits 8-10  reserved
    uint16_t CBC_CNT         : 1;       // bit 11     Cycle By Cycle shutdown retry count selection
    uint16_t CBC             : 1;       // bit 12     Cycle By Cycle shutdown retry mode enable
    uint16_t ALL_CH          : 1;       // bit 13     All channel shutdown enable
    uint16_t                 : 2;       // bits 14-15 reserved
  } bits;
} DRV8334_MON_CTRL6_t;
_Static_assert(sizeof(DRV8334_MON_CTRL6_t) == 2, "DRV8334_MON_CTRL6_t must be 16 bits");

/* DIAG_CTRL1 (0x33) */
#define DRV8334_DIAG_CTRL1_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t PHDEN_LC        : 1;       // bit 0      Phase Diagnostic switch enable on low-side channel C ( SHC-GND
    uint16_t PHDEN_HC        : 1;       // bit 1      Phase Diagnostic switch enable on high-side channel C ( VDRAIN
    uint16_t PHDEN_LB        : 1;       // bit 2      Phase Diagnostic switch enable on low-side channel B ( SHB-GND
    uint16_t PHDEN_HB        : 1;       // bit 3      Phase Diagnostic switch enable on high-side channel B ( VDRAIN
    uint16_t PHDEN_LA        : 1;       // bit 4      Phase Diagnostic switch enable on low-side channel A ( SHA-GND
    uint16_t PHDEN_HA        : 1;       // bit 5      Phase Diagnostic switch enable on high-side channel A ( VDRAIN
    uint16_t                 : 10;      // bits 6-15  reserved
  } bits;
} DRV8334_DIAG_CTRL1_t;
_Static_assert(sizeof(DRV8334_DIAG_CTRL1_t) == 2, "DRV8334_DIAG_CTRL1_t must be 16 bits");

/* SPI_TEST (0x36) */
#define DRV8334_SPI_TEST_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t SPI_TEST        : 16;      // bits 0-15
  } bits;
} DRV8334_SPI_TEST_t;
_Static_assert(sizeof(DRV8334_SPI_TEST_t) == 2, "DRV8334_SPI_TEST_t must be 16 bits");

/* OTP_USR (0x48) */
#define DRV8334_OTP_USR_RESET 0x0000
typedef union {
  uint16_t raw;
  struct {
    uint16_t OTP_USR_PRG     : 1;       // bit 0      (W) Program User OTP
    uint16_t OTP_USR_P_ACC   : 3;       // bits 1-3   Access control of User OTP Program and User OTP Verification
    uint16_t OTP_USR_P_VER   : 1;       // bit 4      Enables memory verification of User OTP Program
    uint16_t                 : 11;      // bits 5-15  reserved
  } bits;
} DRV8334_OTP_USR_t;
_Static_assert(sizeof(DRV8334_OTP_USR_t) == 2, "DRV8334_OTP_USR_t must be 16 bits");

#endif
