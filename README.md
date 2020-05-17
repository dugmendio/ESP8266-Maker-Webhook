# ESP8266-Maker-Webhook
Calls a webhook from ESP8266 over Arduino Uno software serial.

## Setup: 
- Add network to the configuration strings. 
- Add host and command (trigger) as necessary. I can confirm this works with IFTTT webhooks. 
- Baud rate may need to be adjusted based on firware of your ESP module. Typically this will be 115200 or 9600. 
- Ensure ESP-01 module is connected: TX to pin 7, RX to pin 6, VCC & CH_PDD to 3.3V, GND to GND.

## General notes: 
- I strongly suggest connecting to wifi first, and then running this code (comment or remove the connection string). It seems to have a much more stable connection. To do so, connect TX to pin 1, and RX to pin 0. Run a blank sketch, and use the AT command AT+CWJAP="SSID","KEY". In doing this, your ESP module should retain connection and immediately attach to the network. 
- I'm not by any means an expert in ESP8266 modules. This is a patch work of some existing code, I am just trying to make it more accessible. I'd recommend reading https://arduino-esp8266.readthedocs.io/en/2.7.1/ for some more experienced details on what you can do. 
