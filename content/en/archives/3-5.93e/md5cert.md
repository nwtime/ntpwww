---
title: "md5 - generate message digest"
type: archives
--- 

#### Table of Contents

*  [Synopsis](/archives/3-5.93e/md5cert/#synopsis)
*  [Description](/archives/3-5.93e/md5cert/#description)
*  [Options](/archives/3-5.93e/md5cert/#options)

* * *

#### Synopsis

<code>md5 [ -0123456789 ] [ -h] _file_</code>

* * *

#### Description

This program generates the message digest of the given _file_ using the RSA Message Digest 5 (MD5) and other selected algorithms. If _file_ is not given, the program uses the standard input.

* * *

#### Options

<code>**-0123456789**</code>

: Select algorithm from the following list:

| Option | Algorithm |
| ----- | ----- |
| `-0` | null |
| `-1` | MD5 |
| `-2` | SNEFRU |
| `-3` | CRC32 |
| `-4` | CRC16 |
| `-5` | MD4 |
| `-6` | MD2 |
| `-7` | SHA |
| `-8` | HAVAL |
| `-9` | null |

<code>**-h**</code>

: Display the result in hex; the default is base-64.