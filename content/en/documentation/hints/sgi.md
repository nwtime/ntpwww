---
title: "SGI Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

12 Jan 93

* * *

#### adjtime, tick and tickadj

The SGI value for HZ is 100 under Irix 4, with the system clock running in nominal mode (`ftimer off`), so the value for tick is 10000 usec. `tickadj` is a bit more tricky because of the behaviour of `adjtime()`, which seems to try to perform the correction over 100-200 seconds, with a rate limit of 0.04 secs/sec for large corrections.  Corrections of less than 0.017 seconds generally complete in less than a second,
however.

Some measured rates are as follows:

<pre>
	Delta       Rate (sec/sec)
	> 1		0.04
	0.75		0.04
	0.6		0.004
	0.5		0.004
	0.4		0.0026
	0.3		0.0026
	0.2		0.0013
	0.1		0.0015
	0.05		0.0015
	0.02		0.0003
	0.01		0.015</pre>

Strange.  Anyway, since `adjtime` will complete adjustments of less than 17 msec in less than a second, whether the fast clock is on or off, I have used a value of 150 usec/tick for the `tickadj` value.

#### Fast Clock

I get smoother timekeeping if I turn on the fast clock, thereby making the clock tick at 1kHz rather than 100Hz.  With the fast clock off, I see a sawtooth clock offset with an amplitude of 5 msec.  With it on,
the amplitude drops to 0.5 msec (surprise!).  This may be a consequence of having a local reference clock which spits out the time at exactly one-second intervals - I am probably seeing sampling aliasing between
that and the machine clock.  This may all be irrelevant for machines without a local reference clock.  Fiddling with the fast clock doesn't seem to compromise the above choices for `tick` and `tickadj`.

I use the `ftimer` program to switch the fast clock on when the system goes into multiuser mode, but you can set the `fastclock` flag in `/usr/sysgen/master.d/kernel` to have it on by default.  See `ftimer(1)`.

#### timetrim

Irix has a kernel variable called `timetrim` which adjusts the system time increment, effectively trimming the clock frequency.  `xntpd` could use this rather than `adjtime()` to do its frequency trimming, but I haven't the time to explore this.  There is a utility program, `timetrim`, in the `util` directory which allows manipulation of the `timetrim` value in both SGI and `xntpd` native units.  You can fiddle with default `timetrim` value in `/usr/sysgen/master.d/kernel`, but I think that's ugly.  I just use `xntpd` to figure out the right value for `timetrim` for a particular CPU and then set it using `timetrim` when going to multiuser mode.

#### Serial I/O Latency

If you use a local clock on an RS-232 line, look into the kernel configuration stuff with regard to improving the input latency (check out `/usr/sysgen/master.d/[sduart|cdsio]`).  I have a Kinemetrics OM-DC
hooked onto `/dev/ttyd2` (the second CPU board RS-232 port) on an SGI Crimson, and setting the `duart_rsrv_duration` flag to 0 improves things a bit.

Steve Clift, CSIRO Marine Labs, Hobart, Australia