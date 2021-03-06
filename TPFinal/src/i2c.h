/*****************************************************************************
 *   i2c.h:  Header file for NXP LPC11xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   parts of this code are (C) 2010, MyVoice CAD/CAM Services
 *   All rights reserved.
 *
 *   History
 *   2006.07.19  ver 1.00    Preliminary version, first Release
 *   2010.07.19  ver 1.10    Rob Jansen - MyVoice CAD/CAM Services
 *                           Updated to reflect new code
 *   2011.03.07  ver 1.210   Larry Viesse - Corrected Buffer Sizes to accommodate writing 32 data bytes (a full page)
 *
******************************************************************************/
#ifndef __I2C_H
#define __I2C_H


/*
 * These are states returned by the I2CEngine:
 *
 * IDLE     - is never returned but only used internally
 * PENDING  - is never returned but only used internally in the I2C functions
 * ACK      - The transaction finished and the slave returned ACK (on all bytes)
 * NACK     - The transaction is aborted since the slave returned a NACK
 * SLA_NACK - The transaction is aborted since the slave returned a NACK on the SLA
 *            this can be intentional (e.g. an 24LC08 EEPROM states it is busy)
 *            or the slave is not available/accessible at all.
 * ARB_LOSS - Arbitration loss during any part of the transaction.
 *            This could only happen in a multi master system or could also
 *            identify a hardware problem in the system.
 */
#define I2CSTATE_IDLE     0x000
#define I2CSTATE_PENDING  0x001
#define I2CSTATE_ACK      0x101
#define I2CSTATE_NACK     0x102
#define I2CSTATE_SLA_NACK 0x103
#define I2CSTATE_ARB_LOSS 0x104

#define FAST_MODE_PLUS	0

#define Master_Buffer_BUFSIZE	35
#define Slave_Buffer_BUFSIZE	32
#define MAX_TIMEOUT		0x00FFFFFF

#define I2CMASTER		0x01
#define I2CSLAVE		0x02

#define PCF8594_ADDR	0xA0
#define READ_WRITE		0x01

#define RD_BIT			0x01

#define I2CONSET_I2EN		0x00000040  /* I2C Control Set Register */
#define I2CONSET_AA			0x00000004
#define I2CONSET_SI			0x00000008
#define I2CONSET_STO		0x00000010
#define I2CONSET_STA		0x00000020

#define I2CONCLR_AAC		0x00000004  /* I2C Control clear Register */
#define I2CONCLR_SIC		0x00000008
#define I2CONCLR_STAC		0x00000020
#define I2CONCLR_I2ENC		0x00000040

#define I2DAT_I2C			0x00000000  /* I2C Data Reg */
#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */
#define I2SCLH_SCLH			150 /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			150  /* I2C SCL Duty Cycle Low Reg */
#define I2SCLH_HS_SCLH		0x00000020  /* Fast Plus I2C SCL Duty Cycle High Reg */
#define I2SCLL_HS_SCLL		0x00000020  /* Fast Plus I2C SCL Duty Cycle Low Reg */


extern volatile uint8_t I2CMasterBuffer[Master_Buffer_BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[Slave_Buffer_BUFSIZE];
extern volatile uint32_t I2CReadLength, I2CWriteLength;

extern uint32_t I2CInit( uint32_t I2cMode );
extern uint32_t I2CEngine( void );

void i2c_showbuffers(void);
void i2c_clearbuffers(void);

#endif /* end __I2C_H */

/* vim: set et sw=4: */
