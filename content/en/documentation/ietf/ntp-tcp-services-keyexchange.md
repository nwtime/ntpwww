---
title: "Network Time Protocol: TCP Services: Key Exchange"
type: archives
description: "This document describes the Key Exchange commands that are included in the NTP TCP Services protocol, which is used to implement the Secure Network Time protocol."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-tcp-services-keyexchange-00
Published:    		10 July 2018 
Intended Status:	Standards Track
Expires:		11 January 2019
Author:			H. Stenn, Network Time Foundation
			D. Mills, Network Time Foundation
			P. Prindeville, Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-tcp-services-keyexchange/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-tcp-services-keyexchange/#11-requirements-language)
*   [2. NTP TCP Services: Key Exchange](/documentation/ietf/ntp-tcp-services-keyexchange/#2-ntp-tcp-services-key-exchange)
*   [3. IANA Considerations](/documentation/ietf/ntp-tcp-services-keyexchange/#3-iana-considerations)
*   [4. Security Considerations](/documentation/ietf/ntp-tcp-services-keyexchange/#4-security-considerations)
*   [5. Normative References](/documentation/ietf/ntp-tcp-services-keyexchange/#5-normative-references)
*   [Authors' addresses](/documentation/ietf/ntp-tcp-services-keyexchange/#authors-addresses)

***

####  1. Introduction

The NTP Secure Network Time proposal relies on the secure pre-exchange of information to create and validate NTP MACs,

This secure pre-exchange is performed using NTP TCP Services.

This document describes that protocol.

*** 

##### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. NTP TCP Services: Key Exchange

To perform the key exchange for Secure Network Time, one side opens a TCP connection to the other host, performs any initial handshake, and SHOULD issue a STARTTLS directive to create a secure channel between the two processes.

Once that has been done, ... 

[RFC 5705](https://datatracker.ietf.org/doc/html/rfc5705)

[RFC7301](https://datatracker.ietf.org/doc/html/rfc7301)

[Show how this works for Client/Server mode] 

[Show how this works for symmetric mode] 

[Show how this work for manycast/multicast] 

[Show how this would work for broadcast mode where the client can open a connection to the server]

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

[RFC5705]
: Rescorla, E., "Keying Material Exporters for Transport Layer Security (TLS)", RFC 5705, DOI 10.17487/RFC5705, March 2010, <https://www.rfc-editor.org/info/rfc5705>.

[RFC5905]
: Mills, D., Martin, J., Ed., Burbank, J., and W. Kasch, "Network Time Protocol Version 4: Protocol and Algorithms Specification", RFC 5905, DOI 10.17487/RFC5905, June 2010, <https://www.rfc-editor.org/info/rfc5905>.

[RFC5906]
: Haberman, B., Ed. and D. Mills, "Network Time Protocol Version 4: Autokey Specification", RFC 5906, DOI 10.17487/RFC5906, June 2010, <https://www.rfc-editor.org/info/rfc5906>.

[RFC7301]
: Friedl, S., Popov, A., Langley, A., and E. Stephan, "Transport Layer Security (TLS) Application-Layer Protocol Negotiation Extension", RFC 7301, DOI 10.17487/RFC7301, July 2014, <https://www.rfc-editor.org/info/rfc7301>.

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