---
title: "Time and Standard Frequency Station TDF (France)"
description: "Information about TDF, an amplitude modulated longwave broadcasting station, transmitting the programs of the France-Inter Network of Telediffusion
de France (TDF)."
type: archives
---

Information provided by Richard B. Langley, University of New Brunswick

* * *

<pre>
Station:       TDF, Allouis, France

Address:       Centre National d'Etudes des Telecommunications
               PAB - STC - Etalons de frequence et de temps
               196 avenue Henri Ravera
               F - 92220  Bagneux
               France

Coordinates:   47d 10' N, 2d 12' E

Frequency:     162 kHz

Power:         2,000 kW

Schedule:      continuous except every Tuesday from 01:00 to 05:00 UTC

Form of Time Signals:

TDF is an amplitude modulated longwave broadcasting station,
transmitting the programs of the France-Inter Network of Telediffusion
de France (TDF). Time signals are transmitted by phase modulation of the
carrier by + and -1 radian in 0.1 s every second except the 59th second
of each minute. This modulation is doubled to indicate binary 1.  The
numbers of the minute, hour, day of the month, day of the week, month
and year are transmitted each minute from the 21st to the 58th second,
in accordance with the French legal time scale.  In addition, a binary 1
at the 17th second indicates that the local time is 2 hours ahead of UTC
(i.e., summer time), a binary 1 at the 18th second indicates when the
local time is 1 hour ahead of UTC (i.e., winter time).  A binary 1 at
the 14th second indicates that the current day is a public holiday (14
July, Christmas, etc.) and a binary 1 at the 13th second indicates that
the current day is the day before a public holiday.

Relative Uncertainty of the Carrier Frequency:  2 parts in 10^12.

Radio Clocks Available:

Horloge 59 HF
  BHL Electronique
  Zone Industrielle
  B.P. 8
  F - 14540  Bourguebus
  France

Recepteur horaire sur France-Inter G-O
  Dyna Electronique
  36 avenue Gambetta
  F - 75980  Paris Cedex 20
  France

RTD 101
  telematique SA
  Zirst-chemin des pres
  F - 38240  Meylan
  France

Information Sources:
Annual Report of the BIPM Time Section for 1989, Bureau International
des Poids et Mesures, Pavillon de Breteuil, F - 92312 Sevres Cedex,
France.

Zeitzeichensender / Time Signal Stations (bilingual: German and English)
by Gerd Klawitter, Siebel Verlag, Bonhoeffer Weg 16, D-5309  Meckenheim,
Germany.

The phase modulation pattern.
-----------------------------

One signal element consists of the following : the phase of the carrier
is advanced linearly up to +1 radian in 0.025 second, then retarded
linearly up to -1 rad in 0.050 second, then advanced again to reach zero
after another 0.025 second. One signal element is always sent at each
second between 0 and 58. The epoch is when the down ramp crosses zero.
If a '1' bit is to be stransmitted, two signal elements are sent in
sequence. Since the phase is the integral of the frequency, to this
triangular phase modulation corresponds a square frequency modulation
with an amplitude of about + and - 6Hz.

                 binary '0'                      binary '1'


                 / \                       / \         / \
  phase     ___ /   \       ___       ___ /   \       /   \       ___
                      \   /                     \   /       \   /
                       \ /                       \ /         \ /

   (0.025 s    |  |  |  |  |             |  |  |  |  |  |  |  |  |
    ticks)           |                         |
                   epoch                     epoch

                __       __               __       _____       __
               |  |     |  |             |  |     |     |     |  |
 frequency  ___|  |     |  |___       ___|  |     |     |     |  |___
                  |     |                   |     |     |     |
                  |_____|                   |_____|     |_____|

Both the average phase and the average frequency deviation are thus
zero. More data is sent by phase modulation during the rest of each
second. But the second marker (and data bit) is always preceded by 0.1
second without modulation. There is no marker at the beginning of the
59th second, nor any data sent during the entire duration of that
second.

The binary encoding of date and time data.
------------------------------------------

Seconds 20 to 58 carry exactly the same information as the signal of the
German transmitter DCF77.
</pre>
