---
title: "Anatomy of a Hollerith Card"
type: archives
toc_hide: true
---
 
![gif](/documentation/pic/ibmcarda.gif)  

[A Hollerith Card](/documentation/pic/ibmcard.webp)  

In 1896 Herman Hollerith organized the Tabulating Machines Company, which grew in subsequent mergers to become the IBM of today. The Hollerith punched card was the principal means for recording, accounting and archiving functions, not to mention the US census, until recently. In the early 1960's Hollerith cards were the only practical means to input programs for a IBM mainframe, but today these cards are seldom seen.

Hollerith cards have 12 rows and 80 columns. Decimal digits are encoded in rows 0-9, one per column as shown above. Other characters are encoded using these rows plus rows 11-12 above row 0. Programmers prepared input using the IBM 407 Printing Calculator and IBM 026 Card Punch, which were entirely mechanical. The 026 produced copious amounts of rectangular chad which we used in place of rice at weddings.

Coinciding with the rise and decline of Hollerith input was the Fortran scientific programming language. A few of us old hands still prefer Fortran over languages with sissy single-character names. The card above is preprinted with the fields used in preparing Fortran input. So far, this discourse is pretty boring; but, the real secrets lost to the younger generation is why the card has this format and why the Fortran fields are as they are. Read on.

The first scientific computer larger than a Volkswagen and capable of floating-point arithmetic was the IBM 704, which used vacuum tubes and magnetic core memory. It had a cycle time of 2.1 microseconds, a memory of 32,768 36-bit words, two 36-bit arithmetic registers and three 15-bit index registers. Fortran and a raft of other early programming languages were born from that womb.

The early designers were faced with the problem of adapting the Hollerith card to the 36-bit word used by the 704, especially how to bootstrap the machine with the punched-card loader program. The 704 online card reader was a most primitive device. It read cards by row starting from row 9. For each row the machine read bits from column 1 through 36 into one word, then bits from column 37 through 72 into the next. Machine operators knew this as 9-left format, but casual programmers had no idea what it meant. The same reader was used in the later 709 and its transistorized brother 709T; oops, I mean 7090.

As a young grad student, I had personal use of the 7090 on Sundays when the computing center was shut down. I arrived one Sunday morning and found the online card reader refused to budge. In fear for my dearly cherished machine time, I searched for a way to fix the thing. Looking inside for fuses, etc., I came upon a real live crank, just like for a Model T. Sure enough, I was able to spin the crank, ignite the bootstrap and light up the machine. Hollerith would approve.

Back to our story. Why were early Fortran program variable names limited to six characters? Well, the 704 packed six 6-bit Binary Coded Decimal (BCD) characters in one 36-bit word. Why were statement numbers limited to five digits? They were held in 15-bit index registers. Why does the business end of the card have 72 columns with an 8-character card identifier/sequence number at the end? Remember the online card reader? 9-left, 9-right, 8-left, 8-right,...

Eventually, the online card reader was supplanted by an offline IBM 1401 machine that was only smart enough to transcribe cards to magnetic tape for input and tape to printer for output. This machine had a much faster, more rugged card reader. However, it read the cards by column, not by row, so the 9-left card became obsolete. However, by this time the 9-left format had become embedded in library programs and a program was needed to transcribe this format to column-binary (aka Chinese Binary) format.

Writing that library program was my first paid programming job. Now you know why this page is here.