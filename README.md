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
These panels have really nice digts, crist and clear.
The info panel and speedometer stays the same from 1985-1989.
The tachometer is without upshift symbol.

**1986**
This year the tachometer had an up-arrow with the text UPSHIFT FOR BEST ECONOMY.

**1987-1988**
The tachometer had an O and D added segments for Drive and/or Overdrive symbol.

**1989**
This year the tachometer had an up-arrow with the text UPSHIFT ONE TO FOUR.

I will add code for the different years once I have them tested.
