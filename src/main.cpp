#include <WiFi.h> // built-in library
#include <HTTPClient.h> // built-in library
#include <ArduinoJson.h> // Download it from Library Manager
#include <Adafruit_SSD1306.h> // Download it from Library Manager
#include <Adafruit_GFX.h> // this library available in Adafruit_SSD1306 library
// OLED Display Pins 
#define SCK_PIN 22 // SCL -> Signal Clock ########## I2C bus in ESP32 WROOM 32D
#define SDA_PIN 21 // SDA -> Send/Recive Data ########## I2C bus in ESP32 WROOM 32D
// OLED Display Config
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin) **** I2C display doesn't have reset pin
#define SCREEN_ADDRESS 0x3C // See datasheet or run a Scan for Address; 0x3D for 128x64, 0x3C for 128x32
// Start Display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// WIFI or Hotspot Information
const char* ssid = "Your-SSID-Here"; // Enter the Name of WIFI
const char* password = "Your-WIFI-Password-Here"; // Enter the password of WIFI
// Final URL for the API
String URL = "https://api.open-meteo.com/v1/forecast?latitude=*********&longitude=*********&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code,apparent_temperature&timezone=auto";
// Replace with your location Credentials             ******              ******
// latitude  
// longitude 

void temperatureStatus(float temp){
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Temperature
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(35, 10);           // موقعیت نوشتار (x=10, y=25)
  display.print("Temp:"); // "Temperature: " won't fit in the Display
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(20, 40);
  display.print(temp);
  display.print(" ");
  display.write(167); // prints a special character degeree °
  display.println("C");
  // Update Display
  display.display();

}

void humidityStatus(float humidity){
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Humidity
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(15, 10);           // موقعیت نوشتار (x=10, y=25)
  display.print("Humidity:");
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(25, 40);
  display.print(humidity);
  display.println(" %");
  // Update Display
  display.display();
}

void tempFeelStatus(float apparentTemp) {
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Tempeture Feel
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(5, 10);           // موقعیت نوشتار (x=10, y=25)
  display.print("Temp Feel:");
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(20, 40);
  display.print(apparentTemp);
  display.print(" ");
  display.write(167); // prints a special character degeree °
  display.println("C");
  // Update Display
  display.display();
}

void windStatus(float wind){
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Wind Speed
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(35, 10);           // موقعیت نوشتار (x=10, y=25)
  display.print("Wind:"); // "Wind Speed: " won't Fit in the display
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(15, 40); 
  display.print(wind);
  display.println("K/h");
  // Update Display
  display.display();

}

void weatherStatus(int weatherCode){
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Weather Status
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(15, 10);           // موقعیت نوشتار (x=10, y=25)
  display.println("Weather:");
  display.setTextSize(2);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(15, 40);
  // print status by weatherCode
  switch (weatherCode) {
    case 0:
      display.println("Clear sky"); // آسمان صاف
      break;

    case 1: 
      display.println("Mostly Clear"); // صاف کمی ابری
      break;
    
    case 2: 
      display.println("Cloudy"); // ابری
      break;

    case 3:
      display.println("Overcast"); // ابری
      break;

    case 45: 
      display.println("Fog"); // مه
      break;

    case 48:
      Serial.println("Heavy Fog"); // مه سنگین
      break;

    case 51: case 53: case 55: 
      display.println("Drizzle"); // بارش باران نم نم
      break;

    case 56: case 57: case 66: case 67:
      display.println("Hail"); // تگرگ
      break;

    case 61: case 63: case 65:
      display.println("Rainy"); // بارانی
      break;
    
    case 71: case 73: case 75:case 77: 
      display.println("Snowy"); // برفی
      break;
    
    case 80: case 81: case 82: 
      display.println("Heavy Rain"); // باران سنگین
      break;
    
    case 85: case 86:
      display.println("Heavy Snow"); // برف سنگین
      break;
    
      default:
      Serial.println("Unknown");
      break;
  }
  // Update Display
  display.display();
}

void errorMessage(){
  // Display Config
  display.clearDisplay();
  display.drawRect(0,0,SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
  // Displaying Error message 
  display.setTextSize(1);              // اندازه فونت (1 کوچک، 2 بزرگ‌تر و ...)
  display.setTextColor(SSD1306_WHITE); // رنگ متن
  display.setCursor(15, 10);           // موقعیت نوشتار (x=10, y=25)
  display.println("Something went wrong...");
  display.setCursor(15, 20);
  display.println("Please try again.");
  // Update Display
  display.display();
}

void setup() {
  // Start Serial Monitor #### Don't Forget the platformio.ini / monitor_speed
  Serial.begin(115200);
  // initialize the OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  // Start Adafruit Welcom Display
  display.display();
  delay(2000);
  display.clearDisplay();
  // We start by connecting to a WiFi network or a hotspot
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // wait for WiFi connection
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    // if you have a special/paid api there is a example
    // Set HTTP Request Final URL with Location and API key information
    // http.begin(URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey);
    http.begin(URL);

    // start connection and send HTTP Request
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {

      //Read Data as a JSON string
      String JSON_Data = http.getString();
      // Serial.println(JSON_Data); // prints the resault of http request in serial monitor

      //Retrieve some information about the weather from the JSON format
      DynamicJsonDocument doc(2048);
      DeserializationError error = deserializeJson(doc, JSON_Data);
      if (error) {
          Serial.print(F("Json Error:"));
          Serial.println(error.c_str());
          return;
        }
      
      // in the https://open-meteo.com/ you can recive other imformation like MSL-pressure, wind direction and more...
      float temp = doc["current"]["temperature_2m"];
      float humidity = doc["current"]["relative_humidity_2m"];
      // float pressure = doc["current"]["pressure_msl"];
      float wind = doc["current"]["wind_speed_10m"];
      float apparentTemp = doc["current"]["apparent_temperature"];
      int weatherCode = doc["current"]["weather_code"];

      temperatureStatus(temp);
      sleep(5); // or you can use delay(5000);
      humidityStatus(humidity);
      sleep(5);
      tempFeelStatus(apparentTemp);
      sleep(5);
      windStatus(wind);
      sleep(5);
      weatherStatus(weatherCode);
      sleep(5);


      temperatureStatus(temp);
      sleep(5);
      humidityStatus(humidity);
      sleep(5);
      tempFeelStatus(apparentTemp);
      sleep(5);
      windStatus(wind);
      sleep(5);
      weatherStatus(weatherCode);
      sleep(5);

      } else {
      Serial.println("Error!");
      errorMessage();
    }

    http.end();

  }
  
  // Wait for 1 second 
  delay(1000);
}