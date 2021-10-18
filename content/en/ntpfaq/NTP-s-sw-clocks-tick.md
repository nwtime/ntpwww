---
title: "Making Time go on"
type: "archives"
--- 

As seen before, the number of bits together with a definition of resolution and epoch are used to store time stamps. For a real clock, time must advance automatically.

Obviously a defined resolution of nanoseconds is useless if the value is updated once per minute. If you are still not convinced, consider reading such a clock three times a minute, and compare the time you would get.

So we want a frequent update of the time bits. In most cases such an update is done in an _interrupt service routine_, and the interrupt is triggered by a programmable timer chip. Unfortunately updating the clock bits compared to generating a timer interrupt is slow (After all, most processors have other work to do as well). Popular values for the interrupt frequency are 18.2, 50, 60, and 100Hz. DEC Alpha machines typically use 1024Hz.

Because of the speed requirement, most time bits use a linear time scale like seconds (instead of dealing with seconds, minutes, hours, days, etc.). Only if a human is in need of the current time, the time stamp is read and converted.

In theory the mathematics to update the clock are easy: If you have two interrupts per hour, just add 30 minutes every interrupt; if you have 100 interrupts per second, simply add 10ms per interrupt. In the popular UNIX clock model the units in the time bits are microseconds, and the increase per interrupt is 1000000 / HZ (HZ is the interrupt frequency). (Of course it's highly desirable to use numbers where the division works without remainder.) The value added every timer interrupt is frequently referred to as `tick`.

