---
title: "Network Time Protocol Extended Information Extension Field"
type: archives
description: "The core network packet used by NTP has no spare bits available for reporting additional state information and no larger data areas available for larger amounts of information. This proposal offers a new extension field that would contain this additional information."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-extended-information-04
Published:    		10 July 2019 
Intended Status:	Standards Track
Expires:		11 January 2020
Author:			H. Stenn
			Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-extended-information-ef/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-extended-information-ef/#11-requirements-language)
*   [2. The Extended Information Extension Field](/documentation/ietf/ntp-extended-information-ef/#2-the-extended-information-extension-field)
    *   [2.1. Version 0 Content Descriptor and Content Data Fields](/documentation/ietf/ntp-extended-information-ef/#21-version-0-content-descriptor-and-content-data-fields)
*   [3. Acknowledgements](/documentation/ietf/ntp-extended-information-ef/#3-acknowledgements)
*   [4. IANA Considerations](/documentation/ietf/ntp-extended-information-ef/#4-iana-considerations)
*   [5. Security Considerations](/documentation/ietf/ntp-extended-information-ef/#5-security-considerations)
*   [6. Normative References](/documentation/ietf/ntp-extended-information-ef/#6-normative-references)
*   [Author's address](/documentation/ietf/ntp-extended-information-ef/#authors-address)

***

#### 1. Introduction

The core NTP packet format has changed little since [RFC 958](/reflib/rfc/rfc958.txt) was published in 1985. Since then, there has been demonstrated need to convey additional information about NTP's state in an NTP packet but no backward-compatible way to usurp the few otherwise potentially available bits has been found, and no larger data areas are available in the core packet structure. This proposal offers a new extension field that would contain this additional information.

*** 

##### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

*** 

#### 2. The Extended Information Extension Field

The Field Type of the Extended Information EF includes a version number field in the low-order bits of the first octet, to make it easier to evolve this specification. The initial specification for this proposal uses Version 0, which equates to 0x0009 [ADJUST AS NEEDED BASED ON IANA, IF AN IANA REGISTRY IS USED]. A future revision for Version 1 would use 0x0109 [IBID].
The payload for Version 0 is comprised of a two octet Content Descriptor followed by a two octet Content Data field, as described below.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|          Field Type           |        Field Length           |
+-------------------------------+-------------------------------+
|     Content Descriptor 1      |       Content Data 1          |
+---------------------------------------------------------------+
```

_Figure 1: NTP Extension Field: Extended Information_

Field Type: 
: TBD (Recommendation for IANA: 0x0009 (Extended-Information, Version 0))

Field Length: 
: as needed

*** 

##### 2.1. Version 0 Content Descriptor and Content Data fields

There are 16 bits available for state information in the Version 0 Extended Information Content Descriptor. These bits are allocated as follows:

0x0001:
: TAI Offset is stored in the low-order 8 bits (the second octet) of the Content Data.

0x0002:
: Interleave Mode indicator in the low order bit of the first octet of the Content Data. [NOTE: this may not be useful, and it can be removed if desired. It can serve as a belt-and-suspenders way to identify when a packet contains interleaved timestamps.]

0xFFFD:
: Reserved for future versions. SHOULD be zeroes for Version 0, and the meaning of any nonzero values is unspecified.

The Content Data field of the Version 0 Extended Information extension field is comprised of two octets, with the contents allocated as follows:

0xXXNN:
: The low-order 8 bits (NNNN) are the TAI Offset. Any data in the high-order 8 bits (XXXX) are not part of the TAI Offset.

0xX0XX:
: A value of 0 in the low-order bit of the first octet indicates that the timestamps in the base packet are not interleave-mode timestamps.

0xX1XX:
: A value of 1 in the low-order bit of the first octet indicates that the timestamps in the base packet are interleave-mode timestamps.

0xN2XX:
: thru

0xNDXX:
: Any of the seven high-order bits in the first octet are reserved for future versions and SHOULD be zero for Version 0. The meaning of any nonzero values is unspecified.

```
 Content Descriptor 1     Content Data 1
         0x0001         TAI offset in the low-order 8 bits, 24-31
         0x0002         Interleave Mode indicator in Bit 23
         0xFFFD         Reserved (Zeroes)

 Interleave Mode: 1 if the sender is in interleave mode, 0 otherwise
```

_Figure 2: NTP Extension Field: Extended Information, Version 0 Content Fields_

Example: A system that wants to convey an offset to TAI of 36 seconds, and show it is in interleave mode.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|    Field Type (0x0009)        |   Field Length (0x0008)       |
+-------------------------------+-------------------------------+
|            0x0003             |           0x0124              |
+-------------------------------+-------------------------------+
```

_Figure 3: NTP Extension Field: Extended Information V0, Example_


*** 

#### 3. Acknowledgements

The author wishes to acknowledge the contributions of Martin Burnicki and Sam Weiler.

*** 

#### 4. IANA Considerations

This memo requests IANA to allocate NTP Extension Field Type

`0x0009 (Extended-Information, Version 0)`

for this proposal.

#### 5. Security Considerations

No unusual or special security considerations are known to be associated with this proposal.

***

#### 6. Normative References

[RFC0958]
: Mills, D., "Network Time Protocol (NTP)", RFC 958, DOI 10.17487/RFC0958, September 1985, <https://www.rfc-editor.org/info/rfc958>. 

[RFC2119]
: Bradner, S., "Key words for use in RFCs to Indicate Requirement Levels", BCP 14, RFC 2119, DOI 10.17487/RFC2119, March 1997, <https://www.rfc-editor.org/info/rfc2119>. 

[RFC5905]
: Mills, D., Martin, J., Ed., Burbank, J., and W. Kasch, "Network Time Protocol Version 4: Protocol and Algorithms Specification", RFC 5905, DOI 10.17487/RFC5905, June 2010, <https://www.rfc-editor.org/info/rfc5905>. 

***

#### Author's Address

Harlan Stenn
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: stenn@nwtime.org

***
