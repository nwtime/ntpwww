---
title: "Network Time Protocol: TCP Services"
type: archives
description: "Traditionally, NTP has only used UDP. Since UDP packets have length limits, and there are rate limits imposed by the protocol specification, TCP can be used for efficient exchange of larger data packets and to perform better authentication and authorization checks."
---

```
Workgroup:		Internet Engineering Task Force
Internet-Draft:		draft-stenn-ntp-tcp-services-00
Published:    		10 July 2018 
Intended Status:	Standards Track
Expires:		11 January 2019
Author:			H. Stenn, Network Time Foundation
			D. Mills, Network Time Foundation
			P. Prindeville, Network Time Foundation
```					
					
#### Table of Contents

*   [1. Introduction](/documentation/ietf/ntp-tcp-services/#1-introduction)
    *   [1.1. Requirements Language](/documentation/ietf/ntp-tcp-services/#11-requirements-language)
*   [2. NTP TCP Services](/documentation/ietf/ntp-tcp-services/#2-ntp-tcp-services)
*   [3. IANA Considerations](/documentation/ietf/ntp-tcp-services/#3-iana-considerations)
*   [4. Security Considerations](/documentation/ietf/ntp-tcp-services/#4-security-considerations)
*   [5. Normative References](/documentation/ietf/ntp-tcp-services/#5-normative-references)
*   [Authors' addresses](/documentation/ietf/ntp-tcp-services/#authors-addresses)

***

####  1. Introduction

NTP was assigned port number 123 in 1985, in RFC 960. The NTP protocol only uses UDP for its work, and UDP is an appropriate protocol for time synchronization. However, there are other needs for NTP, including monitoring and control, and ephemeral key exchange.

For some of these cases, a TCP connection is much better.

This specification describes a high-level framework for providing TCP services for NTP.

*** 

##### 1.1. Requirements Language

The key words "MUST", "MUST NOT", "REQUIRED", "SHALL", "SHALL NOT", "SHOULD", "SHOULD NOT", "RECOMMENDED", "MAY", and "OPTIONAL" in this document are to be interpreted as described in [RFC 2119](https://datatracker.ietf.org/doc/html/rfc2119).

***

#### 2. NTP TCP Services

To provide NTP TCP Services, an NTP instance establishes communications with a TCP Listener. This could be a separate process or it could be part of the NTP daemon. Support STARTTLS. [RFC 5705](https://datatracker.ietf.org/doc/html/rfc5705) [RFC7301](https://datatracker.ietf.org/doc/html/rfc7301)

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