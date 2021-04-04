/*
*   DIY IR Thermo Camera with
*
*   ESP32 development board   - controller unit
*   MLX90640                  - IR sensor
*   ILI9341                   - TFT touch display
*   
*
*
*/

// ==================================
// ==== includes and definitions ==== 
// ==================================
#include <Arduino.h>
#include <Wire.h>
#include "SPI.h"

// ==== tft display related =========
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_LED   1
// USE VSPI pins via hardware SPI
#define TFT_CS   17 
#define TFT_DC   16
#define TFT_RST   5

#define TFT_MOSI 23 // just for reference, this variable is not used
#define TFT_CLK  18 // just for reference, this variable is not used
#define TFT_MISO 19 // just for reference, this variable is not used

// Use hardware SPI
// CS, DC and RST can be chosen freely. 
// The hardware SPI pins (VSPI) are known by the Arduino IDE.
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// colormap array
#include "colormaps.h"

// ==== ir sensor related ===========
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

const byte MLX90640_address = 0x33;                         // Default 7-bit unshifted address of the MLX90640
#define TA_SHIFT 8                                          // Default shift for MLX90640 in open air

static float mlx90640To[768];                               // 1D-array holding the 32x24=768 temperature measurements
paramsMLX90640 mlx90640;

// reinterpret the 1D temperature array as a 2D 32*24 array
//static float (&mlx90640To2D)[32][24] = reinterpret_cast<static float (&)[32][24]>(mlx90640To);

// ==== variables
// sensor refresh rate. set one of the following:
// 0:  0.25 Hz (works)
// 1:  0.50 Hz (works)
// 2:  1.00 Hz (works)
// 3:  2.00 Hz (works)
// 4:  4.00 Hz (works)
// 5:  8.00 Hz (works at 800 kHz I2C clock speed, see setup below)
// 6: 16.00 Hz (works at 800 kHz I2C clock speed, see setup below)
// 7: 32.00 Hz (fails)
uint8_t mlx_refreshRate = 4;

// config for the different camera modes
bool mode_dual = false;
int  mode_interp = 0;
int  mode_unit = 0;
bool mode_auto_scale = true;
int  mode_colormap = 0;

// important temperature readings
float T_max = 0.0;
float T_min = 0.0;
float T_center = 0.0;
float T_probe = 0.0;

unsigned long t_loop = 0;
float fps_value = 0.0;


// ==================================
// ==== SETUP =======================
// ==================================

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    Wire.setClock(400000);                                  // increase I2C clock speed to 400kHz

    while (!Serial);                                        // wait for user to open terminal. comment out in final (standalone IR cam) upload
    Serial.println("MLX90640 IR Thermal Camera");

    if (isConnected() == false)
    {
        Serial.println("MLX90640 not detected at default I2C address. Please check wiring. Freezing.");
        while (1);
    }
    Serial.println("MLX90640 online!");

    // get device parameters - we only have to do this once
    int status;
    uint16_t eeMLX90640[832];

    status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
    if (status != 0) Serial.println("Failed to load system parameters (DumpEE failed).");

    status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
    if (status != 0)
    {
        Serial.println("Parameter extraction failed");
        Serial.print(" status = ");
        Serial.println(status);
    }

    // write the value 1901 (HEX) = 6401 (DEC) in the register at position 0x800D 
    // to enable reading out the temperatures! 
    MLX90640_I2CWrite(0x33, 0x800D, 6401);    

    // set sensor refresh rate
    MLX90640_SetRefreshRate(MLX90640_address, mlx_refreshRate);

    // initialize TFT display
    pinMode(TFT_LED, OUTPUT);
    digitalWrite(TFT_LED, HIGH);
    tft.begin();
    tft.setRotation(3);

    // draw the default GUI
    draw_gui();

    t_loop = millis();
}


// ==================================
// ==== LOOP ========================
// ==================================

