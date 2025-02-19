// TFT Library & Setup
//
// This Code is made to run on the Elegoo 2,8" TFT Shield
// to use other Display Shields the Driver Specified needs
// to be changed accordingly to the correct one.
//
// For one I was using this was the 0x9341 with a Resolution of 320x240.


#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <HX8347D_kbv.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
//#include <Adafruit_TFTLCD.h>
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

uint16_t g_identifier;



//Temperature & Humidity Sensor
#include <DHT.h>
#define DHTPIN 30
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float Humidity_OLD = 0;
float Temperature_OLD = 0;


//Buttons ( can be changed to any Pin on the Mega. 
//The only open Ports on an Arduino Uno with the Shield are only the 18th and 19th Pins)
const int ButtonU = 44;
const int ButtonD = 46;
const int Button_Check = 48;

int ButtonU_val = 0;
int ButtonD_val = 0;
int Button_Check_val= 0;

int prevButtonU_val = LOW;
int prevButtonD_val = LOW;
int prevButton_Check = LOW;


//Menu Infos
int MenuValue = 0;
int Menuvis = 1;
int MenuValue_old = 99;


//Module Infos
int ActiveModule = 0;


void setup()
{
  Serial.begin(9600);
  dht.begin();
// Setup Pins
  pinMode(44, INPUT);
  pinMode(46, INPUT);
  pinMode(48, INPUT);


  uint32_t when = millis(); //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
  if (!Serial) delay(5000);           //allow some time for Leonardo
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  static uint16_t identifier;
  //    tft.reset();                 //we can't read ID on 9341 until begin()
  g_identifier = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(g_identifier, HEX);
  if (g_identifier == 0x00D3 || g_identifier == 0xD3D3) g_identifier = 0x9481; // write-only shield
  if (g_identifier == 0xFFFF) g_identifier = 0x9341; // serial

    tft.begin(g_identifier);
    tft.fillScreen(BLACK);
}


//------------------------------------
//----------------CODE----------------
//------------------------------------


void loop() 
{
  Serial.println(Menuvis);
  if (Menuvis == 1 ){
    Menu();
  } 
  else
  {
    tft.fillScreen(BLACK);

    switch (MenuValue) 
    {
      case 0:
        Temp_Humi();
        break;
      case 1:
        no_module();
        break;
      case 2:
        no_module();
        break;
      case 3:
        no_module();
        break;
      case 4:
        no_module();
        break;
      case 5:
        no_module();
        break;
      case 6:
        no_module();
        break;
      case 7:
        no_module();
        break;
      case 8:
        no_module();
        break;
      case 9:
        no_module();
        break;
      default:
        break;
    }
  }
}


int Menu() 
{
  DrawMenu();
  while (Menuvis = 1)
  {
    Button_Check_val = digitalRead(Button_Check);
    MenuNav();

    if (Button_Check_val == 1 && Menuvis == 1) 
    {
      --Menuvis;
      Serial.println("Lowerd Menu Vis by 1");
      return Menuvis = 0;
    }
  }
}


void MenuNav() 
{
  ButtonU_val = digitalRead(ButtonU);
  ButtonD_val = digitalRead(ButtonD);

  if (ButtonU_val == HIGH && prevButtonU_val == LOW) 
  {
      ++MenuValue;
  }
  else if (ButtonD_val == HIGH && prevButtonD_val == LOW)
  {
      --MenuValue;
  }
  prevButtonU_val = ButtonU_val;
  prevButtonD_val = ButtonD_val;

  if(MenuValue >=10) 
  {
    MenuValue = 0;
  }
  else if ( MenuValue <= -1)
  {
    MenuValue = 9;
  }
  
  if (MenuValue != MenuValue_old)
  {
    Update_SelectMenu();
  }

  MenuValue_old = MenuValue;    
}


void DrawMenu()
{
  tft.setTextSize(1);
  Serial.println("DrawMenu");
  tft.setTextColor(WHITE, BLACK);
  tft.println("1. [ ] -Luftfeuchtigkeit");
  tft.println("2. [ ] -Temperatur");
  tft.println("3. [ ] -Millis since Start");
  tft.println("4. [ ] -");
  tft.println("5. [ ] -");
  tft.println("6. [ ] -");
  tft.println("7. [ ] -");
  tft.println("8. [ ] -");
  tft.println("9. [ ] -");
  tft.println("10.[ ] -");
  Serial.println("Done Drawing Menu");

  Update_SelectMenu();
}


