#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h>

const char *ssid = "";
const char *password = "";

ESP8266WebServer server(80);

unsigned long ota_progress_millis = 0;

void setup(void)
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Головна сторінка
  server.on("/", HTTP_GET, []()
            { server.send(200, "text/html", "<h1>ESP8266 Home Dashboard</h1><p><a href='/update'>Go to OTA Update</a></p>"); });

  // Ініціалізація ElegantOTA (автоматично створює маршрут /update)
  ElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
  ElegantOTA.loop();
}