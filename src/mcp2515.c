/* Copyright (c) 2007 Fabian Greif
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
// ----------------------------------------------------------------------------


#include <avr/io.h>
#include <util/delay.h>

#if ARDUINO>=100
#include <Arduino.h> // Arduino 1.0
#else
#include <Wprogram.h> // Arduino 0022
#endif
#include <stdint.h>
#include <avr/pgmspace.h>

#include "global.h"
#include "mcp2515.h"
#include "mcp2515_defs.h"


#include "defaults.h"

// -------------------------------------------------------------------------
// Schreibt/liest ein Byte ueber den Hardware SPI Bus

uint8_t spi_putc( uint8_t data )
{
	// put byte in send-buffer
	SPDR = data;

	// wait until byte was send
	while( !( SPSR & (1<<SPIF) ) )
		;

	return SPDR;
}

// -------------------------------------------------------------------------
void mcp2515_write_register( uint8_t adress, uint8_t data )
{
	RESET(MCP2515_CS);

	spi_putc(SPI_WRITE);
	spi_putc(adress);
	spi_putc(data);

	SET(MCP2515_CS);
}

// -------------------------------------------------------------------------
uint8_t mcp2515_read_register(uint8_t adress)
{
	uint8_t data;

	RESET(MCP2515_CS);

	spi_putc(SPI_READ);
	spi_putc(adress);

	data = spi_putc(0xff);

	SET(MCP2515_CS);

	return data;
}

// -------------------------------------------------------------------------
void mcp2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data)
{
	RESET(MCP2515_CS);

	spi_putc(SPI_BIT_MODIFY);
	spi_putc(adress);
	spi_putc(mask);
	spi_putc(data);

	SET(MCP2515_CS);
}

// ----------------------------------------------------------------------------
uint8_t mcp2515_read_status(uint8_t type)
{
	uint8_t data;

	RESET(MCP2515_CS);

	spi_putc(type);
	data = spi_putc(0xff);

	SET(MCP2515_CS);

	return data;
}

// -------------------------------------------------------------------------
uint8_t mcp2515_init(uint8_t speed, uint8_t clock)
{

	uint8_t cfg1, cfg2, cfg3;
		switch(clock) {

			case (MCP_8MHZ):
			switch (speed)
        {
            case (CAN_5KBPS):                                               //   5KBPS
            	cfg1 = MCP_8MHz_5kBPS_CFG1;
            	cfg2 = MCP_8MHz_5kBPS_CFG2;
            	cfg3 = MCP_8MHz_5kBPS_CFG3;
            break;

            case (CAN_10KBPS):                                              //  10KBPS
            	cfg1 = MCP_8MHz_10kBPS_CFG1;
            	cfg2 = MCP_8MHz_10kBPS_CFG2;
            	cfg3 = MCP_8MHz_10kBPS_CFG3;
            break;

            case (CAN_20KBPS):                                              //  20KBPS
            	cfg1 = MCP_8MHz_20kBPS_CFG1;
            	cfg2 = MCP_8MHz_20kBPS_CFG2;
            	cfg3 = MCP_8MHz_20kBPS_CFG3;
            break;

            case (CAN_31K25BPS):                                            //  31.25KBPS
            	cfg1 = MCP_8MHz_31k25BPS_CFG1;
            	cfg2 = MCP_8MHz_31k25BPS_CFG2;
            	cfg3 = MCP_8MHz_31k25BPS_CFG3;
            break;

            case (CAN_33K3BPS):                                             //  33.33KBPS
            	cfg1 = MCP_8MHz_33k3BPS_CFG1;
            	cfg2 = MCP_8MHz_33k3BPS_CFG2;
            	cfg3 = MCP_8MHz_33k3BPS_CFG3;
            break;

            case (CAN_40KBPS):                                              //  40Kbps
            	cfg1 = MCP_8MHz_40kBPS_CFG1;
            	cfg2 = MCP_8MHz_40kBPS_CFG2;
            	cfg3 = MCP_8MHz_40kBPS_CFG3;
            break;

            case (CAN_50KBPS):                                              //  50Kbps
            	cfg1 = MCP_8MHz_50kBPS_CFG1;
            	cfg2 = MCP_8MHz_50kBPS_CFG2;
            	cfg3 = MCP_8MHz_50kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            	cfg1 = MCP_8MHz_80kBPS_CFG1;
            	cfg2 = MCP_8MHz_80kBPS_CFG2;
            	cfg3 = MCP_8MHz_80kBPS_CFG3;
            break;

            case (CAN_100KBPS):                                             // 100Kbps
            	cfg1 = MCP_8MHz_100kBPS_CFG1;
            	cfg2 = MCP_8MHz_100kBPS_CFG2;
            	cfg3 = MCP_8MHz_100kBPS_CFG3;
            break;

            case (CAN_125KBPS):                                             // 125Kbps
            	cfg1 = MCP_8MHz_125kBPS_CFG1;
            	cfg2 = MCP_8MHz_125kBPS_CFG2;
            	cfg3 = MCP_8MHz_125kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            	cfg1 = MCP_8MHz_200kBPS_CFG1;
            	cfg2 = MCP_8MHz_200kBPS_CFG2;
            	cfg3 = MCP_8MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            	cfg1 = MCP_8MHz_250kBPS_CFG1;
            	cfg2 = MCP_8MHz_250kBPS_CFG2;
            	cfg3 = MCP_8MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            	cfg1 = MCP_8MHz_500kBPS_CFG1;
            	cfg2 = MCP_8MHz_500kBPS_CFG2;
            	cfg3 = MCP_8MHz_500kBPS_CFG3;
            break;

            case (CAN_1000KBPS):                                            //   1Mbps
            	cfg1 = MCP_8MHz_1000kBPS_CFG1;
            	cfg2 = MCP_8MHz_1000kBPS_CFG2;
            	cfg3 = MCP_8MHz_1000kBPS_CFG3;
            break;

            default:
							cfg1 = MCP_8MHz_500kBPS_CFG1;
            	cfg2 = MCP_8MHz_500kBPS_CFG2;
            	cfg3 = MCP_8MHz_500kBPS_CFG3;
            break;
        }
			break;
			
			case(MCP_16MHZ):
    		switch (speed) {

					case (CAN_5KBPS):
        		cfg1 = MCP_16MHz_5kBPS_CFG1;
        		cfg2 = MCP_16MHz_5kBPS_CFG2;
        		cfg3 = MCP_16MHz_5kBPS_CFG3;
        	break;

        	case (CAN_10KBPS):
        		cfg1 = MCP_16MHz_10kBPS_CFG1;
        		cfg2 = MCP_16MHz_10kBPS_CFG2;
        		cfg3 = MCP_16MHz_10kBPS_CFG3;
        	break;

        	case (CAN_20KBPS):
        		cfg1 = MCP_16MHz_20kBPS_CFG1;
        		cfg2 = MCP_16MHz_20kBPS_CFG2;
        		cfg3 = MCP_16MHz_20kBPS_CFG3;
        	break;

        	case (CAN_31K25BPS):
        		cfg1 = MCP_16MHz_31k25BPS_CFG1;
        		cfg2 = MCP_16MHz_31k25BPS_CFG2;
        		cfg3 = MCP_16MHz_31k25BPS_CFG3;
        	break;

        	case (CAN_40KBPS):
        		cfg1 = MCP_16MHz_40kBPS_CFG1;
        		cfg2 = MCP_16MHz_40kBPS_CFG2;
        		cfg3 = MCP_16MHz_40kBPS_CFG3;
        	break;

        	case (CAN_50KBPS):
        		cfg1 = MCP_16MHz_50kBPS_CFG1;
        		cfg2 = MCP_16MHz_50kBPS_CFG2;
        		cfg3 = MCP_16MHz_50kBPS_CFG3;
        	break;

        	case (CAN_80KBPS):
        		cfg1 = MCP_16MHz_80kBPS_CFG1;
        		cfg2 = MCP_16MHz_80kBPS_CFG2;
        		cfg3 = MCP_16MHz_80kBPS_CFG3;
        	break;

        	case (CAN_100KBPS):
        		cfg1 = MCP_16MHz_100kBPS_CFG1;
        		cfg2 = MCP_16MHz_100kBPS_CFG2;
        		cfg3 = MCP_16MHz_100kBPS_CFG3;
        	break;

        	case (CAN_125KBPS):
        		cfg1 = MCP_16MHz_125kBPS_CFG1;
        		cfg2 = MCP_16MHz_125kBPS_CFG2;
        		cfg3 = MCP_16MHz_125kBPS_CFG3;
        	break;

        	case (CAN_200KBPS):
        		cfg1 = MCP_16MHz_200kBPS_CFG1;
        		cfg2 = MCP_16MHz_200kBPS_CFG2;
        		cfg3 = MCP_16MHz_200kBPS_CFG3;
        	break;

        	case (CAN_250KBPS):
        		cfg1 = MCP_16MHz_250kBPS_CFG1;
        		cfg2 = MCP_16MHz_250kBPS_CFG2;
        		cfg3 = MCP_16MHz_250kBPS_CFG3;
        	break;

        	case (CAN_500KBPS):
        		cfg1 = MCP_16MHz_500kBPS_CFG1;
        		cfg2 = MCP_16MHz_500kBPS_CFG2;
        		cfg3 = MCP_16MHz_500kBPS_CFG3;
        	break;

        	case (CAN_1000KBPS):
        		cfg1 = MCP_16MHz_1000kBPS_CFG1;
        		cfg2 = MCP_16MHz_1000kBPS_CFG2;
        		cfg3 = MCP_16MHz_1000kBPS_CFG3;
        	break;

        	default:
        	break;
    	}
		}

	SET(MCP2515_CS);
	SET_OUTPUT(MCP2515_CS);

	RESET(P_SCK);
	RESET(P_MOSI);
	RESET(P_MISO);

	SET_OUTPUT(P_SCK);
	SET_OUTPUT(P_MOSI);
	SET_INPUT(P_MISO);

	SET_INPUT(MCP2515_INT);
	SET(MCP2515_INT);

	// active SPI master interface
	SPCR = (1<<SPE)|(1<<MSTR) | (0<<SPR1)|(1<<SPR0);
	SPSR = 0;

	// reset MCP2515 by software reset.
	// After this he is in configuration mode.
	RESET(MCP2515_CS);
	spi_putc(SPI_RESET);
	SET(MCP2515_CS);

	// wait a little bit until the MCP2515 has restarted
	_delay_us(10);

	// load CNF1..3 Register
	RESET(MCP2515_CS);
	spi_putc(SPI_WRITE);
	spi_putc(CNF3);

/*	spi_putc((1<<PHSEG21));		// Bitrate 125 kbps at 16 MHz
	spi_putc((1<<BTLMODE)|(1<<PHSEG11));
	spi_putc((1<<BRP2)|(1<<BRP1)|(1<<BRP0));
*/
/*
	spi_putc((1<<PHSEG21));		// Bitrate 250 kbps at 16 MHz
	spi_putc((1<<BTLMODE)|(1<<PHSEG11));
	spi_putc((1<<BRP1)|(1<<BRP0));
*/
/*
	spi_putc((1<<PHSEG21));		// Bitrate 250 kbps at 16 MHz
	spi_putc((1<<BTLMODE)|(1<<PHSEG11));
	//spi_putc(1<<BRP0);
    spi_putc(speed);
*/

	spi_putc(cfg3);
	spi_putc(cfg2);
	spi_putc(cfg1);

	// activate interrupts
	spi_putc((1<<RX1IE)|(1<<RX0IE));
	SET(MCP2515_CS);

	// test if we could read back the value => is the chip accessible?
	if (mcp2515_read_register(CNF1) != speed) {
		SET(LED2_HIGH);

		return false;
	}

	// deaktivate the RXnBF Pins (High Impedance State)
	mcp2515_write_register(BFPCTRL, 0);

	// set TXnRTS as inputs
	mcp2515_write_register(TXRTSCTRL, 0);

	// turn off filters => receive any message
	mcp2515_write_register(RXB0CTRL, (1<<RXM1)|(1<<RXM0));
	mcp2515_write_register(RXB1CTRL, (1<<RXM1)|(1<<RXM0));

	// reset device to normal mode
	mcp2515_write_register(CANCTRL, 0);
