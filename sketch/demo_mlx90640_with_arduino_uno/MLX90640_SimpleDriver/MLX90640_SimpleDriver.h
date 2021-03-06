/**
 * @copyright (C) 2017 Melexis N.V.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <math.h>

//I2C_BUFFER_LENGTH is defined in Wire.H

//#define I2C_BUFFER_LENGTH BUFFER_LENGTH
#define I2C_BUFFER_LENGTH 32

int MLX90640_I2CWrite(uint8_t _deviceAddress, unsigned int writeAddress, uint16_t data)
{
  Wire.beginTransmission((uint8_t)_deviceAddress);
  Wire.write(writeAddress >> 8); //MSB
  Wire.write(writeAddress & 0xFF); //LSB
  Wire.write(data >> 8); //MSB
  Wire.write(data & 0xFF); //LSB
  
  if (Wire.endTransmission() != 0)
  {
    //Sensor did not ACK
    Serial.println("Error: Sensor did not ack");
    return (-1);
  }

  uint16_t dataCheck;
int   MLX90640_I2CRead(_deviceAddress, writeAddress, 1, &dataCheck);
  if (dataCheck != data)
  {
    //Serial.println("The write request didn't stick");
    return -2;
  }

  return (0); //Success
}

void ProgmemExtractVDDParameters(uint16_t datastatus){

  //since we have data directly in epprom, all we do here is verify it matches sensor data and return status
  //rest of code will look at internal flash of progmem directly. it will however generate an error here
  //is we do not have values to extract or they do not match system.
}




int MLX90640_I2CRead(uint8_t _deviceAddress, unsigned int startAddress, unsigned int nWordsRead, uint16_t *data)
{

  //Caller passes number of 'unsigned ints to read', increase this to 'bytes to read'
  uint16_t bytesRemaining = nWordsRead * 2;

  //It doesn't look like sequential read works. Do we need to re-issue the address command each time?

  uint16_t dataSpot = 0; //Start at beginning of array

  //Setup a series of chunked I2C_BUFFER_LENGTH byte reads
  while (bytesRemaining > 0)
  {
    Wire.beginTransmission(_deviceAddress);
    Wire.write(startAddress >> 8); //MSB
    Wire.write(startAddress & 0xFF); //LSB
    if (Wire.endTransmission(false) != 0) //Do not release bus
    {
      Serial.println("No ack read");
      return (0); //Sensor did not ACK
    }

    uint16_t numberOfBytesToRead = bytesRemaining;
    if (numberOfBytesToRead > I2C_BUFFER_LENGTH) numberOfBytesToRead = I2C_BUFFER_LENGTH;

    Wire.requestFrom((uint8_t)_deviceAddress, numberOfBytesToRead);
    if (Wire.available())
    {
      for (uint16_t x = 0 ; x < numberOfBytesToRead / 2; x++)
      {
        //Store data into array
        data[dataSpot] = Wire.read() << 8; //MSB
        data[dataSpot] |= Wire.read(); //LSB

        dataSpot++;
      }
    }

    bytesRemaining -= numberOfBytesToRead;

    startAddress += numberOfBytesToRead / 2;
  }

  return (0); //Success
}

int MLX90640_DumpEE(uint8_t slaveAddr, uint16_t *eeData)
{
     return MLX90640_I2CRead(slaveAddr, 0x2400, 832, eeData);
}



int MLX90640_GetFrameData(uint8_t slaveAddr, uint16_t *frameData)
{
    uint16_t dataReady = 1;
    uint16_t controlRegister1;
    uint16_t statusRegister;
    int error = 1;
    uint8_t cnt = 0;
    Serial.println(".");
    dataReady = 0;
    while(dataReady == 0)
    {
        error = MLX90640_I2CRead(slaveAddr, 0x8000, 1, &statusRegister);
        if(error != 0)
        {
            return error;
        }    
        dataReady = statusRegister & 0x0008;
    }       
        
    while(dataReady != 0 && cnt < 5)
    { 
        error = MLX90640_I2CWrite(slaveAddr, 0x8000, 0x0030);
        if(error == -1)
        {
            return error;
        }
            
        error = MLX90640_I2CRead(slaveAddr, 0x0400, 832, frameData); 
        if(error != 0)
        {
            return error;
        }
                   
        error = MLX90640_I2CRead(slaveAddr, 0x8000, 1, &statusRegister);
        if(error != 0)
        {
            return error;
        }    
        dataReady = statusRegister & 0x0008;
        cnt = cnt + 1;
    }
    
    if(cnt > 4)
    {
        return -8;
    }    
    
    error = MLX90640_I2CRead(slaveAddr, 0x800D, 1, &controlRegister1);
    frameData[832] = controlRegister1;
    frameData[833] = statusRegister & 0x0001;
    
    if(error != 0)
    {
        return error;
    }
    
    return frameData[10];    
}
int MLX90640_GetCurResolution(uint8_t slaveAddr)
{
    uint16_t controlRegister1;
    int resolutionRAM;
    int error;
    
    error = MLX90640_I2CRead(slaveAddr, 0x800D, 1, &controlRegister1);
    if(error != 0)
    {
        return error;
    }    
    resolutionRAM = (controlRegister1 & 0x0C00) >> 10;
    
    return resolutionRAM; 
}

int MLX90640_GetCurMode(uint8_t slaveAddr)
{
    uint16_t controlRegister1;
    int modeRAM;
    int error;
    
    error = MLX90640_I2CRead(slaveAddr, 0x800D, 1, &controlRegister1);
    if(error != 0)
    {
        return error;
    }    
    modeRAM = (controlRegister1 & 0x1000) >> 12;
    
    return modeRAM; 
}

int MLX90640_GetRefreshRate(uint8_t slaveAddr)
{
    uint16_t controlRegister1;
    int refreshRate;
    int error;
    
    error = MLX90640_I2CRead(slaveAddr, 0x800D, 1, &controlRegister1);
    if(error != 0)
    {
        return error;
    }    
    refreshRate = (controlRegister1 & 0x0380) >> 7;
    
    return refreshRate;
}
void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
}


