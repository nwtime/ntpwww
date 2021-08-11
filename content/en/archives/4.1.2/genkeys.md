---
title: "ntp-genkeys - generate public and private keys"
type: archives
---

![gif](/archives/pic/alice23.gif)[from _Alice's Adventures in Wonderland_, Lewis Carroll](/reflib/pictures)

Alice holds the key.

* * *

#### Table of Contents

*   [Synopsis](/archives/4.1.2/genkeys/#synopsis)
*   [Description](/archives/4.1.2/genkeys/#description)
*   [Symmetric Key File Format](/archives/4.1.2/genkeys/#symmetric-key-file-format)
*   [Files](/archives/4.1.2/genkeys/#files)
*   [Bugs](/archives/4.1.2/genkeys/#bugs)

* * *

#### Synopsis

<tt>ntp-genkeys</tt>

* * *

#### Description

This program generates random keys used by either or both the NTPv3/NTPv4 symmetric key or the NTPv4 public key (Autokey) cryptographic authentication schemes. By default the program generates the <tt>ntp.keys</tt> file containing 16 random symmetric keys. In addition, if the <tt>rsaref20</tt> package is configured for the software build, the program generates cryptographic values used by the Autokey scheme. These values are incorporated as a set of three files, <tt>ntpkey</tt> containing the RSA private key, <tt>ntpkey__host_</tt> containing the RSA public key, where <tt>_host_</tt> is the DNS name of the generating machine, and <tt>ntpkey_dh</tt> containing the parameters for the Diffie-Hellman key-agreement algorithm. All files and are in printable ASCII format. A timestamp in NTP seconds is appended to each. Since the algorithms are seeded by the system clock, each run of this program produces a different file and file name.

The <tt>ntp.keys</tt> file contains 16 MD5 keys. Each key consists of 16 characters randomized over the ASCII 95-character printing subset. The file is read by the daemon at the location specified by the <tt>keys</tt> configuration file command and made visible only to root. An additional key consisting of a easily remembered password should be added by hand for use with the <tt>ntpq</tt> and <tt>ntpdc</tt> programs. The file must be distributed by secure means to other servers and clients sharing the same security compartment. While the key identifiers for MD5 and DES keys must be in the range 1-65534, inclusive, the <tt>ntp-genkeys</tt> program uses only the identifiers from 1 to 16. The key identifier for each association is specified as the key argument in the <tt>server</tt> or peer configuration file command.

The <tt>ntpkey</tt> file contains the RSA private key. It is read by the daemon at the location specified by the <tt>privatekey</tt> argument of the <tt>crypto</tt> configuration file command and made visible only to root. This file is useful only to the machine that generated it and never shared with any other daemon or application program.

The <tt>ntpkey__host_</tt> file contains the RSA public key, where <tt>_host_</tt> is the DNS name of the host that generated it. The file is read by the daemon at the location specified by the <tt>publickey</tt> argument to the <tt>server</tt> or <tt>peer</tt> configuration file command. This file can be widely distributed and stored without using secure means, since the data are public values.

The <tt>ntp_dh</tt> file contains two Diffie-Hellman parameters: the prime modulus and the generator. The file is read by the daemon at the location specified by the <tt>dhparams</tt> argument of the <tt>crypto</tt> configuration file command. The file can be distributed by insecure means to other servers and clients sharing the same key agreement compartment, since the data are public values.

The file formats begin with two lines, the first containing the generating system DNS name and the second the datestamp. Lines beginning with <tt>#</tt> are considered comments and ignored by the daemon. In the <tt>ntp.keys</tt> file, the next 16 lines contain the MD5 keys in order. If necessary, this file can be further customized by an ordinary text editor. The format is described in the following section. In the <tt>ntpkey</tt> and <tt>ntpkey__host_</tt> files, the next line contains the modulus length in bits followed by the key as a PEM encoded string. In the <tt>ntpkey_dh</tt> file, the next line contains the prime length in bytes followed by the prime as a PEM encoded string, and the next and final line contains the generator length in bytes followed by the generator as a PEM encoded string.

Note: See the file <tt>./source/rsaref.h</tt> in the <tt>rsaref20</tt> package for explanation of return values, if necessary.

#### Symmetric Key File Format

In the case of DES, the keys are 56 bits long with, depending on type, a parity check on each byte. In the case of MD5, the keys are 64 bits (8 bytes). <tt>ntpd</tt> reads its keys from a file specified using the <tt>-k</tt> command line option or the <tt>keys</tt> statement in the configuration file. While key number 0 is fixed by the NTP standard (as 56 zero bits) and may not be changed, one or more of the keys numbered 1 through 15 may be arbitrarily set in the keys file.

The key file uses the same comment conventions as the configuration file. Key entries use a fixed format of the form

_<tt>keyno type key</tt>_

where _<tt>keyno</tt>_ is a positive integer, _<tt>type</tt>_ is a single character which defines the key format, and _<tt>key</tt>_ is the key itself.

The key may be given in one of three different formats, controlled by the _<tt>type</tt>_ character. The three key types, and corresponding formats, are listed following.

<dt><tt>S</tt></dt>

The key is a 64-bit hexadecimal number in the format specified in the DES specification; that is, the high order seven bits of each octet are used to form the 56-bit key while the low order bit of each octet is given a value such that odd parity is maintained for the octet. Leading zeroes must be specified (i.e., the key must be exactly 16 hex digits long) and odd parity must be maintained. Hence a zero key, in standard format, would be given as <tt>0101010101010101</tt>.

<dt><tt>N</tt></dt>

The key is a 64-bit hexadecimal number in the format specified in the NTP standard. This is the same as the DES format, except the bits in each octet have been rotated one bit right so that the parity bit is now the high order bit of the octet. Leading zeroes must be specified and odd parity must be maintained. A zero key in NTP format would be specified as <tt>8080808080808080</tt>.

<dt><tt>A</tt></dt>

The key is a 1-to-8 character ASCII string. A key is formed from this by using the low order 7 bits of each ASCII character in the string, with zeroes added on the right when necessary to form a full width 56-bit key, in the same way that encryption keys are formed from Unix passwords.

<dt><tt>M</tt></dt>

The key is a 1-to-8 character ASCII string, using the MD5 authentication scheme. Note that both the keys and the authentication schemes (DES or MD5) must be identical between a set of peers sharing the same key number.

Note that the keys used by the <tt>ntpq</tt> and <tt>ntpdc</tt> programs are checked against passwords requested by the programs and entered by hand, so it is generally appropriate to specify these keys in ASCII format.

* * *

#### Files

The RSA Laboratories package <tt>rsaref20</tt> of cryptographic routines is necessary in order to build and use this program. 

#### Bugs

It can take quite a while to generate the RSA public/private key pair and Diffie-Hellman parameters, from a few seconds on a modern workstation to several minutes on older machines. 