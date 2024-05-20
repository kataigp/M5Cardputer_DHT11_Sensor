#include "M5Cardputer.h"
#include "DHT11.h"
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"

M5Canvas sprite(&M5Cardputer.Display);

const int DHT11PIN = 1;

DHT11 dht11(DHT11PIN);

bool tempSelected = true;

void setup() {

  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setBrightness(70);
  
  sprite.createSprite(240,135);
  sprite.setTextDatum(TL_DATUM);

  drawHeader("---");
  sprite.pushSprite(0,0);
}

void loop() {  
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_FN)) {
      tempSelected=!tempSelected;
    }
    drawHeader("    ");
    delay(60);
  }
  drawSensorData();
}

void drawSensorData() {
    sprite.loadFont(NotoSansBold36);
    if(tempSelected) {
      int temperature = dht11.readTemperature();
      if(temperature < 51) {
        String tempStr = String(temperature);
        if(temperature < 10) {
          tempStr = "  "+tempStr;
        }

        sprite.setTextColor(TFT_SILVER, TFT_BLACK);
        sprite.drawString(tempStr, 82, 60);
        sprite.fillCircle(130,64,3,TFT_SILVER);
        sprite.drawString("C", 134, 60);
      }
    }
    else {
      int humidity = dht11.readHumidity();
      if(humidity < 91)
        sprite.setTextColor(TFT_SILVER, TFT_BLACK);
        sprite.drawString(String(humidity), 82, 60);
        sprite.drawString("%", 130, 60);
    }
    sprite.pushSprite(0,0);
}

void drawHeader(String placeholder) {

  sprite.fillSprite(BLACK);
  sprite.loadFont(NotoSansBold15);
  sprite.setTextColor(TFT_WHITE,TFT_BLACK);
  
  sprite.setTextColor(TFT_SILVER,(tempSelected ? TFT_BLUE : TFT_BLACK));
  sprite.drawString(" TEMPERATURE ",6,4);
  sprite.setTextColor(TFT_SILVER,(!tempSelected ? TFT_BLUE : TFT_BLACK));
  sprite.drawString(" HUMIDITY ", 6,22);
  
  sprite.unloadFont();
  sprite.loadFont(NotoSansBold36);
  sprite.setTextColor(TFT_BLUE,TFT_BLACK);
  sprite.drawString("DHT11", 122, 4);

  sprite.drawString(placeholder, 90, 60);
  sprite.unloadFont();

  sprite.drawString("Press Fn to change function!", 6, 120);
}