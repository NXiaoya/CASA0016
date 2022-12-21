# CASA0016- Home Weather Forecast By: Xiaoya Nie
<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/icon.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/icon.png" width="400" height="400" />

## Project Aim:
As we know, the weather in London is changeable and it rains a lot. I often forget to bring my umbrella. I wanted to design a device that would hang next to the door. Every time when I'm leaving, it will tell me the weather today. It would remind the user if the umbrella is needed before he/she go out. At the same time, to save on system consumption, the reminder would only be activated when it detects someone approaching the door.

## Project Inspiration:

      https://www.geeky-gadgets.com/the-ambient-umbrella-30-12-2009/
     

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/idea.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/idea.png" width="400"/>

Ambient umbrella:
   - different patterns of light corresponding to different weather
   - a wireless data-radio chip embedded into the handle of the umbrella.
   - costs $130


## Hardware need:
The list of components:
   - Feather Huzzah Esp8266: The microcontroller of the project. It can connect to WIFI to get the weather from open weather map api.
   - PIR sensor: Detect the motion of the user. The sensor reading is used as a trigger.
   - Grove - LCD RGB Backlight: Display the weather information.
   - Buzzer: work as an alarm if the umbrella is needed.
   - AM2302: The temperature and humidity sensor, measuring the data in the room. (Same as DHT22)

Hardware connection:

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/circuit.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/circuit.png" width="600"/>

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Pin.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Pin.png" width="600"/>

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Grove.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Grove.png" width="600"/>

 It takes I2C as communication method with the microcontroller. So number of pins required for data exchange and backlight control shrinks to 2, relieving IOs for other tasks.
#### I2C:

Serial data line(SDA) is for Data transmission.

Serial clock line (SCL) is a Clock line, which controls the time sequence of data transmission.

## API used:

      https://home.openweathermap.org/users/sign_in

Open weather map API: free, can get the weather in different cities. The httpGETRequest() function makes a request to OpenWeatherMap and it retrieves a string with a JSON object that contains the weather information.

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/API.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/API.png" width="800"/>

   <img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/ToAPI.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/ToAPI.png" width="400"/> 
   
   ![jsonvar](https://github.com/NXiaoya/CASA0016/blob/main/pictures/jsonvar.png)
   
## Project Flow:

![flow](https://github.com/NXiaoya/CASA0016/blob/main/pictures/flow.png)

## Home Weather Forecast:


<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/inside.jpg" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/inside.jpg" width="400"/>

![whole](https://github.com/NXiaoya/CASA0016/blob/main/pictures/whole.jpg)


## Improvements:
   - Redesign the storage box
   - Make it a battery based system
   - Add other environment detection sensors to make it an integrated home weather station
   - Add buttons or a touch screen to allow users to interact with the device


## References:
1.https://randomnerdtutorials.com/esp8266-nodemcu-http-get-open-weather-map-thingspeak-arduino/

2.https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/

