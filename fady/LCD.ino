#include <LiquidCrystal.h>
 
// Create An LCD Object. Signals: [ RS, EN, D4, D5, D6, D7 ]
LiquidCrystal My_LCD(13, 12, 14, 27, 26, 25);
 
byte WIFIChar[] = {
  B00001,
  B00011,
  B00111,
  B11111,
  B11111,
  B00111,
  B00011,
  B00001
};
 
void setup()
{
  // Initialize The LCD. Parameters: [ Columns, Rows ]
  My_LCD.begin(16, 2);
  // Create a Custom Character (WIFI)
  My_LCD.createChar(0, WIFIChar);
  // Clears The LCD Display
  My_LCD.clear();
 
  // Display The First Message In Home Position (0, 0)
  My_LCD.print("WIFI Scanner ");
  // Append The New Char To The Message
  // Note That: byte(0) Now Represents Our 1st New Custom Char
  My_LCD.write(byte(0));
}
 
void loop()
{
  // Do Nothing...
}