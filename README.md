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
* RGB LED Strip. (I used [this one](http://www.adafruit.com/products/1948) with a 4-pin JST SM since I had it laying around.)
* Wire or JST SM to hook up the RGB LED Strip
* [Spark Core](https://store.spark.io/)
