#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVE_PIN 12 // Pin pro připojení IR přijímače

// Definice pinů pro LED diody
#define RED_LED_PIN 3
#define GREEN_LED_PIN 5
#define BLUE_LED_PIN 6

// Definice IR kódů pro jednotlivá tlačítka
unsigned long codes[] = {
    3910598400, // 0
    4077715200, // 1
    3877175040, // 2
    2707357440, // 3
    4144561920, // 4
    3810328320, // 5
    2774204160, // 6
    3175284480, // 7
    2907897600, // 8
    3041591040, // 9
};

// Definice barev
#define RED 0
#define GREEN 1
#define BLUE 2

int selectedColor = -1; // Vybraná barva LED

void setup()
{
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializace přijimače
  pinMode(RED_LED_PIN, OUTPUT);                          // Nastavení pinu červené LED jako výstup
  pinMode(GREEN_LED_PIN, OUTPUT);                        // Nastavení pinu zelené LED jako výstup
  pinMode(BLUE_LED_PIN, OUTPUT);                         // Nastavení pinu modré LED jako výstup
}

void setLedColor(int color)
{
  switch (color)
  {
  case RED:
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, LOW);
    break;
  case GREEN:
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(BLUE_LED_PIN, LOW);
    break;
  case BLUE:
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(BLUE_LED_PIN, HIGH);
    break;
  }
}

void loop()
{
  if (IrReceiver.decode())
  {
    unsigned long irData = IrReceiver.decodedIRData.decodedRawData; // Přečtení kodu z přijímače

    for (int i = 0; i < sizeof(codes) / sizeof(codes[0]); i++)
    {
      if (irData == codes[i])
      {
        selectedColor = i;
        break;
      }
    }

    if (selectedColor != -1)
    {
      setLedColor(selectedColor);
    }

    IrReceiver.resume();
  }
}