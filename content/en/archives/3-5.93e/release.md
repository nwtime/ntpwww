---
title: "Release Notes"
type: archives
---

The following changes are in the version 3-5.85 distribution relative to the previous 3.5f version.

1.  The automatic build procedure has been replaced with GNU <tt>autoconfigure</tt>. This should make porting to nonstandard machines and operating systems much easier and should simplify the maintenance for multi-architecture sites. See the <tt>./WHERE-TO- START/</tt>, <tt>./INSTALL</tt> and <tt>./README</tt> files for a brief overview of the new building and installing procedures. See the building and installing pages in the HTML documentation for further information.
2.  A clock driver (type 11) is included for the Arbiter 1088A/B GPS Receiver.
3.  The Windows NT build procedure is changed. See the <tt>./util/wininstall</tt> directory for further information.
4.  A clock driver (type 11) is included for the Arbiter 1088A/B GPS Receiver.
5.  The HTML documentation has been edited and updated to correct outdated information and minor typographical errors. A new page has been added for the Arbiter 1088A/B GPS Receiver.
6.  The <tt>xntpd</tt> daemon now calculates the authentication delay automatically, so it no longer needs to be specified for each architecture and operating system. The <tt>-e</tt> command-line switch has been removed from the <tt>xntpd</tt> program. The <tt>authdelay</tt> configuration option has been removed.
7.  The <tt>auth</tt>, <tt>monitor</tt>, <tt>pll</tt> and <tt>stats</tt> flags are enabled by default. The <tt>bclient</tt> and <tt>pps</tt> flags are disabled by default.

The following changes are in the version 3.5f distribution relative to the previous 3.4y version.

1.  Please note the scripts for configuring radio clock drivers do not work. See the building and installing documentation for specific information.
2.  The documentation has been completely reworked in HTML format suitable for web browsing.
3.  The automatic build procedure has been improved to
    *   support the line disciplines, streams modules and precision time kernel modifications. These are controlled by the presence of certain system-dependent header files in the <tt>/usr/include/sys</tt> directory.
    *   include by default all reference clock drivers known to work with each combination of hardware and operating system. (The particular defaults are specified in the <tt>../machines</tt> files for each machine.)
    *   activate precision time kernel modifications by default if detected by the build procedure. (Previous versions required an undocumented addition to the <tt>ntp.drift</tt> file in order to activate these modifications.)
4.  Three TrueTime reference clock drivers, which did slightly different things with each model, have been replaced with one driver (type 5) that works with all models. Two new reference clock drivers have been added, one for the Bancomm IRIG interface, the other for the TrueTime GPS-VME interface. Both of these work only with the HP architecture.
5.  There is a new <tt>pps</tt> option to the <tt>xntpdc</tt> program and configuration file <tt>enable/disable</tt> command, which enables or disables the PPS precision time control signal for both the PPS clock driver and kernel PPS interface, where available. This is primarily intended for situations where external equipment has malfunctioned or the signal has become excessively noisy.
6.  The <tt>precision</tt> configuration file command and <tt>xntpdc</tt> command have been removed; the precision variable quantity is now determined automatically and cannot be changed.
7.  The <tt>authenticate</tt> and <tt>monitor</tt> commands in <tt>xntpdc</tt> have been removed; the functions formerly provided by these commands are now provided by the <tt>enable</tt> and <tt>disable</tt> commands.
8.  Fixed minor problems peculiar to different machines and system environments. Fixed minor problem in the PPS interfaces and mitigation rules. See the ./patches directory for details.

Version 3.5 has been compiled and run on at least the following machines, operating systems and compilers. In all known cases, if the gcc compiler eats it with some success, the cc compiler also enjoys the meal; the converse is not always true. Note that, while all clock drivers have been compiled, only certain ones have been tested with each machine and operating system.

Previous versions have been compiled and run on at least the following machines, operating systems and compilers.

