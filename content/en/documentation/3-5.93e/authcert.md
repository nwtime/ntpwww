---
title: "authcert - DES validation program"
type: archives
noindex: true 
sitemap_exclude: true
---

#### Table of Contents

*  [Synopsis](/documentation/3-5.93e/authcert/#synopsis)
*  [Description](/documentation/3-5.93e/authcert/#description)
*  [Files](/documentation/3-5.93e/authcert/#files)

* * *

#### Synopsis

<code>authcert</code>

* * *

#### Description

This program verifies whether the DES encryption algorithm is operating correctly in the particular architecture. The program reads a line from the standard input containing a key, plaintext block and the corresponding encrypted ciphertext block, respectively, as in the following

<pre>0000000000000000 0000000000000000 8CA64DE9C1B123A7
FFFFFFFFFFFFFFFF FFFFFFFFFFFFFFFF 7359B2163E4EDC58
3000000000000000 1000000000000001 958E6E627A05557B
1111111111111111 1111111111111111 F40379AB9E0EC533
0123456789ABCDEF 1111111111111111 17668DFC7292532D
1111111111111111 0123456789ABCDEF 8A5AE1F81AB8F2DD
0000000000000000 0000000000000000 8CA64DE9C1B123A7
FEDCBA9876543210 0123456789ABCDEF ED39D950FA74BCC4
7CA110454A1A6E57 01A1D6D039776742 690F5B0D9A26939B
</pre>

and generates output as in the following

<pre> K: 0000000000000000 P: 0000000000000000 C: 8ca64de9c1b123a7 OK
 K: ffffffffffffffff P: ffffffffffffffff C: 7359b2163e4edc58 OK
 K: 3000000000000000 P: 1000000000000001 C: 958e6e627a05557b OK
 K: 1111111111111111 P: 1111111111111111 C: f40379ab9e0ec533 OK
 K: 0123456789abcdef P: 1111111111111111 C: 17668dfc7292532d OK
 K: 1111111111111111 P: 0123456789abcdef C: 8a5ae1f81ab8f2dd OK
 K: 0000000000000000 P: 0000000000000000 C: 8ca64de9c1b123a7 OK
 K: fedcba9876543210 P: 0123456789abcdef C: ed39d950fa74bcc4 OK
 K: 7ca110454a1a6e57 P: 01a1d6d039776742 C: 690f5b0d9a26939b OK
</pre>

* * *

#### Files

<code>./authstuff/certdata</code> - a representative test file