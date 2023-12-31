---
title: "A-UX Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Introduction

Included in this distribution of XNTP V3 is a configuration file suitable for use under Apple's A/UX Version 3.x.x  There is also one for A/UX 2.0.1 but it has not been fully tested. To make the executables follow the steps outlined below.

> **NOTE:**  You must have `gcc` installed to successfully compile the current distribution; the native `cc` supplied with A/UX will NOT correctly compile this source.  See the FAQ in comp.unix.aux for places to obtain `gcc` from and how to install it.

* * *

#### Making XNTPD for A/UX


First, you need to create the makefiles (after you've downloaded the source, of course):

`make clean`

`make refconf`

After that, you should edit `Config.local` to make sure that `BINDIR` is correct for where you wish the programs to be installed. The default (and what I use) is `/usr/local/etc`. Make sure that `DEFS_LOCAL` and `CLOCKDEFS` are commented out! Presently, only the `LOCAL_CLOCK/REFCLOCK` clock is used and supported.

After this is done (you should be told that your system is A/UX 3), make `xntpd` (the options to `gcc` are held in `compilers/aux3.gcc`):

`make`

I do not normally use the `make install` option and so have not verified its compatibility with A/UX.  Rather, I pull out each of the executables and place them in the locally appropriate locations.

* * *

#### Starting XNTPD

At this point you need to set things up so that `xntpd` is started upon boot-up. You can do this in 1 of 2 ways: either add entries in `/etc/inittab` or, more ideally, create and use an `/etc/rc.local` file. Since `rc.local` is what I recommend, here's how you do it:

By default, A/UX doesn't have `rc.local`, so you'll need to add the following to `/etc/inittab`:

<pre>
net6:2:wait:/etc/syslogd		        # set to "wait" to run a syslog daemon
jmj0:2:wait:/etc/rc.local 1>/dev/syscon 2>&1	# Local stuff
dbg2::wait:/etc/telinit v	                # turn off init's verbose mode
</pre>

Now, the look of a sample `/etc/rc.local` is as follows:

    #!/bin/sh
    :
    : rc.local
    :
    #	@(#)Copyright Apple Computer 1987	Version 1.17 of rc.sh on 91/11/08 15:56:21 (ATT 1.12)

    #	Push line discipline/set the device so it will print
    /etc/line_sane 1
    echo " "
    echo "Entering rc.local..."

    set `/bin/who -r`
    if [ "$7" = 2 ]
    then
        /bin/echo " now setting the time..."
        /usr/local/etc/ntpdate -s -b <host.domain>
        sleep 5
    #
    # start up 'xntpd' if we want
    #
        if [ -f /etc/ntp.conf ]
        then
    	/bin/echo " setting tick and tickadj..."
    	/usr/local/etc/tickadj -t 16672 -a 54
    	sleep 5
    	/bin/echo " starting xntpd..."
    	/usr/local/etc/xntpd <&- > /dev/null 2>&1
    	sleep 5
        fi
    #
    fi

    echo "Leaving rc.local..."

There are a few things to notice about the above:

* When run, `ntpdate` forces your clock to the time returned by the host(s) specified by <code>\<host.domain></code> (you'll need to replace this with the IP address(es) of your timehosts). This is good since it gets things close to start off with. You can use more than one time server.

* `tickadj` is also called. This does two things: changes the default value of `tick` (which is the amount of time, in ms, that is added to the clock every 1/60 seconds) and changes the value of `tickadj` which is the amount that is added or subtracted from `tickadj` when `adjtime()` is called.

Now Mac clocks are pretty bad and tend to be slow. So, instead of having A/UX add the default of 16666 ms every 1/60th of a second, you may want it to add more (or less) so that it keeps better time. The above value works for me but your best value may be different and will likely require some fooling around to find the best value. As a general rule of thumb, if you see `xntpd` make a lot of negative clock  adjustments, then your clock is fast and you'll need to _decrease_ the value of `tick`. If your adjustments are positive, then you need to increase `tick`. To make a guess on how fast/slow your clock is, use `ntpdate` to sync your clock. Now watch `xntpd` and see how it operates. If, for example, it resets your clock by 1 second every 30 minutes, then your clock is (`1/(30*60)`) about 0.056% off and you'll need to adjust `tick` by 16666*0.00056 or about 9 (i.e. `tick` should be ~16675 if slow or ~16657 if fast).

A/UX's default value of `tickadj` is 1666 which is too big for `xntpd` so it also needs to be adjusted. I like using larger values than the recommended value of 9 for `tickadj` (although not anything near as big as 1666) since this allows for quick slews when adjusting the clock. Even with semi-large values of `tickadj` (~200), getting 5ms (1/200 s) accuracy is easy.

Finally, before A/UX and `xntpd` will work happily together, you need to patch the kernel. This is due to the fact that A/UX attempts to keep the UNIX-software clock and the Mac-hardware clock in sync. Neither the h/w or the s/w clock are too accurate. Also, `xntpd` will be attempting to adjust the software clock as well, so having A/UX muck around with it is asking for headaches. What you therefore need to do is tell the kernel _not_ to sync the s/w clock with the h/w one. This is done using `adb`. The following is a shell script that will do the patch for you:

    #! /bin/sh
    adb -w /unix <<!
    init_time_fix_timeout?4i
    init_time_fix_timeout?w 0x4e75
    init_time_fix_timeout?4i
    $q
    !

This must be done _every_ time you create a new kernel (via `newconfig` or `newunix`) or else `xntpd` will go crazy.

* * *

#### History

John Dundas was the original porter of `xntpd` and a lot of the additions and A/UX-ports are from him. I got involved when I wanted to run `xntpd` on jagubox. It was also around this time that the base-patchlevel of `xntpd` changed relatively (the so-called "jones" version). Since then, I've been maintaining `xntpd` for A/UX for the xntp development team.

The original kernel patch (which patched `time_fix_timeout`) was from Richard Todd. I suggest patching `init_time_fix_timeout` which prevents `time_fix_timeout` from even being called.

* * *

#### Technical Notes

*  As configured (see `machines/aux3`), `xntpd` will log messages via `syslogd` using the `LOC_LOCAL1` facility. I would suggest the following in `/etc/syslog.conf`:

   `local1.notice		/usr/adm/ntpd-syslog`

*  As mentioned above, the clocks on A/UX and Macs are kinda bad. Not only that, but logging in and out of the MacOS mode as well as extensive floppy use causes A/UX to drop and lose clock interupts (these are sent every 1/60th of a second). So, if you do these activities a lot, you find out that you lose about 300ms of time (i.e., you become 300ms slow). The `xntpd` default way of handling this is to call `settimeofday()` and step the clock to the correct time. I prefer having `xntpd` slew the clock back into line by making gradual adjustments to the clock over a couple of minutes or so. It's for this reason that `SLEWALWAYS` is defined in `include/ntp_machine.h` for SYS_AUX3. It's also for this reason than I like larger values of `tickadj`.

Good luck!  If you have problems under A/UX feel free to contact me (e-mail is preferred).

    Jim Jagielski               |  "That is no ordinary rabbit... 'tis the
								|   most foul, cruel and bad-tempered
    NASA/GSFC, Code 734.4       |   rodent you ever set eyes on"
    Greenbelt, MD 20771         |                   Tim the Enchanter