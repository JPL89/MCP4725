// @File		MCP4725.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		20/03/24
//
//
// Copyright (C) 2024 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef MCP4725_H
#define MCP4725_H

#define MCP4725_SLA_W 0xC0
#define MCP4725_SLA_R 0xC1

// POWER DOWN BITS
#define MCP4725_NORMAL_MODE 0x00
#define MCP4725_1K_RESISTOR_TO_GROUND 0x03
#define MCP4725_100K_RESISTOR_TO_GROUND 0x04 
#define MCP4725_500K_RESISTOR_TO_GROUND 0x06 

// COMMAND
#define MCP4725_WRITE_DAC_REGISTER 0x40 
#define MCP4725_WRITE_DAC_AND_EEPROM_REGISTER 0x60 

void MCP4725_write(unsigned char command, unsigned int data)
{            
    data <<= 4;
    
    Wire_Start();
    Wire_Write(MCP4725_SLA_W);
    Wire_Write(command);
    Wire_Write((unsigned char)((data >> 8) & 0xFF));
    Wire_Write((unsigned char)(data & 0xFF));
    Wire_Stop();
}

unsigned int MCP4725_read(void)
{   
    unsigned int data = 0;
    unsigned char command = 0;
    
    Wire_Start();
    Wire_Write(MCP4725_SLA_R);
    command = Wire_Ack();
    data |= Wire_Ack();   
    data <<= 8;
    data |= Wire_Nack();   
    Wire_Stop();
    
    return ((unsigned int) (data >> 4));
}

#endif