void loop()
{
    for (byte x = 0 ; x < 2 ; x++)                          // Read both subpages
    {
        uint16_t mlx90640Frame[834];

        int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);
        if (status != 0)
        {
            Serial.print("GetFrameData Error: ");
            Serial.println(status);
        }

        float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
        float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

        float tr = Ta - TA_SHIFT;                           // Reflected temperature based on the sensor ambient temperature 
        float emissivity = 0.95;

        MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
    }

    // Manually correct broken pixels. Change according to the individual unit!
    // e.g.
    // mlx90640To2d[3,15] = 0.25 * (mlx90640To2d[2][15] + mlx90640To2d[4][15] + mlx90640To2d[3][14] + mlx90640To2d[3][16]);
    
    find_T_minmax();

    // Postprocessing and display
    if (mode_interp == 0) 
    {
        PP_not_interpolated();
        //PP_not_interpolated(mlx90640To2D);
    }
    else
    {
        //PP_interpolated(mlx90640To2D);
    }

    // user interaction (touch display)

    // update parts of gui
    draw_crosshair();
    draw_scale_min_max();
    draw_value_center();
    draw_value_hotspot();

    fps_value = 1000.0/(millis() - t_loop);
    t_loop = millis();
    draw_fps();
    
    
    delay(20);
}




// =================================================
// ==== additional function definitions ============
// =================================================



/* 
*    Returns true if the MLX90640 is detected on the I2C bus
*/
boolean isConnected()
   {
    Wire.beginTransmission((uint8_t)MLX90640_address);
  
    if (Wire.endTransmission() != 0)
       return (false); //Sensor did not ACK
    
    return (true);
   }  


// ==================================
// ==== gui     routines ============
// ==================================

void draw_gui()
{
    tft.fillScreen(ILI9341_BLACK);
    draw_grid();
    draw_scale();
    draw_scale_min_max();
    draw_button_dual();
    draw_button_interpolation();
    draw_value_center();
    draw_value_hotspot();
    draw_unit();
    draw_scale_mode();
}

void draw_grid()
{
    // horizontal line below image
    tft.drawLine(0, 193, 320, 193, ILI9341_WHITE);
    // vertical line to the right of the image
    tft.drawLine(257, 0, 257, 240, ILI9341_WHITE);
    // dividers for buttons below image
    tft.drawLine( 65, 193,  65, 240, ILI9341_WHITE);
    tft.drawLine(140, 193, 140, 240, ILI9341_WHITE);
}

void draw_scale()
{
    for (int i = 0; i < 128; i++)
    {
        tft.drawLine(259, 150 - i, 279, 150 - i, colormap[mode_colormap][2*i]);
    }
}

void draw_button_dual()
{
    if (mode_dual)
    {
        tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN);
    }
    else
    {
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }

    tft.setCursor(1, 200);
    tft.setTextSize(2);
    tft.print("DUAL");    
}

void draw_button_interpolation()
{
    tft.setCursor(1, 225);
    tft.setTextSize(2);

    if (mode_interp == 1) // linear interpolation
    {
        tft.setTextColor(ILI9341_BLACK, ILI9341_GREEN);
        tft.print("INT 1");
    }
    else // no interpolation
    {
        tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
        tft.print("INT 0");
    }    
}

void draw_value_center()
{
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(145, 200);
    tft.setTextSize(2);
    tft.print("+ ");

    tft.setCursor(160, 200);
    char tmp[5];
    dtostrf(T_center,5,1,tmp);
    tft.print(tmp);    
}

void draw_value_hotspot()
{
    tft.setTextColor(ILI9341_RED, ILI9341_BLACK);
    tft.setCursor(145, 220);
    tft.setTextSize(2);
    tft.print("o ");

    tft.setCursor(160, 220);
    char tmp[5];
    dtostrf(T_max,5,1,tmp);
    tft.print(tmp);     
}

void draw_unit()
{
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(1);
    tft.setCursor(235, 203);
    tft.print("o");
    if (mode_unit == 0) // temperature degree Celsius
    {
        tft.setTextSize(2);
        tft.setCursor(242, 210);
        tft.print("C");
    }
    else if (mode_unit == 1) // temperature degree Fahrenheit
    {
        tft.setTextSize(2);
        tft.setCursor(242, 210);
        tft.print("F");
    }
}

