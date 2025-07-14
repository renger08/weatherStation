# Weather Station
 Recive Weather information from internet using API

 ![GitHub Repo stars](https://img.shields.io/github/stars/renger08/weatherStation)
 ![GitHub followers](https://img.shields.io/github/followers/renger08)
![GitHub watchers](https://img.shields.io/github/watchers/renger08/weatherStation)



 ![](./pic/above%202.jpg)

 ![](./pic/screen%201.jpg)

 ![](./pic/screen%202.jpg)

# components:
* ESP32-WROOM-32D (Espressif32 ESP32 Dev Module)
* I2C Oled Display 128*64
* Some jumper wires

![](./pic/above.jpg)
# Connections
* Gnd --> Gnd 
* Vcc --> 3.3
* Sck/Scl --> GPI/O 22 (Default SCL pin)
* SDA --> GPI/O 21 (Default SDA pin)
* you can use any pin but you have to define these pins (look for proper tutorial for this)

![](./pic/schematic.png)
# Make some changes in the Code
you have to change these lines:

`const char* ssid = "Your-SSID-Here";`

`const char* password = "Your-WIFI-Password-Here";`

`String URL = "https://api.open-meteo.com/v1/forecast?latitude=*********&longitude=*********&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code,apparent_temperature&timezone=auto";`

* Replace *** (stars) with your location Credentials
* you can get a custom link from [here](https://open-meteo.com/)

# Don't Forget to install libraries
for more information check the [platformio.ini](./platformio.ini) file.

# Give it a Star!
I'll be greatefull if you give this project a star⭐.

![renger08's Stats](https://github-readme-stats.vercel.app/api?username=renger08&theme=vue-dark&show_icons=true&hide_border=true&count_private=false)

![renger08's Top Languages](https://github-readme-stats.vercel.app/api/top-langs/?username=renger08&theme=vue-dark&show_icons=true&hide_border=true&layout=compact)
