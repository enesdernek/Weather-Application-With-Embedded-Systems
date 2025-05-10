#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// BME280 adres
#define BME280_ADDRESS 0x76
Adafruit_BME280 bme;

// LoRa pinleri
#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 26
SPIClass SPI_LoRa(VSPI);

// Sensör pinleri
#define RAIN_SENSOR_PIN 12      // Dijital
#define SOIL_SENSOR_PIN 32       // Analog
#define FIRE_SENSOR_PIN 33      // Analog

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22);
  if (!bme.begin(BME280_ADDRESS)) {
    Serial.println("BME280 bulunamadı!");
    while (true);
  }

  SPI_LoRa.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);
  LoRa.setSPI(SPI_LoRa);
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa başlatılamadı!");
    while (true);
  }

  pinMode(RAIN_SENSOR_PIN, INPUT);
  Serial.println("LoRa verici hazır.");
}

void loop() {
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0F;

  int rainDigitalValue = digitalRead(RAIN_SENSOR_PIN);
  String rainStatus = (rainDigitalValue == 0) ? "VAR" : "YOK";

  int soilValue = analogRead(SOIL_SENSOR_PIN);
  int soilPercent = map(soilValue, 2500, 1100, 0, 100);
  Serial.print("SOIL VALUE: ");
Serial.println(soilValue);

  soilPercent = constrain(soilPercent, 0, 100);

  int fireAnalogValue = analogRead(FIRE_SENSOR_PIN);
  bool fireDetected = fireAnalogValue < 250;
  String fireStatus = fireDetected ? "VAR" : "YOK";

  String pumpStatus = soilPercent < 30 ? "Pompa Çalışıyor." : "Pompa Çalışmıyor.";

  String mesaj = "Sicaklik:" + String(temp, 2) + "C, " +
                 "Nem:" + String(hum, 2) + "%, " +
                 "Basinc:" + String(pres, 2) + "hPa, " +
                 "YagmurDegeri:" + rainStatus + ", " +
                 "ToprakNem:" + String(soilPercent) + "%, " +
                 "Yangin:" + fireStatus + " (" + fireAnalogValue + "), " +
                 pumpStatus;

  LoRa.beginPacket();
  LoRa.print(mesaj);
  LoRa.endPacket();

  Serial.println("Gönderildi: " + mesaj);
  delay(5000);
}
