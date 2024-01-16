// TFT Library & Setup
//
// This Code is made to run on the Elegoo 2,8" TFT Shield
// to use other Display Shields the Driver Specified needs
// to be changed accordingly to the correct one.
//
// For one I was using this was the 0x9341 with a Resolution of 320x240.

#include <UTFTGLUE.h>
UTFTGLUE tft(0x9341,A5,A4,A3,A2,A0); 


//Colors
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

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


  // Setup the LCD
  tft.InitLCD();
  tft.setFont(SmallFont);
  tft.setColor(WHITE);
  tft.fillScreen(BLACK);


};

//------------------------------------
//----------------CODE----------------
//------------------------------------

void loop() {
  Serial.println(Menuvis);
  if (Menuvis == 1 ){

    Menu();

  } else {

    tft.fillScreen(BLACK);

    switch (MenuValue) {
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

int Menu() {
  DrawMenu();
  while (Menuvis = 1) {
    Button_Check_val = digitalRead(Button_Check);
    MenuNav();

    if (Button_Check_val == 1 && Menuvis == 1) {
      --Menuvis;
      Serial.println("Lowerd Menu Vis by 1");
      return Menuvis = 0;
    }
  }
}



void MenuNav() {
    ButtonU_val = digitalRead(ButtonU);
    ButtonD_val = digitalRead(ButtonD);

    if (ButtonU_val == HIGH && prevButtonU_val == LOW) {
      ++MenuValue;
    } else if (ButtonD_val == HIGH && prevButtonD_val == LOW) {
      --MenuValue;
    }
    prevButtonU_val = ButtonU_val;
    prevButtonD_val = ButtonD_val;
 
    if(MenuValue >=10) {
      MenuValue = 0;
    } else if ( MenuValue <= -1)  {
      MenuValue = 9;
    }

    if (MenuValue != MenuValue_old) {
      Update_SelectMenu();
    }

     MenuValue_old = MenuValue;    
}


void DrawMenu(){
    Serial.println("DrawMenu");
    tft.setFont(SmallFont);
    tft.setColor(WHITE);
    tft.print("1. [ ] -Luftfeuchtigkeit", 0 ,0);
    tft.print("2. [ ] -Temperatur", 0, 11);
    tft.print("3. [ ] -Millis since Start", 0 ,22);
    tft.print("4. [ ] -", 0, 33);
    tft.print("5. [ ] -", 0 ,44);
    tft.print("6. [ ] -", 0, 55);
    tft.print("7. [ ] -", 0, 66);
    tft.print("8. [ ] -", 0, 77);
    tft.print("9. [ ] -", 0, 88);
    tft.print("10.[ ] -", 0, 99);
  
    Update_SelectMenu();
}

void Update_SelectMenu(){
  tft.setColor(BLACK);
  tft.fillRect(30, 0, 39,240);
  
  tft.setColor(WHITE);
  switch (MenuValue) {
    case 0:
      tft.print("*", 32 ,0);
      break;
    case 1:
      tft.print("*", 32 ,11);
      break;
    case 2:
      tft.print("*", 32 ,22);
      break;
    case 3:
      tft.print("*", 32 ,33);
      break;
    case 4:
      tft.print("*", 32 ,44);
      break;
    case 5:
      tft.print("*", 32 ,55);
      break;
    case 6:
      tft.print("*", 32 ,66);
      break;
    case 7:
      tft.print("*", 32 ,77);
      break;
    case 8:
      tft.print("*", 32 ,88);
      break;
    case 9:
      tft.print("*", 32 ,99);
      break;
    default:
      break;
  }
}




//-------------------------------------------------
//------------Modules for Menu---------------------
//-------------------------------------------------

void no_module(){
    tft.setColor(BLUE);
    tft.fillRoundRect(100, 90, 220, 150);
    tft.setColor(WHITE);
    tft.fillRoundRect(105, 95, 215, 145);
    tft.setColor(RED);
    tft.setBackColor(WHITE);
    tft.print("No Module", CENTER, 115);

    tft.setColor(WHITE);
    tft.setBackColor(BLACK);
    tft.print("Going back to Main Menu in  ", CENTER, 180);
    tft.print("5",265,180);
    
    for (int i = 5; i > 0; i--) {
      tft.print(String(i), 265, 180);
      delay(1000);
      tft.setColor(BLACK);
      tft.fillRect(260, 175, 270, 190);
      tft.setColor(WHITE);
  }
  Menuvis = 1;
  tft.fillScreen(BLACK);
};

void Temp_Humi(){
  ActiveModule = 1;
  while (ActiveModule == 1) {
    Button_Check_val = digitalRead(Button_Check);
    if (Button_Check_val == 1 && ActiveModule == 1) {

      tft.fillScreen(BLACK);
      ActiveModule = 0;
  	  Menuvis = 1;
      return ActiveModule, Menuvis;

    } else {
      
      float Luftfeuchtigkeit = dht.readHumidity();
      float Temperatur = dht.readTemperature();

      if (Luftfeuchtigkeit != Humidity_OLD && Temperatur != Temperature_OLD)  {  
      
      tft.setColor(BLACK);
      tft.fillRect(0, 0, 180,22);
      tft.setColor(WHITE);
      tft.print("Luftfeuchtigkeit: ", 0 ,0);
      tft.println(Luftfeuchtigkeit);
      tft.print("Temperatur: ", 0, 11);
      tft.println(Temperatur);
      Humidity_OLD = Luftfeuchtigkeit;
      Temperature_OLD = Temperatur;
      }      
    }
  }
  return;
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