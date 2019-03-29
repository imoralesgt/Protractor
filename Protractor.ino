#include <Ultrasonic.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



/* ===================== 
 * Board pin definitions
 * =====================
*/
//Ultrasonic sensor 0
#define ULTRASONIC_TRIGGER_PIN 8
#define ULTRASONIC_ECHO_PIN    7

//OLED 128x64 Display
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13


/* =========
 * Constants
 * =========
*/
//OLED Definitions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels




/* =======
 * Globals
 * =======
*/
Ultrasonic u0(ULTRASONIC_TRIGGER_PIN, ULTRASONIC_ECHO_PIN); //Trigger Pin, Echo Pin  
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);



/* =================== 
 * Function prototypes
 * ===================
*/
int initUltrasonic(Ultrasonic sensor);
int getDistance(Ultrasonic sensor);




void setup(){
  Serial.begin(115200);
  initUltrasonic(u0);
  display.begin(SSD1306_SWITCHCAPVCC);

  //IRM Init OLED display
  //display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
}

void loop(){
  int x;
  x = getDistance(u0);

  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(x);
  display.setTextSize(2);
  display.println(F("cm."));
  display.display();
  //Serial.println(x);
  delay(500);
}


int getDistance(Ultrasonic sensor){
  int dist;
  dist = sensor.distance(1); //IRM Measure distance in cm
  if(dist > 400) //IRM if out of range
    return -1; 
  return dist; //IRM Otherwise return measured value
}

int initUltrasonic(Ultrasonic sensor){
  sensor.init();
  return 0;
}

