---
title: "3. How do Computer Clocks work?"
type: "archives"
--- 

This section tries to explain the basics of software clocks used in computers. In principle, such clocks just consist of an oscillator and a counter. 

* * *

#### 3.1 Bits and Registers

Computers are good at adding bits. Therefore time is stored in a number of bits, and adding to these bits makes the time go on. The meaning of the value "zero" has to be defined separately (usually this is called the _epoch_).

Using more bits can widen the range of the time value, or it can increase the resolution of the stored time.

**Example 3.1: Range and Resolution**

If we use 8 bits to store a time stamp, there can be 256 different values. If we choose to store seconds, our resolution is one second, and the range is from 0 to 255 seconds. If we prefer to store the time in minutes, we can store up to 255 minutes.

With 64 bits you could have nanosecond resolution while still having a range significantly longer than your life.