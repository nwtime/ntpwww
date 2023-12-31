---
title: "Configuration Options"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Basic Configuration Options - the <tt>configure</tt> utility

The following options are for compiling and installing a working version of the xntp3 distribution. In most cases, the build process is completely automatic. In some cases where memory space is at a premium, or the binaries are to be installed in a different place, it is possible to tailor the configuration to remove such features as reference clock driver support, debugging support, and so forth.

Configuration options are specified as arguments to the <code>configure</code> script. Following is a summary of the current options:

Usage: <code>configure [options] [host]</code>  
Options: [defaults in brackets after descriptions]

<pre>Configuration

  --cache-file=FILE      cache test results in FILE
  --help                 print this message
  --no-create            do not create output files
  --quiet, --silent      do not print `checking...' messages
  --version              print the version of autoconf that created
                         configure
Directory and file names

  --prefix=PREFIX        install architecture-independent files in
                         PREFIX [/usr/local]
  --exec-prefix=EPREFIX  install architecture-dependent files in EPREFIX
                         [same as prefix]
  --bindir=DIR           user executables in DIR [EPREFIX/bin]
  --sbindir=DIR          system admin executables in DIR [EPREFIX/sbin]
  --libexecdir=DIR       program executables in DIR [EPREFIX/libexec]
  --datadir=DIR          read-only architecture-independent data in DIR
                         [PREFIX/share]
  --sysconfdir=DIR       read-only single-machine data in DIR
                         [PREFIX/etc]
  --sharedstatedir=DIR   modifiable architecture-independent data in DIR
                         [PREFIX/com]
  --localstatedir=DIR    modifiable single-machine data in DIR
                         [PREFIX/var]
  --libdir=DIR           object code libraries in DIR [EPREFIX/lib]
  --includedir=DIR       C header files in DIR [PREFIX/include]
  --oldincludedir=DIR    C header files for non-gcc in DIR
                         [/usr/include]
  --infodir=DIR          info documentation in DIR [PREFIX/info]
  --mandir=DIR           man documentation in DIR [PREFIX/man]
  --srcdir=DIR           find the sources in DIR [configure dir or ..]
  --program-prefix=PREFIX prepend PREFIX to installed program names
  --program-suffix=SUFFIX append SUFFIX to installed program names
  --program-transform-name=PROGRAM run sed PROGRAM on installed program
                         names
Host type

  --build=BUILD          configure for building on BUILD [BUILD=HOST]
  --host=HOST            configure for HOST [guessed]
  --target=TARGET        configure for TARGET [TARGET=HOST]
Features and packages

  --disable-FEATURE      do not include FEATURE (same as --enable-
                         FEATURE=no)
  --enable-FEATURE[=ARG] include FEATURE [ARG=yes]
  --with-PACKAGE[=ARG]   use PACKAGE [ARG=yes]
  --without-PACKAGE      do not use PACKAGE (same as --with-PACKAGE=no)
  --x-includes=DIR       X include files are in DIR
  --x-libraries=DIR      X library files are in DIR

--enable- and --disable- with options recognized

     debugging           Include debugging code [enable]
     gdt-surveying       Include GDT survey code [disable]
     md5                 Include support for MD5 keys [enable]
     des                 Include support for DES keys [enable]
     all-clocks          Include drivers for all reference clocks
                         [enable]

  Radio Clocks (these are ordinarily enabled, if supported by the
                         machine and operating system)

     ACTS                NIST dialup clock
     ARBITER             Arbiter 1088A/B GPS receiver
     AS2201              Austron 2200A or 2201A GPS receiver
     ATOM                ATOM clock
     BANCOMM             BANCOMM clock
     CHU                 CHU clock
     DATUM               Datum Programmable Time System
     DCF7000             ELV/DCF7000
     GPSVME              GPS-VME Clock
     HEATH               HeathKit GC-1000 Most Accurate Clock
     HOPF6021            HOPF6021 Radio Clock support
     HPGPS               HP 58503A GPS Time & Frequency receiver
     IRIG                IRIG (Audio) Clock
     LEITCH              Leitch CSD 5300 Master Clock System Driver
     LOCAL-CLOCK         Local Clock driver
     MEINBERG            Meinberg clocks
     MSFEES              MSFEES clock
     MOTO                Motorola GPS clock
     MX4200              MX4200 clock
     NMEA                NMEA GPS clock
     PARSE               PARSE clock code
     PST                 PST/Traconex 1020 WWV/H receiver
     PTBACTS             PTB dialup clock support
     RAWDCF              use raw DCF77 time code
     RCC8000             RCC8000 Radio Clock support
     SCHMID              SCHMID DCF77 clock support
     TRAK                TRAK 8810 GPS station clock
     TPRO                KSI/Odetics TPRO/S IRIG Interface
     TRIMTAIP            Trimble GPS/TAIP Protocol
     TRIMTSIP            Trimble GPS/TSIP Protocol
     TRUETIME            Kinemetrics/TrueTime (generic) receiver
     WWVB                Spectracom 8170 or Netclock/2 WWVB receiver
     USNO                US Naval Observatory dialup clock

  Miscellany

     accurate-adjtime    The adjtime() call is accurate
     kmem                Read kmem
     tick=VALUE          Force a value for 'tick'
     tickadj=VALUE       Force a value for 'tickadj'
     udp-wildcard        Use UDP wildcard delivery
     slew-always         Always slew the time
     step-slew           Step and slew the time
     ntpdate-step        If ntpdate should step the time
     hourly-todr-sync    If we should sync TODR hourly
</pre>