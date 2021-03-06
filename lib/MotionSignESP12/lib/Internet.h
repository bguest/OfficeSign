#ifndef INTERNET_H
#define INTERNET_H

#include "Data.h"
#include <ESP8266WiFi.h>
#include <WifiClientSecure.h>

typedef const enum _REQUESTS {
  GET_RESERVED = 0,
  GET_DISPLAY,
  REQUEST_COUNT
} REQUESTS;

class Internet {
  public:
    void init();
    void run(Data &data);

  private:
    uint8_t currRequest;
    void getReserved(Data &data, WiFiClient &client);
    void getDisplay(Data &data, WiFiClient &client);
    void waitForData(WiFiClient &client);
    unsigned long lastRun;
};
#endif
