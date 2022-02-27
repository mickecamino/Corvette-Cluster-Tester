# Corvette Cluster Tester
## Test the Corvette Cluster 1984-1989 LCD panel

This is something I did while trying to repair a Corvette Digital Cluster from 1985.
I decoded the bit stream from the CPU board to the LCD board and coded that into an Arduino.
I can now test the LCD board without the CPU board and verify that all LCD segments are working.

There are three LCD screens in the cluster, one speedometer, one info and one tachometer.
The LCD panels differs between the years:

**1984**
All panels are unique for 1984, they only exists this year. 
The digits on the info LCD are really small, the larger digits has curved segments.

**1985**
These panels have really nice digts, crisp and clear.
The info panel and speedometer stays the same from 1985-1989.
The tachometer is without upshift symbol.

**1986**
This year the tachometer had an up-arrow with the text UPSHIFT FOR BEST ECONOMY.

**1987-1988**
The tachometer had an O and D added segments for Drive and/or Overdrive symbol.

**1989**
This year the tachometer had an up-arrow with the text UPSHIFT ONE TO FOUR.

I will add code for the different years once I have them tested.

## How the LCD panel is driven
The PCB with the LCD panels has 8 40-pin IC's that control the three LCD screens.  
The IC's are M8438B6 from SGS-Thomson or AY0438 from Microchip. They control up to 32 LCD segments and is driven by serial data. Each IC has one Data In and one Data Out.  
8 IC's * 32 outputs = 256 and that is how the panel is driven, a burst of clocked 256 bit data followed by a Strobe to output the data. Each pin is latched.

## The Code
The code is pretty simple and easy to modify.  
Most of the code contains array's for the different segments. There is one function that outputs data to the display, it takes two arguments, parameter one is the array name and parameter two is the number of positions to output.

## Connections
Pin 5 (Strobe) of the cluster connects to pin 8 on the Arduino  
Pin 7 (Clock)  of the cluster connects to pin 9 on the Arduino  
Pin 8 (Data)   of the cluster connects to pin 10 on the Arduino  
