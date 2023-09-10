// #define _DEBUG_ 1 // Uncomment to get serial logs

/** * * * * * * * * * * * * * * * * * * * * * * * * * * *. * * * * * * * 
* eCal
* --- 
* @author isctylr
*
* A low-power digital Google calendar display using 
* Arduino SAMD21 wifiNina (Nano 33 IoT) + WaveShare ePaper display
* Requires an AppsScript with permission to read a Google Cal's events
* which are made externally available as in a json format.
* 
* Json formatting:
* {
*   "date": Date string format: DDD MMM dd
*   "today": Array of strings - today's event names (up to 13 lines)
*   "later": { 
*      [date string as key]: event names on date as string array of current week
*   }
*   "next": { 
*      [date string as key]: event names on date as string array of next week
*   }
* }
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Sleeping
#include <ArduinoLowPower.h> 

// Display
#include <SPI.h>
#include <GxEPD2_BW.h>
#include "GxEPD2_display_selection.h"

// Fonts (Must be included after display library)
#include <Fonts/FreeSans12pt7b.h>
// Custom fonts from https://oleddisplay.squix.ch/
#include <OpenSansBold90Nums.h>
#include <OpenSansRegular29Min.h>
#include <Roboto39.h>
#include <RobotoBold20.h>

// Getting calendar events
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "wifi_secret.h"

// --- CONSTANTS --- //
// time to sleep before reloading in seconds
const int DELAY_SECS = 60 * 60; // 1 hour
const int TODAY_X = 5;
const int LATER_X = 272;
const int NEXT_X = 539;
const int FIRST_LINE_Y = 170;
const int LINE_HEIGHT = 25;

/// -- globals -- ///
// Wifi 
int wifiStatus = WL_IDLE_STATUS;
WiFiSSLClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, server, 443);
// To check if success or failure
bool didGetData = false;
// If it failed, don't continue redrawing the screen
bool didDrawFail = false;

void setup()
{
  /// Moving all the inits to the loop, since the loop will be waking up from long sleeps
  // // Start display
  // initScreen();
  // // Initialize wifi
  // initWifi();
}

void loop() {
#ifdef _DEBUG_
  Serial.begin(115200);
  Serial.println(F("Begin loop"));
#endif
  // Reset the data check
  didGetData = false;
  // Start display
  initScreen();
  // Initialize wifi
  initWifi();
  // Get the data (which then calls drawScreen as well)
  // will set didGetData true if it worked, otherwise repeats.
  while (!didGetData) {
    httpRequest();
    delay(10000);
  }

  // Shut off screen and wifi then sleep 
  disconnectPeripherals();
  LowPower.deepSleep(1000 * DELAY_SECS);
};

void drawScreen(String &jsonData) {
  DynamicJsonDocument parsedData(1100);
  DeserializationError parseError = deserializeJson(parsedData, jsonData);

#ifdef _DEBUG_
  Serial.print(F("Drawing pages. Pagecount: "));
  Serial.println(display.pages());
#endif

  display.firstPage();
  do
  {
    if (jsonData.length() > 0 && !parseError) {
      // Successfully got something
      didGetData = true;
      didDrawFail = false;
      
      // Draw all the big numbers and titles
      String dateStr = parsedData["date"].as<String>();
      drawTitles(dateStr);

      // Start drawing the events
      display.setFont(&FreeSans12pt7b);
      
      int x = TODAY_X;
      int y = FIRST_LINE_Y; 

      // TODAY events - just an array of titles
      JsonArray todayEvents = parsedData["today"];
      for (int i = 0; i < todayEvents.size(); i++) {
        drawEventTitle(todayEvents[i].as<String>(), x, y);
      }

      x = LATER_X;
      y = FIRST_LINE_Y; 

      bool left = false; // If there are unlisted events

      // LATER THIS WEEK events - object of dates with arrays of titles
      JsonObject laterDates = parsedData["later"];

      for (JsonPair kv : laterDates) {

        String key = String(kv.key().c_str());
        JsonArray value = kv.value();

#ifdef _DEBUG_
  Serial.print(F("Later Key:"));
  Serial.println(key); 
  Serial.print(F("Events in date(s):"));
  Serial.println(value.size());
  Serial.print(F("Events in Later:"));
  Serial.println(laterDates.size());
#endif

        // print date laterDates[i]
        if (key == "left") {
          left = true;
          continue;
        }

        drawDate(key, x, y);

        for (int j = 0; j < value.size(); j++) {
          // print title dateEvents[j]
          dateStr = value[j].as<String>();
          drawEventTitle(dateStr, x, y);
        }
      }

      if (left) {
        // print parsedData["later"]["left"]
        display.setCursor(x, y);
        display.setFont(&Roboto_Bold_20);
        // display.print("            ");
        display.print((const char*) parsedData["later"]["left"]);
        display.print(" more...");
      }

      x = NEXT_X;
      y = FIRST_LINE_Y;
      left = false;

      // NEXT WEEK events - object of dates with arrays of titles 
      JsonObject nextDates = parsedData["next"];

      for (JsonPair kv : nextDates) {
        String key = String(kv.key().c_str());
        JsonArray value = kv.value();

#ifdef _DEBUG_
  Serial.print(F("Later Key:"));
  Serial.println(key); 
  Serial.print(F("Events in date(s):"));
  Serial.println(value.size());
  Serial.print(F("Events in Later:"));
  Serial.println(laterDates.size());
#endif

        if (key == "left") {
          left = true;
          continue;
        }

        // print date nextDates[i]
        drawDate(key, x, y);

        for (int j = 0; j < value.size(); j++) {
          // print title dateEvents[j]
          dateStr = value[j].as<String>();
          drawEventTitle(dateStr, x, y);
        }
      }

      if (left) {
        // print parsedData["next"]["left"]
        display.setCursor(x, y);
        display.setFont(&Roboto_Bold_20);
        // display.print("            ");
        display.print((const char*) parsedData["next"]["left"]);
        display.print(" more...");
      }
    } else if (!didDrawFail) {
#ifdef _DEBUG_
      Serial.println(F("Failed somewhere."));
#endif
      if (WiFi.status() == WL_NO_MODULE) {
        display.setFont(&Open_Sans_Regular_29);
        display.setCursor(20, 20);
        display.print("Unable to communicate with WiFi Module");
      } else {
        display.setFont(&Open_Sans_Regular_29);
        display.setCursor(20, 20);
        display.print("No data received");
      }
      didDrawFail = true;
    }
  }
  while (display.nextPage());

#ifdef _DEBUG_
  Serial.println(F("Finished drawing screen"));
#endif
}

void initScreen() {
#ifdef _DEBUG_
  Serial.println(F("initScreen"));
  display.init(115200, true, 2, false); // // Serial enabled
#else
  display.init(0, true, 2, false);
#endif

  // Default settings for all drawing
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
}

void drawTitles(String &dateStr) {

  display.setFont(&Open_Sans_Bold_90_Nums);
  String dateNums = getDate(dateStr);
  display.setCursor(0, 70);
  display.print(dateNums.substring(0,1));
  display.setCursor(50, 70);
  display.print(dateNums.substring(1));

  // Big month name
  display.setFont(&Roboto_39);
  display.setCursor(108, 34);
  display.print(translateMonths(dateStr));

  // Big day name
  display.setCursor(108, 67);
  String day = dateStr.substring(0,3);
  display.print(translateDays(day));

  // Titles
  display.setFont(&Open_Sans_Regular_29);
  display.setCursor(TODAY_X, 120);
  display.print("Today");
  display.drawRect(10, 133, 50, 2, GxEPD_BLACK);

  display.setCursor(LATER_X, 120);
  display.print("Later This Week");
  display.drawRect(277, 133, 50, 2, GxEPD_BLACK);

  display.setCursor(NEXT_X, 120);
  display.print("Next Week");
  display.drawRect(544, 133, 50, 2, GxEPD_BLACK);
  
}

void drawDate(String &dateStr, int &x, int &y) {
  display.setCursor(x, y);
  display.setFont(&Roboto_Bold_20);

  if (dateStr.length() > 6) {
    // Multiday
    display.print(dateStr);
  } else {
    // Single day so expand the day name
    display.print(dateStr.substring(0, 2) + " ");
    String day = dateStr.substring(3);
    display.print(translateDays(day));
  }

  y += LINE_HEIGHT;
}

void drawEventTitle(String eventTitle, int& x, int& y) {
  display.setCursor(x, y);
  display.setFont(&FreeSans12pt7b);

  // Determine if the title is too long, then cut and add "..."
  // String title = String((const char*) eventTitle);

#ifdef _DEBUG_
  Serial.print(F("Event title:"));
  Serial.println(F(eventTitle.c_str()));
#endif

  String title2 = "";
  if (eventTitle.length() > 20) {
    title2 = "      " + eventTitle.substring(20, 31);
    if (eventTitle.length() > 31) {
      title2 += "...";
    }
    eventTitle = eventTitle.substring(0, 20);
  }

  display.print(eventTitle);

  if (title2 != "") {
    y += LINE_HEIGHT;
    display.setCursor(x, y);
    display.print(title2);
  }

  y += LINE_HEIGHT;
}

void initWifi() {
#ifdef _DEBUG_
  Serial.println(F("initWifi"));
#endif
    
  if (WiFi.status() == WL_NO_MODULE) {
#ifdef _DEBUG_
    Serial.println(F("Communication with WiFi module failed!"));
#endif
    
    String e = "";
    drawScreen(e);
  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
#ifdef _DEBUG_
    Serial.println(F("Please upgrade the firmware"));
#endif
  }

  // attempt to connect to Wifi network:
  while (wifiStatus != WL_CONNECTED) {

#ifdef _DEBUG_
    Serial.print(F("Attempting to connect to SSID: "));
    Serial.println(F(ssid));
#endif

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    wifiStatus = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);

    // Serial.println(F(wifiStatus));
  }
}

void disconnectPeripherals() {
  // Serial.println(F("disconnectPeriphs"));
  // display.end();
  display.hibernate();
  wifiStatus = WiFi.disconnect();
  WiFi.end();
#ifdef _DEBUG_
  Serial.end();
#endif
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // Serial.println(F("httpRequest"));

  // // if there's a successful connection:
  if (wifiStatus == WL_CONNECTED) {

    httpClient = HttpClient(wifiClient, server, 443);
    // Serial.println(F("making GET request"));
    httpClient.get(initialUrl);

    // read the status code and body of the response
    int statusCode = httpClient.responseStatusCode();
    // Serial.print("Status code: ");
    // Serial.println(F(statusCode));
    
    while (statusCode == 302 || statusCode == 303) {
      String location;
      // Serial.println(F("Redirecting:"));
      
      while (httpClient.headerAvailable()) {
        if (httpClient.readHeaderName() == "Location") {
          location = httpClient.readHeaderValue();
          break;
        }
      }
      if (location.length()) {
        uint16_t path_begin = location.substring(8).indexOf('/');
        String newServer = location.substring(8, path_begin + 8);
        String newPath = location.substring(path_begin + 8);
        // Serial.println(F(newServer + newPath));
        httpClient = HttpClient(wifiClient, newServer, 443);
        httpClient.get(newPath);
        statusCode = httpClient.responseStatusCode();
        // Serial.print("Status code after redirect is: ");
        // Serial.println(F(statusCode));
      }
    }

    if (statusCode == 200) {
      String response = httpClient.responseBody();

// #ifdef _DEBUG_
//       Serial.println(F("Finished getting connected. Response:"));
//       Serial.println(response);
// #endif

      // drawScreen(httpClient.responseBody());
      drawScreen(response);
    } else {
      String e = "";
      drawScreen(e);
    }

    // note the time that the connection was made:
    // lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
#ifdef _DEBUG_
    Serial.println(F("Wifi connection failed"));
#endif
    String e = "";
    drawScreen(e);
  }
}

// String translateMonths(const JSONVar& dateStr) {
String translateMonths(String &dateStr) {
  String month = dateStr.substring(4,7);

  if (month == "Jan")
    return "January";
  if (month == "Feb")
    return "February";
  if (month == "Mar")
    return "March";
  if (month == "Apr")
    return "April";
  if (month == "May")
    return "May";
  if (month == "Jun")
    return "June";
  if (month == "Jul")
    return "July";
  if (month == "Aug")
    return "August";
  if (month == "Sep")
    return "September";
  if (month == "Oct")
    return "October";
  if (month == "Nov")
    return "November";
  if (month == "Dec")
    return "December";
}

String translateDays(String& dateStr) {

  if (dateStr == "Mon")
      return "Monday";
  if (dateStr == "Tue")
    return "Tuesday";
  if (dateStr == "Wed")
    return "Wednesday";
  if (dateStr == "Thu")
    return "Thursday";
  if (dateStr == "Fri")
    return "Friday";
  if (dateStr == "Sat")
    return "Saturday";
  if (dateStr == "Sun")
    return "Sunday";
}

String getDate(String &dateStr) {
  return dateStr.substring(8,10);
}