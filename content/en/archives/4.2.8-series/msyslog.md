---
title: "ntpd System Log Messages"
type: archives
---

![gif](/archives/pic/flatheads.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](http://www.eecis.udel.edu/~mills/pictures.html)

The log can be shrill at times.

Last update: 10-Mar-2014 05:12 UTC

* * *

#### Table of Contents

*   [Introduction](/archives/4.2.8-series/msyslog/#introduction)
*   [Protocol Module](/archives/4.2.8-series/msyslog/#protocol-module)
*   [Clock Discipline Module](/archives/4.2.8-series/msyslog/#clock-discipline-module)
*   [Cryptographic Module](/archives/4.2.8-series/msyslog/#cryptographic-module)

* * *

#### Introduction

You have come here because you found a cryptic message in the system log. This page by no means lists all messages that might be found, since new ones come and old ones go. Generally, however, the most common ones will be found here. They are listed by program module and log severity code in bold: <tt>**LOG_ERR**</tt>, **<tt>LOG_NOTICE</tt>** and <tt>**LOG_INFO**</tt>.

Most of the time **<tt>LOG_ERR</tt>** messages are fatal, but often <tt>ntpd</tt> limps onward in the hopes of discovering more errors. The <tt>**LOG_NOTICE**</tt> messages usually mean the time has changed or some other condition that probably should be noticed. The <tt>**LOG_INFO**</tt> messages usually say something about the system operations, but do not affect the time.

In the following a '?' character stands for text in the message. The meaning should be clear from context.

* * *

#### Protocol Module

<tt>**LOG_ERR**</tt>

<dl>

<dt><tt>buffer overflow ?</tt></dt>

<dd>Fatal error. An input packet is too long for processing.</dd>

</dl>

<tt>**LOG_NOTICE**</tt>

<dl>

<dt><tt>no reply; clock not set</tt></dt>

<dd>In <tt>ntpdate</tt> mode no servers have been found. The server(s) and/or network may be down. Standard debugging procedures apply.</dd>

</dl>

<tt>**LOG_INFO**</tt>

<dl>

<dt><tt>proto_config: illegal item ?, value ?</tt></dt>

Program error. Bugs can be reported [here](/archives/4.2.8-series/bugs).

<dt><tt>receive: autokey requires two-way communication</tt></dt>

<dd>Configuration error on the <tt>broadcastclient</tt> command.</dd>

<dt><tt>receive: server _server_ maaximum rate exceeded</tt></dt>

<dd>A kiss-o'death packet has been received. The transmit rate is automatically reduced.</dd>

<dt><tt>pps sync enabled</tt></dt>

<dd>The PPS signal has been detected and enabled.</dd>

<dt><tt>transmit: encryption key ? not found</tt></dt>

<dd>The encryption key is not defined or not trusted.</dd>

<dt><tt>precision = ? usec</tt></dt>

<dd>This reports the precision measured for this machine.</dd>

<dt><tt>using 10ms tick adjustments</tt></dt>

<dd>Gotcha for some machines with dirty rotten clock hardware.</dd>

<dt><tt>no servers reachable</tt></dt>

<dd>The system clock is running on internal batteries. The server(s) and/or network may be down.</dd>

</dl>

* * *

#### Clock Discipline Module

<tt>**LOG_ERR**</tt>

<dl>

<dt><tt>time correction of ? seconds exceeds sanity limit (?); set clock manually to the correct UTC time</tt>.</dt>

<dd>Fatal error. Better do what it says, then restart the daemon. Be advised NTP and Unix know nothing about local time zones. The clock must be set to Coordinated Universal Time (UTC). Believe it; by international agreement abbreviations are in French and descriptions are in English.</dd>

<dt><tt>sigaction() fails to save SIGSYS trap: ? </tt> 
</tt><tt>sigaction() fails to restore SIGSYS trap: ?</tt></dt>

Program error. Bugs can be reported [here](/archives/4.2.8-series/bugs).

</dl>

<tt>**LOG_NOTICE**</tt>

<dl>

<dt><tt>frequency error ? exceeds tolerance 500 PPM</tt></dt>

<dd>The hardware clock frequency error exceeds the rate the kernel can correct. This could be a hardware or a kernel problem.</dd>

<dt><tt>time slew ? s</tt></dt>

<dd>The time error exceeds the step threshold and is being slewed to the correct time. You may have to wait a very long time.</dd>

<dt><tt>time reset ? s</tt></dt>

<dd>The time error exceeds the step threshold and has been reset to the correct time. Computer scientists don't like this, but they can set the <tt>ntpd -x</tt> option and wait forever.</dd>

<dt><tt>kernel time sync disabled ?</tt></dt>

<dd>The kernel reports an error. See the codes in the <tt>timex.h</tt> file.</dd>

<dt><tt>pps sync disabled</tt></dt>

<dd>The PPS signal has died, probably due to a dead radio, broken wire or loose connector.</dd>

</dl>

<tt>**LOG_INFO**</tt>

<dl>

<dt><tt>kernel time sync status ?</tt></dt>

<dd>For information only. See the codes in the <tt>timex.h</tt> file.</dd>

</dl>

* * *

#### Cryptographic Module

<tt>**LOG_ERR**</tt>

<dl>

<dt><tt>cert_parse ?  
</tt><tt>cert_sign ?  
</tt><tt>crypto_cert ?  
</tt><tt>crypto_encrypt ?  
</tt><tt>crypto_gq ?  
</tt><tt>crypto_iff ?  
</tt><tt>crypto_key ?  
</tt><tt>crypto_mv ?  
</tt><tt>crypto_setup ?  
</tt><tt>make_keys ?</tt></dt>

<dd>Usually fatal errors. These messages display error codes returned from the OpenSSL library. See the OpenSSL documentation for explanation.</dd>

<dt><tt>crypto_setup: certificate ? is trusted, but not self signed.  
</tt><tt>crypto_setup: certificate ? not for this host  
</tt><tt>crypto_setup: certificate file ? not found or corrupt  
</tt><tt>crypto_setup: host key file ? not found or corrupt  
</tt><tt>crypto_setup: host key is not RSA key type  
</tt><tt>crypto_setup: random seed file ? not found  
</tt><tt>rypto_setup: random seed file not specified</tt></dt>

<dd>Fatal errors. These messages show problems during the initialization procedure.</dd>

</dl>

<tt>**LOG_INFO**</tt>

<dl>

<dt><tt>cert_parse: expired ?  
</tt><tt>cert_parse: invalid issuer ?  
</tt><tt>cert_parse: invalid signature ?  
</tt><tt>cert_parse: invalid subject ?</tt></dt>

<dd>There is a problem with a certificate. Operation cannot proceed until the problem is fixed. If the certificate is local, it can be regenerated using the <tt>ntp-keygen</tt> program. If it is held somewhere else, it must be fixed by the holder.</dd>

<dt><tt>crypto_?: defective key  
</tt><tt>crypto_?: invalid filestamp  
</tt><tt>crypto_?: missing challenge  
</tt><tt>crypto_?: scheme unavailable</tt></dt>

<dd>There is a problem with the identity scheme. Operation cannot proceed until the problem is fixed. Usually errors are due to misconfiguration or an orphan association. If the latter, <tt>ntpd</tt> will usually time out and recover by itself.</dd>

<dt><tt>crypto_cert: wrong PEM type ?</tt></dt>

<dd>The certificate does not have MIME type <tt>CERTIFICATE</tt>. You are probably using the wrong type from OpenSSL or an external certificate authority.</dd>

<dt><tt>crypto_ident: no compatible identity scheme found</tt></dt>

<dd>Configuration error. The server and client identity schemes are incompatible.</dd>

<dt><tt>crypto_tai: kernel TAI update failed</tt></dt>

<dd>The kernel does not support this function. You may need a new kernel or patch.</dd>

<dt><tt>crypto_tai: leapseconds file ? error ?</tt></dt>

<dd>The leapseconds file is corrupt. Obtain the latest file from <tt>time.nist.gov</tt>.</dd>

</dl>
