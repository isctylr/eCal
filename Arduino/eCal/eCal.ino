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
const int MAX_RETRIES = 3;         // Maximum fetch attempts before sleeping
const int HTTP_TIMEOUT_MS = 25000; // 25s timeout to handle Google Apps Script cold starts

/// -- globals -- ///
// Wifi 
int wifiStatus = WL_IDLE_STATUS;
WiFiSSLClient wifiClient;
HttpClient httpClient = HttpClient(wifiClient, server, 443);
// Keep track of successful data pull/draw. Otherwise, continue trying instead of sleeping
bool didGetData = false;
// Keep the most recent json string & only update screen if changes
String jsonData = "";

void setup()
{
  /// Inits are executed in the loop since the device wakes up from long deep sleeps
}

void loop() {
#ifdef _DEBUG_
  Serial.begin(115200);
  while(!Serial) ;
  Serial.println(F("Begin loop"));
#endif

  // Reset the data check
  didGetData = false;
  int retries = 0;
  String lastError = "";

  // Start display
  initScreen();

  // Attempt up to MAX_RETRIES to fetch data
  while (!didGetData && retries < MAX_RETRIES) {
    retries++;
#ifdef _DEBUG_
    Serial.print(F("Fetch attempt "));
    Serial.print(retries);
    Serial.print(F(" of "));
    Serial.println(MAX_RETRIES);
#endif
    initWifi();
    lastError = httpRequest();
    if (!didGetData && retries < MAX_RETRIES) {
      delay(5000); // Back off before retrying
    }
  }

  // If all retries failed, draw error to screen so it's clearly visible
  if (!didGetData && lastError.length() > 0) {
    drawScreen(lastError, true);
  }

  // Shut off screen and wifi then sleep 
  disconnectPeripherals();
  LowPower.deepSleep(1000UL * DELAY_SECS);
}

void drawScreen(String &newData, bool isError) {
  // If there was an error that wasn't caught and no data, treat as error anyway
  if (newData.length() == 0) {
    isError = true;
    newData = "Error in drawScreen: No data provided.";
  }

  // If there's no error so far, parse the data
  DynamicJsonDocument parsedData(2560);
  if (!isError) {
    DeserializationError parseError = deserializeJson(parsedData, newData);

#ifdef _DEBUG_
    Serial.print(F("Drawing pages. Pagecount: "));
    Serial.println(display.pages());
#endif

    // Catch parsing errors
    if (parseError) {
      isError = true;
      newData = "JSON Parse Error: " + String(parseError.c_str());
    } else if (parsedData.containsKey("error")) {
      isError = true;
      newData = "Calendar Error: " + parsedData["error"].as<String>();
    } else {
      // No initial error and no parsing error, data is good.
      didGetData = true;
    }
  }

  // Compare new data to old data (incl. errors). Don't bother redrawing if it's identical.
  if (newData == jsonData) {
    return;
  }
  // If it's different, update cache
  jsonData = newData;

  // Start drawing
  display.firstPage();

  if (isError) {
    // Draw readable error screen
    do {
      drawErrorScreen(newData);
    } while (display.nextPage());

#ifdef _DEBUG_
    Serial.print(F("Received and drew error - "));
    Serial.println(newData); 
#endif

  } else {
    // No errors. Draw screen with calendar data.
    do {
      // Draw all the big numbers and titles
      String dateStr = parsedData["date"].as<String>();
      drawTitles(dateStr);

      // Start drawing the events
      display.setFont(&FreeSans12pt7b);
      
      int x = TODAY_X;
      int y = FIRST_LINE_Y; 

      // TODAY events - array of titles
      JsonArray todayEvents = parsedData["today"];
      for (size_t i = 0; i < todayEvents.size(); i++) {
        drawEventTitle(todayEvents[i].as<String>(), x, y);
      }

      if (parsedData.containsKey("today_left")) {
        display.setCursor(x, y);
        display.setFont(&Roboto_Bold_20);
        display.print(parsedData["today_left"].as<String>());
        display.print(" more...");
      }

      x = LATER_X;
      y = FIRST_LINE_Y; 

      bool left = false;

      // LATER THIS WEEK events
      JsonObject laterDates = parsedData["later"];

      for (JsonPair kv : laterDates) {
        String key = String(kv.key().c_str());
        JsonArray value = kv.value();

#ifdef _DEBUG_
        Serial.print(F("Later Key:"));
        Serial.println(key); 
        Serial.print(F("Events in date(s):"));
        Serial.println(value.size());
#endif

        if (key == "left") {
          left = true;
          continue;
        }

        drawDate(key, x, y);

        for (size_t j = 0; j < value.size(); j++) {
          dateStr = value[j].as<String>();
          drawEventTitle(dateStr, x, y);
        }
      }

      if (left) {
        display.setCursor(x, y);
        display.setFont(&Roboto_Bold_20);
        display.print(parsedData["later"]["left"].as<String>());
        display.print(" more...");
      }

      x = NEXT_X;
      y = FIRST_LINE_Y;
      left = false;

      // NEXT WEEK events
      JsonObject nextDates = parsedData["next"];

      for (JsonPair kv : nextDates) {
        String key = String(kv.key().c_str());
        JsonArray value = kv.value();

#ifdef _DEBUG_
        Serial.print(F("Next Key:"));
        Serial.println(key); 
        Serial.print(F("Events in date(s):"));
        Serial.println(value.size());
#endif

        if (key == "left") {
          left = true;
          continue;
        }

        drawDate(key, x, y);

        for (size_t j = 0; j < value.size(); j++) {
          dateStr = value[j].as<String>();
          drawEventTitle(dateStr, x, y);
        }
      }

      if (left) {
        display.setCursor(x, y);
        display.setFont(&Roboto_Bold_20);
        display.print(parsedData["next"]["left"].as<String>());
        display.print(" more...");
      }
    }
    while (display.nextPage());
  }
#ifdef _DEBUG_
  Serial.println(F("Finished drawing screen"));
#endif
}

