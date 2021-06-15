---
title: "vxWorks port"
type: archives
---

Last update: 21-Oct-2010 23:44 UTC

Creating a port for vxWorks posed some problems. This port may help as a starting point for similar ports to real-time OS's and other embeddable kernels, particularly where <tt>main()</tt> is not allowed, and where the configure scripts need to be altered.

* * *

#### Configuration issues

I decided to do as little invasive surgery as possible on the NTP code, so I brought the vxWorks header tree in line with the standard Unix tree. The following changes were needed, as a side effect these changes will allow for easy porting of other autoconfigure enabled code.

Where I have 386 you will need to put in your target type. The vxWorks tree entry point is <tt>/usr/wind</tt>. If these are the same for your system, you should be able to cut and paste the changes.

<blink>WARNING: Check you are not overwriting files, before entering the following: there should be no conflict, but check first...</blink>

<pre>            export CC="cc386 -nostdlib -m486 -DCPU=I80486 -I/usr/wind/target/h"
            export RANLIB=ranlib386
            export AR=ar386
            export VX_KERNEL=/usr/wind/target/config/ims_std_bsp/vxWorks  

            cd /usr/wind/target/sys
            ln -s ../signal.h
            ln -s ../time.h
            ln -s socket.h sockio.h
            ln -s ../selectLib.h select.h
            ln -s ../timers.h
            touch file.h param.h resource.h utsname.h var.h ../netdb.h ../a.out.h ../termios.h
         echo " ******ADD #include \"sys/times.h\" to sys/time.h "
            </pre>

The configure script must be changed in the following way to get the linking tests to work, once in the correct directory issue the following commands:

<pre>      sed -e 's%main.*()%vxmain()%' configure > configure.vxnew
            mv configure.vxnew configure
            chmod 755 configure
      </pre>

The new version 4 of NTP requires some maths functions so it links in the maths library (-lm) in the <tt>./ntpd/Makefile.am</tt> file change the line <tt>ntpd_LDADD = $(LDADD) -lm</tt> by removing the "-lm".

You are now ready to compile.

The ./configure.in file needed to be altered to allow for a host-target configuration to take place.

*   The define SYS_VXWORKS was added to the compilation flags.
*   Little endianess is set if the target is of type iX86.
*   The size of char, integer, long values are all set. If Wind River ever changes these values they will need to be updated.
*   clock_settime() is defined to be used for setting the clock.
*   The Linking flags have -r added to allow for relinking into the vxWorks kernel

Unfortunately I have had to make use of the <tt>./include/ntp_machine.h</tt> file to add in the checks that would have been checked at linking stage by <tt>autoconf</tt>, a better method should be devised.

*   There is now a <tt>NO_MAIN_ALLOWED</tt> define that simulates command line args, this allows the use of the normal startup sysntax.
*   POSIX timers have been added.
*   Structures normally found in <tt>netdb.h</tt> have been added with, the corresponding code is in <tt>./libntp/machines.c</tt>. Where possible the defines for these have been kept non-vxWorks specific.

Unfortunately there are still quite a few <tt>SYS_VXWORKS</tt> type defines in the source, but I have eliminated as many as possible. You have the choice of using the <tt>usrtime.a</tt> library available from the vxworks archives or forgoing <tt>adjtime()</tt> and using the <tt>clock_[get|set]time()</tt>. The <tt>./include/ntp_machine.h</tt> file clearly marks how to do this.

* * *

#### Compilation issues

You will need autoconf and automake ... available free from the gnu archives worldwide.

The variable <tt>arch</tt> is the target architecture (e.g. i486)

<pre>            mkdir A.vxworks)
            cd A.vxworks
            ../configure --target=arch-wrs-vxworks
            make
       </pre>

Options I normally use are the <tt>--disable-all-clocks --enable-LOCAL-CLOCK</tt> flags. The program should proceed to compile without problem. The daemon ntpd, ntpdate, ntptrace, ntpdc, ntpq programs and of course the libraries are all fully ported. The other utilities are not, but they should be easy to port.

* * *

#### Running the software

Load in the various files, call them in the normal vxWorks function type manner. Here are some examples. Refer to the man pages for further information.

<pre>            ld < ntpdate/ntpdate
            ld < ntpd/ntpd
            ld < ntptrace/ntptrace
            ld < ntpq/ntpq
            ld < ntpdc/ntpdc
            ntpdate ("-b", "192.168.0.245")
            sp(ntpd, "-c", "/export/home/casey/ntp/ntp.conf")
            ntpdc("-c", "monlist", "192.168.0.244")
            ntpq("-c", "peers", "192.168.0.244")
            ntptrace("192.168.0.244")
        </pre>

Casey Crellin, casey@csc.co.za
