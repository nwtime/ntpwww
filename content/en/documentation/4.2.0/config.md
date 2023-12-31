---
title: "Configuration Options"
type: archives
noindex: true 
sitemap_exclude: true
---


![gif](/documentation/pic/pogo3a.gif)[from _Pogo_, Walt Kelly](/reflib/pictures/)

Gnu autoconfigure tools are in the backpack.

* * *

#### Table of Contents

*   [Basic Configuration Options - the <tt>configure</tt> utility](/documentation/4.2.0/config/#basic-configuration-options---the-ttconfigurett-utility)
*   [Options](/documentation/4.2.0/config/#options)
*   [Directory and File Names](/documentation/4.2.0/config/#directory-and-file-names)
*   [Host Type](/documentation/4.2.0/config/#host-type)
*   [Optional Packages](/documentation/4.2.0/config/#optional-packages)
*   [Optional Features](/documentation/4.2.0/config/#optional-features)
*   [Radio Clocks](/documentation/4.2.0/config/#radio-clocks)
*   [PARSE Clocks](/documentation/4.2.0/config/#parse-clocks)

* * *

#### Basic Configuration Options - the <tt>configure</tt> utility

The following options are for compiling and installing a working version of the NTP distribution. In most cases, the build process is completely automatic. In some cases where memory space is at a premium, or the binaries are to be installed in a different place, it is possible to tailor the configuration to remove such features as reference clock driver support, debugging support, and so forth.

Configuration options are specified as arguments to the <code>configure</code> script. Following is a summary of the current options, as of the 4.0.99m version:

Usage: <code>configure [options] [host]</code>  

#### Options

Defaults are in brackets after descriptions. 

Configuration:

<pre> --cache-file=FILE      cache test results in FILE
 --help                 print this message
 --no-create            do not create output files
 --quiet, --silent      do not print `checking...' messages
 --version              print the version of autoconf that created configure
</pre>

#### Directory and File Names

<pre> --prefix=PREFIX        install architecture-independent files in PREFIX [/usr/local]
 --exec-prefix=EPREFIX  install architecture-dependent files in EPREFIX [same as prefix]
 --bindir=DIR           user executables in DIR [EPREFIX/bin]
 --sbindir=DIR          system admin executables in DIR [EPREFIX/sbin]
 --libexecdir=DIR       program executables in DIR [EPREFIX/libexec]
 --datadir=DIR          read-only architecture-independent data in DIR [PREFIX/share]
 --sysconfdir=DIR       read-only single-machine data in DIR [PREFIX/etc]
 --sharedstatedir=DIR   modifiable architecture-independent data in DIR [PREFIX/com]
 --localstatedir=DIR    modifiable single-machine data in DIR [PREFIX/var]
 --libdir=DIR           object code libraries in DIR [EPREFIX/lib]
 --includedir=DIR       C header files in DIR [PREFIX/include]
 --oldincludedir=DIR    C header files for non-gcc in DIR [/usr/include]
 --infodir=DIR          info documentation in DIR [PREFIX/info]
 --mandir=DIR           man documentation in DIR [PREFIX/man]
 --srcdir=DIR           find the sources in DIR [configure dir or ..]
 --x-includes=DIR       X include files are in DIR
 --x-libraries=DIR      X library files are in DIR
 --program-prefix=PREFIX           prepend PREFIX to installed program names
 --program-suffix=SUFFIX           append SUFFIX to installed program names
 --program-transform-name=PROGRAM  run sed PROGRAM on installed program names
</pre>

#### Host Type

<pre> --build=BUILD          configure for building on BUILD [BUILD=HOST]
 --host=HOST            configure for HOST [guessed]
 --target=TARGET        configure for TARGET [TARGET=HOST]
</pre>

#### Optional Packages

<pre> --with-PACKAGE[=ARG]   use PACKAGE [ARG=yes]
 --without-PACKAGE      do not use PACKAGE (same as --with-PACKAGE=no)

 openssl-libdir=DIR     OpenSSL object code libraries in DIR [/usr/lib/usr/local/lib/usr/local/ssl/lib]
 openssl-incdir=DIR     OpenSSL header files in DIR [/usr/include/usr/local/include/usr/local/ssl/include]
 crypto=autokey         Use autokey cryptography
 crypto=rsaref          Use the RSAREF library
 electricfence          Compile with ElectricFence malloc debugger
</pre>

#### Optional Features

<pre> --disable-FEATURE      do not include FEATURE (same as
 --enable-FEATURE=no)
 --enable-FEATURE[=ARG] include FEATURE [ARG=yes]

 accurate-adjtime       The adjtime() call is accurate
 clockctl               use /dev/clockctl (non root control of system clock)
 debugging              Include debugging code [enable]
 des                    Include support for DES keys [enable]
 dst-minutes=VALUE      Minutes per DST adjustment [60]
 gdt-surveying          Include GDT survey code [disable]
 hourly-todr-sync       If we should sync TODR hourly
 kernel-fll-bug         If we should avoid a (Solaris) kernel FLL bug
 kmem                   Read /dev/kmem for 'tick' and/or 'tickadj'
 md5                    Include support for MD5 keys [enable]
 ntpdate-step           If ntpdate should step the time
 slew-always            Always slew the time
 step-slew              Step and slew the time
 tick=VALUE             Force a value for 'tick'
 tickadj=VALUE          Force a value for 'tickadj'
 udp-wildcard           Use UDP wildcard delivery
</pre>

#### Radio Clocks

These are ordinarily enabled, if supported by the machine and operating system:

<pre> all-clocks             Include drivers for all suitable non-PARSE clocks [enable]
 ACTS                   NIST dialup clock
 ARBITER                Arbiter 1088A/B GPS receiver
 ARCRON_MSF             Arcron MSF receiver
 AS2201                 Austron 2200A or 2201A GPS receiver
 ATOM                   ATOM PPS interface
 AUDIO-CHU              CHU audio decoder
 BANCOMM                Datum/Bancomm BC635/VME interface (requires an explicit --enable-BANCOMM request)
 CHRONOLOG              Chrono-log K-series WWVB receiver
 CHU                    CHU modem decoder
 DATUM                  Datum Programmable Time System
 DUMBCLOCK              Dumb generic hh:mm:ss local clock
 FG                     Forum Graphic GPS
 GPSVME                 TrueTime GPS receiver with VME interface (requires an explicit --enable-GPSVME request)
 HEATH                  HeathKit GC-1000 Most Accurate Clock
 HOPFPCI                HOPF 6039 PCI board
 HOPFSERIAL             HOPF serial clock device
 HPGPS                  HP 58503A GPS Time & Frequency receiver
 IRIG                   IRIG (Audio) Clock
 JUPITER                Rockwell Jupiter GPS receiver
 LEITCH                 Leitch CSD 5300 Master Clock System Driver
 LOCAL-CLOCK            Local clock driver
 MSFEES                 EES M201 MSF receiver
 MX4200                 Magnavox MX4200 GPS receiver
 NMEA                   NMEA GPS receiver
 ONCORE                 Motorola VP/UT Oncore GPS receiver
 PALISADE               Palisade clock
 PCF                    Conrad parallel port radio clock
 PST                    PST/Traconex 1020 WWV/H receiver
 PTBACTS                PTB dialup clock support
 SHM                    Clock attached through shared memory (requires an explicit --enable-SHM request)
 SPECTRACOM             Spectracom 8170/Netclock/2 WWVB receiver
 TRAK                   TRAK 8810 GPS station clock
 TPRO                   KSI/Odetics TPRO/S IRIG Interface
 TRUETIME               Kinemetrics/TrueTime (generic) receiver
 ULINK                  Ultralink WWVB receiver
 USNO                   US Naval Observatory dialup clock
 WWV                    WWV audio receiver
</pre>

#### PARSE Clocks

<pre> parse-clocks           Include drivers for all suitable PARSE clocks [enable]
 COMPUTIME              Diem Computime Radio Clock
 DCF7000                ELV/DCF7000 Clock
 HOPF6021               HOPF 6021 Radio Clock support
 MEINBERG               Meinberg clocks
 RAWDCF                 DCF77 raw time code
 RCC8000                RCC 8000 Radio Clock support
 SCHMID                 SCHMID DCF77 clock support
 TRIMTAIP               Trimble GPS/TAIP Protocol
 TRIMTSIP               Trimble GPS/TSIP Protocol
 VARITEXT               VARITEXT clock
 WHARTON                Wharton 400A Series clock
</pre>
