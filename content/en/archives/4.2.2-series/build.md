---
title: "Building and Installing the Distribution"
type: archives
---

![gif](/archives/pic/beaver.gif)[from _Pogo_, Walt Kelly](http://www.eecis.udel.edu/%7emills/pictures.html)

For putting out compiler fires.

Last update: 03:06 AM UTC Monday, October 13, 2003

* * *

#### Table of Contents

*   [Building and Installing the Distribution](/archives/4.2.2-series/build/#building-and-installing-the-distribution)
*   [Building and Installing under Unix](/archives/4.2.2-series/build/#building-and-installing-under-unix)
*   [Compilation](/archives/4.2.2-series/build/#compilation)
*   [Installation](/archives/4.2.2-series/build/#installation)
*   [Configuration](/archives/4.2.2-series/build/#configuration)
*   [If You Have Problems](/archives/4.2.2-series/build/#if-you-have-problems)
*   [Additional <tt>make</tt> Commands](/archives/4.2.2-series/build/#additional-ttmakett-commands)
*   [Building and Installing Under Windows NT](/archives/4.2.2-series/build/#building-and-installing-under-windows-nt)

* * *

#### Building and Installing the Distribution

As a practical matter, every computer architecture and operating system version seems to be different than any other. The device drivers may be different, the input/output system may be idiosyncratic and the libraries may have different semantics. It is not possible in a software distribution such as this one to support every individual system with a common set of binaries, even with the same system but different versions. Therefore, it is necessary to individually configure the software build for each system and version, both at compile time and at run time. In almost all cases, these procedures are completely automatic and all the newbie user need do is type `configure`, `make` and `install` in that order and the autoconfigure system does the rest. There are some exceptions, as noted below and on the [Hints and Kinks](/archives/4.2.2-series/hints) page.

If available, the OpenSSL library from https://www.openssl.org is used to support public key cryptography. The library must be built and installed prior to building NTPv4. The procedures for doing that are included in the OpenSSL documentation. The library is found during the normal NTPv4 configure phase and the interface routines compiled automatically. Only the <tt>libcrypto.a</tt> library and associated header files are used. If the library is not available or disabled, this step is not required.

* * *

#### Building and Installing Under Unix

Make sure that you have all necessary tools for building executables. These tools include <tt>cc/gcc</tt>, <tt>make</tt>, <tt>awk</tt>, <tt>sed</tt>, <tt>tr</tt>, <tt>sh</tt>, <tt>grep</tt>, <tt>egrep</tt> and a few others. Not all of these tools exist in the standard distribution of modern Unix versions (compilers are likely to be an add-on product). If this is the case, consider using the GNU tools and <tt>gcc</tt> compiler. For a successful build, all of these tools should be accessible via the current path.

The first thing to do is uncompress the distribution and extract the source tree. In the distribution base directory use the <tt>./configure</tt> command to perform an automatic configuration procedure. This command inspects the hardware and software environment and tests for the presence of system header files and the contents of these files to determine if certain features are present. When one or more of these features are present, the code is compiled to use them; if not, no special code is compiled. However, even if the code is compiled to use these features, the code does a special test at run time to see if one or more are actually present and avoids using them if not present. In such cases a warning message is sent to the system log, but the daemon should still work properly.

The default build normally includes the debugging code, which can be useful in diagnosing problems found in initial test, and all reference clock drivers known to work with each machine and operating system. Unless memory space is at a premium, this is a sensible strategy and greatly simplifies debugging and support. If you need to delete either the debugging code or one or all reference clock drivers to save space, see the [Configuration Options](/archives/4.2.2-series/config) page.

If your site supports multiple architectures and uses NFS to share files, you can use a single source tree to compile executables for all architectures. While running on a target architecture machine and in the distribution base directory create a subdirectory using a command like <tt>mkdir A.`config.guess`</tt>, which will create an architecture-specific directory with name peculiar to the architecture and operating system. Then change to this directory and emit a <tt>../configure</tt> command. The remaining steps are the same whether building in the base directory or in the subdirectory.

* * *

#### Compilation

Use the <tt>make</tt> command to compile all source modules, construct the libraries and link the distribution. Expect few or no warnings using <tt>cc</tt> and a moderate level of warnings using <tt>gcc</tt>. **Note:** On some Unix platforms <tt>gcc</tt> may show quite a few complaints about system header files and type inconsistencies, especially with pointer variables. This is usually the case when the system header files are not up to ANSI standards or <tt>gcc</tt> expectations, when <tt>gcc</tt> is not installed properly, or when operating system updates and patches are applied and <tt>gcc</tt> is not reinstalled. While the autoconfigure process is quite thorough, the Unix programming cultures of the various workstation makers still remain idiosyncratic.

* * *

#### Installation

As root, use the <tt>make install</tt> command to install the binaries in the destination directory. Most commonly, these programs are installed in <tt>/usr/local/bin</tt>, but this can be overridden during configuration. You must of course have write permission on the install in the destination directory. This includes the following programs:

* [ntpd - Network Time Protocol (NTP) daemon](/archives/4.2.2-series/ntpd)
* [ntpq - standard NTP query program](/archives/4.2.2-series/ntpq)
* [ntpdc - special NTP query program](/archives/4.2.2-series/ntpdc)
* [ntpdate - set the date and time via NTP](/archives/4.2.2-series/ntpdate)
* [ntptrace - trace a chain of NTP servers back to the primary source](/archives/4.2.2-series/ntptrace) 

If the precision time kernel modifications are present, the following program is installed:

* [ntptime - read kernel time variables](/archives/4.2.2-series/ntptime) 

If the public key authentication functions are present, the following program is installed:

* [ntp-keygen - generate public and private keys](/archives/4.2.2-series/keygen) 

In some systems that include the capability to edit kernel variables, the following program is installed:

* [tickadj - set time-related kernel variables](/archives/4.2.2-series/tickadj) 

Cryptographic support, both symmetric and public key, requires one or more key files, commonly installed in <tt>/usr/local/etc</tt>. Public key cryptography requires a random seed file, usually called <tt>.rnd</tt>, installed in a dark place such as the root directory or <tt>/etc</tt>. Directions for generating keys is on the [Authentication Options](/archives/4.2.2-series/authopt) page.

* * *

#### Configuration

You are now ready to configure the daemon and start it. You will need to create a NTP configuration file <tt>ntp.conf</tt> and a cryptographic key file <tt>ntp.keys</tt>. The latter file is necessary only for remote configuration support, if needed. Newbies should see the [Quick Start](/archives/4.2.2-series/quick) page for orientation. Seasoned veterans can start with the [ntpd - Network Time Protocol (NTP) daemon](/archives/4.2.2-series/ntpd) page and move on to the specific configuration option pages from there. A tutorial on NTP subnet design and configuration options is in the [Notes on Configuring NTP and Setting up a NTP Subnet](/archives/4.2.2-series/notes) page.

* * *

#### If You Have Problems

If you have problems peculiar to the particular hardware and software environment (e.g. operating system-specific issues), browse the [Hints and Kinks](/archives/4.2.2-series/hints) page. For other problems a tutorial on debugging technique is in the [NTP Debugging Technique](/archives/4.2.2-series/debug) page. As always, the first line of general assistance is the NTP web site www.ntp.org and the FAQ resident there. Requests for assistance of a general nature and of interest to other timekeepers should be sent to the NTP newsgroup comp.protocols.time.ntp. Bug reports of a specific nature should be sent to bugs@ntp.org. Bug reports of a specific nature on features implemented by the programmer corps mentioned in the [Copyright](/archives/4.2.2-series/copyright) page should be sent directly to the implementor listed in that page, with copy to bugs@ntp.org.

Please include the version of the source distribution (e.g., ntp-4.0.70a) in your bug report, as well as billboards from the relevant utility programs and debug trace, if available. Please include the output of <tt>config.guess</tt> in your bug report. It will look something like:

<tt>pdp11-dec-fuzzos3.4</tt>

* * *

#### Additional <tt>make</tt> commands

<dt><tt>make clean</tt></dt>

Cleans out object files, programs and temporary files.

<dt><tt>make distclean</tt></dt>

Does the work of <tt>clean</tt>, but cleans out all directories in preparation for a new distribution release.

<dt><tt>make dist</tt></dt>

Does the work of <tt>make distclean</tt>, but constructs compressed tar files for distribution. You must have GNU automake to perform this function.

* * *

#### Building and Installing under Windows NT

See [Windows NT Hints](/archives/hints/winnt) for directions to compile the sources and install the executables.