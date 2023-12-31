---
title: "Solaris Bug #4095849"
type: archives
noindex: true 
sitemap_exclude: true
---

**Bug Id:** `4095849`
: **Category:** kernel
: **Subcategory:** syscall
: **State:** evaluated
: **Synopsis:** time_constant value >6 with PLL in use leads to integer divide zero trap panic
: **Description:** If the `time_constant` parameter is 7 or higher, and the phase-lock looping model
  is in use, the system will take a "integer divide zero trap" panic in the clock routine as soon as the `time_offset` becomes non-zero.

:  `time_constant` defaults to 0.  The only place it is set is in the `ntp_adjtime` system call, from the `constant` element of the `timex` structure argument.
: **Work around:** Never set the `constant` element of the `timex` structure passed to `ntp_adjtime` to
  a value larger than 6.

* * *

satish.mynam@Eng 1998-04-30

1. Use Sun's version of NTP software instead of PD version. This problem is not seen with Sun's NTP version (which is mostly eqivalent to PD NTP 3.4 plus some Sun's local functionality futures).

2. **Workaround for the public domain NTP version ONLY:** The workaround for public domain NTP version is   to disable the `KERNEL_PLL` from the NTP code. This way the `ntp_Adjtime()` system call is totally bypassed without sacrificing any of the functionality of NTP. The only hit you might see is the way  kernel precision timinig is done without the PLL algorithm in the kernel.

   The easiest way to disable `ntp_adjtime` option is(without changing any makefiles or other config files) to disable the `KERNEL_PLL` value in the `./config.h` file.

   After doing a `./configure` for probing for all the necessary tools(compilers, OS version, libraries),  please comment out `KERNEL_PLL` macro in the `./config.h` file.  This will disable the `KERNEL_PLL` part of the source code and the newly obtained `xntpd` is just similar to the old one but it does not use `ntp_adjtime()` system call. This prevents it from panicing the kernel.

   <code>/\*#define KERNEL_PLL 1\*/</code>

   I complied a new `xntpd` binary this way and it does not have any `ntp_adjtime()` related stuff.

   Default:

       /net/divya/export/home/mynam/public_domain/ntp/xntp3-5.92/xntpd>strings
       xntpd |
       grep ntp_adjtime
       354:adj_frequency: ntp_adjtime failed: %m
       357:loop_config: ntp_adjtime() failed: %m
       435:get_kernel_info: ntp_adjtime() failed: %m

   With `KERNEL_PLL` disabled in `config.h` file:

       /net/divya/export/home/mynam/public_domain/ntp/xntp3-5.92/xntpd>strings
       xntpd.nopll | grep ntp_adjtime

* * *

Integrated in releases:
: **Duplicate of:**
: **Patch id:**
: **See also:** 4133517
: **Summary:** If the time_constant parameter is 7 or higher, and the phase-lock looping model is in use,    the system will take a "integer divide zero trap" panic in the clock routine as soon as the  `time_offset` becomes non-zero.

    `time_constant` defaults to 0.  The only place it is set is in the `ntp_adjtime` system call, from the `constant` element of the `timex` structure argument.