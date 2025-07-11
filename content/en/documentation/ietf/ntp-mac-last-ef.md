---
title: "Network Time Protocol MAC/Last Extension Fields"
type: archives
description: "NTP packets can be authenticated by a Message Authentication Code (MAC) if a MAC is present at the end of an NTP packet. The legacy format for this MAC is not formatted as an NTP Extension Field, and its presence may cause some implementations a parsing ambiguity. This proposal introduces two ways to resolve this problem."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-mac-last-ef-04
Published:    		11 July 2019 
Intended Status:	Standards Track
Expires:		12 January 2020
Author:			H. Stenn, Network Time Foundation
			D. Mayer, Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-mac-last-ef/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-mac-last-ef/#11-requirements-language)
*   [2 The Last Extension Field Extension Field: LAST-EF](/documentation/ietf/ntp-mac-last-ef/#2-the-last-extension-field-extension-field-last-ef)
*   [3 MAC Extension Field](/documentation/ietf/ntp-mac-last-ef/#3-mac-extension-field)
*   [4. Acknowledgements](/documentation/ietf/ntp-mac-last-ef/#4-acknowledgements)
*   [5. IANA Considerations](/documentation/ietf/ntp-mac-last-ef/#5-iana-considerations)
*   [6. Security Considerations](/documentation/ietf/ntp-mac-last-ef/#6-security-considerations)
*   [7. Normative References](/documentation/ietf/ntp-mac-last-ef/#7-normative-references)
*   [Authors' addresses](/documentation/ietf/ntp-mac-last-ef/#authors-addresses)

***

####  1. Introduction

NTPv4 is defined by [RFC 5905](/reflib/rfc/rfc5905.txt), and it and earlier versions of the NTP Protocol have supported symmetric private key Message Authentication Code (MAC) authentication. MACs were first described in Appendix C of [RFC 1305](/reflib/rfc/rfc1305/rfc1305b.pdf) and are further described in [RFC 5905](/reflib/rfc/rfc5905.txt). As the number of Extension Fields grows there is an increasing chance some implementations will find a parsing ambiguity when deciding if the "next" set of data is an Extension Field or a legacy MAC. This proposal defines two new Extension Fields to avoid this potential ambiguity. One, LAST-EF, is used to signify that it is the last Extension Field in the packet. If the LAST-EF is present, any subsequent data MUST be considered to be a legacy MAC, or if you prefer, any subsequent data MUST NOT be considered to be an EF. The other, MAC-EF, allows one or more MACs to be encapsulated in an Extension Field. If all parties in an association support MAC-EF, the use of a legacy MAC may be avoided.

***

#### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. The Last Extension Field Extension Field: LAST-EF

Now that multiple extension fields are a possibility, additional packet data could be either an Extension Field or a legacy MAC. Having a means to indicate that there are no more Extension Fields in an NTP packet and any subsequent data MUST be something else, almost certainly a legacy MAC, is a valuable facility.

The format of a LAST-EF is an Extension Field comprised of an identified Field Type and an appropriate Field Length. 

In the example below the Field Length in the LAST-EF is 4, because there is clearly no need in this case for the 28 octets required by [RFC 7822](https://datatracker.ietf.org/doc/html/rfc7822). But the LAST-EF could have any supported length, as any payload is ignored.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|          Field Type           |        Field Length           |
+-------------------------------+-------------------------------+
```

_Figure 1: NTP Extension Field: Last Extension Field - LAST-EF_

Field Type: 
: TBD (Recommendation for IANA: 0x0008 (Last Extension Field))

Field Length: 
: 4 (minimum)

Payload: 
: Ignored if present - none needed. SHOULD be zeroes.

Example:

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|     Field Type (0x0008)       |    Field Length (0x0004)      |
+-------------------------------+-------------------------------+
|                          MAC Key ID                           |
+-------------------------------+-------------------------------+
|                            Sixteen                            |
+-------------------------------+-------------------------------+
|                             Octets                            |
+-------------------------------+-------------------------------+
|                              of                               |
+-------------------------------+-------------------------------+
|                              MAC                              |
+-------------------------------+-------------------------------+
```

_Figure 2: Example: NTP Extension Field: Last Extension Field, followed by a Legacy MAC_

***

#### 3. MAC Extension Field

Now that multiple extension fields are a possibility, there is a chance that additional packet data could be either an Extension Field or a legacy MAC. There is benefit to encapsulating the MAC in an extension field. By encapsulating the MAC in an EF, we also have the option to include multiple MACs in a packet, which may be of use in broadcast scenarios, for example.

There are two forms of this extension field. The first supports a single MAC, requiring 4 octets' overhead for the EF header. The second form supports one or more MACs in the EF payload, and requires at least 8 octets. 

The format of a MAC-EF is an Extension Field comprised of an identified Field Type and an appropriate Field Length. 

A Field Type value of TBD (0x0003 is suggested) identifies this extension field as a MAC Extension field for a single MAC. In this case, the payload consists of the four octet MAC Key ID followed by the MAC digest, and any desired (possibly random data) padding. 

A Field Type value of TBD (0x0103 is suggested) identifies this extension field as a MAC extension field for one or more MACs. In this case, the payload consists of an unsigned 16-bit MAC Count (N) followed by N unsigned 16-bit MAC length fields. If there are an even number of MACs specified there is an unused 16-bit field which SHOULD be 0x0000 at the end of the set of MAC length values so that the subsequent MAC data is longword (4-octet) aligned. Each MAC SHALL be padded so that any subsequent MAC starts on a 4-octet boundary. Optional (possibly random data) padding is allowed.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|     Field Type (0x0003)       |        Field Length           |
+-------------------------------+-------------------------------+
.                         MAC 1 Key ID                          .
.                                       +-+-+-+-+-+-+-+-+-+-+-+-.
.         MAC 1 Key Data                | Random Data Padding   .
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

_Figure 3: NTP Extension Field: MAC EF Format (Single MAC)_

Field Type: 
: TBD (Recommendation for IANA: 0x0003 (MAC-EF: Single MAC))

Field Length:
: As needed.

Payload:
: As described.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|     Field Type (0x0103)       |        Field Length           |
+-------------------------------+-------------------------------+
|          MAC Count            |        MAC 1 Length           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          MAC 2 Length         |        MAC 3 Length           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                         MAC 1 Key ID                          .
.                                       +-+-+-+-+-+-+-+-+-+-+-+-.
.         MAC 1 Key Data                | Random Data Padding   .
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                         MAC 2 Key ID                          .
.                                     +-+-+-+-+-+-+-+-+-+-+-+-+-.
.        MAC 2 Key Data               | Random Data Padding     .
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
.                         MAC 3 Key ID                          .
.                                           +-+-+-+-+-+-+-+-+-+-.
.          MAC 3 Key Data                   |Random Data Padding.
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Padding (as needed)                     |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

_Figure 4: NTP Extension Field: MAC EF Format (1 or more MACs)_

Field Type: 
: TBD (Recommendation for IANA: 0x0103 (MAC-EF: 1 or more MACs))

Field Length: 
: As needed.

Payload: 
: As described. 

A MAC consisting of 4 octets of zeros means the MAC is a crypto-NAK, as defined by [RFC 5905](/reflib/rfc/rfc5905.txt). 

Additional MACs SHOULD NOT be present if there is a crypto-NAK present in the packet. 

Each MAC within the extension field consists of a 32-bit key identifier which SHOULD be unique to the set of key identifiers in this MAC extension field followed by ((MAC Length) - 4) octets of data, optionally followed by random octets to pad the key data to the length specified earlier in the extension field. That key identifier is a shared secret which defines the algorithm to be used and a cookie or secret to be used in generating the digest. The MAC digest is produced by hashing the data from the beginning of the NTP packet up to but not including the start of the MAC extension field. The calculation of the digest SHOULD be a hash of this data concatenated with the 32-bit keyid (in network-order), and the key. When sending or receiving a key identifier each side needs to agree on the key identifier, algorithm and the cookie or secret used to produce the digest along with the digest lengths. Note that the sender may send more bytes than are required by the digest algorithm. This would be done to make it more difficult for a casual observer to identify the algorithm being used based on the length of the data. The digest data begins immediately after the key ID, and any padding octets SHOULD be random.

***

#### 4. Acknowledgements

MAC-EF: The authors gratefully acknowledge Dave Mills for his insightful comments. Hal Murray asked if there was a way for the MAC-EF to require only 4 octets of overhead if there was only a single MAC in the payload.

*** 

#### 5. IANA Considerations

This memo requests IANA to allocate NTP Extension Field Types:

* 0x0003 MAC-EF (Single MAC)

* 0x0103 MAC-EF (1 or more MACs)

* 0x0008 LAST-EF

***

#### 6. Security Considerations

The security considerations of time protocols in general are discussed in [RFC 7384](https://www.rfc-editor.org/rfc/rfc7384.html), and the security considerations of NTP are discussed in [RFC 5905](/reflib/rfc/rfc5905.txt).

Digests MD5, DES and SHA-1 are considered compromised and should not be used [COMP]. 

[DISCUSS] Each MAC length should be at least 20 octets long to allow for 4 octets of key ID and at least 16 octets of digest and random padding. For a 128-bit digest, there would be 4 octets of key ID, 16 octets of digest, plus any desired octets of random padding. For SHA-256 digests there are 4 octets of key ID, 32 octets digest, plus any desired octets of random padding. Using MAC lengths that include random padding may make it more difficult for an attacker to know which digest algorithms are used.

***

#### 7. Normative References

[RFC1305]
: Mills, D., "Network Time Protocol (Version 3) Specification, Implementation and Analysis", RFC 1305, DOI 10.17487/RFC1305, March 1992, <https://www.rfc-editor.org/info/rfc1305>.

[RFC2119]
: Bradner, S., "Key words for use in RFCs to Indicate Requirement Levels", BCP 14, RFC 2119, DOI 10.17487/RFC2119, March 1997, <https://www.rfc-editor.org/info/rfc2119>.

[RFC5905]
: Mills, D., Martin, J., Ed., Burbank, J., and W. Kasch, "Network Time Protocol Version 4: Protocol and Algorithms Specification", RFC 5905, DOI 10.17487/RFC5905, June 2010, <https://www.rfc-editor.org/info/rfc5905>.

[RFC7384]
: Mizrahi, T., "Security Requirements of Time Protocols in Packet Switched Networks", RFC 7384, DOI 10.17487/RFC7384, October 2014, <https://www.rfc-editor.org/info/rfc7384>.

[RFC7822]
: Mizrahi, T. and D. Mayer, "Network Time Protocol Version 4 (NTPv4) Extension Fields", RFC 7822, DOI 10.17487/RFC7822, March 2016, <https://www.rfc-editor.org/info/rfc7822>.

***

#### Authors' Addresses

Harlan Stenn
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: stenn@nwtime.org

Danny Mayer
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: mayer@ntp.org

***