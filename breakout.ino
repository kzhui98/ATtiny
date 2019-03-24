#include <U8glib.h>

U8GLIB_SSD1306_128X64 u8g(1, 0, 3, 4, 5);

int direction = 1;
/*
  upright = 1
  downright= 2
  downleft = 3
  upleft = 4
 */
  

int x, x_line,ball_x = 64, ball_y = 50;

void setup() {
  // put your setup code here, to run once:
  //U8GLIB_SSD1306_128X64 u8g(1, 0, 3, 4, 5);
  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_fur11r);
  //u8g.setColorIndex(1); 
}

void loop() {
  // put your main code here, to run repeatedly:

  u8g.firstPage();
  do {
    drawframe();
    //drawbox();
    drawline();
    //u8g.drawBox(5,5,20,5);
    drawball();
        
  } while ( u8g.nextPage() );

}

void drawframe() {
  u8g.drawFrame(0,0,127,67);
  /*u8g.drawHLine(0,0,1);
  u8g.drawVLine(0,0,1);
  u8g.drawVLine(127,0,1);*/
}

void drawbox() {
  for(int i=2; i<127; i+=21){
    for(int j=2; j<25; j+=6){
      u8g.drawBox(i,j,20,5);
    }
  }
}

void drawline() {
  x_line = map(analogRead(A1), 0, 1023, 97, 0);
  u8g.drawLine(x_line, 62, (x_line + 30), 62);
}

void drawball() {
  switch (direction) {
    case 1:{  //upright
      if (ball_y<=5){
        direction = 2;
      }
      else if (ball_y>=6){
        u8g.drawCircle(ball_x++, ball_y--, 3);
        if (ball_x >=122){
          direction = 4;
        }
      }
    }break;
    case 2:{  //downright
      if (ball_x>=122 ){
        direction = 3;
      }
      else if (ball_x<=121){
        u8g.drawCircle(ball_x++, ball_y++, 3);
        if (ball_y>=58){
          if (ball_x>=x_line && ball_x<=(x_line+30)) {
            direction = 1;
          }
          else {
            //u8g.drawStr(20, 10, "Game Over");
            u8g.setPrintPos(20, 30);
            u8g.print("Game over");
          }
        }
      }
    }break;
    case 3:{   //downleft
      if (ball_y>=58) {
        if(ball_x>=x_line && ball_x<=(x_line+30)) {
          direction = 4;
        }
        else{
          //u8g.drawStr(20, 10, "Game Over");
          u8g.setPrintPos(20, 30);
          u8g.print("Game over");
        }
      }
      else if (ball_y<=57){
        u8g.drawCircle(ball_x--, ball_y++, 3);
        if (ball_x<=5){
          direction = 2;
        }
      }
    }break;
    case 4:{   //upleft
      if (ball_y<=5){
        direction = 3;
      }
      else if (ball_y>=6){
        u8g.drawCircle(ball_x--, ball_y--, 3);
        if (ball_x<=5){
          direction = 1;
        }
      }
    }
  }
}
