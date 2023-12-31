---
title: "Solaris Bug #4023118"
type: archives
noindex: true 
sitemap_exclude: true
---

Bug Id: `4023118`
: **Category:** kernel
: **Subcategory:** other
: **State:** integrated
: **Synopsis:** sun4u doesn't keep accurate time
: **Description:**

* * *

[ bmc, 12/20/96 ]

The clock on a sun4u drifts unacceptably.  On a typical 143 mHz Ultra, the clock took 1.0001350 seconds to count 1 second.  While this may seem trivial, it adds up quickly.  In this case, the TOD chip will have to pull the clock forward by 2 seconds every 4 hours and 7 minutes. This drift rate is so high, that the clock is close to being too broken for NTP to guarantee correctness (in order for NTP's mechanism to work, it must be assured that the local clock drifts no more than 20 ms in 64 seconds;  this particular 143 mHz Ultra will drift by nearly 9 ms in that period).  This problem has been reproduced on virtually all sun4u classes.

The fundamental problem lies in the kernel's perception of ticks per second.  The PROM is responsible for determining this figure exactly, and the kernel extracts it into the variable `cpu_tick_freq`.  On sun4u's, this number is disconcertingly round:  143000000, 167000000, 248000000, etc.  Indeed, a simple experiment revealed that these numbers were quite far from the actual ticks per second.  Typical was the 143 mHz Ultra which was discovered to tick around 142,980,806 (+/- 10) times per second.

* * *

**Work around:** `Integrated in releases: s297_27`
: **Duplicate of:**
: **Patch id:**
: **See also:**
: **Summary:**