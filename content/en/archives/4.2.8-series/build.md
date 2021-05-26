---
title: "Building and Installing the Distribution"
type: archives
---

![gif](/archives/pic/beaver.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/%7emills/pictures.html)

For putting out compiler fires.

Last update: 1-Apr-2015 02:57

* * *

#### Table of Contents

*   [Building and Installing the Distribution](/archives/4.2.8-series/build/#building-and-installing-the-distribution)
*   [Building and Installing for Unix](/archives/4.2.8-series/build/#building-and-installing-for-unix)
*   [Building and Installing for Windows](/archives/4.2.8-series/build/#building-and-installing-for-windows)
*   [Configuration](/archives/4.2.8-series/build/#configuration)
*   [If You Have Problems](/archives/4.2.8-series/build/#if-you-have-problems)
*   [Additional <tt>make</tt> Commands](/archives/4.2.8-series/build/#additional-ttmakett-commands)

* * *

#### Building and Installing the Distribution

It is not possible in a software distribution such as this to support every individual computer and operating system with a common executable, even with the same system but different versions and options. Therefore, it is necessary to configure, build and install for each system and version. In almost all cases, these procedures are completely automatic, The user types <tt>./configure</tt>, and <tt>make install</tt> in that order and the autoconfigure system does the rest. There are some exceptions, as noted below and on the [Hints and Kinks](/archives/4.2.8-series/hints) pages.

If available, the [OpenSSL library](https://www.openssl.org) is used to support public key cryptography. The library must be built and installed prior to building NTP. The procedures for doing that are included in the OpenSSL documentation. The library is found during the normal NTP configure phase and the interface routines compiled automatically. Only the <tt>libcrypto.a</tt> library file and <tt>openssl</tt> header files are needed. If the library is not available or disabled, this step is not required.

The [Build Options](/archives/4.2.8-series/config) page describes a number of options that determine whether debug support is included, whether and which reference clock drivers are included and the locations of the executables and library files, if not the default. By default debugging options and all reference clock drivers are included.

* * *

#### Building and Installing for Unix

This distribution uses common compilers and tools that come with most Unix distributions. Not all of these tools exist in the standard distribution of modern Unix versions (compilers are likely to be an add-on product). If this is the case, consider using the GNU tools and <tt>gcc</tt> compiler included as freeware in some systems. For a successful build, all of these tools should be accessible via the current path.

The first thing to do is uncompress the distribution and extract the source tree. In the distribution base directory use the <tt>./configure</tt> command to perform an automatic configuration procedure. This command inspects the hardware and software environment and configures the build process accordingly. Use the <tt>make</tt> command to compile and link the distribution and the <tt>install</tt> command to install the executables by default in <tt>/usr/local/bin</tt>.

If your site supports multiple architectures and uses NFS to share files, you can use a single source tree to build executables for multiple architectures. While running on a particular architecture, change to the base directory and create a subdirectory using a command like <tt>mkdir A.machine,</tt> which will create an architecture-specific directory, then change to this directory and mumble <tt>../configure</tt>. The remaining steps are the same whether building in the base directory or in the subdirectory.

* * *

#### Building and Installing for Windows

NTP supports Windows 2000 and later. See the [Windows NT](/archives/hints/winnt) page for directions to compile the sources and install the executables. A precompiled executable is available.

* * *

#### Configuration

You are now ready to configure the daemon. You will need to create a NTP configuration file by default in <tt>/etc/ntp.conf.</tt> Newbies should see the [Quick Start](/archives/4.2.8-series/quick) page for orientation. Seasoned veterans can start with the [<tt>ntpd</tt> - Network Time Protocol (NTP) daemon](/archives/4.2.8-series/ntpd) page and move on to the specific configuration option pages from there.

* * *

#### If You Have Problems

If you have problems with your hardware and software environment (e.g. operating system-specific issues), browse the [Hints and Kinks](/archives/4.2.8-series/hints) pages. For other problems a tutorial on debugging technique is in the [NTP Debugging Technique](/archives/4.2.8-series/debug) page. A list of important system log messages is on the [<tt>ntpd</tt> System Log Messages](/archives/4.2.8-series/msyslog) page.

The first line of general assistance is the NTP web site [www.ntp.org](http://www.ntp.org) and the helpful documents resident there. Requests for assistance of a general nature and of interest to other timekeepers should be sent to the NTP newsgroup comp.protocols.time.ntp.

Users are invited to report bugs and offer suggestions via the [NTP Bug Reporting Procedures](/archives/4.2.8-series/bugs) page.

* * *

#### Additional <tt>make</tt> commands

<dl>

<dt><tt>make clean</tt></dt>

<dd>Cleans out object files, programs and temporary files.</dd>

<dt><tt>make distclean</tt></dt>

<dd>Does the work of <tt>clean</tt>, but cleans out all directories in preparation for a new distribution release.</dd>

<dt><tt>make dist</tt></dt>

<dd>Does the work of <tt>make distclean</tt>, but constructs compressed tar files for distribution. You must have GNU automake to perform this function.</dd>

</dl>

* * *