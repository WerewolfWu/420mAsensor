//Example sketch for 4-20mA sensor
#include <Wire.h>
#include <hd44780.h>                       // For running the LCD screen. copy pasted from library example, main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // For running the LCD screen. copy pasted from library example. i2c expander i/o class header
const int SENSOR_PIN = A6; 
const int NUM_AVG = 1000; //many ADC reads + average = lower noise 
const float RESISTOR_VALUE = 144.4;
const float ANALOG_REFERENCE_VALUE = 3.417; //Analog reference, which is also the full scale voltage of ADC in this case
hd44780_I2Cexp lcd(0x27); // declare lcd object: auto locate & auto config expander chip
//----------------------------------------
void setup() {    // put your setup code here, to run once:
  lcd.begin(20,4); //LCD screen size 20 columns by 4 lines
  lcd.backlight(); //If you don't want backlight, use lcd.noBacklight();
  analogReference(EXTERNAL); //use external 3.3V reference
}
//-----------------------------------------
void display_sensor_value() {
  long int adc_reading = 0;
  for (int i = 0; i<NUM_AVG; i++) {adc_reading += analogRead(SENSOR_PIN);}
  float voltage_value = ((float)adc_reading/NUM_AVG + 0.5 )/1024.0*ANALOG_REFERENCE_VALUE; // +0.5 is to change from round down to round to nearest for ADCs
  float current_value_mA = voltage_value / RESISTOR_VALUE * 1000.0;
  float percentage_value = current_value_mA*6.25 - 25.0;
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("4-20mA Sensor Demo");
  lcd.setCursor(0,1); lcd.print(String("Voltage: ") + String(voltage_value,3) + " V");
  lcd.setCursor(0,2); lcd.print(String("Current: ") + String(current_value_mA, 3) + " mA");
  lcd.setCursor(0,3); lcd.print(String("Percentage: ") + String(percentage_value,2) + '%');
}
//-----------------------------------------
void loop() {  // put your main code here, to run repeated
  display_sensor_value();
  delay(1000);
}
