// These examples are from the Electronics Cookbook by Simon Monk
//https://github.com/LSatan/SmartRC-CC1101-Driver-Lib
// mod by Little_S@tan
#include <cc1101_driver.h>

int gdo0;

byte transmitt_byte[11] = {72,101,108,108,111,32,87,111,114,108,100};
char *transmitt_char = "Hello World";

void setup() {

#ifdef ESP32
gdo0 = 2;  // for esp32! GDO0 on GPIO pin 2.
#elif ESP8266
gdo0 = 5;  // for esp8266! GDO0 on pin 5 = D1.
#else
gdo0 = 6;  // for Arduino! GDO0 on pin 6.
#endif 

    Serial.begin(9600);
    if (cc1101_driver.getCC1101()){         // Check the CC1101 Spi connection.
    Serial.println("Connection OK");
    }else{
    Serial.println("Connection Error");
    }
  
    cc1101_driver.Init();               // must be set to initialize the cc1101!
    cc1101_driver.setGDO0(gdo0);         // set lib internal gdo pin (gdo0). Gdo2 not use for this example.
    cc1101_driver.setCCMode(1);       // set config for internal transmission mode.
    cc1101_driver.setModulation(0);  // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    cc1101_driver.setMHZ(433.92);   // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
    cc1101_driver.setSyncMode(2);  // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
 // cc1101_driver.setPA(10);      // set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
    cc1101_driver.setCrc(1);     // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
    Serial.println("Tx Mode");
}

void loop() {

//3 different methods to send data

//Transmitt "Hello World" from byte format.
cc1101_driver.SendData(transmitt_byte, 11);
delay(2000);

//Transmitt "Hello World" from char format.
cc1101_driver.SendData(transmitt_char);
delay(2000);

//Transmitt "Hello World" from char format directly.
cc1101_driver.SendData("Hello World");
delay(2000);
}
