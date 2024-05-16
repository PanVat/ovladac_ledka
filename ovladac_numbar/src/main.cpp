#include <Arduino.h>
#include <IRremote.hpp>

#define IR_USE_AVR_TIMER1
#define IR_RECEIVE_PIN 12 // Pin pro připojení IR přijímače
// Definice pinů pro LED diody
#define RED_LED_PIN 5
#define GREEN_LED_PIN 6
#define BLUE_LED_PIN 9
// Enter pro každou barvu
#define RED_ENTER 3125149440
#define GREEN_ENTER 3108437760
#define BLUE_ENTER 3091726080

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
int codesLength = sizeof(codes) / sizeof(codes[0]);
String stringNum = "";

void reset(){
  for (int i = RED_LED_PIN; i < BLUE_LED_PIN; i++)
  {
    analogWrite(i, LOW);
  }
}

String input(unsigned long irData)
{
  for (int i = 0; i < codesLength; i++)
  {
    if (irData == codes[i])
    {
      return String(i);
    }
  }
  return "";
}

void setup()
{
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Inicializace přijimače
  pinMode(RED_LED_PIN, OUTPUT);                          // Nastavení pinu červené LED jako výstup
  pinMode(GREEN_LED_PIN, OUTPUT);                        // Nastavení pinu zelené LED jako výstup
  pinMode(BLUE_LED_PIN, OUTPUT);                         // Nastavení pinu modré LED jako výstup
  Serial.begin(9600);
}

void loop()
{
  if (IrReceiver.decode())
  {
    unsigned long irData = IrReceiver.decodedIRData.decodedRawData; // Přečtení kodu z přijímače
    if (irData > 0)
    {
      if (irData == RED_ENTER)
      {
        reset();
        int intNum = stringNum.toInt();
        if (intNum < 256)
        {
          analogWrite(RED_LED_PIN, intNum);
          stringNum = "";
        }
        else
        {
          Serial.println("Mimo rozsah");
          reset();
          stringNum = "";
        }
      }
      else
      {
        stringNum += input(irData);
        Serial.println(stringNum);
      }
    }
    IrReceiver.resume();
  }
}