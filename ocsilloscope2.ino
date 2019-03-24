#include "U8glib.h"


U8GLIB_SSD1306_64X48 u8g(1, 0, 3, 4, 5);

int val;
int xPos = 0;
int trigger = 0;
int scanVal[64];
int xDraw;

void drawText(void) {
  val = analogRead(A1);
  val = map(val, 0, 1023, 47, 0);

  scanVal[xPos] = val;
  //u8g.setPrintPos(50, 63);
  //u8g.print("Y");
  //u8g.print(val);

  //u8g.setPrintPos(20, 63);// Set Cursor.
  //u8g.print("X");
  //u8g.print(xPos);// Print out the X value.
}

void drawScan(void) {
  val = scanVal[xDraw];
  u8g.drawPixel(xDraw, val);
  xDraw++;
}


void drawScannew(void) {
  if  (xDraw <= 63) {
    scanVal[xDraw] = scanVal[(xDraw + 1)];
    val = scanVal[xDraw];
    u8g.drawPixel(xDraw, val);
    xDraw++;
  }
  else {
    scanVal[xDraw] = scanVal[63];
    u8g.drawPixel(xDraw, val);
    xDraw++;
  }
}

void setup(void) {
  //u8g.setRot180();
  //u8g.setFont(u8g_font_6x10r);
}

void loop(void) {
  u8g.firstPage();
  do {
    drawText();
    xDraw = 0;

    if (trigger == 1) {
      do
      {
        drawScannew();
      }
      while (xDraw <= 63);
    }

    else {
      do
      {
        drawScan();
      }
      while (xDraw <= 63);
    }
  } while (u8g.nextPage());


  if (xPos == 63) trigger = 1;
  else xPos++;

}
