#include "FastLED.h"
#include <IRremote.h>

#define IR_RECEIVE_PIN  2

#define LED_PIN  6

#define NUM_LEDS 44

const int COMMAND_BRIGHTNESS_UP = 0x5;
const int COMMAND_BRIGHTNESS_DOWN = 0x4;
const int COMMAND_OFF = 0x6;
const int COMMAND_ON = 0x7;
const int COMMAND_RED = 0x9;
const int COMMAND_RED_1 = 0xD;
const int COMMAND_RED_2 = 0x15;
const int COMMAND_RED_3 = 0x19;
const int COMMAND_RED_4 = 0x11;
const int COMMAND_GREEN = 0x8;
const int COMMAND_GREEN_1 = 0xC;
const int COMMAND_GREEN_2 = 0x14;
const int COMMAND_GREEN_3 = 0x18;
const int COMMAND_GREEN_4 = 0x10;
const int COMMAND_BLUE = 0xA;
const int COMMAND_BLUE_1 = 0xE;
const int COMMAND_BLUE_2 = 0x16;
const int COMMAND_BLUE_3 = 0x1A;
const int COMMAND_BLUE_4 = 0x12;
const int COMMAND_WHITE = 0xB;
const int COMMAND_FLASH = 0xF;
const int COMMAND_STROBE = 0x17;
const int COMMAND_FADE = 0x1B;
const int COMMAND_SMOOTH = 0x13;

CRGB leds[NUM_LEDS];

const float BRIGHTNESS_STEP = 0.20;

float brightness = 1;
int colorR = 255;
int colorG = 255;
int colorB = 255;

bool isModeRainbow = false;
int rainbowHue = 0;

const int STROBE_PERIOD = 40;

bool isModeStrobe = false;
int strobeProgress = 0;
float strobeBrightness = 0;

void progressRainbow() {
  rainbowHue += 1;
  if (rainbowHue > 255) {
    rainbowHue = 0;
  }

  fill_rainbow(leds, NUM_LEDS, rainbowHue);
  FastLED.show();
}

void progressStrobe() {
  strobeProgress += 1;

  if (strobeProgress == STROBE_PERIOD) {
    if (strobeBrightness < 0.5) {
      strobeBrightness = 1;
    }
    else {
      strobeBrightness = 0;
    }

    strobeProgress = 0;

    writeColor(strobeBrightness);
  }
}

int applyBrightness(int color, float brightness)
{
    return min(max(round(color * brightness), 0), 255);
}

void writeColor(float brightness)
{
    fill_solid(leds, NUM_LEDS, CRGB(applyBrightness(colorR, brightness), applyBrightness(colorG, brightness), applyBrightness(colorB, brightness)));
    FastLED.show();
}

void setColor(int r, int g, int b, float brightness)
{
    isModeRainbow = false;
    isModeStrobe = false;
    colorR = r;
    colorG = g;
    colorB = b;
    brightness = brightness;
}

void processRemoteCommand()
{
  if (IrReceiver.decode())
    {
      // Print a short summary of received data
      IrReceiver.printIRResultShort(&Serial);
      if (IrReceiver.decodedIRData.protocol == UNKNOWN)
      {
          // We have an unknown protocol here, print more info
          IrReceiver.printIRResultRawFormatted(&Serial, true);
      }
      Serial.println();

      /*
        * Finally, check the received data and perform actions according to the received command
        */
      if (IrReceiver.decodedIRData.command == COMMAND_BRIGHTNESS_UP)
      {
          brightness = max(min(brightness + BRIGHTNESS_STEP, 1), 0);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BRIGHTNESS_DOWN)
      {
          brightness = max(min(brightness - BRIGHTNESS_STEP, 1), 0);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_ON)
      {
          brightness = 1;
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_OFF)
      {
          brightness = 0;
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_RED)
      {
          setColor(255, 0, 0, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_RED_1)
      {
          setColor(255, 146, 99, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_RED_2)
      {
          setColor(255, 96, 28, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_RED_3)
      {
          setColor(250, 170, 135, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_RED_4)
      {
          setColor(255, 255, 0, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_GREEN)
      {
          setColor(0, 255, 0, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_GREEN_1)
      {
          setColor(148, 255, 148, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_GREEN_2)
      {
          setColor(122, 255, 244, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_GREEN_3)
      {
          setColor(17, 168, 191, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_GREEN_4)
      {
          setColor(0, 91, 105, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BLUE)
      {
          setColor(0, 0, 255, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BLUE_1)
      {
          setColor(62, 116, 250, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BLUE_2)
      {
          setColor(153, 0, 255, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BLUE_3)
      {
          setColor(125, 0, 46, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_BLUE_4)
      {
          setColor(247, 126, 241, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_WHITE)
      {
          setColor(255, 255, 255, 1);
          writeColor(brightness);
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_SMOOTH)
      {
        isModeRainbow = true;
        isModeStrobe = false;
      }
      else if (IrReceiver.decodedIRData.command == COMMAND_STROBE)
      {
        isModeStrobe = true;
        isModeRainbow = false;
      }

      delay(1);

      IrReceiver.resume();
    } 
    else if (IrReceiver.isIdle() && isModeRainbow)
    {
      progressRainbow();
      delay(1);
    } 
    else if (IrReceiver.isIdle() && isModeStrobe)
    {
      progressStrobe();
      delay(1);
    }
}

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);

  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
}

void loop() { 
  processRemoteCommand();
}