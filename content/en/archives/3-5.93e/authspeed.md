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

<tt>authspeed [ -cdm ] [ -n _loops_ ] auth.samplekeys</tt>

* * *

#### Description

This program encrypts a test file and determines the authentication delay to use in the NTP configuration file. There are two choices of encryption algorithm, DES Cipher-Block-Chaining (DES-CBC) and Message Digest 5 (MD5).

* * *

#### Options

<dt><tt>-c</tt></dt>

Select total cost of encryption. Default is value to use in the authdelay configuration command.

<dt><tt>-d</tt></dt>

Enable debug output. Default is no debug output.

<dt><tt>-m</tt></dt>

Enable MD5 algorithm. Default is DES-CBC algorithm.

<dt><tt>-n _loops_</tt></dt>

Specify the number of program loops. Default is 20,000.

* * *

#### Files

<tt>./authstuff/auth.samplekeys</tt> - a representative list of keys

<tt>./authstuff/auth.speed</tt> - a listing of results for a representative set of architectures and compilers