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
8.3.4.2.1. [In Linux 2.2 serial events seem inaccurate. Why?](#in-linux-22-serial-events-seem-inaccurate-why)  
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
8.3.4.5.2. [It seems my DEC Alpha won't get synchronized. What's the problem?](#it-seems-my-dec-alpha-wont-get-synchronized-whats-the-problem)  
8.3.7 [Solaris](#solaris)  
8.3.7.1. [Is there some specific Support for Solaris?](#is-there-some-specific-support-for-solaris)  
8.3.7.2. [Why doesn't xntpd step the Clock in Solaris 8?](#why-doesn't-xntpd-step-the-clock-in-solaris-8)  
8.3.7.3. [Why is my Ultra-2 Server rebooting when running SunOS 5.6 and xntpd?](#why-is-my-ultra-2-server-rebooting-when-running-sunos-56-and-xntpd)  
8.3.7.4. [Why doesn't xntpd synchronize in Solaris 2.7?](#why-doesnt-xntpd-synchronize-in-solaris-27)  
8.3.7.5. [What does the message NTP user interface routines not configured in this kernel mean?](#what-does-the-message-ntp-user-interface-routines-not-configured-in-this-kernel-mean)  
8.3.7.6. [What is dosyncdr?](#what-is-dosyncdr)  
8.3.7.7. [I have read some conflicting advice on the use of **tickadj -s** to ensure that the OS is not trying to synchronize the kernel clock to the Clock/calendar chip on <span class="SYSTEMITEM">Solaris</span> systems. On recent <span class="SYSTEMITEM">Solaris</span> systems, e.g. 2.5, 2.6, 7, and 8, how does one ensure that **xntpd** has full control of clock synchronization?](NTP-s-trbl-spec.htm#AEN6321)</dt>
8.3.7.8. [What causes occasional 2s Time Steps?](#what-causes-occasional-2s-time-steps)  
8.3.7.9. [Why is xntpd using that much CPU?](#why-is-xntpd-using-that-much-cpu)  
8.3.7.10. [Why does my System think the year is 1934?](#why-does-my-system-think-the-year-is-1934)  
8.3.7.11. [Why won't ntpdate finish while booting Solaris?](#why-wont-ntpdate-finish-while-booting-solaris)  
8.3.11. [Windows/NT Family](#windows-nt-family)  
8.3.11.1. [General](#general)  
8.3.11.1.1. [Why won't NTP work on Windows/2000 running Microsoft® SQL Server?](NTP-s-trbl-spec.htm#AEN6491)  
8.3.11.1.2. [Why doesn't net time /setsntp:server synchronize the Time?](NTP-s-trbl-spec.htm#AEN6513)  
8.3.11.2. [Implementations](#implementations)  
8.3.11.2.1. [Are there any known Bugs in Windows/2000's SNTP Server?](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-WINNT-IMPL-2K)  
8.3.11.2.2. [What about Bugs in Windows/XP's SNTP Client?](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-WINNT-IMPL-XP)  
8.3.11.2.3. [I want to synchronize time from my server running Windows/NT. Is TimeServ the correct solution? Are there other applications?](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-WINNT-IMPL-NTP)  
8.3.11.2.4. [Why doesn't TimeServ synchronize to my NTP Server?](NTP-s-trbl-spec.htm#AEN6648)  
8.3.11.2.5. [Where is the Documentation for the Windows/NT Version?](NTP-s-trbl-spec.htm#AEN6664)  

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

#### 8.3.3. Irix

#### 8.3.3.1. Why won't my SGI O2 sync?

[Marc Brett](NTP-a-faq.htm#AU-MB) contributed: (...) "We're running an O2 with IRIX 6.5, and it had a horrendous clock drift." (...) All was cured by turning off NTP and `timed`, running <code>timeslave -P /var/adm/timetrim -H _timeserver_</code> for a couple of days against a server with a known good clock, and then examining `/var/adm/timetrim` for the recommended `timetrim` value. Then edit the file `/var/sysgen/mtune/kernel` with the new `timetrim` value, rebuild the kernel with `autoconfig -v`, reboot, and voila! A stable clock. Turn off `timeslave` and `timed`, turn on NTP, and all is sweetness and light."</span>

* * *

#### 8.3.4. Linux

#### 8.3.4.1. Kernel Messages

#### 8.3.4.1.1. What does set_rtc_mmss: can't update from 54 to 5 mean?

The function `set_rtc_mmss()` updates minutes and seconds of the CMOS clock from system time. It does not update the hour or date to avoid problems with timezones.[<span class="footnote">[1]</span>](NTP-s-trbl-spec.htm#FTN.AEN5808) The message shown was added to make users and implementers aware of the problem that not all time updates will succeed.

Imagine the system time is 17:56:23 while the CMOS clock is already at 18:03:45. Updating just minutes and seconds would set the hardware clock to 18:56:23, a wrong value. The solution for this problem is either to wait a few minutes, or to install a kernel patch that fixes the problem. Normally a wrong time in the hardware clock will not show up until after reboot, or maybe after APM slowed down your system.

* * *

#### 8.3.4.1.2. What does the syslog message kernel: adjtimex: _ntpd_ could be using obsolete ADJ_TICKADJ mean?

Very short answer: Flag `MOD_NANO` has been set in the kernel by `ntpd`.

Longer answer: This message only appears if you are using the new nanokernel clock model, usually by having applied a recent PPSkit. Thus the message is coming directly from the kernel, or more precisely from `adjtimex()`. That function is used to implement `ntp_gettime()` and `ntp_adjtime()` in addition to `adjtime()`, in Linux (which was a bad design decision after all). The constant `ADJ_TICKADJ` (`0x2000`) is an extension to `ntp_adjtime()` that allows to set the value of `tickadj` (similar extensions use constants named `ADJ_OFFSET_SINGLESHOT` or `ADJ_ADJTIME`, `ADJ_TICK`).

Unfortunately that value is also used for `MOD_NANO` in the latest kernel clock algorithm. Therefore it was decided to relocate conflicting bits, thereby causing incompatibilities with old software that uses these extensions. However the decision is not critical as only very few programs use these extensions. At this point, it's also clear that the kernel can't decide whether a new program is using a new function (in which case everything is fine), or an old program is trying to use the old function (in which case the intended operation was not performed, but instead some different operation took place). In the latter case you might be in trouble with the system clock running wild.

If you really need that functionality (`ADJ_OFFSET_SINGLESHOT`, `ADJ_TICKADJ`, `ADJ_TICK`), you should recompile your application using the current `timex.h` header file. If it still fails, you'll have to recompile the C library, or write a replacement function that is linked instead of the routine from the C library.

* * *

#### 8.3.4.2. Serial Port

#### 8.3.4.2.1. In Linux 2.2 serial events seem inaccurate. Why?

Between releases 2.0 and 2.2 of the Linux kernel the serial driver has been optimized for throughput. The new driver does not generate an interrupt for each character received, but instead when either the UART's receive buffer exceeds a threshold of typically ten characters, or when the next timer interrupt is scheduled.

The new default introduces an inaccuracy for received characters up to 10ms. Fortunately you can tell the driver to deliver received characters as soon as possible using the flag `ASYNC_LOW_LATENCY` for the port. The command `setserial /dev/refclock-0 low_latency` in connection with a recent release of the `setserial` utility can do that.

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

As up to these changes most people did not care much about the kernel's timezone, the time zone is not set correctly in many cases. There is a trick to copy the current timezone to the kernel.[<span class="footnote">[2]</span>](NTP-s-trbl-spec.htm#FTN.AEN6051) I use the following code in `/sbin/init.d/boot.local` (<SuSE Linux):

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

#### 8.3.4.5.2. It seems my DEC Alpha won't get synchronized. What's the problem?

(According to [John Sager](NTP-a-faq.htm#AU-JCS)) The interrupt frequency for DEC Alpha is 1024Hz. According to [Section 3.2](NTP-s-sw-clocks-tick.htm) the value of `tick` is 977µs. Unfortunately `1024*977` is `1000448`, giving an intrinsic frequency error of 448 PPM, even for a perfect crystal.[<span class="footnote">[3]</span>](NTP-s-trbl-spec.htm#FTN.AEN6098)

As not all versions of the Linux kernel and of NTP daemons can handle such a large frequency error, there may be a problem. Watch out whether your frequency seems to get stuck at some magical value (See [Section 8.1](NTP-s-trouble.htm#S-TRBL-MONITORING)). Trying the latest versions might help.

* * *

#### 8.3.5. Macintosh

#### 8.3.5.1. Which NTP/SNTP Clients exist for the Macintosh?

According to [Brian Bergstrand](NTP-a-faq.htm#AU-BB2) "If/when you upgrade to a PPC machine, OS 8.5 and above have a built in NTP client that can be activated in the Date & Time control panel."

Another product seems to be Vremya.

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

#### 8.3.7.1. Is there some specific Support for Solaris

As pointed out in [Q: 4.1.7.](NTP-s-def.htm#Q-DEF-WHICH-VERSION), some versions of NTP software are supported by the vendors directly. Others are more or less supported by the Open Source Community (read: newsgroup news://comp.protocols.time.ntp).

For vendor support try to get the Sun BluePrints™ titled _Using NTP to Control and Synchronize System Clocks_.[<span class="footnote">[4]</span>](NTP-s-trbl-spec.htm#FTN.FTN-SUN-BLUEPRINTS-NTP) NTP support is available beginning with Solaris 2.6 and ntp-3.4y. Beginning with Solaris 8 the supported version is ntp-3-5.93e, one of the last releases of NTP version 3.

#### 8.3.7.2. Why doesn't xntpd step the Clock in Solaris 8?

There's a patch, `109667` that lets `xntpd` always slew the clock. Beginning with revision 04 of the patch there is an option to turn that feature off.

* * *

#### 8.3.7.3. Why is my Ultra-2 Server rebooting when running SunOS 5.6 and xntpd?

In an article [Casper H. Dik](NTP-a-faq.htm#AU-CHD) wrote:

"The kernel `adjtimex` code is broken when it was changed to support a kernel settable hz value. You'll see a "divide by 0" trap. This happens when the `constant` value in the `timex` structure is > 6. Bug id is #4095849."

[Dirk A. Niggemann](NTP-a-faq.htm#AU-DABN) contributed (slightly adapted):

The problem is apparently fixed in Solaris 7 and 8 above a certain patch level (according to SunSolve bug-tracking docs. (...)) Minimum kernel release is s998_20 for Solaris 7 and s28_26 for Solaris 8 (again according to docs on SunSolve). All of the kernel PLL problems except for that described by Bug ID 4095849 are reputedly fixed in 2.6 kernel patch 101581-13 (current patch is 101581-22 so grab that if you need to upgrade). The interesting question is whether there is any way to test if the divide-by-zero fault panic has been fixed in this patch as well(...)

I believe these all to be public patches so people shouldn't need to have SunSolve access to get them.

[Mike Nolan](NTP-a-faq.htm#AU-MN) contributed (slightly edited):

(...) I have the following: SunOS xxxxx 5.6 Generic_105181-17 sun4m sparc SUNW,SPARCclassic running as a stratum-1 server with a PPS input (only). (...) At that patch level (from a fairly recent Recommended (free) patch cluster), the FLL bug has supposedly been fixed, and it runs somewhat better with it running. Note that the configure script doesn't check for all patchlevels automatically, so I configure with `--disable-kernel-fll-bug` by hand, after checking that the patchlevel is at least 105181-17 for 2.6 or 106541-07 for 2.7\. (...)

* * *

#### 8.3.7.4. Why doesn't xntpd synchronize in Solaris 2.7?

The `xntpd` supplied with Solaris 2.7 fails to adjust the clock frequency on a Ultra 5, but it succeeds on a SPARCstation 10. The output of `ntpq` may look like this:

<pre>status=06f4 leap_none, sync_ntp, 15 events, event_peer/strat_chg,
system="UNIX/Solaris 2.x", leap=00, stratum=2, rootdelay=3.330,
rootdispersion=33.020, peer=28188,
refid=pctick1a.dvm.klinik.uni-regensburg.de,
reftime=bc8484e2.9d718000 Thu, Mar 23 2000 12:56:18.615, poll=6,
clock=bc84850a.6a29c000 Thu, Mar 23 2000 12:56:58.414, phase=11.594,
freq=0.00, error=13.32</pre>

The following messages can be found in the syslog file:

<pre>xntpd version=3.4y (beta multicast); Fri Aug 23 19:54:40 PDT 1996 (2)
tickadj = 625, tick = 10000, tvu_maxslew = 61875
NTP user interface routines not configured in this kernel.</pre>

As it seems, it's a software problem that is related to the hardware. There is actually a patch (108338, obsoleted by patch 109409 (currently at revision 4)) that provides a different binary of `xntpd` 3.4y, and that version seems to work (contributed by [Arthur Darren Dunham](NTP-a-faq.htm#AU-ADD)). Revision 4 also contains a fix for a root vulnerability in `xntpd`.[<span class="footnote">[5]</span>](NTP-s-trbl-spec.htm#FTN.AEN6287) See also [Q: 4.1.7.](NTP-s-def.htm#Q-DEF-WHICH-VERSION).

[James Kirkpatrick](NTP-a-faq.htm#AU-JK) contributed: "Be sure to have the latest kernel patch 106541-10 or newer (fixes for some NTP issues went in at versions 9 and 4 and 1), as well as 108338 as was suggested (latest is version 1)."

* * *

#### 8.3.7.5. What does the message NTP user interface routines not configured in this kernel mean?

See [Q: 8.3.7.4.](NTP-s-trbl-spec.htm#Q-SOLARIS-XNTPD).

* * *

#### 8.3.7.6. What is dosyncdr?

There's a kernel variable named `dosyncdr` that influences how the kernel keeps time. Generally it's neither necessary nor recommended to change the value from the default. Only in Solaris 2.5.1 (where NTP was not officially supported) it was necessary to set `dosyncdr` manually to `0`.

* * *

#### 8.3.7.7. I have read some conflicting advice on the use of tickadj -s to ensure that the OS is not trying to synchronize the kernel clock to the Clock/calendar chip on Solaris systems. On recent Solaris systems, e.g. 2.5, 2.6, 7, and 8, how does one ensure that xntpd has full control of clock synchronization?

Generally see [Q: 8.3.7.6.](NTP-s-trbl-spec.htm#Q-SOLARIS-DOSYNCDR). [Michael Sinatra](NTP-a-faq.htm#AU-MS) wrote in news://comp.protocols.time.ntp:

My understanding is, after Solaris 2.6 "not necessary at all" is the correct answer. In the past you need to put `set dosynctodr=0` in `/etc/system`; now, you are NOT supposed to do that. Moreover, you are NOT supposed to use `tickadj`.

* * *

#### 8.3.7.8. What causes occasional 2s Time Steps?

After some experiments, [Thomas Schulz](NTP-a-faq.htm#AU-TS) found out:

This behavior is normal for Solaris when NTP is not running. This wandering is due to Solaris correcting the system clock from the hardware clock (the TODR). The hardware clock is assumed to be the more accurate one (and it is). This correction is done whenever the two clocks are more than about 1.5 to 2 seconds apart. You will see this behavior on any Solaris system if you wait long enough. This correction is not done if NTP is running. Of course on a system with a very bad clock this behavior will be much more obvious than on one with a better clock (no Sparc has a good clock).

* * *

#### 8.3.7.9. Why is xntpd using that much CPU?

In Solaris 2.6 there could be a problem if `xntpd` is started before `nscd`. Reversing the start order should fix the problem.

* * *

#### 8.3.7.10. Why does my System think the year is 1934?

There is a bug in `xntpd` 3.4y provided with Solaris 2.6. The problem is known as Bug Id 4237366.

* * *

#### 8.3.7.11. Why won't ntpdate finish while booting Solaris?

There is a special version of `ntpdate` in Solaris 7 and 8 that has a `-w` switch. Using that switch causes `ntpdate` to wait until a suitable NTP server has been found. If this was not the case, the `syslog` will say something like <code>NTPDATE[_549_]: waiting 300 seconds before trying again.</code>.

The fix is to either kill the `ntpdate` process, or to modify `/etc/init.d/xntpd` as needed.[<span class="footnote">[6]</span>](NTP-s-trbl-spec.htm#FTN.AEN6391)

* * *

#### 8.3.8. Sun Hardware

#### 8.3.8.1. Why is my reference clock inaccurate on an E450?

[Rainer Orth](NTP-a-faq.htm#AU-RO) explains:

This is an unfortunate consequence of the fact that Sun decided to use the Siemens 82532 ESCC (see `se(7D)`) serial controller instead of the older Zilog 8530 SCC (see `zs(7D`)) used in sun4m and the first sun4u (like Ultra 1 and 2) systems. This chip has a 32 byte FIFO, which causes this large (and varying) delay. I have an RFE open with Sun (Bug Id 4357306) to provide for an alternative low-delay mode in the se driver, since it's possible to reduce the fifo size to 1 byte. Currently, the 32 byte setting is hard-coded in the `se` driver; I hope to experiment with other settings with a driver built from Solaris 8 sources when I get around to some planned work on NTP kernel/ppsapi support for Solaris 8.

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

#### 8.3.11.1.1. Why won't NTP work on Windows/2000 running Microsoft® SQL Server?

It seems Microsoft® SQL server occupies the socket address used for NTP. These messages can be found in the event log:

* Error in RegQueryValueEx fetching IpAddress parameter: The operation completed successfully.

* create_sockets: ioctl(SIOCGIFCONF) failed: Overlapped I/O operation is in progress.

The solution is to start NTP first, even though Microsoft® SQL server will complain about not getting a port or socket.

* * *

#### 8.3.11.1.2. Why doesn't net time /setsntp:server synchronize the Time?

[Nicholas Jenkins](NTP-a-faq.htm#AU-NJ) contributed:

(...) The obvious key to this all; however, that doesn't appear in the Microsoft® documentation is that the W32time service is, IN FACT, *NOT* running by default! So, the simple solution to the whole problem is to just change the "startup type" of the w32time service in the "services" control panel to `automatic`, rather than `manual`. Then, either reboot, or just "start" the service, and the time will sync as nicely as you could possibly want!

* * *

#### 8.3.11.2. Implementations

#### 8.3.11.2.1. Are there any known Bugs in Windows/2000's SNTP Server?

According to [David Woolley](NTP-a-faq.htm#AU-DW) there are some anomalies in the implementation of SNTP in Windows/2000:

I just discovered that the office Windows 2000 domain controller and IIS machine have been configured to synchronise to our \*nix time server (`net time /setsntp:`). A quick look at their behavour raises some serious concerns:
 
* the stratum is always 2, even when the upstream server was stratum 3, and even when it has never been synchronised.
 
* `xntpd` and `ntpd` to at least 4.0.99j will synchronise to them even though they are only SNTP (and indicating a false level of reliability).


Never synchronised Windows 2000 servers respond with a zero reference time and reference ID and are ignored, even though the leap bits are valid and the stratum is 2. `ntptrace` reports a root dispersion and synchronisation distance of 1.0 in all cases, but everything else seems to report zero, which makes me wonder whether `ntptrace` has SNTP detection code that is missing from the real daemon.

The `xntpd` used was the original Windows port and the `ntpd` was a Linux port with a reduced max distance (although this is not relevant and the fact that the server sends a distance of zero would defeat this measure, anyway).

This is an `ntptrace` through two Windows 2000 machines (`goonhilly` and `hercnode1`) and a Linux machine (stock Red Hat, NTP 3(?), called `mailgate`). The firewall blocks the next hop.

<pre>ntptrace goonhilly
goonhilly.XXXXX.co.uk: stratum 2, offset -0.133238, synch distance 1.00000
hercnode1.XXXXX.co.uk: stratum 2, offset -0.141267, synch distance 1.00000
mailgate.XXXXX.co.uk: stratum 3, offset -0.018762, synch distance 0.04329
ntp1.uk.psi.net:        *Timeout*</pre>

For comparison, this is from another Red Hat box, `cvs`.

<pre>ntptrace cvs
cvs.XXXXX.co.uk: stratum 4, offset -0.020810, synch distance 0.05432
mailgate.XXXXX.co.uk: stratum 3, offset -0.021750, synch distance 0.04344
ntp1.uk.psi.net:        *Timeout*</pre>

This is a verbose trace, and after a rationalisation of the time service tree (taken from the NTP 4 Linux):

<pre>ntptrace -v goonhilly 
server 192.168.xx.xx, port 123
stratum 2, precision -7, leap 00
refid mailgate.XXXXX.co.uk delay 0.02638, dispersion 0.00000 offset -0.001865
rootdelay 0.00000, rootdispersion 1.00000, synch dist 1.00000
reference time:      be926721.7c2c2d85  Thu, Apr 26 2001 10:21:37.485
originate timestamp: be927134.9e76c8b4  Thu, Apr 26 2001 11:04:36.619
transmit timestamp:  be927134.9b90214a  Thu, Apr 26 2001 11:04:36.607
 
server 192.168.xx.xx, port 123
stratum 3, precision -17, leap 00
refid ntp1.uk.psi.net delay 0.00175, dispersion 0.00000 offset -0.002226
rootdelay 0.08713, rootdispersion 0.02473, synch dist 0.06830
reference time:      be92708a.3d74f000  Thu, Apr 26 2001 11:01:46.240
originate timestamp: be927134.a362f000  Thu, Apr 26 2001 11:04:36.638
transmit timestamp:  be927134.a3b80a9d  Thu, Apr 26 2001 11:04:36.639
 
ntp1.uk.psi.net:        *Timeout*</pre>
 
The relatively low difference between the offsets suggests that Windows/2000 does do frequency correction.

I found RFC 2030 a little confusing, especially when combined with earlier versions, but my impression is that it is trying to say that SNTP servers should send stratum 0, leap 11 unless they are directly connected to a radio clock. (...)

* * * *

#### 8.3.11.2.2. What about Bugs in Windows/XP's SNTP Client?

Possibly the problems described in [Q: 8.3.11.2.1.](NTP-s-trbl-spec.htm#Q-TRBL-SPEC-WINNT-IMPL-2K) still apply. At least the following problems are known:

*   Online help suggests that only SNTP servers may be used, but SNTP is a proper subset of NTP, so any NTP server should work.

*   The client sends a symmetric active package, indicating its willingness to synchronize the server. However, most servers are set up to require authentication for symmetric active modes, and thus will ignore the request. Despite of that, it violates RFC 2030.

[David J. Taylor](NTP-a-faq.htm#AU-DJT) contributed:

I have heard that Win2K/XP syncs correctly to many Internet NTP servers using the Microsoft® provided protocol. Indeed, if it did not, I think there would knowledge around that it was broken. NIST provide some configuration information at http://www.boulder.nist.gov/timefreq/service/pdf/win2000xp.pdf.

There are considerations about the role of the PC within the Domain that may prevent it from synchronising to a time source outside the Domain. Anyone having problems with this may wish to check the registry settings listed at: http://support.microsoft.com/default.aspx?scid=kb;EN-US;q223184.

* * * *

#### 8.3.11.2.3. I want to synchronize time from my server running Windows/NT. Is TimeServ the correct solution? Are there other applications?

[Doug Hogarth](NTP-a-faq.htm#AU-DH) wrote:

TimeServ is not a server -- it is a client (I am the author). Perhaps you just want the actual NTP binaries compiled for Windows/NT, such as a link near the bottom of http://www.five-ten-sg.com/.

Things may never be 100% clear because TimeServ (including SNTP client feature) was written before `ntpd` was ported to Windows/NT (if it had been ported then I wouldn't have too much need for writing TimeServ). Also the current version of Windows/NT (Windows/2000) includes built-in time service which can be SNTP client (and server, if configured appropriately) - so MS basically suggested that I stop working on TimeServ around 1.5 years ago.

* * *

#### 8.3.11.2.4. Why doesn't TimeServ synchronize to my NTP Server?

Specifically if the error "NetRemoteTOD failed for each PrimarySource" occurs [Doug Hogarth](NTP-a-faq.htm#AU-DH) says: "Most likely reason for that error message is that your `.ini` file is in the wrong directory (typically it belongs in `c:\winnt`, don't forget to `timeserv -update` and restart the time service after correcting it). I am the author of TimeServ, feel free to email me if you have further questions - http://www.niceties.com/TimeServ.html.

* * *

#### 8.3.11.2.5. Where is the Documentation for the Windows/NT Version?

Actually there is no special documentation for Windows/NT (AFAIK). Despite that, the popular binary distribution seems to come without the HTML documentation from the source distribution. To make things worse, the URL found in the `README` file is rather unspecific.

Unless there is additional documentation it's recommended to get and unpack the source archive. The files you want can be found in the `html` subdirectory.

* * *

### Notes

[<span class="footnote">[1]</span>](NTP-s-trbl-spec.htm#AEN5808)</td>

<td width="95%" valign="TOP" align="LEFT">

The Linux kernel has no idea about the effective timezone or daylight saving time.

[<span class="footnote">[2]</span>](NTP-s-trbl-spec.htm#AEN6051)

This is only needed if you want your CMOS clock to keep local time instead of UTC. Also keep in mind that the timezone changes when entering or leaving Daylight Saving Time, requiring that you execute the commands for each new timezone.

[<span class="footnote">[3]</span>](NTP-s-trbl-spec.htm#AEN6098)

Compaq Tru64 UNIX (alias Digital Unix or OSF/1 solves the problem by adding 976µs 1023 times, and 1552µs once per second. The newer Linux PPSkit uses fractional nanoseconds for smoothness.

[<span class="footnote">[4]</span>](NTP-s-trbl-spec.htm#FTN-SUN-BLUEPRINTS-NTP)

There was some statement that the following hyperlinks should be rather stable over time:

*   Part I: http://www.sun.com/blueprints/0701/NTP.pdf
*   Part II: http://www.sun.com/blueprints/0801/NTPpt2.pdf
*   Part III: http://www.sun.com/blueprints/0901/NTPpt3.pdf

[<span class="footnote">[5]</span>](NTP-s-trbl-spec.htm#AEN6287)

The PatchFinder on the SunSolve Website does not recognize this as a valid patch id, but it is available on SunSolve ftp site at ftp://sunsolve.sun.com/pub/patches/.

[<span class="footnote">[6]</span>](NTP-s-trbl-spec.htm#AEN6391)

This answer is derived from [James Kirkpatrick](NTP-a-faq.htm#AU-JK)'s article 39F749F7.AE04E01E@uwyo.edu in news://comp.protocols.time.ntp.