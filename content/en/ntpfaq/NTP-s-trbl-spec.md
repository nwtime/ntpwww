---
title: "8.3. Specific Products"
type: "archives"
---

#### 8.3.1. PC Hardware

8.3.1.1. [The CMOS RTC](#the-cmos-rtc)  
8.3.1.1.1. [How accurate is the CMOS clock?](#how-accurate-is-the-cmos-clock)  
8.3.1.1.2. [How can I set the CMOS clock?](#how-can-i-set-the-cmos-clock)  
8.3.1.2. [Enhanced Features](#enhanced-features)  
8.3.1.2.1. [How can SMM affect Interrupt Processing?](#how-can-smm-affect-interrupt-processing)  
8.3.4 [Linux](#linux)  
8.3.4.1. [Kernel Messages](#kernel-messages)  
8.3.4.1.1. [What does set_rtc_mmss: can't update from 54 to 5 mean?](#what-does-set-rtc-mmss-cant-update-from-54-to-5-mean)  
8.3.4.1.2. [What does the syslog message kernel: adjtimex: ntpd could be using obsolete ADJ_TICKADJ mean?](#what-does-the-syslog-message-kernel-adjtimex-ntpd-could-be-using-obsolete-adj-tickadj-mean)  
8.3.4.2. [Serial Port](#serial-port)   
8.3.4.2.2. [Do Multiport Serial Cards cause Trouble?](#do-multiport-serial-cards-cause-trouble)  
8.3.4.2.3. [My DCF77 Receiver gets no Power from the serial Port. Why?](#my-dcf77-receiver-gets-no-power-from-the-serial-port-why)  
8.3.4.3. [Networking](#networking)  
8.3.4.3.1. [How do I open a Firewall for NTP?](#how-do-i-open-a-firewall-for-ntp)  
8.3.4.3.2. [Why can't ntpd running on RedHat Linux talk to other Hosts?](#why-cant-ntpd-running-on-redhat-linux-talk-to-other-hosts)  
8.3.4.4. [Hardware Clock](#hardware-clock)  
8.3.4.4.1. [How can I read or write the CMOS clock?](#how-can-i-read-or-write-the-cmos-clock)  
8.3.4.4.2. [With PPSkit-0.9 my hardware clock is set to UTC; why?](#with-ppskit-09-my-hardware-clock-is-set-to-utc-why)  
8.3.4.5. [Miscellaneous](#miscellaneous)  
8.3.4.5.1. [Why does my Linux system lose several milliseconds every once in a while.](#why-does-my-linux-system-lose-several-milliseconds-every-once-in-a-while)   
8.3.7 [Solaris](#solaris)     
8.3.7.6. [What is dosyncdr?](#what-is-dosyncdr)  
8.3.7.7. [I have read some conflicting advice on the use of **tickadj -s** to ensure that the OS is not trying to synchronize the kernel clock to the Clock/calendar chip on <span class="SYSTEMITEM">Solaris</span> systems. On recent <span class="SYSTEMITEM">Solaris</span> systems, e.g. 2.5, 2.6, 7, and 8, how does one ensure that **xntpd** has full control of clock synchronization?](NTP-s-trbl-spec.htm#AEN6321)</dt>
8.3.7.8. [What causes occasional 2s Time Steps?](#what-causes-occasional-2s-time-steps)   
8.3.11. [Windows/NT Family](#windows-nt-family)  
8.3.11.1. [General](#general)   
8.3.11.1.2. [Why doesn't net time /setsntp:server synchronize the Time?](NTP-s-trbl-spec.htm#AEN6513)       

* * *

#### 8.3.1.1. The CMOS RTC

The CMOS real time clock (RTC) is responsible for preserving the date and time while the PC is turned off.

* * *

#### 8.3.1.1.1. How accurate is the CMOS clock?

Some people say the CMOS RTC is much more accurate than the timer interrupt in terms of frequency error. Actually I don't know, but I have one concrete example:

A PC used a stratum 1 server with PPS had a hardware fault, and it had been powered off for about 18 days. When running the typical frequency error was 15 to 17 PPM and when the system was rebooted the RTC clock was off by 18 seconds. That would be an error of roughly 12 PPM.

* * *

#### 8.3.1.1.2. How can I set the CMOS clock?

Basically `ntpd` only sets the system time of the operating system. Therefore setting the CMOS clock is the responsibility of the operating system and its associated tools. To make things worse, typical PC operating systems and the BIOS set the RTC to local time, while UNIX-like operating systems set the RTC to UTC.

**Example 11. Linux**

In Linux the RTC is either not updated at all, or just the minutes and seconds. The related kernel code has been revised several times, with different behaviour. Setting the system time manually does not update the RTC. Only if the `STA_UNSYNC` bit is cleared, the kernel will periodically update the RTC from the system time. Typically this happens every 11 minutes.

With the optional PPSkit-0.9.0 kernel patch the RTC is updated just like in other PC operating systems. In addition the automatic periodic update can be disabled completely (see the documentation that comes with the product).

There is also a user-space program to set the RTC, but it requires special privileges. Typically the utility is named `hwclock`.

* * *

#### 8.3.1.2. Enhanced Features

#### 8.3.1.2.1. How can SMM affect Interrupt Processing?

Let me quote an explanation written by [Poul-Henning Kamp](NTP-a-faq.htm#AU-PHK) from the newsgroup:

I was gathering some data for [Professor David L. Mills](NTP-a-faq.htm#AU-DLM) today and they looked lousy to put it mildly, every 300-400 seconds I had a 40-50 microsecond peak in my data. After some debugging I know know what it was: The SMM mode interrupts to the BIOS.

This machine is brand new, and I had never put a PPS signal on it before, it uses the PIIX4 chip from Intel and appearantly the SMM BIOS gets called at regular (but not very precise) intervals to monitor temperatures and fans and whats not.

Needless to say, this could not be disabled in the BIOS setup.

I found out I could disable the SMI output from the PIIX4 to the CPU by clearing bit zero in the `GLBCTL` register in the third function of the 82371AB chip. You need to find the IO base address from register `0x40` in the PCI header, and add the `0x28` to that address. For my motherboard that ended up being `0xe428`, your mileage will vary, and you should "Do The Right Thing" to find this location.

Needless to say, the SMM BIOS will not be able to check if your CPU is able to make toast on if you disable it this way, so you'd better know what you're doing.

* * *

#### 8.3.2. FreeBSD

#### 8.3.2.1. What is the cause for kernel: cmd ntpd pid tried to use non-present sched_setscheduler?

Depending on your options for kernel configuration, the required functions may not be included in your kernel. Unfortunately `autoconf` seems unable to detect it.

Check if these options are included in your kernel config file:

<pre>options         P1003_1B
options         _KPOSIX_PRIORITY_SCHEDULING
options         _KPOSIX_VERSION=199309L</pre>

Make sure you have done `config ; make depend ; make ; make install ; reboot`.

* * *

#### 8.3.4. Linux

#### 8.3.4.1. Kernel Messages

#### 8.3.4.1.1. What does set_rtc_mmss: can't update from 54 to 5 mean?

The function `set_rtc_mmss()` updates minutes and seconds of the CMOS clock from system time. It does not update the hour or date to avoid problems with timezones.(The Linux kernel has no idea about the effective timezone or daylight saving time.) The message shown was added to make users and implementers aware of the problem that not all time updates will succeed.

Imagine the system time is 17:56:23 while the CMOS clock is already at 18:03:45. Updating just minutes and seconds would set the hardware clock to 18:56:23, a wrong value. The solution for this problem is either to wait a few minutes, or to install a kernel patch that fixes the problem. Normally a wrong time in the hardware clock will not show up until after reboot, or maybe after APM slowed down your system.

* * *

#### 8.3.4.1.2. What does the syslog message kernel: adjtimex: ntpd could be using obsolete ADJ_TICKADJ mean?

Very short answer: Flag `MOD_NANO` has been set in the kernel by `ntpd`.

Longer answer: This message only appears if you are using the new nanokernel clock model, usually by having applied a recent PPSkit. Thus the message is coming directly from the kernel, or more precisely from `adjtimex()`. That function is used to implement `ntp_gettime()` and `ntp_adjtime()` in addition to `adjtime()`, in Linux (which was a bad design decision after all). The constant `ADJ_TICKADJ` (`0x2000`) is an extension to `ntp_adjtime()` that allows to set the value of `tickadj` (similar extensions use constants named `ADJ_OFFSET_SINGLESHOT` or `ADJ_ADJTIME`, `ADJ_TICK`).

Unfortunately that value is also used for `MOD_NANO` in the latest kernel clock algorithm. Therefore it was decided to relocate conflicting bits, thereby causing incompatibilities with old software that uses these extensions. However the decision is not critical as only very few programs use these extensions. At this point, it's also clear that the kernel can't decide whether a new program is using a new function (in which case everything is fine), or an old program is trying to use the old function (in which case the intended operation was not performed, but instead some different operation took place). In the latter case you might be in trouble with the system clock running wild.

If you really need that functionality (`ADJ_OFFSET_SINGLESHOT`, `ADJ_TICKADJ`, `ADJ_TICK`), you should recompile your application using the current `timex.h` header file. If it still fails, you'll have to recompile the C library, or write a replacement function that is linked instead of the routine from the C library.

* * *

#### 8.3.4.2. Serial Port

* * *

#### 8.3.4.2.2. Do Multiport Serial Cards cause Trouble?

Multiport serial cards are usually optimized for throughput, not for low latency. Therefore, some reference clock drivers may cause trouble.

In case you are already in trouble, and using a standard serial port is not an option, you can only try to find out what's wrong:

* `cat /proc/tty/driver/serial` will show some essential information about the serial ports.
* Depending on the driver, `ntpq`'s `cl` command may show some useful information (like the last received time code or error counters)<
* To see what `ntpd` is doing, you can use <code>strace -p <_pid_</code> to attach to `ntpd`.

* * *

#### 8.3.4.2.3. My DCF77 Receiver gets no Power from the serial Port. Why?

Somewhere in the code cleanup between NTPv3 and NTPv4, the code to set the modem lines of the serial port got lost. The port has to be set up in a special way to provide power to the receiver.

For my receiver the command `setserialbits /dev/refclock-0 -rts` turns on power while `ntpd` is running. Some receivers care about polarity, some don't. You might try substituting `-rts` with `-dtr`.

For the [RAWDCF PARSE driver]() there is a `mode 14`, that turns on power on the port, but my receiver (and others, too) had errors about every 10 seconds. I have reported the problem to the original author.

* * *

#### 8.3.4.3. Networking

#### 8.3.4.3.1. How do I open a Firewall for NTP?

Here is a solution provided by [Wolfgang Barth](NTP-a-faq.htm#AU-WB) for <span class="PRODUCTNAME">SuSE Linux 6.3</span> using the `ipchains` packet filter (originally in German):

1.  Set all default policies to `DENY`.

2.  Allow the NTP protocol on interface `ippp0`:

    <pre>$IPCHAINS -A ippp0_ou  -p UDP -s $ippp0_ip 123 --dport 123 -j ACCEPT -l
    $IPCHAINS -A ippp0_in  -p UDP -d $ippp0_ip 123 --sport 123 -j ACCEPT -l</pre>

Wolfgang writes (originally in German): "Chains <code>ippp0\__xx_</code> become active if interface `ippp0` (my Internet connection) is used. Server to server connections use port `123` exclusively. I even set DNS to `DENY`, and it still works. You only have to remember not to use `ntpq` without `-n` because otherwise it will try to resolve the address."

[Wolfgang Barth](NTP-a-faq.htm#AU-WB) also suggests the following debugging procedure:

Rules are processed beginning at the top. It's useful to have all the rules (<code>ipchains-save \> file</code>), because the logfile contains the rule numbers also. For example:

<pre>Mar 13 22:44:49 swobspace kernel: Packet log: ippp0_ou ACCEPT ippp0
PROTO=3D17 149.225.47.53:123 129.132.98.11:123 L=3D76 S=3D0x00 I=3D2201 F=
=3D0x0000
T=3D64 (#12)
Mar 13 22:44:49 swobspace kernel: Packet log: ippp0_in ACCEPT ippp0
PROTO=3D17 129.132.98.11:123 149.225.47.53:123 L=3D76 S=3D0x00 I=3D21191 =
F=3D0x4000
T=3D239 (#16)</pre>

"In chain `ippp0_ou` rule `#12` triggers the `ACCEPT`, and here's the corresponding line from the rule save file:"

<pre>-A ippp0_ou -s 149.225.25.39/255.255.255.255 123:123 -d 0.0.0.0/0.0.0.0
123:123 -p 17 -j ACCEPT -l</pre>

* * *

#### 8.3.4.3.2. Why can't ntpd running on RedHat Linux talk to other Hosts?

According to [Hal Murray](NTP-a-faq.htm#AU-HM), at least RedHat Linux 7.1 was shipped with this line in `/etc/ntp.conf`:

<pre>restrict default ignore</pre>

Thus any NTP network messages are ignored. Either remove that offending line, or selectively allow individual addresses. Usually one would use the IP address, but see how the `restrict` directive really works. Consider this fragment:

<pre>restrict default ignore
server 10.9.8.7
restrict 10.9.8.7</pre>

* * *

#### 8.3.4.4. Hardware Clock

#### 8.3.4.4.1. How can I read or write the CMOS clock?

There are several possibilities besides using the BIOS:

*   You can read the clock using `cat /proc/rtc` (if `CONFIG_RTC` is set), or `hwclock --show` (`hwclock` is a newer replacement for the older `clock` program). C programmers could use the `ioctl()` interface and `RTC_RD_TIME` (see `/usr/include/linux/mc146818rtc.h` and `/usr/src/linux/Documentation/rtc.txt`).

*   You can set the clock using either `hwclock --set` (possibly with `--utc`) or the `ioctl()` interface and `RTC_SET_TIME`.

*   The kernel will normally read the clock during boot (when it does not know the timezone yet) and when APM had been active. When the kernel PLL is used, the system time will be written to the clock periodically (see also [Q: 8.3.1.1.2.](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-HW-CLOCK) and [Q: 8.3.4.1.1.](NTP-s-trbl-spec.htm#Q-LINUX-SET-RTC-MMSS)). Setting or adjusting the time by other means will not update the hardware clock.

    However beginning with PPSkit-0.9< the hardware clock will be updated if the system time is set. You can even set up the correct timezone (see [Q: 8.3.4.4.2.](NTP-s-trbl-spec.htm#Q-LINUX-CMOS-UTC) for details).

* * *

#### 8.3.4.4.2. With PPSkit-0.9 my hardware clock is set to UTC; why?

See also [Q: 8.3.1.1.2.](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-HW-CLOCK). According to the `README` file that comes along with PPSkit-0.9, there are some new features:

*   The hardware clock's date and time is set whenever it is updated. Previously only the minutes and seconds were updated. Naturally this requires different treatment depending on whether the hardware clock is expected to run in UTC or local time.
*   The hardware clock is updated whenever the system time is set (actually it happens 0.5s after the next second begins, but that's only because of the strange hardware).
*   The interval for automatic updates of the RTC can be modified. Automatic updates can be disabled completely.

These changes were designed to make everybody happy. Therefore some new `sysctl()` functions were introduced. These variables can be accessed through files in `/proc/sys/kernel/time`:

<code>**rtc_runs_localtime**</code>
: Decides whether RTC is set to UTC or local time. A value of `0` means UTC.

<code>**rtc_update**</code>
: Determines the interval after which the RTC is updated. If the value is `0`, no automatic update happens.

<code>**timezone**</code>
: Determines the kernel timezone. This is a pair of values: The first value determines the minutes west of GMT, and the second value determines whether DST is in effect. These values are used when the kernel has to convert UTC to local time.

As up to these changes most people did not care much about the kernel's timezone, the time zone is not set correctly in many cases. There is a trick to copy the current timezone to the kernel. (This is only needed if you want your CMOS clock to keep local time instead of UTC. Also keep in mind that the timezone changes when entering or leaving Daylight Saving Time, requiring that you execute the commands for each new timezone.) I use the following code in `/sbin/init.d/boot.local` (<SuSE Linux):

<pre>timezone=$(date +%z | sed -e 's/\([0-9][0-9]\)\([0-9][0-9]\)/(60*10#\1+10#\2)/')
TIMESYSCTL=/proc/sys/kernel/time
[ -w $TIMESYSCTL/timezone ] && echo $((-$timezone)) 0 >$TIMESYSCTL/timezone
[ -w $TIMESYSCTL/rtc_runs_localtime ] && echo 1 >$TIMESYSCTL/rtc_runs_localtime</pre>

For Slackware Linux the proper place seems to be `rc.local`. (Contributed by [Richard M. Hambly](NTP-a-faq.htm#AU-RMH))

* * *

#### 8.3.4.5. Miscellaneous

#### 8.3.4.5.1. Why does my Linux system lose several milliseconds every once in a while.

You are using `/sbin/kerneld` for automatic module loading. Several modules do not take good care of the time during initialization. If you can spare the memory, please load the modules at boot time.

The original contributor remarks: "This once occured to me. The sound system was demand loaded. A small application told the time every 15 minutes (saytime running in cron). The ntp logging showed me that something strange happened every 15 minutes. I found out it was the loading of the sound module every 15 minutes."

In addition removal of modules also seems to block interrupts.

Another reason for lost interrupts are closely connected with the use of IDE drives that are operated in polled mode (PIO), and not im DMA mode. Still another reason can be a BIOS that disables interrupts when APM routines are called.

* * *

#### 8.3.6. Oncore Compatibles

#### 8.3.6.1. Will the M12 work with the Oncore driver?

It seems this product speaks a different protocol than the original hardware. To complicate matters, Gary Sanders found out that "If you got your eval kit from Synergy Systems, the PPS output on the eval board is inverted from the older Oncores(...)". To really confuse the users "(...) Synergy has a simple wiring change on the eval board to fix it. The boards that are currently shipping have this fix incorporated."

[Mark Martinec](NTP-a-faq.htm#AU-MM) contributed: "I just stumbled across the specs of the 12-channel GPS receiver Motorola Oncore M12. Its acquisition time (time to first fix) for cold start is less than 60 seconds typical. See http://www.motorola.com/ies/GPS/pdfs/m12.pdf".

* * *

#### 8.3.6.2. Why is the UT+ reporting clk_noreply?

According to the documentation driver `30` should work for the UT+ "as long as they support the Motorola Binary Protocol". Furthermore the documentation recommends: "When first starting to use the driver you should definitely review the information written to the clockstats file to verify that the driver is running correctly."

Unfortunately some essential documentation can only be found in the source file (`ntpd/refclock_oncore.c`). Some anonymous person wrote in news://comp.protocols.time.ntp:

(...) When the GPS is in (navigation mode), the driver simply discards the timestamp, resulting in the `clk_noreply`. The clock _did_ indeed reply, but the driver just threw it away with no messages to inform me about what it was doing.

(...) yes, the GPS is indeed in Naviation mode. The Oncore driver _does_ change the mode, even though the code comment quoted above says "don't do anything to change it" (mode `0`).

(...) So I start using mode `1` instead, which initializes the Oncore with a user supplied position and then switches into Position Hold mode. Now in this new mode I am _still_ getting `clk_noreply`, but now these messages are alternated with `clk_badtime`.

(...) The binary code is getting decoded just fine, I can print out hours, minutes, seconds. (...) I discover that clocktime fails because it thinks that the time offset between the GPS and my computer's clock is more than half a day!

(...) I do `ntpdate` to fix the clock, then run NTP. Hey, it works! HalleleujahPraiseTheLord.

* * *

#### 8.3.7. Solaris

#### 8.3.7.6. What is dosyncdr?

There's a kernel variable named `dosyncdr` that influences how the kernel keeps time. Generally it's neither necessary nor recommended to change the value from the default. Only in Solaris 2.5.1 (where NTP was not officially supported) it was necessary to set `dosyncdr` manually to `0`.

* * *

#### 8.3.7.7. I have read some conflicting advice on the use of tickadj -s to ensure that the OS is not trying to synchronize the kernel clock to the Clock/calendar chip on Solaris systems. On recent Solaris systems, e.g. 2.5, 2.6, 7, and 8, how does one ensure that xntpd has full control of clock synchronization?

[Michael Sinatra](NTP-a-faq.htm#AU-MS) wrote in news://comp.protocols.time.ntp:

My understanding is, after Solaris 2.6 "not necessary at all" is the correct answer. In the past you need to put `set dosynctodr=0` in `/etc/system`; now, you are NOT supposed to do that. Moreover, you are NOT supposed to use `tickadj`.

* * *

#### 8.3.7.8. What causes occasional 2s Time Steps?

After some experiments, [Thomas Schulz](NTP-a-faq.htm#AU-TS) found out:

This behavior is normal for Solaris when NTP is not running. This wandering is due to Solaris correcting the system clock from the hardware clock (the TODR). The hardware clock is assumed to be the more accurate one (and it is). This correction is done whenever the two clocks are more than about 1.5 to 2 seconds apart. You will see this behavior on any Solaris system if you wait long enough. This correction is not done if NTP is running. Of course on a system with a very bad clock this behavior will be much more obvious than on one with a better clock (no Sparc has a good clock).

* * *

#### 8.3.9. Trimble Clocks

#### 8.3.9.1. Only one Edge of my Trimble Acutime's PPS Pulse is detected

If the device uses very short pulses (like 1 microsecond), the hardware or software may have trouble processing the pulse correctly (See [Q: 8.2.2.2.](NTP-s-trbl-general.htm#Q-PPS-MISSING-EDGE) and [Q: 6.2.4.6.1.](NTP-s-config-adv.htm#Q-CONFIG-ADV-PPS-HW-SHORTEST-SERIAL-PULSE)). Recent clocks feature a programmable pulse width. Using 100 or 200 milliseconds as width will assist you finding the right edge, assuming that the first edge is the more accurate one.

* * *

#### 8.3.10. TrueTime

#### 8.3.10.1. My TrueTime box is not accepted as an NTP server

Most likely you are using NTP version 4 on your client while the firmware in your TrueTime box only knows about NTP version 3. If you are using NTP version 4 on the client, all outgoing protocol packets will also request version 4. If the server does not know about that version, these packets will simply be ignored.

1.  Use `ping` to make sure that the network configuration and connection is working.
2.  Locate and examine your NTP configuration file for `server` and `peer` statements. If your `TrueTime box only knows about version 3, add `version 3 to these lines. This will make the client use version 3 protocol packets for the specified server.
3.  You might consult the vendor of your TrueTime box about a firmware upgrade that can handle version 4 packets.

[John K. Doyle, Jr.](NTP-a-faq.htm#AU-JKD) contributed: "Another good quickie debugging technique is to point just about any Cisco brand router running just about any release of Cisco IOS (9.21 or later) at a TrueTime unit. Cisco handles (or doesn't care) the differing NTP protocol version numbers and was always happy with the TrueTime unit. This is how I knew that the TrueTime unit was OK even though `xntp` for Windows/NT said that it was unreachable."

* * *

#### 8.3.11. Windows/NT Family

This section is about the operating systems based on Windows/NT, namely Windows/NT, Windows/2000, and Windows/XP.

#### 8.3.11.1. General

#### 8.3.11.1.2. Why doesn't net time /setsntp:server synchronize the Time?

[Nicholas Jenkins](NTP-a-faq.htm#AU-NJ) contributed:

(...) The obvious key to this all; however, that doesn't appear in the Microsoft® documentation is that the W32time service is, IN FACT, *NOT* running by default! So, the simple solution to the whole problem is to just change the "startup type" of the w32time service in the "services" control panel to `automatic`, rather than `manual`. Then, either reboot, or just "start" the service, and the time will sync as nicely as you could possibly want!

* * *