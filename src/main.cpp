#include <Arduino.h>
#include <SoftwareSerial.h>

#define pinRX 0
#define pinTX 1

#define LED_PIN 13

#define uart_delay 10

String uart_command = "";
SoftwareSerial softSerial(pinTX, pinRX);

void setup()
{

  softSerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

long uart_millis = 0;

void loop()
{
  if (softSerial.available() > 0)
  {
    while (softSerial.available())
    {
      uart_command += char(softSerial.read());
      if (uart_command == "ON")
      {
        digitalWrite(LED_BUILTIN, LOW);
        uart_command = "";
      }

      if (uart_command == "OFF")
      {
        digitalWrite(LED_BUILTIN, HIGH);
        uart_command = "";
      }
      if (millis() - uart_millis > 10) {
      uart_millis = millis();
      Serial.println(uart_command); //вывод значений, которые приходят по UART
      }
    }

    // for (uint64_t i = 0; i < uart_command.length();)
    // {

    //   if (memcmp(&uart_command[i], "OFF", 3) == 0)
    //   {
    //     i += 3;
    //     digitalWrite(LED_PIN, HIGH);
    //   }
    // }
  }
}