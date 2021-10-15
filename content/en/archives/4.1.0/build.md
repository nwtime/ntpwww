---
title: "Building and Installing the Distribution"
type: archives
---

![gif](/archives/pic/beaver.gif)[from _Pogo_, Walt Kelly](/reflib/pictures)

For putting out compiler fires.

* * *

#### Table of Contents

*   [Building and Installing the Distribution](/archives/4.1.0/build/#building-and-installing-the-distribution)
*   [Building and Installing under Unix](/archives/4.1.0/build/#building-and-installing-under-unix)
*   [Compilation](/archives/4.1.0/build/#compilation)
*   [Installation](/archives/4.1.0/build/#installation)
*   [Configuration](/archives/4.1.0/build/#configuration)
*   [If You Have Problems](/archives/4.1.0/build/#if-you-have-problems)
*   [Additional <tt>make</tt> Commands](/archives/4.1.0/build/#additional-ttmakett-commands)
*   [Building and Installing Under Windows NT](/archives/4.1.0/build/#building-and-installing-under-windows-nt)

* * *

#### Building and Installing the Distribution

As a practical matter, every computer architecture and operating system version seems to be different than any other. The device drivers may be different, the input/output system may be idiosyncratic and the libraries may have different semantics. It is not possible in a software distribution such as this one to support every individual sysdtem with a common set of binaries, even with the same system but different versions. Therefore, it is necessary to configure each system individually for each system and version, both at compile time and at run time. In almost all cases, these procedures are completely automatic and all the newbie user need do is type `make` and the autoconfigure system does the rest. There are some exceptions, as noted below.

Some programs included in this distribution use cryptographic algorithms to verify server authenticity and credentials. As required by the International Trade in Arms Regulations (ITAR), now called the Defense Trade Regulations (DTR), certain cryptographic products and media, including the Data Encryption Standard (DES), cannot be exported without per-instance license. For this reason, the DES encryption routine has been removed from the current version, even though it is used only to compute a message digest. Current DTR regulations allow export of the MD5 message digest routine, which is in fact the preferred algorithm, and this is included in the current version.

The NTP authentication routines conform to the interface used by RSA Laboratories in the <code>rsaref20.zip</code> package, which was formerly downloadable from <code>ftp.rsa.com</code> or via the web at <code>www.rsa.com</code>, but this may no longer be the case. Outside the US and Canada, the functionally identical <code>rsaeuro.zip</code> package is available from J.S.A. Kapp and other sources. The recommended way to integrate the routines in either package with the NTP build procedures is to uncompress and extract the <code>rsaref20</code> files in a top level directory with that name. Then install a link to that directory from <code>rsaref2</code> in the top level directory of the distribution. Use <code>rsaeuro1</code> instead for that distribution. These steps must be completed
before the configuration process described below.</p>

* * *

#### Building and Installing Under Unix

Make sure that you have all necessary tools for building executables. These tools include <code>cc/gcc</code>, <code>make</code>, <code>awk</code>, <code>sed</code>, <code>tr</code>, <code>sh</code>, <code>grep</code>, <code>egrep</code> and a few others. Not all of these tools exist in the standard distribution of modern Unix versions (compilers are likely to be an add-on product - consider using the GNU tools and <code>gcc</code> compiler in this case). For a successful build, all of these tools should be accessible via the current path.

The first thing to do is uncompress the distribution and extract the source tree. Use the <code>./configure</code> command to perform an automatic configuration procedure. This command inspects the hardware and software environment and tests for the presence of system header files and the contents of these files to determine if certain features are present. When one or more of these features are present, the code is compiled to use them; if not, no special code is compiled. However, even if the code is compiled to use these features, the code does a special test at run time to see if one or more are actually present and avoids using them if not present. In such cases a warning message is sent to the system log, but the daemon should still work properly.

The default build normally includes the debugging code, which can be useful in diagnosing problems found in initial test, and all reference clock drivers known to work with each machine and operating system. Unless memory space is at a premium, this is a sensible strategy and saves lots of messy fiddling. If you need to delete either the debugging code or one or all reference clock drivers to save space, see the [Configuration Options](/archives/4.1.0/config) page.

If your site supports multiple architectures and uses NFS to share files, you can use a single source tree to compile executables for all architectures. While running on a target architecture machine and in the distribution base directory active, create a subdirectory using a command like <code>mkdir A.\`config.guess\`</code>, which will create an architecture-specific directory with name peculiar to the architecture and operating system. Then change to this directory and configure with the <code>./configure</code> command. The remaining steps are the same whether building in the base directory or in the subdirectory.

* * *

#### Compilation

Peruse the operating-system-specific information for your architecture under [Hints and Kinks](/archives/4.1.0/hints). 

Use the <code>make</code> command to compile all source modules, construct the libraries and link the distribution. Expect few or no warnings using <code>cc</code> and a moderate level of warnings using <code>gcc</code>.
> **Note:** On some Unix platforms the use of <code>gcc</code> can result in quite a few complaints about system header files and type inconsistencies, especially about pointer variables. This is usually the case when the system header files are not up to ANSI standards or <code>gcc</code>-isms, when gcc is not installed properly, or when operating system updates and patches are applied and gcc is not reinstalled. While the autoconfigure process is quite thorough, the Unix programming cultures of the various workstation makers still remain idiosyncratic.

* * *

#### Installation

As root, use the <code>make install</code> command to install the binaries in the destination directory. You must of course have write permission on the install in the destination directory. This includes the following programs:

* [ntpd - Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd)
* [ntpq - standard NTP query program](/archives/4.1.0/ntpq)
* [ntpdc - special NTP query program](/archives/4.1.0/ntpdc)
* [ntpdate - set the date and time via NTP](/archives/4.1.0/ntpdate)
* [ntptrace - trace a chain of NTP servers back to the primary source](/archives/4.1.0/ntptrace) 

If the precision time kernel modifications are present, the following program is installed:

* [ntptime - read kernel time variables](/archives/4.1.0/ntptime) 

If the public key authentication functions are present, the following program is installed:

* [ntp-genkeys - generate public and private keys](/archives/4.1.0/genkeys) 

In some systems that include the capability to edit kernel variables, the following program is installed:

* [tickadj - set time-related kernel variables](/archives/4.1.0/tickadj) 

* * *

#### Configuration

You are now ready to configure the daemon and start it. You will need to create a NTP configuration file <code>ntp.conf</code> and possibly a cryptographic key file <code>ntp.keys</code>. Newbies should see the [Quick Start](/archives/4.1.0/quick) page for orientation. Seasoned veterans can start with the [ntpd - Network Time Protocol (NTP) daemon](/archives/4.1.0/ntpd) page and move on to the specific configuration option pages from there. A tutorial on NTP subnet design and configuration options is in the [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.1.0/notes) page.

* * *

#### If You Have Problems

If you have problems peculiar to the particular hardware and software environment (e.g. operating system-specific issues), browse the [Hints and Kinks](/archives/4.1.0/hints) page. For other problems a tutorial on debugging technique is in the [NTP Debugging Technique](/archives/4.1.0/debug) page. As always, the first line of general assistance is the [NTP web site](http://www.ntp.org) and the FAQ resident there. Requests for assistance of a general nature and of interest to other timekeepers should be sent to the NTP newsgroup. Bug reports of a specific nature should be sent to bugs@ntp.org. Bug reports of a specific nature on features implemented by the programmer corps mentioned in the [Copyright](/archives/4.1.0/copyright) page should be sent directly to the implementor listed in that page, with copy to bugs@ntp.org.

Please include the version of the source distribution (e.g., ntp-4.0.70a) in your bug report, as well as billboards from the relevant utility programs and debug trace, if available. Please include the output of <code>config.guess</code> in your bug report. It will look something like:

`pdp11-dec-fuzzos3.4`

* * *

#### Additional <tt>make</tt> commands

<code>**make clean**</code>

: Cleans out object files, programs and temporary files.

<code>**make distclean**</code>

: Does the work of <code>clean</code>, but cleans out all directories in preparation for a new distribution release.

<code>**make dist**</code>

: Does the work of <code>make distclean</code>, but constructs compressed tar files for distribution. You must have GNU automake to perform this function.

* * *

#### Building and Installing under Windows NT

See [Windows NT Hints](/archives/hints/winnt) for directions to compile the sources and install the executables.