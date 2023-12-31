---
title: "Solaris frequency patch"
type: archives
noindex: true 
sitemap_exclude: true
---

<pre>#!/bin/ksh

#
# File:         patchfreq
# Author:       Bryan Cantrill (bmc@eng.sun.com), Solaris Performance
# Modified:     Sat Apr 26 04:00:59 PDT 1997
#
# This is a little script to patch a 5.5 or 5.5.1 kernel to get around
# the cpu_tick_freq inaccuracy.  Before running this script, one must
# know the true frequency of one's CPU;  this can be derived by NTP,
# or by observing the clock relative to the time-of-day chip over a
# long period of time (the TOD will pull system time when it drifts
# by more than two seconds).
#
# Patching a kernel can render a machine unbootable;  do not run this
# script unless you are prepared to accept that possibility.  It
# is advisable to have a backout path (e.g. net booting, an alternate
# boot disk, an installation CD) should your machine fail to boot.
#
# This is not a product of Sun Microsystems, and is provided "as is",
# without warranty of any kind expressed or implied including, but not
# limited to, the suitability of this script for any purpose.
#

if [ $# -eq 0 ]; then
        echo "Usage:  $0 cpu_tick_freq [ alternate_kernel ]"
        exit 1
fi

cpu_tick_freq=$1
kernel=/platform/sun4u/kernel/unix

if [ $# -eq 2 ]; then
        kernel=$2
fi

if [ ! -w $kernel ]; then
        echo "$0:  Cannot open $kernel for writing."
        exit 1
fi

arch=`echo utsname+404?s | adb $kernel | cut -d: -f2`

if [ ! $arch = "sun4u" ]; then
        echo "Patch only applies to sun4u"
        exit 1
fi

rel=`echo utsname+202?s | adb $kernel | cut -d: -f2`

if [ ! $rel = "5.5" ] && [ ! $rel = "5.5.1" ]; then
        echo "Patch only applies to 5.5 or 5.5.1..."
        exit 1
fi

nop="1000000"           # nop
store_mask="ffffe000"   # mask out low 13 bits
store="da256000"        # st      %o5, [%l5 + offset]

instr=`echo setcpudelay+34?X | adb $kernel | cut -d: -f 2 | nawk '{ print $1 }'`

if [ $instr = $nop ]; then
        echo "Instruction already patched..."
else
        let masked="(16#$store_mask & 16#$instr) - 16#$store"
        if [ $masked -ne 0 ]; then
                echo "Couldn't find instruction to patch;  aborting."
                exit 1
        fi

        if ! echo setcpudelay+34?W $nop | adb -w $kernel 1> /dev/null
        then
                echo "adb returned an unexpected error;  aborting."
        fi
fi

echo "Patching cpu_tick_freq to $cpu_tick_freq..."

if ! echo cpu_tick_freq?W 0t$cpu_tick_freq | adb -w $kernel 1> /dev/null; then
        echo "adb returned an unexpected error;  aborting."
        exit 1
fi

echo "$kernel successfully patched."
exit 0

</pre>