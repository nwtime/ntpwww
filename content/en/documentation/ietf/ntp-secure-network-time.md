---
title: "Network Time Protocol: Secure Network Time"
type: archives
description: "The proposal specifies a means for NTP instances that can establish a TCP connection between themselves to create secure ephemeral keys. With the known weaknesses of the public-key security protocol, Autokey, which is defined by RFC 5906, a replacement for Autokey that supports at least Client/Server and Symmetric modes must be provided."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-secure-network-time-00
Published:    		10 July 2018 
Intended Status:	Standards Track
Expires:		11 January 2019
Author:			H. Stenn, Network Time Foundation
			D. Mills, Network Time Foundation
			P. Prindeville, Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-secure-network-time/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-secure-network-time/#11-requirements-language)
*   [2. Secure Network Time](/documentation/ietf/ntp-secure-network-time/#2-secure-network-time)
*   [3. IANA Considerations](/documentation/ietf/ntp-secure-network-time/#3-iana-considerations)
*   [4. Security Considerations](/documentation/ietf/ntp-secure-network-time/#4-security-considerations)
*   [5.  Normative References](/documentation/ietf/ntp-secure-network-time/#5-normative-references)
*   [Authors' addresses](/documentation/ietf/ntp-secure-network-time/#authors-addresses)

***

####  1. Introduction

From almost the beginning, NTP has provided a mechanism to authenticate an NTP packet. To date, that mechanism is a Message Authentication Code, or MAC. The MAC is comprised of two subfields, a 32-bit keyID and a signature. A keyID with a value between 1 and 65535, inclusive, is a symmetric key. A keyID with a value greater than 65535 is not provided by the symmetric key file, and has traditionally been negotiated ephemerally, with Autokey, defined by [RFC 5906](/reflib/rfc/rfc5906.txt), being one example.

The mechanism by which keys are exchanged between NTP instance can be thought of as a black-box exchange. One of these black-box key exchange mechanisms is "the way the ntp.keys file containing symmetric keys is distributed." Another way keys have been exchaned is via Autokey.

This Secure Network Time proposal uses the NTP TCP Services mechanism to perform key exchange, follwed by negotiation of a keyID, a hash algorithm, and a secret key over a TLS connection. Once this has been done, each participant can use the keyID, hash algorithm, and secret key to provide MAC protection for NTP packets, using ephemeral keys that can be re-negotiated as-needed.

Should additional security measures be desired, for example using a cookie as additional replay prevention, that can be easily provided.

***

##### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. Secure Network Time

Secure Network Time uses "NTP TCP Services" to perform key exchange over a TLS connection, followed by an agreement on a keyID, hash algorithm, and a secret. With the secure communication of a keyID, a cryptographically strong hash algorithm, and a secret of sufficient strength, we have an ephemeral key exchange mechanism that provides MAC authentication for NTP packets.

***

#### 3. IANA Considerations

TBD

***

#### 4. Security Considerations

Additional information TBD

***

#### 5. Normative References

[RFC2119]
: Bradner, S., "Key words for use in RFCs to Indicate Requirement Levels", BCP 14, RFC 2119, DOI 10.17487/RFC2119, March 1997, <https://www.rfc-editor.org/info/rfc2119>.

[RFC5905]
: Mills, D., Martin, J., Ed., Burbank, J., and W. Kasch, "Network Time Protocol Version 4: Protocol and Algorithms Specification", RFC 5905, DOI 10.17487/RFC5905, June 2010, <https://www.rfc-editor.org/info/rfc5905>.

[RFC5906]
: Haberman, B., Ed. and D. Mills, "Network Time Protocol Version 4: Autokey Specification", RFC 5906, DOI 10.17487/RFC5906, June 2010, <https://www.rfc-editor.org/info/rfc5906>.

***

#### Authors' Addresses

Harlan Stenn
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: stenn@nwtime.org

David L. Mills
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: mills@udel.edu

Philip Prindeville
: Network Time Foundation
: P.O. Box 918
: Talent, OR, 97540
: United States of America
: Email: prindeville@ntp.org

***