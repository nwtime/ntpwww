---
title: "HPUX Hints"
type: archives
noindex: true 
sitemap_exclude: true
---

This file hopefully describes the whatever and however of how to get `xntp` running on HP-UX 7.0 and later: s300, s400, s700, and s800.

First off,  all the standard disclaimers hold here ... HP doesn't have anything to do with this stuff.  I fool with it in my spare time because we use it and because I like to.  We just happen to have a lot of HP machines around here :-) `xntpd` has been in use here for several years and has a fair amount of mileage on various HP platforms within the company.  I can't really guarantee bug fixes but I'd certainly like to hear about bugs and I won't hestitate to look at any fixes sent to me.

Now lets talk OS.  If you don't have 7.0 or later, pretty much hang it up now. This stuff has run here on pretty much everything from 8.0 upward on s300, s700, and s800.  It is known to run on 7.0 s300/s400 but all reports are from the field and not my personal experience.

If you are lucky enough to have a s300 or s400 with 9.03, then you no longer
have to worry about `adjtimed` as HP-UX now has `adjtime(2)`.  The rest of you
will have to wait on 10.0 which will have `adjtime(2)` and a supported though
a bit older version of `xntpd`.

Next, let me explain a bit about how this stuff works on HP-UX's that do not have `adjtime(2)`.  The directory `adjtime` contains `libadjtime.a` and the `adjtimed` daemon.  Instead of the `adjtime(2)` system call, we use a library routine to talk to `adjtimed` thru message queues.  `adjtimed` munges into `/dev/kmem` and causes the clock to skew properly as needed.  PLEASE NOTE that the `adjtime` code provided here is NOT a general replacement for `adjtime(2)` ... use of this `adjtime(3)/adjtimed(8)` other than with `xntpd` may yield very odd results.

What to do to get this stuff running? If you are running an OS less than 10.0 or do not have a s300/s400 with 9.03 or better:

      cd machines
	  vi hpux
  (change `-DSYS_HPUX=?` to match whatever you are running [7,8,9])

	  cd ..
      make makeconfig
      make 
	  
  Sit back for a few minutes.

      cd authstuff
	  ./authcert < certdata

  Check the output.  Every line should end with "OK" ... if not, we got trouble.
  
	  ./authspeed auth.samplekeys  
	  
  What we want to remember here is the "authentication delay in CPU time".
	
	  cd ..
      make install

I'd suggest reading the `xntp` docs about now :-) ... seriously !!

One thing I have added to this version of `xntpd` is a way to select config files if you are sharing `/usr/local` thru NFS or whatever. If the file `/usr/local/etc/xntp.conf` happens to be a directory, the  files in that directory are searched until a match is found. The rules for a match are:
1. Our hostname
2. <code>default.\<machine id></code> (as in `default.375` or `default.850`)
3. default

Ok, make sure `adjtimed` is running (just start it up for now with `/usr/local/etc/adjtimed`).  Using `-z` as an option will get you a usage message.

Now start up `xntpd` and watch it work.

Make sure that `adjtimed` gets started at boot right before `xntpd`. We do this in `/etc/netbsdsrc`.  They must both run as root!

Possible problems:

* On some 320's and 835's we have had to run `adjtimed` with `-p 45` or so to get rid of `syslog` messages about "last adjust did not finish".

* At 9.0, there is a problem with DIAGMON (patch available from the response center) which causes it to delete the message queue that `adjtimed/xntpd` use to communicate. (see next note for result)

* `xntpd` has been known to get really ticked off when `adjtime()` fails which is usually only while running the emulation code on HP-UX. When it gets mad, it usually jumps the clock into never never land.
 Possible reasons for this are `adjtimed` being killed or just never started or `adjtimed` being completely swapped out on a really busy machine (newer `adjtimed` try to lock themselves in memory to prevent this one).

Anything else ... just drop me a line at ken@sdd.hp.com

* * *

<pre>
Received: from louie.udel.edu by huey.udel.edu id aa14418; 15 Jun 95 9:19 EDT
Received: from host5.colby.edu (host-05.colby.edu) by host-04.colby.edu with ESMTP  (1.37.109.15/Colby 1.1)
	id AA165442355; Thu, 15 Jun 1995 09:19:16 -0400
Received: by host5.colby.edu  (1.37.109.15/Colby 1.1)
	id AA056252339; Thu, 15 Jun 1995 09:18:59 -0400
Date: Thu, 15 Jun 1995 09:18:59 -0400 (EDT)
From: "Jeff A. Earickson" &lsaquo;jaearick@colby.edu&rsaquo;
To: Mills@huey.udel.edu
Subject: More minor bugs in xntp3.4s
In-Reply-To: &lsaquo;9506150022.aa12727@huey.udel.edu&rsaquo;
Message-Id: &lsaquo;Pine.HPP.3.91.950615083549.4557A-100000@host5.colby.edu&rsaquo;
Mime-Version: 1.0
Content-Type: TEXT/PLAIN; charset=US-ASCII

Dave,
   After reading the hpux hints file, I realized I didn't install or
start adjtimed.  In the course of doing this, I discovered that:

--> $(TOP) is not defined in adjtime/Makefile, so "make install" can't
    find the install.sh script.

--> "make install" from the main Makefile never goes into the adjtime
    directory, so I added the following two lines into the install
    target of the main Makefile:

    @echo installing from adjtime
    @cd adjtime && $(MAKE) $(MFLAGS) MFLAGS="$(MFLAGS)" MAKE="$(MAKE)" install

This twiddle may not be right for all systems, but it got adjtimed
installed for me.

   You might also want to add to the hpux hints file that one way to
fire things up at boot time is to add the following lines to the localrc
function of /etc/rc:

    #---daemons for Network Time Protocol (version 3.4s)
    #---note that adjtimed is only needed for HP-UX 9.X, not 10.0
    #---adjtimed must be running or xntpd won't work right...
    if [ -x /usr/local/bin/adjtimed ]; then
        /usr/local/bin/adjtimed -r & echo -n ' adjtimed'
        if [ -x /usr/local/bin/xntpd ]; then
            /usr/local/bin/xntpd &    echo -n ' xntpd'
        fi
    fi

I discovered that the "-r" option of adjtimed is needed to clear out any
trash from a previous execution of it.  Otherwise adjtimed quietly dies
and leaves xntpd in the lurch...

Thanks for the help.

** Jeff A. Earickson, Ph.D                         PHONE: 207-872-3659
** Senior UNIX Sysadmin, Information Technology    EMAIL: jaearick@colby.edu
** Colby College, 4214 Mayflower Hill,               FAX: 207-872-3555
** Waterville ME, 04901-8842

On Thu, 15 Jun 1995 Mills@huey.udel.edu wrote:

> Jeff,
>
> Read the hpux file in the hints directory.
>
> Dave
</pre>