void drawScreen(String &newData) {
  drawScreen(newData, false);
}

void drawErrorScreen(const String &errorMsg) {
  display.setTextColor(GxEPD_BLACK);

  // Header banner (y = 60 baseline ensures no glyph tops are clipped)
  display.setFont(&Open_Sans_Regular_29);
  display.setCursor(20, 60);
  display.print("eCal - Sync Error");
  display.drawFastHLine(20, 75, 760, GxEPD_BLACK);

  // Error details using FreeSans12pt7b with word-wrapping
  display.setFont(&FreeSans12pt7b);
  int currentY = 125;
  const int lineSpacing = 30;
  const int maxCharsPerLine = 48;

  String remaining = errorMsg;
  while (remaining.length() > 0 && currentY < 420) {
    String line = "";
    if (remaining.length() <= maxCharsPerLine) {
      line = remaining;
      remaining = "";
    } else {
      int splitAt = remaining.lastIndexOf(' ', maxCharsPerLine);
      if (splitAt <= 0) {
        splitAt = maxCharsPerLine;
      }
      line = remaining.substring(0, splitAt);
      remaining = remaining.substring(splitAt);
      remaining.trim();
    }
    display.setCursor(20, currentY);
    display.print(line);
    currentY += lineSpacing;
  }

  // Footer notice
  display.setFont(&Roboto_Bold_20);
  display.setCursor(20, 445);
  display.print("Will automatically retry at next hourly refresh.");
}

void initScreen() {
#ifdef _DEBUG_
  Serial.println(F("initScreen"));
  display.init(115200, true, 2, false); // Serial enabled
#else
  display.init(0, true, 2, false);
#endif

  // Default settings for all drawing
  display.setRotation(0);
  display.setTextColor(GxEPD_BLACK);
  display.setFullWindow();
}

void drawTitles(const String &dateStr) {
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
  String day = dateStr.length() >= 3 ? dateStr.substring(0,3) : "";
  display.print(translateDays(day));

  // Column titles
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

void drawDate(const String &dateStr, int &x, int &y) {
  display.setCursor(x, y);
  display.setFont(&Roboto_Bold_20);

  if (dateStr.length() > 6) {
    // Multiday
    display.print(dateStr);
  } else if (dateStr.length() >= 3) {
    // Single day so expand the day name
    display.print(dateStr.substring(0, 2) + " ");
    String day = dateStr.substring(3);
    display.print(translateDays(day));
  } else {
    display.print(dateStr);
  }

  y += LINE_HEIGHT;
}

void drawEventTitle(String eventTitle, int& x, int& y) {
  display.setCursor(x, y);
  display.setFont(&FreeSans12pt7b);

#ifdef _DEBUG_
  Serial.print(F("Event title:"));
  Serial.println(eventTitle);
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
    String e = "Communication with WiFi module failed! Check hardware wiring.";
    drawScreen(e, true);
    return;
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
#ifdef _DEBUG_
    Serial.println(F("Please upgrade the WiFi firmware"));
#endif
  }

  // Attempt to connect to Wifi network with max 3 attempts
  int attempts = 0;
  while (wifiStatus != WL_CONNECTED && attempts < 3) {
    attempts++;
#ifdef _DEBUG_
    Serial.print(F("Attempting to connect to SSID: "));
    Serial.println(ssid);
#endif

    wifiStatus = WiFi.begin(ssid, pass);
    if (wifiStatus != WL_CONNECTED) {
      delay(3000);
    }
  }

  // Allow NTP and background network stack to settle before TLS connection
  if (wifiStatus == WL_CONNECTED) {
    delay(1500);
  }
}

