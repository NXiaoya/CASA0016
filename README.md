# CASA0016- Home Weather Forecast By: Xiaoya Nie
<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/icon.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/icon.png" width="400" height="400" />

## Project Aim:
As we know, the weather in London is changeable and it rains a lot. I often forget to bring my umbrella. I wanted to design a device that would hang next to the door. Every time when I'm leaving, it will tell me the weather today. It would remind the user if the umbrella is needed before he/she go out. At the same time, to save on system consumption, the reminder would only be activated when it detects someone approaching the door.

## Project Inspiration:

https://www.geeky-gadgets.com/the-ambient-umbrella-30-12-2009/

<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/idea.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/idea.png" width="400"/>

## Hardware need:
The list of components:
   - ESP8266: The microcontroller of the project. It can connect to WIFI to get the weather from open weather map api.
   - PIR sensor: Detect the motion of the user. The sensor reading is used as a trigger.
   - Grove - LCD RGB Backlight: Display the weather information.
   - Buzzer: work as an alarm if the umbrella is needed.
   - AM2302: The temperature and humidity sensor, measuring the data in the room.

Hardware connection:
<img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Pin.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/Pin.png" width="600"/>

## API used:
    https://home.openweathermap.org/users/sign_in
    Open weather map API: free, can get the weather in different cities.
   <img src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/ToAPI.png" data-canonical-src="https://github.com/NXiaoya/CASA0016/blob/main/pictures/ToAPI.png" width="400"/> 
   
## Project schematic:
![flow](https://github.com/NXiaoya/CASA0016/blob/main/pictures/flow.png)