void Update_SelectMenu()
{
  tft.fillRect(22, 0, 5,240,BLACK);
  
  tft.setTextColor(WHITE);
  switch (MenuValue) 
  {
    case 0:
      tft.setCursor(24 ,0);
      tft.print("*");
      break;
    case 1:
      tft.setCursor(24 ,11);
      tft.print("*");
      break;
    case 2:
      tft.setCursor(24 ,22);
      tft.print("*");
      break;
    case 3:
      tft.setCursor(24 ,33);
      tft.print("*");
      break;
    case 4:
      tft.setCursor(24 ,44);
      tft.print("*");
      break;
    case 5:
      tft.setCursor(24 ,55);
      tft.print("*");
      break;
    case 6:
      tft.setCursor(24 ,66);
      tft.print("*");
      break;
    case 7:
      tft.setCursor(24 ,77);
      tft.print("*");
      break;
    case 8:
      tft.setCursor(24 ,88);
      tft.print("*");
      break;
    case 9:
      tft.setCursor(24 ,99);
      tft.print("*");
      break;
    default:
      break;
  }
}



//-------------------------------------------------
//------------Modules for Menu---------------------
//-------------------------------------------------


void no_module()
{
  tft.setTextColor(BLUE,BLACK);
  tft.fillRoundRect(100, 90, 220, 150,50,RED);
  tft.setTextColor(WHITE,BLACK);
  tft.fillRoundRect(105, 95, 215, 145,50,RED);
  tft.setTextColor(RED,BLACK);
  tft.print("No Module");

  tft.print("Going back to Main Menu in  ");
  tft.setCursor(265,180);
  tft.print("5");
  
  for (int i = 5; i > 0; i--) 
  {
    tft.setCursor(265, 180);
    tft.print(String(i));
    delay(1000);
    tft.fillRect(260, 175, 270, 190, BLACK);

  }

  Menuvis = 1;
  tft.fillScreen(BLACK);
};


void Temp_Humi()
{
  ActiveModule = 1;
  while (ActiveModule == 1) 
  {
    Button_Check_val = digitalRead(Button_Check);

    if (Button_Check_val == 1 && ActiveModule == 1) 
    {
      tft.fillScreen(BLACK);
      ActiveModule = 0;
  	  Menuvis = 1;
      return ActiveModule, Menuvis;

    }
    else
    { 
      float Luftfeuchtigkeit = dht.readHumidity();
      float Temperatur = dht.readTemperature();

      if (Luftfeuchtigkeit != Humidity_OLD && Temperatur != Temperature_OLD)
      {  
      
        tft.fillRect(0, 0, 180,22,BLACK);
        tft.setTextColor(WHITE);
        tft.print("Luftfeuchtigkeit: ");
        tft.println(Luftfeuchtigkeit);
        tft.print("Temperatur: ");
        tft.println(Temperatur);
        Humidity_OLD = Luftfeuchtigkeit;
        Temperature_OLD = Temperatur;
      }      
    }
  }
}


//save for later use / copy paste often used commands
//  tft.setColor(BLACK);
//  tft.fillRect(0,0,320,240);

//  delay(2000);
//  tft.fillScr(BLACK);
//  tft.fillScr(BLUE);
//  tft.setColor(RED);
//  tft.fillRoundRect(80, 70, 239, 169);
  
//  tft.setColor(WHITE);
//  tft.setBackColor(RED);
//  tft.setCursor(93, 0);
//  tft.print("That's it!", CENTER, 93,30);
//  tft.print("Restarting in a", CENTER, 119,30);
//  tft.print("few seconds...", CENTER, 132,30);
  
//  tft.setColor(0, 255, 0);
//  tft.setBackColor(0, 0, 255);
//  tft.print("Runtime: (msecs)", CENTER, 210);
//  tft.printNumI(millis(), CENTER, 225);