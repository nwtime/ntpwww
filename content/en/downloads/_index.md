---
title: "Download NTP"
type: archives
date: 2021-10-26T01:48:02+00:00
--- 

The current release of NTP is [4.2.8p15](http://support.ntp.org/bin/view/Main/SecurityNotice#June_2020_ntp_4_2_8p15_NTP_Relea) which was released on June 23, 2020. 

<a link rel="alternate" type="application/rss+xml" href="/downloads/index.xml" title="Downloads"><i class="bi-rss"></i></a>

| Software Type | Download Link |
| ----- | ----- |
| Source code | [tar.gz](http://archive.ntp.org/ntp4/ntp-4.2/ntp-4.2.8p15.tar.gz) with [md5](http://archive.ntp.org/ntp4/ntp-4.2/ntp-4.2.8p15.tar.gz.md5) and [Changelog](https://archive.ntp.org/ntp4/ChangeLog-stable) |
| Windows installer (XP and later) | [exe](https://www.meinbergglobal.com/download/ntp/windows/ntp-4.2.8p15-v2-win32-setup.exe) and [instructions](https://www.meinbergglobal.com/english/sw/ntp.htm#ntp_stable) |
| Debian pkg | [Debian 11 (bullseye)](https://packages.debian.org/bullseye/ntp) |
| Slackware pkg | [Slackware 14.2](https://slackware.pkgs.org/14.2/slackware-patches-x86_64/ntp-4.2.8p15-x86_64-1_slack14.2.txz.html) |
| OpenSusE, Fedora, Mageia, OpenMandriva | [rpm](https://rpmfind.net/linux/rpm2html/search.php?query=ntp) |
| FreeBSD | [port](https://www.freshports.org/net/ntp) |
| NetBSD | [pkgsrc](https://ftp.netbsd.org/pub/pkgsrc/current/pkgsrc/net/ntp4/index.html) |


<div><span style="width: 100%;text-align: center">
{{% pageinfo color="primary" %}}

NTP users are strongly urged to [implement Ingress and Egress filtering through BCP38](http://bcp38.info) to ensure that their NTP daemon is not susceptible to use in a [reflected denial-of-service (DRDoS) attack](https://support.ntp.org/bin/view/Main/SecurityNotice#April_2010_DRDoS_Amplification_A). Please see this [Network Time Foundation Post](http://networktimefoundation.org/ntp-winter-2013-network-drdos-attacks/) for more information.
{{% /pageinfo %}}
</span></div>