void draw_scale_mode()
{
    tft.fillRect(290, 24, 320, 130, ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setCursor(295, 60);
    if (mode_auto_scale) // automatic scaling
    {
        tft.print("a");
        tft.setCursor(295, 73);
        tft.print("u");
        tft.setCursor(295, 86);
        tft.print("t");
        tft.setCursor(295, 99);
        tft.print("o");
    }
    else
    {
        tft.print("m");
        tft.setCursor(295, 73);
        tft.print("a");
        tft.setCursor(295, 86);
        tft.print("n");
        tft.setCursor(295, 99);
        tft.print(".");
        
        // ^ symbol at max. value
        tft.drawLine(290, 34, 300, 24, ILI9341_WHITE);
        tft.drawLine(300, 24, 310, 34, ILI9341_WHITE);
        // v symbol at max. value
        tft.drawLine(290, 39, 300, 49, ILI9341_WHITE);
        tft.drawLine(300, 49, 310, 39, ILI9341_WHITE);
        // ^ symbol at min. value
        tft.drawLine(290, 135, 300, 125, ILI9341_WHITE);
        tft.drawLine(300, 125, 310, 135, ILI9341_WHITE);
        // v symbol at min. value
        tft.drawLine(290, 140, 300, 150, ILI9341_WHITE);
        tft.drawLine(300, 150, 310, 140, ILI9341_WHITE);
    }
}

void draw_scale_min_max()
{
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(2);

    // max value
    tft.setCursor(260, 1);
    char tmp[3];
    dtostrf(T_max,3,0,tmp);
    tft.print(tmp);

    // min value
    tft.setCursor(260, 157);
    dtostrf(T_min,3,0,tmp);
    tft.print(tmp);
}

void draw_fps()
{
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setTextSize(1);
    
    tft.setCursor(270, 225);
    char tmp[3];
    dtostrf(fps_value,3,0,tmp);
    tft.print(tmp);

    tft.setCursor(300, 225);
    tft.print("fps");
}

void draw_crosshair()
{
    // draw white crosshair in center
    tft.drawLine(128, 93, 128, 100, ILI9341_WHITE);
    tft.drawLine(129, 93, 129, 100, ILI9341_WHITE);
    tft.drawLine(125, 96, 132,  96, ILI9341_WHITE);
    tft.drawLine(125, 97, 132,  97, ILI9341_WHITE);
}

// ==================================
// ==== post processing =============
// ==================================

void PP_not_interpolated()
{

  /* With 1D field
   *  
   */

   T_center = 0.25 * (mlx90640To[11*32+15] + mlx90640To[11*32+16] + mlx90640To[12*32+15] + mlx90640To[12*32+15]);
   for (int i = 0; i < 24 ; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int magnitude = (int) 256.0 * (mlx90640To[i*32+j] - T_min)/(T_max - T_min);
            tft.fillRect(j*8, i*8, 8, 8, colormap[mode_colormap][magnitude]);
        }
    }

  /* With 2D field
    T_center = 0.25 * (T[16][12] + T[17][12] + T[16][13] + T[17][13]); 

    for (int i = 0; i < 24 ; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            int magnitude = (int) 256.0 * (T[i][j] - T_min)/(T_max - T_min);
            tft.fillRect(j*8, i*8, 8, 8, colormap[mode_colormap][magnitude])
        }
    }
  */
}

// ==================================
// ==== search / sort functions =====
// ==================================

void find_T_minmax()
{
    T_max = -273.15;
    T_min = 4000.00;

    for (int i=0; i<768; i++)
    {
      T_probe = mlx90640To[i];
      if (T_probe > T_max)
      {
        T_max = T_probe;
      }
      if (T_probe < T_min)
      {
        T_min = T_probe;
      }
    }
}
