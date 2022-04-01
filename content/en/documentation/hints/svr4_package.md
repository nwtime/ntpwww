---
title: "Solaris NTPv3 package"
type: archives
---

<pre>Date: Wed, 12 Apr 1995 12:42:03 +0100
Message-ID: <513.797686923@concurrent.co.uk>
From: Andy Chittenden <asc@concurrent.co.uk></pre>

Dave

Here is a uuencoded, compressed tar file. The only file I've changed is `Makefile` - I've included the full file rather than diffs. There are some new files as well:

xntp	
: Shell script that starts up ntp during boot up (the packaging stuff creates links to it so it comes up at run level 2). As with all svr4 start/stop scripts, it takes one parameter which is either `start` or `stop`. It assumes that `ntp.conf` is in /`etc/inet/ntp.conf` (where it should be on svr4 machines).
	
prototype	
: Describes the file contents of the package. You might like to review its contents to see whether you want to include any other files or remove some. NB: I've made the man pages go into 1m as they should on svr4.

preinstall	
: Runs before installation takes place. It ensures that ntp is down if it is up before installing a replacement package.

postinstall
: Starts up ntp after package installation.

preremove
: Brings down ntp before removing the package.

You create a package using `make package`. This creates a file called `xntp.pkg`. To install this package, you use <code>pkgadd -d \`pwd\`/xntp.pkg xntp</code>. This will start up ntp if `/etc/inet/ntp.conf` exists. If you don't want the package anymore, use `pkgrm xntp`. I have tested this on Solaris 2.4.