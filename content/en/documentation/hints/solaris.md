---
title: "Solaris Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

Information on compiling and executing `ntpd` under Solaris.

If you're not running Solaris 2.5.1 or later, it is likely that you will have problems; upgrading would be a really good plan.

---

#### Table of Contents

* [All Solaris versions](/documentation/hints/solaris/#all-solaris-versions)
* [Dealing with Frequency Tolerance Violations](/documentation/hints/solaris/#dealing-with-frequency-tolerance-violations)
* [Solaris 2.6](/documentation/hints/solaris/#solaris-26)
* [Solaris 2.5 and 2.5.1](/documentation/hints/solaris/#solaris-25-and-251)
* [Solaris 2.2](/documentation/hints/solaris/#solaris-22)
* [Solaris 2.1](/documentation/hints/solaris/#solaris-21)


### All Solaris versions

> We have a report that says starting with Solaris 2.6 we should leave <code>_dosynctodr_</code> alone. [Here is the report](/documentation/hints/solaris-dosynctodr/).

Proper operation of ntp under Solaris may require setting the kernel variable <code>_dosynctodr_</code> to zero (meaning "do not synchronize the clock to the hardware time-of-day clock"). This can be done with the `tickadj` utility:

`tickadj -s`

If you prefer, it can also be done with the native Solaris kernel debugger:

`echo dosynctodr/W0 | adb -k -w /dev/ksyms /dev/mem`

Or, it can also be set by adding a line to `/etc/system`:

`set dosynctodr = 0`

Instead of the <code>_tick_</code> kernel variable, which many operating systems use to control microseconds added to the system time every clock tick (see [Dealing with Frequency Tolerance Violations](/documentation/hints/solaris/#dealing-with-frequency-tolerance-violations)), Solaris has the variables <code>_nsec_per_tick_</code> and <code>_usec_per_tick_</code>.

<code>_nsec_per_tick_</code> and <code>_usec_per_tick_</code> control the number of nanoseconds and microseconds, respectively, added to the system clock each clock interrupt. Enterprising souls may set these based on information collected by `ntpd` in the `/etc/ntp.drift` file to correct for individual hardware variations.

On UltraSPARC systems, <code>_nsec_per_tick_</code> and <code>_usec_per_tick_</code> are ignored in favor of the <code>_cpu_tick_freq_</code> variable, which should be automatically determined by the PROM in an accurate fashion.

In general, the same ntp binaries should not be used across multiple operating system releases. There is enough variation in the core operating system support for timekeeping that a rebuild of `ntpd` for the idiosyncracies of your specific operating system version is advisable.

It is recommended that ntp be started via a script like [this one](/documentation/hints/solaris.xtra.S99ntpd/), installed in `/etc/init.d/ntpd` with a symbol link from `/etc/rc2.d/S99ntpd`.<a id="frequency_tolerance"></a>

* * *

#### Dealing with Frequency Tolerance Violations

The NTP Version 3 specification [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) calls for a maximum oscillator frequency tolerance of +-100 parts-per-million (PPM), which is representative of those components suitable for use in relatively inexpensive workstation platforms. For those platforms meeting this tolerance, NTP will automatically compensate for the frequency errors of the individual oscillator and no further adjustments are required, either to the configuration file or to various kernel variables. For the NTP Version 4 release, this tolerance has been increased to +-500 PPM.

However, in the case of certain notorious platforms, in particular Sun 4.1.1 systems, the performance can be improved by adjusting the values of certain kernel variables; in particular, `tick` and `tickadj`. The variable `tick` is the increment in microseconds added to the system time on each interval-timer interrupt, while the variable `tickadj` is used by the time adjustment code as a slew rate, in microseconds per tick. When the time is being adjusted via a call to the system routine `adjtime()`, the kernel increases or reduces tick by `tickadj` microseconds per tick until the specified adjustment has been completed. Unfortunately, in most Unix implementations the tick increment must be either zero or plus/minus exactly `tickadj` microseconds, meaning that adjustments are truncated to be an integral multiple of `tickadj` (this latter behaviour is a misfeature, and is the only reason the `tickadj` code needs to concern itself with the internal implementation of `tickadj` at all). In addition, the stock Unix implementation considers it an error to request another adjustment before a prior one has completed.

Thus, to make very sure it avoids problems related to the roundoff, the `tickadj` program can be used to adjust the values of `tick` and `tickadj`. This ensures that all adjustments given to `adjtime()` are an even multiple of `tickadj` microseconds and computes the largest adjustment that can be completed in the adjustment interval (using both the value of `tick` and the value of `tickadj`) so it can avoid exceeding this limit. It is important to note that not all systems will allow inspection or modification of kernel variables other than at system build time. It is also important to know that, with the current NTP tolerances, it is rarely necessary to make these changes, but in many cases they will substantially improve the general accuracy of the time service.

Unfortunately, the value of `tickadj` set by default is almost always too large for `ntpd`. NTP operates by continuously making small adjustments to the clock, usually at one-second intervals. If `tickaj` is set too large, the adjustments will disappear in the roundoff; while, if `tickadj` is too small, NTP will have difficulty if it needs to make an occasional large adjustment. While the daemon itself will read the kernel's values of these variables, it will not change the values, even if they are unsuitable. You must do this yourself before the daemon is started using the `tickadj` program included in the `./util` directory of the distribution. Note that the latter program will also compute an optimal value of `tickadj` for NTP use based on the kernel's value of `tick`.

The `tickadj` program can reset several other kernel variables if asked. It can change the value of `tick` if asked. This is handy to compensate for kernel bugs which cause the clock to run with a very large frequency error, as with SunOS 4.1.1 systems. It can also be used to set the value of the kernel `dosynctodr` variable to zero. This variable controls whether to synchronize the system clock to the time-of-day clock, something you really don't want to happen when `ntpd` is trying to keep it under control. In some systems, such as recent Sun Solaris kernels, the `dosynctodr` variable is the only one that can be changed by the `tickadj` program. In this and other modern kernels, it is not necessary to change the other variables in any case.

> We have a report that says starting with Solaris 2.6 we should leave <code>_dosynctodr_</code> alone.

In order to maintain reasonable correctness bounds, as well as reasonably good accuracy with acceptable polling intervals, <code>ntpd</code> will complain if the frequency error is greater than 500 PPM. For machines with a value of `tick` in the 10-ms range, a change of one in the value of `tick` will change the frequency by about 100 PPM. In order to determine the value of `tick` for a particular CPU, disconnect the machine from all sources of time (`dosynctodr = 0`) and record its actual time compared to an outside source (eyeball-and-wristwatch will do) over a day or more. Multiply the time change over the day by 0.116 and add or subtract the result to tick, depending on whether the CPU is fast or slow. An example call to `tickadj` useful on SunOS 4.1.1 is:

`tickadj -t 9999 -a 5 -s`

which sets tick 100 PPM fast, `tickadj` to 5 microseconds and turns off the clock/calendar chip fiddle. This line can be added to the `rc.local` configuration file to automatically set the kernel variables at boot time.

All this stuff about diddling kernel variables so the NTP daemon will work is really silly. If vendors would ship machines with clocks that kept reasonable time and would make their `adjtime()` system call apply the slew it is given exactly, independent of the value of `tickadj`, all this could go away. This is in fact the case on many current Unix systems.

* * *

### Solaris 2.6

Solaris 2.6 adds support for kernel PLL timekeeping, but breaks this support in such a fashion that using it worse than not. This is [SUN Bug ID 4095849](/documentation/hints/solaris.xtra.4095849/), and it is not yet fixed as of June 1998.

* * *

### Solaris 2.5 and 2.5.1

On UltraSPARC systems, calculation of <code>_cpu_tick_freq_</code> is broken such that values that are off by significant amounts may be used instead. This unfortunately means that `ntpd` may have severe problems keeping synchronization. This is [SUN Bug ID 4023118](/documentation/hints/solaris.xtra.4023118/). Bryan Cantrill of Sun posted [patchfreq](/documentation/hints/solaris.xtra.patchfreq/), a workaround script, to comp.protocols.time.ntp in March of 1997.

* * *

## OLD DATA

**I can't vouch for the accuracy the information below this rule. It may be significantly dated or incorrect.**

* * *

### Solaris 2.2

Solaris 2.2 and later contain completely re-written clock code to provide high resolution microsecond timers. A benefit of the re-written clock code is that adjtime does not round off its adjustments, so ntp does not have to compensate for this rounding. Under Solaris 2.2 and later, ntp `#define`'s `ADJTIME_IS_ACCURATE`, and does not look for the `tickadj` kernel variable.

* * *

### Solaris 2.1

(This originally written by William L. Jones)

Solaris 2.1 contains fairly traditional clock code, with `tick` and `tickadj`.

Since `settimeofday` under Solaris 2.1 only sets the seconds part of `timeval`, care must be used in starting `xntpd`. I suggest the following start up script:

<pre>tickadj -s -a 1000
ntpdate -v server1 server2
sleep 20
ntpdate -v server1 server2
sleep 20
tickadj -a 200
xntpd</pre>

The first `tickadj` turns of the time of day clock and sets the tick adjust value to 1 millisecond. This will insure that an `adjtime` value of at most 2 seconds will complete in 20 seconds.

The first `ntpdate` will set the time to within two seconds using `settimeofday` or it will adjust time using `adjtime`.

The first `sleep` insures the `adjtime` has completed for the first `ntpdate`.

The second `ntpdate` will use `adjtime` to set the time of day since the clock should be within 2 seconds of the correct time.

The second `tickadj` set the tick adjust system value to 5 microseconds.

The second `sleep` insures that `adjtime` will complete before starting the next `xntpd`.

I tried running with a `tickadj` of 5 microseconds with out much success. 200 microseconds seems to work well.

* * *

Prior versions of this file had major text contributed by:

*   Denny Gentry