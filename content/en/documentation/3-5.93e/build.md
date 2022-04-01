---
title: "Building and Installing the Distribution"
type: archives
noindex: true
---

#### Table of Contents

*   [Building and Installing under Unix](/documentation/3-5.93e/build/#building-and-installing-under-unix)
*   [Configuration](/documentation/3-5.93e/build/#configuration)
*   [Compilation](/documentation/3-5.93e/build/#compilation)
*   [Installation](/documentation/3-5.93e/build/#installation)
*   [Additional <tt>make</tt> Commands](/documentation/3-5.93e/build/#additional-ttmakett-commands)
*   [Building and Installing Under Windows NT](/documentation/3-5.93e/build/#building-and-installing-under-windows-nt)

* * *

Following are instructions to build and install the programs in this distribution.

Note that the automatic build process inspects the machine environment and tests for the presence of system header files and the contents of these files to determine if certain features are available. When one or more of these features are present, the code is compiled to use them; if not, no special code is compiled. However, even if the code is compiled to use these features, the code does a special test at run time to see if one or more are actually present and avoids using them if not present. In such cases a warning message is sent to the system log, but the daemon should still work properly. 

* * *

#### Building and Installing Under Unix

Make sure that you have all necessary tools for building executables. These tools include <code>cc/gcc</code>, <code>make</code>, <code>awk</code>, <code>sed</code>, <code>tr</code>, <code>sh</code>, <code>grep</code>, <code>egrep</code> and a few others. Not all of these tools exist in the standard distribution of modern Unix versions (compilers are likely to be an add-on product - consider using the GNU tools and <code>gcc</code> compiler in this case). For a successful build, all of these tools should be accessible via the current path.

* * *

#### Configuration

Use the <code>configure</code> command to perform an automatic configuration procedure. This procedure normally includes the debugging code, which can be useful in diagnosing problems found in initial test, and all reference clock drivers known to work with each machine and operating system. Unless memory space is at a premium, this is a sensible strategy and saves lots of messy fiddling. If you need to delete either the debugging code or one or more or all reference clock drivers to save space, see the [Configuration Options](/documentation/3-5.93e/config/) page.

If your site supports multiple architectures and uses NFS to share files, you can use a single source tree to compile executables for all architectures. While running on a target architecture machine and with the distribution base directory active, create a subdirectory using a command like <code>mkdir \`config.guess\`</code>, which will create an architecture-specific directory with name peculiar to the architecture and operating system. Then change to this directory and configure with the <code>./configure command</code>. The remaining steps are the same whether building in the base directory or in the subdirectory. 

* * *

#### Compilation

Peruse the operating-system-specific information for your architecture under [Hints and Kinks](/documentation/3-5.93e/hints/). 

Use the <code>make</code> command to compile all source modules, construct the libraries and link the distribution. Expect few or no warnings using <code>cc</code> and a moderate level of warnings using <code>gcc</code>.
> **Note:** On some Unix platforms the use of <code>gcc</code> can result in quite a few complaints about system header files and type inconsistencies, especially about pointer variables. This is usually the case when the system header files are not up to ANSI standards or <code>gcc</code>-isms. While the autoconfigure process is quite thorough, the Unix programming cultures of the various workstation makers still remain idiosyncratic.

* * *

#### Installation

As root, use the <code>make install</code> command to install the binaries in the destination directory. You must of course have write permission on the install in the destination directory. This includes the programs [xntpd](/documentation/3-5.93e/xntpd/) (the daemon), [xntpdc](/documentation/3-5.93e/xntpdc/) (an <code>xntpd</code>-dependent query program), [ntpq](/documentation/3-5.93e/ntpq/) (a standard query program), [ntpdate](/documentation/3-5.93e/ntpdate/) (an <code>rdate</code> replacement for boot time date setting and sloppy time keeping) and [ntptrace](/documentation/3-5.93e/ntptrace/) (a utility useful to find the primary (stratum-1) servers). In some systems, the [tickadj](/documentation/3-5.93e/tickadj/) (a utility useful to adjust kernel variables) is installed. If the precision time kernel modifications are present, the [ntptime](/documentation/3-5.93e/ntptime/) (a utility useful to debug kernel time functions) is installed. 

You are now ready to configure the daemon and start it. You will need to create a NTP configuration file <code>ntp.conf</code> and possibly a cryptographic key file <code>ntp.keys</code>. Directions for doing that are in the [Notes on Configuring NTP and Setting up a NTP Subnet](/documentation/3-5.93e/notes/). A tutorial on debugging technique is in [NTP Debugging Technique](/documentation/3-5.93e/debug/) page. If problems peculiar to the particular hardware and software environment are suspected, browse the [Hints and Kinks](/documentation/3-5.93e/hints/) page. 

Bug reports of a general nature can be sent to David Mills (mills@udel.edu). Bug reports of a specific nature on features implemented by the programmer corps mentioned in the [Copyright](/documentation/3-5.93e/copyright/) page should be sent directly to the implementor listed in that page, with copy to mills@udel.edu.

**Please include the version of the source distribution (e.g., xntp3-5.87) in your bug report.** 
 
**Please include the output of <code>config.guess</code> in your bug report.** 

**It will look something like: <code>pdp11-dec-fuzzos3.4</code>**

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

Under Windows NT, you will need Visual C++ 4.0 or above, InstallShield SDK (comes with VC++), Perl5 and some version of the archiving program ZIP.

See the <code>./scripts/wininstall/readme.nt</code> file for directions to compile the sources, build the libraries and link the executables. Initiate the build by running either <code>bldrel.bat</code> or <code>blddbg.bat</code> to compile all of the source and create an <code>InstallShield</code> based graphical installation package.

To install the executables, make sure that you are logged in as a system account, or one with administrator privileges such as the "administrator" account. As part of the build an <code>InstallShield</code> based graphical installer was created. Run `\xntp\scripts\wininstall\intel\disk1\setup.exe` to begin the installation. This installer will prompt for basic defaults, copy the binaries, install the service, and start it up. The other option is to run `\xntp\scripts\wininstall\distrib\install.bat` which will do the basic installation from the command line.