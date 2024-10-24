---
title: "SunOS 4.1.1 and 4.1.3 Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Notes on CPU clock oscillator tolerance with SunOS 4.1.1 and 4.1.3

A bug in SunOS 4.1.1 results in the kernel time losing 1 microsecond per tick of the system clock. The bug was fixed (bugid 1094383) for SunOS 4.1.1 and corrected in SunOS 4.1.3. The easiest way to fix this
is to replace the 4.1.1 binary `clock.o` with the corresponding 4.1.3 binary. Without this change it is necessary to use the `tickadj` program included in this distribution with the `-t 9999` option.

The `tickadj` option will work in all cases except when the kernel has been modified to correct the CPU clock oscillator frequency using a 1-pps signal from a precision source. The bugfix must be installed for
this wrinkle to work properly.

[Dave Mills](https://www.nwtime.org/tribute-to-david-l-mills/)