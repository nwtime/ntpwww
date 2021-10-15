---
title: "authspeed - determine authentication delays"
type: archives
---

#### Table of Contents

*   [Synopsis](/archives/3-5.93e/authspeed/#synopsis)
*   [Description](/archives/3-5.93e/authspeed/#description)
*   [Options](/archives/3-5.93e/authspeed/#options)
*   [Files](/archives/3-5.93e/authspeed/#files)

* * *

#### Synopsis

<code>authspeed [ -cdm ] [ -n _loops_ ] auth.samplekeys</code>

* * *

#### Description

This program encrypts a test file and determines the authentication delay to use in the NTP configuration file. There are two choices of encryption algorithm, DES Cipher-Block-Chaining (DES-CBC) and Message Digest 5 (MD5).

* * *

#### Options

<code>**-c**</code>

: Select total cost of encryption. Default is value to use in the authdelay configuration command.

<code>**-d**</code>

: Enable debug output. Default is no debug output.

<code>**-m**</code>

: Enable MD5 algorithm. Default is DES-CBC algorithm.

<code>**-n _loops_**</code>

: Specify the number of program loops. Default is 20,000.

* * *

#### Files

<code>./authstuff/auth.samplekeys</code> - a representative list of keys

<code>./authstuff/auth.speed</code> - a listing of results for a representative set of architectures and compilers