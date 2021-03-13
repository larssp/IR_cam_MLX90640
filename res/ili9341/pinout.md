# Pinout 2.4" TFT LCD ILI9341 Shield

![photo of the backside of the board](bottom_side.jpg "ILI9341 pinout")


| pin | details |
|-----|---------|
| GND | The ground pins are here for a simple common ground |
| 5V  | The input voltage will be pass to the LCD by the 5V pin. |
| 3V3 | This pin will attach to the 3V3 volts | 
| RST | The LCD has a reset pin which helps to clear the GRAM of the driver |
| CS  | The CD pin helps to enable the data from registers to the LCD. |
| RS  | The RS pin will help to toggle the data/command registers in the driver. |
| WR  | The WR pin which only requires to activate when the device needs to write the data on the LCD. | 
| RD  | The RD pin is to enable the reading of data from the LCD. |
| D0 - D7 | These all pins from D0~D7 are the digital data input pins. It requires only when a developer needs to work with LCD using 8-bit data or using Assemble language. The Arduino library mostly uses the SPI pins. | 
| SD_SCK | The SCK pin the common clock pin of the LCD with microcontroller/Arduino | 
| SD_DO  | DO pin the data output pin of the SPI communication system. |
| SD_DI  | The DI pin is the data input pin of the SPI communication system. |
| SD_SS  |  	The SS pin will enable the SPI communication through the signal of the SS pin. | 


Description of the pins copied from [here](https://microcontrollerslab.com/2-4-tft-lcd-touch-screen-module/).


## Alternative table from [here](http://www.lcdwiki.com/2.4inch_Arduino_Display)

| Pin Label |	Pin Description |
|-----------|-------------------|
| LCD_RST   |	LCD bus reset signal, low level reset |
| LCD_CS 	| LCD bus chip select signal, low level enable |
| LCD_RS 	| LCD bus command / data selection signal, low level: command, high level: data |
| LCD_WR 	| LCD bus write signal | 
| LCD_RD 	| LCD bus read signal | 
| GND 	    | Power ground | 
| 5V 	    | 5V power input | 
| 3V3 	    | 3.3V power input, this pin can be disconnected | 
| LCD_D0-LCD_D7  | 	LCD 8-bit data Bit0-Bit7 | 
| SD_SS 	| SD card SPI bus chip select signal, low level enable | 
| SD_DI 	| SD card SPI bus MOSI signal | 
| SD_DO 	| SD card SPI bus MISO signal | 
| SD_SCK 	| SD card SPI bus clock signal | 