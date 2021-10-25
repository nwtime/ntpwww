---
title: "8.3. Troubleshooting Specific Products"
type: "archives"
---

8.3.1 [PC Hardware](#831-pc-hardware)  
8.3.1.1 [How accurate is the CMOS clock?](#8311-how-accurate-is-the-cmos-clock)  
8.3.1.2 [How can I set the CMOS clock?](#8312-how-can-i-set-the-cmos-clock)  
8.3.1.3 [How can I read or write the CMOS clock?](#8313-how-can-i-read-or-write-the-cmos-clock)  
8.3.1.4 [How can SMM affect Interrupt Processing?](#8314-how-can-smm-affect-interrupt-processing)  
8.3.2 [Linux](#832-linux)  
8.3.2.1 [What does set_rtc_mmss: can't update from 54 to 5 mean?](#8321-what-does-set_rtc_mmss-cant-update-from-54-to-5-mean)  
8.3.2.2 [Why does my Linux system lose several milliseconds every once in a while.](#8322-why-does-my-linux-system-lose-several-milliseconds-every-once-in-a-while)   
8.3.4 [Serial Port](#834-serial-port)   
8.3.4.1 [Do Multiport Serial Cards cause Trouble?](#8341-do-multiport-serial-cards-cause-trouble)  
8.3.4.2 [Why does my DCF77 Receiver not get Power from the serial Port?](#8342-why-does-my-dcf77-receiver-not-get-power-from-the-serial-port)  
8.3.5 [Oncore Compatibles](#835-oncore-compatibles)  
8.3.5.1 [Will the M12 work with the Oncore driver?](#8351-will-the-m12-work-with-the-oncore-driver)  
8.3.5.2 [Why is the UT+ reporting clk_noreply?](#8352-why-is-the-ut-reporting-clk_noreply)   
8.3.6 [Solaris](#836-solaris)     
8.3.6.1 [What is dosyncdr?](#8361-what-is-dosyncdr)  
8.3.6.2 [What causes occasional 2s Time Steps?](#8362-what-causes-occasional-2s-time-steps)  
8.3.7 [Trimble Clocks](#837-trimble-clocks)  
8.3.7.1 [Only one Edge of my Trimble Acutime's PPS Pulse is detected](#8371-only-one-edge-of-my-trimble-acutimes-pps-pulse-is-detected)  

* * *

#### 8.3.1. PC Hardware

#### 8.3.1.1 How accurate is the CMOS clock?

The CMOS real time clock (RTC) is responsible for preserving the date and time while the PC is turned off.

Some people say the CMOS RTC is much more accurate than the timer interrupt in terms of frequency error. Actually I don't know, but I have one concrete example: a PC used a stratum 1 server with PPS had a hardware fault, and it had been powered off for about 18 days. When running, the typical frequency error was 15 to 17 PPM and when the system was rebooted the RTC clock was off by 18 seconds. That would be an error of roughly 12 PPM.

* * *

#### 8.3.1.2 How can I set the CMOS clock?

Basically `ntpd` only sets the system time of the operating system. Therefore setting the CMOS clock is the responsibility of the operating system and its associated tools. To make things worse, typical PC operating systems and the BIOS set the RTC to local time, while UNIX-like operating systems set the RTC to UTC.

**Example 8.3a: Linux**

In Linux the RTC is either not updated at all, or just the minutes and seconds. The related kernel code has been revised several times, with different behaviour. Setting the system time manually does not update the RTC. Only if the `STA_UNSYNC` bit is cleared, the kernel will periodically update the RTC from the system time. Typically this happens every 11 minutes.

With the optional PPSkit-0.9.0 kernel patch the RTC is updated just like in other PC operating systems. In addition the automatic periodic update can be disabled completely (see the documentation that comes with the product).

There is also a user-space program to set the RTC, but it requires special privileges. Typically the utility is named `hwclock`.

* * *

#### 8.3.1.3 How can I read or write the CMOS clock?

There are several possibilities for Linux besides using the BIOS:

*   You can read the clock using `cat /proc/rtc` (if `CONFIG_RTC` is set), or `hwclock --show` (`hwclock` is a newer replacement for the older `clock` program). C programmers could use the `ioctl()` interface and `RTC_RD_TIME` (see `/usr/include/linux/mc146818rtc.h` and `/usr/src/linux/Documentation/rtc.txt`).

*   You can set the clock using either `hwclock --set` (possibly with `--utc`) or the `ioctl()` interface and `RTC_SET_TIME`.

*   The kernel will normally read the clock during boot (when it does not know the timezone yet) and when APM had been active. When the kernel PLL is used, the system time will be written to the clock periodically. Setting or adjusting the time by other means will not update the hardware clock.

* * *

#### 8.3.1.4 How can SMM affect Interrupt Processing?

Let me quote an explanation written by [Poul-Henning Kamp](mailto:phk@freebsd.dk) from the newsgroup:

I was gathering some data for [Professor David L. Mills](mailto:mills@udel.edu) today and they looked lousy to put it mildly; every 300-400 seconds I had a 40-50 microsecond peak in my data. After some debugging I know know what it was: the SMM mode interrupts to the BIOS.

This machine is brand new, and I had never put a PPS signal on it before. It uses the PIIX4 chip from Intel and appearantly the SMM BIOS gets called at regular (but not very precise) intervals to monitor temperatures and fans and whats not.

Needless to say, this could not be disabled in the BIOS setup.

I found out I could disable the SMI output from the PIIX4 to the CPU by clearing bit zero in the `GLBCTL` register in the third function of the 82371AB chip. You need to find the IO base address from register `0x40` in the PCI header, and add the `0x28` to that address. For my motherboard that ended up being `0xe428`, your mileage will vary, and you should "Do The Right Thing" to find this location.

Needless to say, the SMM BIOS will not be able to check if your CPU is able to make toast if you disable it this way, so you'd better know what you're doing.

* * *

#### 8.3.2 Linux

#### 8.3.2.1 What does set_rtc_mmss: can't update from 54 to 5 mean?

The function `set_rtc_mmss()` updates minutes and seconds of the CMOS clock from system time. It does not update the hour or date to avoid problems with timezones.(The Linux kernel has no idea about the effective timezone or daylight saving time.) The message shown was added to make users and implementers aware of the problem that not all time updates will succeed.

Imagine the system time is 17:56:23 while the CMOS clock is already at 18:03:45. Updating just minutes and seconds would set the hardware clock to 18:56:23, a wrong value. The solution for this problem is either to wait a few minutes, or to install a kernel patch that fixes the problem. Normally a wrong time in the hardware clock will not show up until after reboot, or maybe after APM slowed down your system.

* * *

#### 8.3.2.2 Why does my Linux system lose several milliseconds every once in a while.

You are using `/sbin/kerneld` for automatic module loading. Several modules do not take good care of the time during initialization. If you can spare the memory, please load the modules at boot time.

The original contributor remarks: "This once occured to me. The sound system was demand loaded. A small application told the time every 15 minutes (saytime running in cron). The ntp logging showed me that something strange happened every 15 minutes. I found out it was the loading of the sound module every 15 minutes."

In addition removal of modules also seems to block interrupts.

Another reason for lost interrupts are closely connected with the use of IDE drives that are operated in polled mode (PIO), and not im DMA mode. Still another reason can be a BIOS that disables interrupts when APM routines are called.

* * *

#### 8.3.4 Serial Port

#### 8.3.4.1 Do Multiport Serial Cards cause Trouble?

Multiport serial cards are usually optimized for throughput, not for low latency. Therefore, some reference clock drivers may cause trouble.

In case you are already in trouble, and using a standard serial port is not an option, you can only try to find out what's wrong:

* `cat /proc/tty/driver/serial` will show some essential information about the serial ports.
* Depending on the driver, `ntpq`'s `cl` command may show some useful information like the last received time code or error counters.
* To see what `ntpd` is doing, you can use <code>strace -p _pid_</code> to attach to `ntpd`.

* * *

#### 8.3.4.2 Why does my DCF77 Receiver not get Power from the serial Port?

Somewhere in the code cleanup between NTPv3 and NTPv4, the code to set the modem lines of the serial port got lost. The port has to be set up in a special way to provide power to the receiver.

For my receiver the command `setserialbits /dev/refclock-0 -rts` turns on power while `ntpd` is running. Some receivers care about polarity, some don't. You might try substituting `-rts` with `-dtr`.

For the [RAWDCF PARSE driver](/archives/drivers/driver8/) there is a `mode 14`, that turns on power on the port, but my receiver (and others, too) had errors about every 10 seconds. I have reported the problem to the original author.

* * *

#### 8.3.5 Oncore Compatibles

#### 8.3.5.1 Will the M12 work with the Oncore driver?

It seems this product speaks a different protocol than the original hardware. To complicate matters, Gary Sanders found out that "If you got your eval kit from Synergy Systems, the PPS output on the eval board is inverted from the older Oncores(...)". To really confuse the users "(...) Synergy has a simple wiring change on the eval board to fix it. The boards that are currently shipping have this fix incorporated."

[Mark Martinec](mailto:mark.martinec@ijs.si) contributed: "I just stumbled across the specs of the 12-channel GPS receiver Motorola Oncore M12. Its acquisition time (time to first fix) for cold start is less than 60 seconds typical.

* * *

#### 8.3.5.2 Why is the UT+ reporting clk_noreply?

According to the documentation [driver 30](/archives/drivers/driver30/) should work for the UT+ "as long as they support the Motorola Binary Protocol". Furthermore the documentation recommends: "When first starting to use the driver you should definitely review the information written to the `clockstats` file to verify that the driver is running correctly."

Unfortunately some essential documentation can only be found in the source file (`ntpd/refclock_oncore.c`). Some anonymous person wrote in news://comp.protocols.time.ntp:

(...) When the GPS is in (navigation mode), the driver simply discards the timestamp, resulting in the `clk_noreply`. The clock _did_ indeed reply, but the driver just threw it away with no messages to inform me about what it was doing.

(...) yes, the GPS is indeed in Navigation mode. The Oncore driver _does_ change the mode, even though the code comment quoted above says "don't do anything to change it" (mode `0`).

(...) So I start using mode `1` instead, which initializes the Oncore with a user-supplied position and then switches into Position Hold mode. Now in this new mode I am _still_ getting `clk_noreply`, but now these messages are alternated with `clk_badtime`.

(...) The binary code is getting decoded just fine. I can print out hours, minutes, seconds. (...) I discover that clocktime fails because it thinks that the time offset between the GPS and my computer's clock is more than half a day!

(...) I do `ntpdate` to fix the clock, then run NTP. Hey, it works! HalleleujahPraiseTheLord.

* * *

#### 8.3.6 Solaris

#### 8.3.6.1 What is dosyncdr?

There's a kernel variable named `dosyncdr` that influences how the kernel keeps time. Generally it's neither necessary nor recommended to change the value from the default. Only in Solaris 2.5.1 (where NTP was not officially supported) it was necessary to set `dosyncdr` manually to `0`.

[Michael Sinatra](mailto:msinatra@uclink4.berkeley.edu) wrote in news://comp.protocols.time.ntp:

My understanding is, after Solaris 2.6 this is "not necessary at all" . In the past you needed to put `set dosynctodr=0` in `/etc/system`; now, you are NOT supposed to do that. Moreover, you are NOT supposed to use `tickadj`.

* * *

#### 8.3.6.2 What causes occasional 2s Time Steps?

After some experiments, [Thomas Schulz](mailto:schulz@adi.com) found out:

This behavior is normal for Solaris when NTP is not running. This wandering is due to Solaris correcting the system clock from the hardware clock (the TODR). The hardware clock is assumed to be the more accurate one (and it is). This correction is done whenever the two clocks are more than about 1.5 to 2 seconds apart. You will see this behavior on any Solaris system if you wait long enough. This correction is not done if NTP is running. Of course on a system with a very bad clock this behavior will be much more obvious than on one with a better clock (no Sparc has a good clock).

* * *

#### 8.3.7 Trimble Clocks

#### 8.3.7.1 Only one Edge of my Trimble Acutime's PPS Pulse is detected

If the device uses very short pulses (like 1 microsecond), the hardware or software may have trouble processing the pulse correctly: see [Q: 8.2.2.2.](/ntpfaq/ntp-s-trbl-general/#8222-why-is-the-pps-api-only-detecting-one-edge) and [Q: 6.2.4.6](/ntpfaq/ntp-s-config-adv/#6246-what-is-the-shortest-width-for-a-pulse-connected-to-the-dcd-pin-of-an-rs-232-interface). Recent clocks feature a programmable pulse width. Using 100 or 200 milliseconds as width will assist you finding the right edge, assuming that the first edge is the more accurate one.