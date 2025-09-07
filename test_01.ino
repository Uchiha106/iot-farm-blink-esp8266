
//.......................................................................
#define BLYNK_TEMPLATE_ID "TMPL6tpxd59M1"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "xbTz7JtNfVMOmFXPadzCM4STXQMMdj54"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
char ssid[] = "P1";
char pass[] = "11012002";

#define DHTPIN D5
const int sensor_pin = A0;

#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
BLYNK_WRITE(V0) {  // D3
  int switchValue1 = param.asInt();
  if (switchValue1 == 1) {
    digitalWrite(0, HIGH);  // Bật LED khi Switch bật
  } else {
    digitalWrite(0, LOW);  // Tắt LED khi Switch tắt
  }
}

BLYNK_WRITE(V4) {  // D4
  int switchValue2 = param.asInt();
  if (switchValue2 == 1) {
    digitalWrite(2, HIGH);  // Bật LED khi Switch bật
  } else {
    digitalWrite(2, LOW);  // Tắt LED khi Switch tắt
  }
}
void sendSensor()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int mois;

  mois = ( 100.00 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );
    //dht11

  lcd.setCursor(4, 0);
  lcd.print(t);

  lcd.setCursor(13, 0);
  lcd.print(h);

  //soil moisture

  lcd.setCursor(7, 1);
  lcd.print(mois);
  Serial.println(mois);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, mois);
  if ((h < 75) || (t > 30)) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
  if (mois < 65) {
    digitalWrite(15, HIGH);
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(15, LOW);
    digitalWrite(12, LOW);
  }

}

void setup()
{

  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(12, OUTPUT); // lED D6 on/off may bom
  pinMode(13, OUTPUT); // lED D7 canh bao nhiet do, do am khong khi
  pinMode(15, OUTPUT); // lED D8 canh bao do am dat
  pinMode(0, OUTPUT); // lED D3
  pinMode(2, OUTPUT); // lED D4
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  lcd.setCursor(0, 0);
  lcd.print("Temp=");
  lcd.setCursor(6, 0);
  lcd.print("C__Hum=");
  lcd.setCursor(6, 0);
  lcd.print("C__Hum=");
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Soil = ");
  lcd.setCursor(10, 1);
  lcd.print("%");
}

void loop()
{/*
  int h1 = dht.readHumidity();
  int t1 = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  int mois1;

  mois1 = ( 100.00 - ( (analogRead(sensor_pin) / 1023.00) * 100.00 ) );

*/
  Blynk.run();
  timer.run();

}
