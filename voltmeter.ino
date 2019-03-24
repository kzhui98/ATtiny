#include <U8glib.h>

float voltage = 0;
float angle = 0;
float q = 0;
float y1 = 0;
float x1 = 0;
float y = 0;
float x = 0;

U8GLIB_SSD1306_64X48 u8g(1, 0, 3, 4, 5);

int analogPin = (A1);
//int analogPin = (A1, INPUT_PULLDOWN);

void setup() {
}

void display_voltmeter(float volatege, float q, float x1, float y1, float x, float y) {
  float angle = 0;
  
  u8g.firstPage();
  do {
    //u8g.setFont(u8g_font_osb18);
    u8g.setFont(u8g_font_fixed_v0);
    u8g.setPrintPos(38, 7);
    u8g.print(voltage);
    //u8g.drawStr(38, 7, voltage);
    u8g.setPrintPos(8, 49);
    u8g.print("0");
    u8g.setPrintPos(12, 39);
    u8g.print("1");
    u8g.setPrintPos(19, 30);
    u8g.print("2");
    u8g.setPrintPos(39, 30);
    u8g.print("3");
    u8g.setPrintPos(50, 39);
    u8g.print("4");
    u8g.setPrintPos(54, 49);
    u8g.print("5");
    angle = (voltage * 180) / 5;
    y1 = 120 * angle * (180 - angle) / (40500 - (angle * (180 - angle)));
    if (90 <= angle <= 180){
    x1 = -120 * (angle - 90) * (180 - x + 90) / (40500 - (angle - 90) * (180 - angle + 90));
      }
      if ((0 <= angle < 90) || (angle == 0)){
      q = 90 - angle + 90;
      x1 = 120 * (q - 90) * (180 - q + 90) / (40500 - (q - 90) * (180 - q + 90));
      }

      y = 47 - y1;
      x = 32 - x1;

      u8g.drawCircle(32, 47, 30);
      u8g.drawLine(2, 47, 5, 47);
      u8g.drawLine(7, 30, 10, 33);
      u8g.drawLine(22, 19, 23, 22);
      u8g.drawLine(42, 19, 41, 22);
      u8g.drawLine(57, 31, 54, 34);
      u8g.drawLine(62, 47, 59, 47);
      //u8g.setFont(u8g_font_fixed_v0);
      //u8g.setPrintPos(7, 41);
      //u8g.print("0");
      //u8g.setPrintPos(25, 37);
      //u8g.print("1");
      //u8g.setPrintPos(19, 28);
      //u8g.print("2");
      //u8g.setPrintPos(39, 28);
      //u8g.print("3");
      //u8g.setPrintPos(50, 31);
      //u8g.print("4");
      //u8g.setPrintPos(55, 41);
      //u8g.print("5");
      u8g.drawLine(32, 47 , x, y );

  } while ( u8g.nextPage() );
}
void loop() {

  float analog_input = analogRead(analogPin);
  //voltage = map(analogRead(analogPin), 0, 1024, 0, 5); 
  voltage = (analog_input * 5) / 1024;
  display_voltmeter(voltage, q,  x1, y1, x, y);

}