//	SET(LED2_HIGH);
	return true;
}

// ----------------------------------------------------------------------------
// check if there are any new messages waiting

uint8_t mcp2515_check_message(void) {
	return (!IS_SET(MCP2515_INT));
}

// ----------------------------------------------------------------------------
// check if there is a free buffer to send messages

uint8_t mcp2515_check_free_buffer(void)
{
	uint8_t status = mcp2515_read_status(SPI_READ_STATUS);

	if ((status & 0x54) == 0x54) {
		// all buffers used
		return false;
	}

	return true;
}

// ----------------------------------------------------------------------------
uint8_t mcp2515_get_message(tCAN *message)
{
	// read status
	uint8_t status = mcp2515_read_status(SPI_RX_STATUS);
	uint8_t addr;
	uint8_t t;
	if (bit_is_set(status,6)) {
		// message in buffer 0
		addr = SPI_READ_RX;
	}
	else if (bit_is_set(status,7)) {
		// message in buffer 1
		addr = SPI_READ_RX | 0x04;
	}
	else {
		// Error: no message available
		return 0;
	}

	RESET(MCP2515_CS);
	spi_putc(addr);

	// read id
	message->id  = (uint16_t) spi_putc(0xff) << 3;
	message->id |=            spi_putc(0xff) >> 5;

	spi_putc(0xff);
	spi_putc(0xff);

	// read DLC
	uint8_t length = spi_putc(0xff) & 0x0f;

	message->header.length = length;
	message->header.rtr = (bit_is_set(status, 3)) ? 1 : 0;

	// read data
	for (t=0;t<length;t++) {
		message->data[t] = spi_putc(0xff);
	}
	SET(MCP2515_CS);

	// clear interrupt flag
	if (bit_is_set(status, 6)) {
		mcp2515_bit_modify(CANINTF, (1<<RX0IF), 0);
	}
	else {
		mcp2515_bit_modify(CANINTF, (1<<RX1IF), 0);
	}

	return (status & 0x07) + 1;
}

