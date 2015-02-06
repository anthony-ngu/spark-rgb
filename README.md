# Spark-RGB
Connecting an RGB LED Strip, Spark Core, and Node.js Webpage!

[Check out the webpage!](http://sparkrgb.azurewebsites.net)
## What's Included in this repo:
* Node.js webpage
  * Talks to Spark Cloud to query for specific users, their devices, and interact with them.
* spark-rgb.ino for custom additions (currently set up for 4-pin JST SM connection)
  * defines the functions that have endpoints exposed.
* firmware.bin that was compiled from the spark-rgb.ino

## Hardware Required:
* Digital RGB LED Strip because they are individually addressable LEDs (I used [this one](http://www.adafruit.com/products/1948) with a 4-pin JST SM since I had it laying around.)
* Wire or JST SM to hook up the RGB LED Strip
* [Spark Core](https://store.spark.io/)

## Using it!
1. Hook up your RGB LED Strip to your Spark Core. (Depending on how many LEDs your strip has, you might need to provide an external power supply. I suggest looking up the specs to your specific LED Strip for more information as it varies.)
  * If you are using the one I chose, you can connect your pins following the instructions [here](https://learn.adafruit.com/digital-led-strip/wiring)
2. I was able to drive mine from the Spark Core directly without the use of an external power supply, so if you hook:
  * +5V on the strip to 3.3V output from the Spark Core
  * GRD on the strip to GRD on the Spark Core
  * DI on the strip to D2 on the Spark Core
  * CI on the strip to D3 on the Spark Core
3. Flash your Spark Core with the firmware! You have two options here:
  1. Open up [spark.io/build](https://www.spark.io/build) and copy and paste the code from the [spark-rgb.ino](https://github.com/anthony-ngu/spark-rgb/blob/master/spark-rgb.ino) into a new app, then compile and flash it onto your Spark device (as long as it has a WiFi connection).
  2. Download the firmware.bin and install it yourself through a USB connection to your Spark device.
4. The elegance of the Node.js solution is how easy it is for anyone to use it! If you go to [http://sparkrgb.azurewebsites.net](http://sparkrgb.azurewebsites.net) you can login with your Spark Credentials and interact with your own Spark Core!
  * The code for this site is in this repository too, it uses [SparkJS](http://docs.spark.io/javascript/) to allow you to login to your own Spark account and interact with your own spark devices.