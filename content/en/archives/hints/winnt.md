---
title: "Windows NT"
type: archives
---

Last update: 6-Apr-2014 23:27

* * *

#### Introduction

The NTP 4 distribution runs as service on Windows 2000 and later. It will NOT run on Windows 95, 98, ME, etc. Lately it has been run the most on Windows-7 and later. The binaries work on multi-processor systems. This port has not been tested on the Alpha platform. This release now uses OpenSSL for authentication. A ready-to-run install distribution is available from [Meinberg](http://www.meinberg.de/english/sw/ntp.htm).

Users should note that the stock Windows client sends requests as mode-1 packets, which can have unintended consequences and create a security risk. The client should send requests as mode-3 (client) packets, which conform to the protocol specification. The issues and resolution are described in [Microsoft KB 875424](https://docs.microsoft.com/en-us/troubleshoot/windows-server/identity/time-synchronization-not-succeed-non-ntp). A less desirable alternative that avoids changing registry keys is to use the `--with-wintime` option when building the executable.

* * *

#### Authentication Keys

With this release `ntp-keygen` is supported. See the [ntp keygen documentation](/archives/4.2.8-series/keygen) for details on how to use `ntp-keygen`.

`ntpd` can now use the generated keys in the same way as on Unix platforms. Please refer to the [Authentication Options](/archives/4.2.8-series/authopt) for details on how to use these.

> **NOTE:** `ntpd` and `ntp-keygen` both use OpenSSL which requires a random character file called `.rnd` by default. Both of these programs will automatically generate this file if they are not found. The programs will look for an environmental variable called `RANDFILE` and use that for the name of the random character file if the variable exists. If it does not exist it will look for an environmental variable called `HOME` and use that directory to search for a file called `.rnd` in that directory. Finally, if neither `RANDFILE` nor `HOME` exists it will look in `C:\` for a `.rnd` file. In each case it will search for and create the file if the environmental variable exists or in the `C:\` directory if it doesn't.

Note that `ntpd` normally runs as a service so that the only way that it will have either `RANDFILE` or `HOME` defined is if it is a System environmental variable or if the service is run under a specific account name and that account has one of those variables defined. Otherwise it will use the file `c:\.rnd`. This was done so that OpenSSL will work normally on Win32 systems. This obviates the need to ship the `OpenSSL.exe` file and explain how to generate the `.rnd` file. A future version may change this behavior.

Refer to [Compiling Requirements and Instructions](#compiling-requirements) for how to compile the program.

* * *

#### Reference Clocks

Reference clock support under Windows NT is tricky because the IO functions are so much different. Some of the clock types have been built into the `ntpd` executable and should work but have not been tested by the NTP project. If you have a clock that runs on Win32 and the driver is there but not implemented on Win32 you will have make the required configuration changes in `config.h` and then build `ntpd` from source and test it. The [Undisciplined Local Clock (Type 1)](/archives/drivers/driver1) reference clock is known to work and is supported by Windows NT. 

* * *

#### Functions Supported

All NTP functions are supported with some constraints. See the [TODO](#todo) list below. Note that the `ntptrace` executable is not supported and you should use the PERL script version instead.

* * *

#### Accuracy

Greg Brackley has implemented a fantastic interpolation scheme that improves the precision of the NTP clock using a realtime thread (is that poetic or what!) which captures a tick count from the 8253 counter after each OS tick. The count is used to interpolate the time between operating system ticks.

On a typical 200+ MHz system NTP achieves a precision of about 5 microseconds and synchronizes the clock to +/-500 microseconds using the [Trimble Palisade](/archives/drivers/driver29/) as UTC reference. This allows distributed applications to use the 10 milliseconds ticks available to them with high confidence.

* * *

#### ToDo

These tasks are in no particular order of priority.

*   Add IPv6 support (UPDATE: available in newer binaries from Meinberg).
*   See if precision can be improved by using CPU cycle counter for tick interpolation.
*   Make precision time available to applications using `NTP_GETTIME API`.

* * *

#### Compiling Requirements

*   Windows 7 or Windows.NET Server 2003, or later.
*   Windows NT 4.0 Windows 2000, Windows XP or Windows Vista _may_ still work.
*   Microsoft Visual C++ 2008, 2010, or 2013 EE.
*   Some way of uncompressing and untarring the gzipped tar file.
*   OpenSSL must be built on the box before building NTP. Additional steps would be required to not use OpenSSL.
*   Microsoft Visual C++ redistributables.

#### Compiling Instructions

1. Install Microsoft Visual C++ [redistributables](https://www.microsoft.com/en-us/download/details.aspx?id=48145).

2. Install [OpenSSL full installer for Windows](http://www.slproweb.com/products/Win32OpenSSL.html). Add the following to your system environment variables in the control panel (adjusting paths as appropriate to point to the directory containing only an openssl subdirectory, for `OPENSSL_INC`, and to the directory containing `openssl .lib` files for `OPENSSL_LIB:`

        OPENSSL_INC=C:\OpenSSL\include
        OPENSSL_LIB=C:\OpenSSL\lib
		
3.  Unpack the `NTP-4.x.tar.gz` using utilities such as WinZip or WinRar.
4.  Run Microsoft Visual C++ 2008 EE.
5.  Open the `ports\winnt\vs2008\ntp.sln` solution file.
6.  Batch build all projects (Build menu, Batch Build..., select all, build).
7.  The built binaries can be found in the `ports\winnt\v2008\Win32-bin\Release` directory.
8.  If you are shipping binaries in a kit it is strongly recommended that you ship this file along with the binaries.

* * *

#### Configuration File

The default NTP configuration file path is `%SystemRoot%\system32\drivers\etc\`. `%SystemRoot%` is an environmental variable that can be determined by typing `set` at the <kbd>Command Prompt</kbd> or from the <kbd>System</kbd> icon in the <kbd>Control Panel</kbd>.

Refer to your system environment and create your `ntp.conf` file in the directory corresponding to your system  installation. The older `<WINDIR>\ntp.conf` is still supported but you will get a log entry reporting that the first file wasn't found.

* * *

#### Installation Instructions

The `instsrv` program in the `instsrv` subdirectory of the distribution can be used to install `ntpd` as a service and start automatically at boot time. `instsrv` is automatically compiled with the rest of the distribution if you followed the steps above.

1.  Start a command prompt and enter `instsrv.exe <pathname_for_ntpd.exe>`.

2.  Clicking on the <kbd>Services</kbd> icon in the <kbd>Control Panel</kbd> will display the list of currently installed services in a dialog box. The NetworkTimeProtocol service should show up in this list. Select it in the list and hit the <kbd>Start</kbd> button in the dialog box. The NTP service should start.

3.  You can also stop and start the service by typing `net start | stop NetworkTimeProtocol` at the DOS prompt.
4.  View the event log by clicking on the <kbd>Event Viewer</kbd> icon in the <kbd>Administrative Tools</kbd> group, there should be several successful startup messages from NTP. NTP will keep running and restart automatically when the machine is rebooted.

You can change the start mode (automatic/manual) and other startup parameters corresponding to the NTP service in the <kbd>Services</kbd> dialog box if you wish.

* * *

#### Removing NTP

You can also use `instsrv` to delete the NTP service by entering: `instsrv.exe remove`.

* * *

#### Command Line Parameters and Registry Entries

Unlike the Unix environment, there is no clean way to run `ntpdate` and reset the clock before starting `ntpd` at boot time. NTP will step the clock up to 1000 seconds by default. While there is no reason that the system clock should be that much off during bootup if `ntpd` was running before, you may wish to override this default and/or pass other command line directives.

Use the registry editor to edit the value for the `ntpd` executable under `LocalMachine\System\CurrentControlSet\Services\NTP`.

Add the `-g` option to the `ImagePath` key, behind `%INSTALLDIR>\ntpd.exe`. This will force NTP to accept large time errors (including 1.1.1980 00:00).

* * *

#### Bug Reports

Please follow the [NTP Bug Reporting Procedures](/archives/4.2.8-series/bugs) to report bugs or request enhancements.