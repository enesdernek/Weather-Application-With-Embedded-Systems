#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <LoRa.h>

// WiFi bilgileri
const char* ssid = "";
const char* password = "";

// Spring Boot endpointleri
const char* sensorHistoryUrl = "http://192.168.1.105:8080/sensor-history";
const char* fireAlertUrl     = "http://192.168.1.105:8080/fire-alert";

// LoRa pinleri
#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26
SPIClass SPI_LoRa(VSPI);

// Buzzer pini
#define BUZZER_PIN 4

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi bağlandı!");

  SPI_LoRa.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setSPI(SPI_LoRa);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa başlatılamadı!");
    while (1);
  }

  Serial.println("LoRa alıcı hazır.");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String rawData = "";
    while (LoRa.available()) {
      rawData += (char)LoRa.read();
    }

    rawData.trim();
    Serial.println("LoRa'dan gelen veri:");
    Serial.println(rawData);

    // Değer değişkenleri
    float temperature = 0.0;
    float humidity = 0.0;
    int rain = 0;
    float soil = 0.0;
    String pumpStatus = "Bilinmiyor";
    String fireStatus = "YOK";  // default

    // Anahtar kelime index'leri
    int tIndex = rawData.indexOf("Sicaklik:");
    int hIndex = rawData.indexOf("Nem:");
    int rIndex = rawData.indexOf("YagmurDegeri:");
    int sIndex = rawData.indexOf("ToprakNem:");
    int fIndex = rawData.indexOf("Yangin:");
    int pIndex = rawData.indexOf("Pompa");

    // Verileri ayrıştır
    if (tIndex >= 0)
      temperature = rawData.substring(tIndex + 9, rawData.indexOf("C", tIndex)).toFloat();

    if (hIndex >= 0)
      humidity = rawData.substring(hIndex + 4, rawData.indexOf("%", hIndex)).toFloat();

    if (rIndex >= 0)
      rain = rawData.substring(rIndex + 13, rawData.indexOf(",", rIndex)).indexOf("VAR") != -1 ? 1 : 0;

    if (sIndex >= 0)
      soil = rawData.substring(sIndex + 11, rawData.indexOf("%", sIndex)).toFloat();

    if (fIndex >= 0) {
      int parenStart = rawData.indexOf("(", fIndex);
      fireStatus = rawData.substring(fIndex + 7, parenStart);
      fireStatus.trim();
    }

    if (pIndex >= 0) {
      pumpStatus = rawData.substring(pIndex);
      pumpStatus.trim();
    }

    // SensorHistory JSON
    String json = "{";
    json += "\"soilHumidity\":" + String(soil, 2) + ",";
    json += "\"temperature\":" + String(temperature, 2) + ",";
    json += "\"rainSensorValue\":" + String(rain) + ",";
    json += "\"waterPumpStatus\":\"" + pumpStatus + "\"";
    json += "}";

    Serial.println("Gönderilecek SensorHistory JSON:");
    Serial.println(json);

    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(sensorHistoryUrl);
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(json);
      Serial.print("SensorHistory HTTP yanıt kodu: ");
      Serial.println(httpResponseCode);
      http.end();
    }

    // FireAlert JSON
    if (fireStatus == "VAR" || fireStatus == "YOK") {
      bool fireBool = (fireStatus == "VAR");

      // 🔔 Yangın varsa buzzer'ı çalıştır
      if (fireBool) {
        tone(BUZZER_PIN, 2000); // 2 kHz alarm sesi
      } else {
        noTone(BUZZER_PIN);     // Buzzer kapat
      }

      String fireJson = "{";
      fireJson += "\"fireStatus\":" + String(fireBool ? "true" : "false");
      fireJson += "}";

      Serial.println("Gönderilecek FireAlert JSON:");
      Serial.println(fireJson);

      if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(fireAlertUrl);
        http.addHeader("Content-Type", "application/json");
        int httpResponseCode = http.POST(fireJson);
        Serial.print("FireAlert HTTP yanıt kodu: ");
        Serial.println(httpResponseCode);
        http.end();
      }
    }

    delay(3000); // Çok sık istek atmayı engelle
  }
}
