/*
 * original declaration by james villeneuve (https://github.com/jamesdanielv/thermal_cam_mlx90640)
 * 
  Read the temperature pixels from the MLX90640 IR array
this code is a rewrite driver for the MLX90640 to allow working on arudino. 
no inclusion is noteworthy at this point, based on MIT liscencing using wire.h examples for i2c
driver files were included from sparkfun. sparkfun sensor can be found at https://www.sparkfun.com/products/14768
and sensor examples from melexis. might use some example driver code but it is being simplified and only code i'll use for sensor will be included.

driver updates and simplifications written by james villeneuve
all info above must be included with driver updates and use.
//when this device is first used, data for sensors needs to be moved into eeprom, this is done by typing capital 'U',
when responce is 'data written' the sensor can be used with this code. and stored calibration data will be easily accessed.

  Hardware Connections:
 (https://www.sparkfun.com/products/14425)

*/


/*
 * Changelog
 * - moved SimpleDriver to parent directory to be used by all of James' sketches. Added symlink in current folder
 * - modify indentation 
 */



// this code sole purpose is to provide an eeprom dump to terminal which should be cut and paste into main program

#include <Wire.h>
#include "MLX90640_SimpleDriver.h"
#define MLX90640_address 0x33                                 // Default 7-bit unshifted address of the MLX90640

byte        status = 0;                                       // we use for status
static byte mlx90640To[10];




void setup()
{
  pinMode(A5, INPUT);                                         // set pin to input
  digitalWrite(A5, HIGH);                                     // turn on pullup resistors
  pinMode(A4, INPUT);                                         // set pin to input
  digitalWrite(A4, HIGH);                                     // turn on pullup resistor

  Wire.begin(MLX90640_address);
  Wire.setClock(400000);                                      // Increase I2C clock speed to 400kHz
  Serial.begin(115200);                                       // we init this first because i think it gives priority on data bus
  
  for (byte i=0;i<64;i++){Serial.println();}                  //  we clear screen in terminal in case reset.
  Serial.println(F("MLX90640 IR EEpromDump"));
  Serial.println();
  Serial.println(F("The following data is from the sensors eeprom."));
  Serial.println(F("Save it! It will be used later on for calibration."));
  Serial.println(F("The data has to be copied into the other sketches."));
  Serial.println();
  delay(500);                                                 // make sure serial done
  
  Wire.onReceive(receiveEvent);                               // register event

  Serial.println();
  Serial.println(F("********************************cut and paste all information below this line***********************************************"));
  Serial.println();
  delay(200);                                                 // serial data to clear
}




uint16_t mydata[32];                                          // array
uint16_t startvalue[32];                                      // array
uint16_t worddata[1];
float ta ;                                                    // we use 4 corner sensors to determin chip temp at start up, then we take lowest pixel on screen and use that.
float tr;                                                     // reflecitve temp. this is open air shift. going with documentation and using -8
float vddpage0;                                               // we need voltage per page
float vddpage1;                                               // we need voltage per page
float emissivity = 0.95;
bool runonce =true;                                           // singleshot





void loop()
{
  if (runonce){ 
    for (int i=0;i<832;i++){
      MLX90640_I2CRead(MLX90640_address, 0x2400+i, 1,worddata);
      delay(1);
      Serial.print(worddata[0]);
      Serial.print((", "));
      delay(1);
      if ((i&15)==15){Serial.println();}                      // every 16 data make a line break
      delay(5);
    }

  Serial.println();
  Serial.println(F("********************************cut and paste all information above this line***********************************************"));
  Serial.println();
    
    while (0==0){};                                          // freeze, since this is only run once
  }
}




/*
 * function receiveEvent
 * this function is registered as an event, see setup()
 */
void receiveEvent(int howMany) {
  while (1 < Wire.available()) {                            // loop through all but the last
    char c = Wire.read();                                   // receive byte as a character
    Serial.print(c);                                        // print the character
  }
  int x = Wire.read();                                      // receive byte as an integer
  Serial.println(x);                                        // print the integer
}
