---
title: "Network Time Protocol Leap Smear REFID"
type: archives
description: "This proposal offers a mechanism that provides a simple and clean method for NTP clients to trivially ask for leap-smeared time and detect a server that is offering leap-smeared time."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-leap-smear-refid-02
Published:    		11 July 2019 
Intended Status:	Standards Track
Expires:		12 January 2020
Author:			H. Stenn
			Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-leap-smear-refid/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-leap-smear-refid/#11-requirements-language)
*   [2. Leap smear REFID](/documentation/ietf/ntp-leap-smear-refid/#2-leap-smear-refid)
*   [3 Acknowledgements](/documentation/ietf/ntp-leap-smear-refid/#3-acknowledgements)
*   [4. IANA Considerations](/documentation/ietf/ntp-leap-smear-refid/#4-iana-considerations)
*   [5. Security Considerations](/documentation/ietf/ntp-leap-smear-refid/#5-security-considerations)
*   [6. Normative References](/documentation/ietf/ntp-leap-smear-refid/#6-normative-references)
*   [Author's address](/documentation/ietf/ntp-leap-smear-refid/#authors-address)

***

####  1. Introduction

Leap Seconds are applied as needed to UTC in order to keep its time of day close to UT1's mean solar time. 

[RFC 5905](/reflib/rfc/rfc5905.txt) and earlier versions of NTP are the overwhelming method of distributing time on networks. The timescale used by NTP is based on POSIX which, for better or worse, ignores any instances where there are not the ordinary 86,400 seconds per day. 

Leap Seconds will continue to exist for the foreseeable future, and similarly, POSIX can be expected to ignore leap seconds for the foreseeable future. 

Different applications have different requirements for the stability of time during the application of a leap second. Some applications are tolerant of a fast application of the correction, while other applications prefer to "smear" the leap second over a longer period, where the time reported by leap-second aware servers is gradually applied so there is no abrupt change to time during the processing of a leap second. 

While leap second processing can be expected to be properly handled by up-to-date software and by time servers, there are large numbers of out-of-date software installations and client systems that are just not able to properly handle a leap second correction. 

Additionally, some use-cases for calculating elapsed time (a "difference clock") that use POSIX timestamps are greatly complicated in the possible presence of a leap-second corrections. If the presence of leap-smeared time is of greater value than legally-correct time, leap smearing is the choice some administrators will take. 

This proposal offers a way for a system to generate a REFID that indicates that the time being supplied in the NTP packet already contains an amount of leap smear correction, and what that amount is. It also provides part of a solution whereby a client can receive leap-smeared time in the case where part of the leap smear occurs before the actual leap second, and the remainder of the leap smear occurs after the actual leap second.

***

##### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. Leap Smear REFID

[RFC 5905](/reflib/rfc/rfc5905.txt) defines the data type of NTP time values in Section 6, "Data Types":

_All NTP time values are represented in twos-complement format, with bits numbered in big-endian (as described in Appendix A of [RFC0791]) fashion from zero starting at the left, or high-order, position. ..._

The 32 bit signed integer seconds portion and the 32 bit unsigned fractional seconds portion, or 32:32 format is:

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            Seconds                            |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                            Fraction                           |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```

_Figure 1: NTP Timestamp Format (32:32)_

This format provides coverage for 136 years' time to a precision of 232 picoseconds. If a leap-second addition is being completely smeared just before before the stroke of the next POSIX second then the smear correction will be (0,1). If this was the only way to apply a leap smear correction then we could simply use an unsigned value to represent the correction. But while the first popular leap smear implementation applied the correction over an appropriate number of hours' time before the actual leap second so the system time was corrected at the stroke of 00:00, that meant that the difference between system time and UTC spent half of the duration of the smear application at [.5,1) "off" of correct time. The second popular implementation of the leap smear applied the first half-second correction before the stroke of 00:00 for a correction range of (0,.5] and the last half-second correction starting at the stroke of 00:00 for a [-.5,0) correction range. This also means we need a signed value to represent the amount of correction.

If a system implements the leap-smear REFID, the REFID of a system that is supplying smeared time to client requests while leap-smear correction is active would be 254.b1.b2.b3, where the three octets (b1, b2, and b3) are a 2:22 formatted value, yielding precision to 238 nanoseconds, or about a quarter of a microsecond. 

Note that if an NTP server decides to offer smeared time corrections to clients, it SHOULD only offer this time in response to CLIENT time requests. There is something to be said for further only offering smeared time to CLIENT time requests that show an LI value of 0, and perhaps 3. The reason for this is that if a client knows a leap second is pending, it can be expected to know how to process that leap second. An NTP server that is offering smeared time SHOULD NOT send smeared time in any peer exchanges. Also, CLIENT machines SHOULD NOT be distributing time (smeared or otherwise) to other systems. 

We also note that during the application of a leap smear, the REFID from a system offering smeared time cannot provide detection of a timing loop. This is not expected to be a problem because time server systems are not expected to make CLIENT connections with each other, so they should not be receiving smeared time. Moreso, if a time server is configured to make CLIENT connections to a server that offers smeared time, with the mechanism described here it can detect when it is getting smeared time, and either ignore time from that source, or "undo" the leap smear correction and use the corrected time for that sample. 

This proposal is not an attempt to justify servers offering leap smeared time. Its purpose is to make it easy to identify when a client is receiving smeared time, and provide the client a way to know the amount of smear correction as of the latest successful poll.

***

#### 3. Acknowledgements

The author wishes to acknowledge the contributions of Juergen Perlinger.

***

#### 4. IANA Considerations

This memo requests that IANA allocate a pseudo Extension Field Type of 0xFEFF so the proposed "I-Do" exchange can report whether or not this server can offer leap smeared time in response to CLIENT time requests, identifying the amount of correction using the above REFID.

***

#### 5. Security Considerations

No special or unusual security issues have been identified that are directly related to this proposal.

Additional information TBD.

***

#### 6. Normative References

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