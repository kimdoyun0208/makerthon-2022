#include <DHT.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
#define LIGHT 5
#define SOUND 6
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

int on1 = 0;
int on2 = 0;
int keep = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LIGHT, OUTPUT);
    pinMode(SOUND, OUTPUT);

    dht.begin();
}

void loop() {
    // Wait a few seconds between measurements.
    delay(1000);

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

    if (hic >= 40 || keep == 1)
    {
        keep = 1;
        if(on1 == 1)
        {
            on1 = 0;
        }
        else
        {
            on1 = 1;
        }

        if(on2 == 1)
        {
            on2 = 0;
        }
        else
        {
            on2 = 1;
        }
    }
    else
    {
        on1 = 0;
        on2 = 0;
    }

    digitalWrite(SOUND, HIGH * on1);
    digitalWrite(LIGHT, HIGH * on2);

    Serial.println(hic);
}