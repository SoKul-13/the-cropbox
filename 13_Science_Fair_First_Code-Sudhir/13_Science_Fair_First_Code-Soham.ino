#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

//int pump = 11;
int sensor = 8;//Moisture Sensor
int relay = 12  ;
int val;

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


void setup(){
  //pinMode(pump, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
  Serial.println(F(" Test Run!"));

  dht.begin();
}
void loop() {
  
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  val = digitalRead(sensor);
    Serial.println("Vslue is ");
    Serial.println(val);


  if (val == LOW) {
    //HIGH Moisture in the soil, hence the resistance reading is LOW from sensor 
    //So Dont start the pump
    Serial.println("High Moisture so STOP the Pump");

    //digitalWrite(pump,LOW);
    digitalWrite(relay,LOW);
   } 
  else {
    //LOW Moisture in the soil, hence the resistance reading is HIGH from sensor
    //So Start the pump
    Serial.println("Low Moisture so START the Pump");

    //digitalWrite(pump, HIGH);
    digitalWrite(relay, HIGH);
    //If the current outside temperature is higher than 85 degrees then keep the motor running for longer time
    if(f >= 85.00){
        Serial.println("high temperature");
        delay(2000);
    }
  }
  delay(1000);
 // Wait a few seconds between measurements.
  delay(2000);

 

}