---
title: "Network Time Protocol I-Do Extension Field"
type: archives
description: "This proposal defines and describes a mechanism by which cooperating NTP instances may communicate any optional features they are willing to admit they support."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-i-do-06
Published:    		11 July 2019 
Intended Status:	Standards Track
Expires:		12 January 2020
Author:			H. Stenn
			Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-i-do/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-i-do/#11-requirements-language)
*   [2. The I-Do Extension Field](/documentation/ietf/ntp-i-do/#2-the-i-do-extension-field)
    *   [2.1. Overview](/documentation/ietf/ntp-i-do/#21-overview)
    *   [2.2. I-DO Packet Format](/documentation/ietf/ntp-i-do/#22-i-do-packet-format)
    *   [2.3. Behavior](/documentation/ietf/ntp-i-do/#23-behavior)
*   [3 Acknowledgements](/documentation/ietf/ntp-i-do/#3-acknowledgements)
*   [4. IANA Considerations](/documentation/ietf/ntp-i-do/#4-iana-considerations)
*   [5. Security Considerations](/documentation/ietf/ntp-i-do/#5-security-considerations)
*   [6.  References](/documentation/ietf/ntp-i-do/#6-references)
    *   [6.1. Normative References](/documentation/ietf/ntp-i-do/#61-normative-references)
	*   [6.2. Informative References](/documentation/ietf/ntp-i-do/#62-informative-references)
*   [Author's address](/documentation/ietf/ntp-i-do/#authors-address)

***

####  1. Introduction

The first implementation of NTPv4 was released in 2003, and was defined by [RFC 5905](/reflib/rfc/rfc5905.txt). It contains an optional and now obsolete public-key security protocol, Autokey, which is defined by [RFC 5906](/reflib/rfc/rfc5906.txt). Until very recently, Autokey has been the only implemented use of NTP packet Extension Fields. New proposals for extension fields are being written and there is currently no convenient way to learn if a remote instance of NTP supports any extension fields or not. This proposal contains a method to tell a remote instance of NTP what we (are willing to admit we) support, and ask what they (are willing to admit they) support.

***

#### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. The I-Do Extension Field

##### 2.1. Overview

The purpose of the I-DO EF is to provide information to the remote side about our capabilities.

If an incoming packet contains an unrecognized extension field, one of several things will happen. While that unrecognized extension field SHOULD be ignored, an implementation MAY choose to drop the entire packet. 

If any extension field is present there ordinarily SHOULD be a MAC following the extension field. However, an older conforming NTP implementation will require that any EF MUST be followed by a MAC. 

Some extension fields are unable to be "signed" by a MAC, regardless of whether or not that MAC is a traditional MAC or an extension field MAC. 

In the previous two cases, a conforming legacy system that receives these types of packets will interpret the unrecognized EF as a missing or legacy MAC, and return a crypto-NAK. 

If the remote system replies with a crypto-NAK, that is a good indication that it is running older software that does not recognize EFs and thinks we have sent an invalid MAC. In this case, we SHOULD NOT send that system newer EFs. 

If the remote system replies without including an I-DO-RESPONSE EF, we at least know they can handle EFs, but they either don't understand I-DO or are not willing to tell us anything. In this case, we SHOULD NOT send any newer EFs. 

If the remote system replies with a packet that includes an I-DO-RESPONSE EF, then we SHOULD remember what they told us, and use that information appropriately. In other words, we can exchange packets containing any new EFs that we agree on, and we should not exchange packets containing any new EFs that we have not agreed on. 

In client/server mode, it makes sense for the client to send an I-DO to the server, and notice how the server responds. While the server SHOULD respond with an I-DO-RESPONSE EF, it likely does not make sense for the server to send an I-DO EF in response to a client request. 

In symmetric mode, either side may initiate sending an I-DO EF, and the receiving side SHOULD reply with an I-DO-RESPONSE EF. 

In broadcast mode, the broadcast server MAY send broadcast packets that include an I-DO EF, but note that if, counter to recommended practice, these packets are unauthenticated they MAY cause client machines to misinterpret the packet as having invalid authentication. In this situation, the broadcast server SHOULD alternate sending broadcast server packets with and without an I-DO EF, to insure that all clients receive time packets they will accept. Note that if, as recommended, broadcast packets are authenticated, a conforming client SHOULD have no difficulty in receiving a broadcast (mode 5) packet from a server that includes an I-DO EF.

***

#### 2.2. I-DO Packet Format

The content of the I-DO extension field is an ordinary four octet Extension Field header followed by a payload consisting of an appropriate number of two octet I-DO values that use nonzero values to indicate a supported feature. An I-DO value of zero is ignored. The payload section must end on a four-octet boundary.

There are two types of nonzero I-DO values that may be used. They are both defined in the [IANA NTP Extension Field Table (Section 4)](https://www.iana.org/assignments/ntp-parameters/ntp-parameters.xhtml#ntp-parameters-3). These values are either Extension Field Types, where only the low-order values (0x01 thru 0xFE) are used, or I-DO Types, where all 16 bits are used and the bottom octet is currently always 0xFF. The examples below are built using information from the following Standards and proposals:

[RFC 5906](/reflib/rfc/rfc5906.txt)

[NTP-EXTENSION-FIELDS](/documentation/ietf/ntp-extension-fields/)

[MAC-LAST-EF](/documentation/ietf/ntp-mac-last-ef/)

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|          Field Type           |        Field Length           |
+-------------------------------+-------------------------------+
|            I-Do 1             |             ...               |
+-------------------------------+-------------------------------+
|            I-Do N             |            Padding            |
+---------------------------------------------------------------+
```

_Figure 1: NTP Extension Field: I-DO - Overview_

Field Type: 
: TBD (Recommendation for IANA: 0x0007 (I-Do), 0x8007 (I-Do Response))

Field Length: 
: as needed

Payload: 
: An enumeration of the supported base Field Types, followed by any zero padding (0x0000) needed to fill the payload to the desired 32-bit boundary.

Example: A system that wants to advertise support for Autokey and I-DO, sending to a system that responds with support for I-DO, NTS, MAC-EF, and LAST-EF.

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|    Field Type (0x0007)        |   Field Length (0x0008)       |
+-------------------------------+-------------------------------+
|            0x0007             |           0x0002              |
+-------------------------------+-------------------------------+
```

_Figure 2: NTP Extension Field: I-Do - Example_

```
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+---------------+---------------+-------------------------------+
|    Field Type (0x8007)        |   Field Length (0x000a)       |
+-------------------------------+-------------------------------+
|            0x0003             |           0x0004              |
+-------------------------------+-------------------------------+
|            0x0007             |           0x0008              |
+-------------------------------+-------------------------------+
```

_Figure 3: NTP Extension Field: I-Do Response - Example_

***

##### 2.3. Behavior

The sender of any I-Do extension field MUST send an extension field with a Field Type of 0x0007 (I-Do) and SHOULD include a payload with any 0x0000 padding values after enumerating the supported base Extension Field Types. If the responding system recognizes the I-Do extension field, its response MUST include an extension field with a Field Type of 0x8007 (I-Do Response), and SHOULD include a payload with any 0x0000 padding values after enumerating the supported base Extension Field Types.

Any system that receives an I-Do extension field as either an "offer" or a "response" SHOULD scan the entire payload looking for nonzero values that specify the capabilities of the remote association. 

Any system that receives an I-Do "offer", 0x0007, SHOULD reply with an I-Do "response", 0x8007. 

Any system that sends an I-Do "offer" or "response" may send as few or as many of its supported Field Types as it chooses. At any subsequent time, either side may re-negotiate the list of supported field types it is prepared to accept from the other system by sending a new I-Do extension field. 

The most-recently received I-Do list replaces any previous I-Do list.

***

#### 3. Acknowledgements

The author wishes to acknowledge the contributions of Sam Weiler.

***

#### 4. IANA Considerations

This memo requests IANA to allocate NTP Extension Field Types:

* 0x0007 (I-DO)

* 0x8007 (I-DO Response)

and NTP Extension Field I-DO types:

* 0x00FF through

* 0xFDFF Reserved for future I-DO types

* 0xFEFF (I-DO Leap Smear REFIDs)

* 0xFFFF (I-DO IPv6 REFID hash)

for this proposal.

***

#### 5. Security Considerations

No addtional or unusual security considerations are expected if this proposal is adopted.

No feedback has been received suggesting this proposal creates any new security considerations.

***

#### 6. References

##### 6.1. Normative References

[RFC2119]
: Bradner, S., "Key words for use in RFCs to Indicate Requirement Levels", BCP 14, RFC 2119, DOI 10.17487/RFC2119, March 1997, <https://www.rfc-editor.org/info/rfc2119>.

[RFC5905]
: Mills, D., Martin, J., Ed., Burbank, J., and W. Kasch, "Network Time Protocol Version 4: Protocol and Algorithms Specification", RFC 5905, DOI 10.17487/RFC5905, June 2010, <https://www.rfc-editor.org/info/rfc5905>.

***

#### 6.2. Informative References

[DRAFT-MAC-LAST-EF]
: Stenn, H., "draft-stenn-ntp-mac-last-ef", 2018.

[NTP-EXTENSION-FIELD]
: Stenn, H., "draft-stenn-ntp-extension-fields", 2018.

[RFC5906]
: Haberman, B., Ed. and D. Mills, "Network Time Protocol Version 4: Autokey Specification", RFC 5906, DOI 10.17487/RFC5906, June 2010, <https://www.rfc-editor.org/info/rfc5906>.

***

#### Author's Address

Harlan Stenn
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: stenn@nwtime.org

***