void disconnectPeripherals() {
  httpClient.stop();
  wifiClient.stop();
  display.hibernate();
  wifiStatus = WiFi.disconnect();
  WiFi.end();
#ifdef _DEBUG_
  Serial.end();
#endif
}

// Makes an HTTPS connection to the server, following redirects cleanly
String httpRequest() {
  if (wifiStatus != WL_CONNECTED) {
#ifdef _DEBUG_
    Serial.println(F("Wifi connection failed"));
#endif
    return "WiFi connection failed. Unable to connect to SSID: " + String(ssid);
  }

  // Ensure any previous sockets are fully stopped
  httpClient.stop();
  wifiClient.stop();

  String currentServer = server;
  String currentPath = initialUrl;
  int statusCode = 0;
  String response = "";
  int redirectCount = 0;
  const int MAX_REDIRECTS = 3;

  while (redirectCount <= MAX_REDIRECTS) {
    httpClient = HttpClient(wifiClient, currentServer, 443);
    httpClient.setHttpResponseTimeout(HTTP_TIMEOUT_MS);

#ifdef _DEBUG_
    Serial.print(F("GET: https://"));
    Serial.print(currentServer);
    Serial.println(currentPath);
#endif

    int err = httpClient.get(currentPath);
    if (err != 0) {
      httpClient.stop();
      wifiClient.stop();
      return "HTTP GET request failed. Error code: " + String(err);
    }

    statusCode = httpClient.responseStatusCode();
#ifdef _DEBUG_
    Serial.print(F("Status code: "));
    Serial.println(statusCode);
#endif

    // Handle HTTP redirects (302 Found, 303 See Other)
    if (statusCode == 302 || statusCode == 303) {
      String location = "";
      while (httpClient.headerAvailable()) {
        String headerName = httpClient.readHeaderName();
        String headerValue = httpClient.readHeaderValue();
        if (headerName.equalsIgnoreCase("Location")) {
          location = headerValue;
        }
      }

      // Drain unread response body
      while (httpClient.available()) {
        httpClient.read();
      }

      // Cleanly terminate connection to old server
      httpClient.stop();
      wifiClient.stop();

      if (location.length() == 0) {
        return "Redirect received without Location header.";
      }

      // Parse Location URL: "https://<server><path>" or "/<path>"
      if (location.startsWith("https://")) {
        int slashIndex = location.indexOf('/', 8);
        if (slashIndex > 0) {
          currentServer = location.substring(8, slashIndex);
          currentPath = location.substring(slashIndex);
        } else {
          currentServer = location.substring(8);
          currentPath = "/";
        }
      } else if (location.startsWith("/")) {
        currentPath = location;
      }

      redirectCount++;
      continue;
    }

    break;
  }

  if (statusCode == 200) {
    response = httpClient.responseBody();
    httpClient.stop();
    wifiClient.stop();

    if (response.length() == 0) {
      return "Empty response from calendar server.";
    }

    drawScreen(response);
    return "";
  } else {
    httpClient.stop();
    wifiClient.stop();
    return "Failed to get calendar. Response code: " + String(statusCode);
  }
}

String translateMonths(const String &dateStr) {
  if (dateStr.length() < 7) {
    return "";
  }
  String month = dateStr.substring(4,7);

  if (month == "Jan") return "January";
  if (month == "Feb") return "February";
  if (month == "Mar") return "March";
  if (month == "Apr") return "April";
  if (month == "May") return "May";
  if (month == "Jun") return "June";
  if (month == "Jul") return "July";
  if (month == "Aug") return "August";
  if (month == "Sep") return "September";
  if (month == "Oct") return "October";
  if (month == "Nov") return "November";
  if (month == "Dec") return "December";
  return month; // Prevent undefined behavior if month is unrecognized
}

String translateDays(const String &dateStr) {
  if (dateStr.length() < 3) {
    return "";
  }
  String day = dateStr.substring(0, 3);
  if (day == "Mon") return "Monday";
  if (day == "Tue") return "Tuesday";
  if (day == "Wed") return "Wednesday";
  if (day == "Thu") return "Thursday";
  if (day == "Fri") return "Friday";
  if (day == "Sat") return "Saturday";
  if (day == "Sun") return "Sunday";
  return dateStr; // Prevent undefined behavior if day is unrecognized
}

String getDate(const String &dateStr) {
  if (dateStr.length() >= 10) {
    return dateStr.substring(8, 10);
  }
  return "01";
}
