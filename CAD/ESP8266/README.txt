                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


http://www.thingiverse.com/thing:1933779
ESP8266 based modules models library by DonJuanito is licensed under the Creative Commons - Attribution license.
http://creativecommons.org/licenses/by/3.0/

# Summary

This is a models library for most of the existing ESP8266 based modules.
I use these while designing project cases, so I hope it will be helpful for someone.

As some of the devices were drawn from pictures, there could still be some dimensions errors...

The file "ESP8266Models.scad" is meant to be used as a library (using "use <ESP8266Models.scad">"), as illustrated in the "test.scad" file. If it's opened by itself, all modules will be displayed.
The "test.scad" file also illustrates the use of locator functions. These can help to place holes for USB, screws or push buttons for some boards models.

Comments and corrections are welcome.

*Supported modules:*
- ESP-01
- ESP-02 (V3)
- ESP-03
- ESP-04
- ESP-05
- ESP-06
- ESP-07
- ESP-08
- ESP-09
- ESP-10
- ESP-11
- ESP-12F (ESP-12E has the same layout, apart from the antenna path)
- ESP-13
- Witty
- Wemos D1 Mini
- Wemos D1 Battery Shield
- Wemos D1 Prototyping Shield
- NodeMCU V1.0 (Amica version)
- NodeMCU V3 (RoboDyn WiFi-NodeM)
- NodeMCU V3 (LoLin)
- NodeMCU V0.9

**Update V1.4 on 2018-11-16:**
- Added ESP-13
- Added Wemos D1 Battery Shield
- Added Wemos D1 Prototyping Shield
- Added Simplified JST PH 2 pins 90° female connector (2mm picth, 2 versions)
- Added texts to most modules (pins functions)
- Added some locator functions, with more options
- Corrected some minor errors

**Update V1.3 on 2018-11-10 (long overdue update):**
- Added NodeMCU V0.9 (original "devkit" version)
- Added NodeMCU V3 (LoLin version)
- Added NodeMCU V3 (RoboDyn version)

**Update V1.1 on 2017-02-23 :**
- Added holes location functions for USB connectors and push buttons (see test.scad for usage information)