<pre>Machine   OS             Comp Notes
------------------------------------------------------------
A/UX      2.0.1, 3.x.x   gcc  LOCAL_CLOCK    (jmj (94/01/26 see hints)
AIX       3.2            ?    ?
Alpha     OSF/1 1.2a     gcc  no REFCLOCK         (dm 93/11/20)
Alpha     OSF/1 1.3      gcc  no REFCLOCK         (pb 93/10/25)
Alpha     OSF/1 2.0      gcc  no REFCLOCK         (dm 94/10/10)
Alpha     OSF/1 3.0      gcc  no REFCLOCK         (dm 95/07/15)
Alpha     OSF/1 3.2      gcc  all clock drivers (dm 96/02/07)
Convex    Convex OS 10.1 ?    ?
HP3xx     HPUX 9.01      cc   no REFCLOCK         (pb 93/10/25)
HP3xx     HPUX 8.0       cc   no REFCLOCK         (pb 93/10/25)
HP7xx     HPUX 9.0       cc   no REFCLOCK
hp7xx     HPUX 9.01      cc   local + PARSE       (kd 93/10/26)
hp7xx     HPUX 9.03      cc   all REFCLOCK drivers (dm 95/07/15)
HP7xx     HPUX 9.04      gcc  all clock drivers   (uw 96/02/21)
PC        Linux 1.3.59   gcc  (pb1 96/02/10)
MIPS      Ultrix 3a      gcc  green               (pb 93/10/26)
MIPS      Ultrix 4.3a    gcc  all REFCLOCK drivers (dm 93/11/20)
MIPS      Ultrix 4.4     gcc  all clock drivers (dm 96/02/07)
MX500     Sinix-m V5.40  cc   PARSE REFCLOCK
NCR3445   NCR SVR4       cc   LOCAL_CLOCK         (tm 93/11/29)
PC        BSD/386 1.0    gcc  possibly see "build problems"
PC        BSDI 2.0.1     gcc  (pb 96/02/18)
PC        Dell SVR4 v2.2 gcc  ?                   (tl 93/12/30)
PC        FreeBSD        gcc  LOCAL_CLOCK         see "build problems"
PC        NetBSD?        gcc  possibly see "build problems"
PC        Linux (pl14)   gcc  LOCAL_CLOCK         (dw 93/10/30)
PC        Unixware1/SVR4 cc   no tickadj, ?       (ras 93/04/11)
PC        WindowsNT 3.5  VisualC++2.0 no REFCLOCK (vb 95/04/11)
RS6000    AIX 3.2        gcc  no REFCLOCK
S2000     Sequent PTX 1.4 cc  LOCAL_CLOCK         (kd 93/11/10)
S2000     Sequent PTX 1.4 gcc LOCAL_CLOCK         (kd 93/11/10)
SGI       IRIX 4.0.5F    gcc  no REFCLOCK         (pb 93/11/10)
SGI       IRIX 5.3       cc   all clock drivers (dm 96/02/20)
Sun3      SunOS 4.1.1    gcc  no REFCLOCK         (pb 93/10/25)
Sun4      SunOS 4.1.1    gcc  all clock drivers   (dm 96/02/07)
Sun4      SunOS 4.1.3    gcc  all clock drivers   (dm 96/02/07)
Sun4      SunOS 5.1      gcc  no REFCLOCK         (pb 93/10/25)
Sun4      SunOS 5.2      gcc  no REFCLOCK         (dm 93/11/20)
Sun4      SunOS 5.3      gcc  all clock drivers   (dm 96/02/07)
Sun4      SunOS 5.4      gcc  all clock drivers   (dm 96/02/07)
Sun4      SunOS 5.5      ?    all clock drivers   (ao 96/02/16)
VAX-11    4.3 Tahoe      cc   all clock drivers   (dm 96/02/20)

vb: Viraj Bais <vbais@mailman1.intel.com>
pb1: Paolo Bevilacqua <pab@uni.net>
pb: Piete Brooks
dw: Torsten Duwe <duwe@informatik.uni-erlangen.de>
bf: Bill Foster <bill@kryten.kryten.com>
jmj: Jim Jagielski <jim@jagubox.gsfc.nasa.gov>
kd: Frank Kardel
tl: Tony Lill <ajlill@tlill.hookup.net>
dm: David Mills <mills@udel.edu>
tm: Tom Moore <Tom.Moore@DaytonOH.NCR.COM>
ao: Alexandre Oliva <oliva@dcc.unicamp.br>
ras: Ray Schnitzler <schnitz@unipress.com>
uw: Ulrich Windl <Ulrich.Windl@rz.uni-regensburg.de>
</pre>