// ----------------------------------------------------------------------------
uint8_t mcp2515_send_message(tCAN *message)
{
	uint8_t status = mcp2515_read_status(SPI_READ_STATUS);

	/* Statusbyte:
	 *
	 * Bit	Function
	 *  2	TXB0CNTRL.TXREQ
	 *  4	TXB1CNTRL.TXREQ
	 *  6	TXB2CNTRL.TXREQ
	 */
	uint8_t address;
	uint8_t t;
//	SET(LED2_HIGH);
	if (bit_is_clear(status, 2)) {
		address = 0x00;
	}
	else if (bit_is_clear(status, 4)) {
		address = 0x02;
	}
	else if (bit_is_clear(status, 6)) {
		address = 0x04;
	}
	else {
		// all buffer used => could not send message
		return 0;
	}

	RESET(MCP2515_CS);
	spi_putc(SPI_WRITE_TX | address);

	spi_putc(message->id >> 3);
    spi_putc(message->id << 5);

	spi_putc(0);
	spi_putc(0);

	uint8_t length = message->header.length & 0x0f;

	if (message->header.rtr) {
		// a rtr-frame has a length, but contains no data
		spi_putc((1<<RTR) | length);
	}
	else {
		// set message length
		spi_putc(length);

		// data
		for (t=0;t<length;t++) {
			spi_putc(message->data[t]);
		}
	}
	SET(MCP2515_CS);

	_delay_us(1);

	// send message
	RESET(MCP2515_CS);
	address = (address == 0) ? 1 : address;
	spi_putc(SPI_RTS | address);
	SET(MCP2515_CS);

	return address;
}
