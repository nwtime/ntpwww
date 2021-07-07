/*
 * Basic/interleaved NTP protocol simulator
 *
 * This simulates the NTP bsid/interleaved protocol under
 * various conditions of packet loss or duplicate and when
 * the protocol is restarted or whether packets cross in
 * flight.
 */
#include "xlev.h"

/*
 * Globals
 */
int	n;			/* timestamp count */
int	tcnt;			/* successful measurements */
double	dupe = 0;		/* duplicate threshold */
double	odupe = 0;		/* old duplicate */
double	drop = 0;		/* drop threshold */
double	xreset = 0;		/* reset threshold */
int	maxsim = 40;		/* max simulation cycles */
int	polla = 8;		/* poll A */
int	pollb = 8;		/* poll B */
int	debug = 0;		/* debug switch */

/*
* Statistics
*/
int	pkts = 0;		/* generated packets */
int	meas = 0;		/* successful measurements */
int	errs = 0;		/* detected errors */
int	errv[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; /* error tally */

/*
 * Main program
 */
main(
	int	argc,		/* number of arguments */
	char **argv		/* vector of argument pointers */
	)
{
	struct peer *peera;
	struct peer *peerb;
	int	modea = M_ACTV, modeb = M_ACTV, flags = 0;
	int	i, temp;

	/*
	 * Options
	 */
	while ((temp = getopt(argc, argv, "a:b:d:m:o:p:r:s:tx"))
		!= -1) {
		switch (temp) {

		case 'a':			/* poll A */
			sscanf(optarg, "%d", &polla);
			break;

		case 'b':			/* poll B */
			sscanf(optarg, "%d", &pollb);
			break;

		case 'd':			/* random duplicate */
			sscanf(optarg, "%lf", &dupe);
			break;

		case 'm':			/* mode */
			switch (*optarg) {

			case 'c':		/* client/server */
				modea = M_CLNT;
				modeb = M_SERV;
				break;

			case 's':		/* symmetric */
				modea = M_ACTV;
				modeb = M_ACTV;
				break;

			case 'b':		/* broadcast */
				modea = M_BCLT;
				modeb = M_BCST;
				break;

			default:		/* invalid mode */
				printf("invalid mode\n");
				exit(0);
			}
			break;

		case 'o':			/* random old duplicate */
			sscanf(optarg, "%lf", &odupe);
			break;

		case 'p':			/* random drop */
			sscanf(optarg, "%lf", &drop);
			break;

		case 'r':			/* random reset */
			sscanf(optarg, "%lf", &xreset);
			break;

		case 's':			/* max simulation cycles */
			sscanf(optarg, "%d", &maxsim);
			break;

		case 't':			/* trace */
			debug++;
			break;

		case 'x':			/* interleaved */
			flags |= F_XLEV;
			break;

		default:			/* invalid option */
			printf("invalid option\n");
			exit(0);
		}
	}

	/*
	 * Initialze peers A and B
	 */
	printf("drop %f reset %f dupe %f odupe %f\n", drop, xreset,
	    dupe, odupe);
	peera = init('a', modea, flags, polla, 0);
	peerb = init('b', modeb, flags, pollb, 1);

	/*
	 * Main loop
	 *
	 * Run the transmtter followed by the receiver at the first
	 * simulated time. The transmtter schedules its next run
	 * time. The initial start times are staggered so that the
	 * transmitters alternate.
	 */
	for (i = 0; i < maxsim; i++) {

		/*
		 * The duplicate probability threshold can be set
		 * by the -d option.
		 */
		if (peera->next == peerb->next) {
			trans(peera);
			trans(peerb);
			recv(peera, &peerb->pkt);
			recv(peerb, &peera->pkt);
		} else if (peera->next <= peerb->next) {
			trans(peera);
			if (peera->pkt.mode != M_BCLT) {
				recv(peerb, &peera->pkt);
				if (prob(dupe))
					recv(peerb, &peera->pkt);
				if (prob(odupe))
					recv(peerb, &peera->opkt);
			}
		} else {
			trans(peerb);
			recv(peera, &peerb->pkt);
			if (prob(dupe))
				recv(peera, &peerb->pkt);
			if (prob(odupe))
				recv(peera, &peerb->opkt);
		}
	}
	printf("packets %d valid %d errors %d throughput %.3f\n",
	    pkts, meas, errs, (double)meas / pkts);
	for (i = 0; i < 12; i++)
		printf("%6d %s\n", errv[i], tally[i]);
}


/*
 * init() - initialize peer
 */
struct peer *init(
	char id,		/* id */
	int	mode,		/* mode */
	int	flags,		/* flags */
	int	poll,		/* poll interval */
	int	next		/* start poll */
	)
{
	struct peer *peer;

	peer = malloc(sizeof(struct peer));
	memset(peer, 0, sizeof(struct peer));
	peer->id = id;
	peer->pkt.mode = mode;
	peer->flags = flags;
	if (flags & F_XLEV)
		peer->x = 1;
	if (mode == M_BCLT)
		peer->flags |= F_ENAB;
	peer->poll = poll;
	peer->next = next;
	printf("id %c mode %d flags %x poll %d next %d\n", peer->id,
	    peer->pkt.mode, peer->flags, peer->poll, peer->next);
	return(peer);
}
		

/*
 * trans() - transmit routine called at the activation time.
 */
void
trans(
	struct peer *peer)	/* peer structure */
{
	struct pkt *pkt;

	pkt = &peer->pkt;
	peer->next += peer->poll;
	if (peer->pkt.mode == M_BCLT)
		return;

	/*
	 * The protocol reset probability threshold can be set
	 * by the -r option.
	 */
	peer->opkt = peer->pkt;
	if (prob(xreset))
		rst(peer);

	/*
	 * Client/server and symmetric modes
	 */
	if (peer->pkt.mode != M_BCST) {
		pkt->org = peer->rec;
		pkt->rec = peer->dst;

		/*
		 * Basic symmetric mode
		 */
		if (peer->x == 0) {
			peer->aorg = ++n;
			pkt->xmt = peer->aorg;

		/*
		 * Interleaved symmetric mode
		 */
		} else {
			if (peer->x > 0) {
				peer->aorg = ++n;
				pkt->xmt = peer->borg;
			} else {
				peer->borg = ++n;
				pkt->xmt = peer->aorg;
			}
		peer->x = -peer->x;
		}

	/*
	 * Basic and interleaved broadcast mode
	 */
	} else {
		if (peer->flags & F_XLEV)
			pkt->org = peer->aorg;
		else
			pkt->org = 0;
		peer->aorg = ++n;
		pkt->rec = 0;
		pkt->xmt = peer->aorg;
	}
	peer->flags |= F_ENAB;
	pkts++;
}


/*
 * recv() - receive routine called following the transmit routine
 */
void
recv(
	struct peer *peer,	/* peer structure */
	struct pkt *pkt
	)
{
	int	t1, t2, t3, t4;
	int	err;

	err = R_OK;
	t1 = t2 = t3 = t4 = 0;

	/*
	 * The receiver is disabled until the first packet has been
	 * sent. The drop probablity threshold can be set by the -p
	 * optoin.
	 */
	if (pkt->mode == M_BCLT)
		return;

	if (!(peer->flags & F_ENAB)) {
		err = R_ENAB;	/* discard until first transmission */
	} else if (prob(drop)) {
	 	err = R_DROP;	/* disard with probability p */
	} else if (pkt->xmt != 0 && peer->xmt == pkt->xmt) {
		err = R_DUPE;	/* duplicate packet */

	/*
	 * Basic and interleaved broadcast mode
	 *
	 * An interleaved broadcast mode packet is recognized when
	 * the pkt->torg is nonzero.
	 */
	} else if (pkt->mode == M_BCST) {
		peer->xmt = pkt->xmt;
		if (pkt->org == 0) {
			peer->dst = ++n;
			t3 = pkt->xmt;
			t4 = peer->dst;
		} else {
			t3 = pkt->org;
			t4 = peer->borg;

			/*
			 * Discard unsynchronized packet and packet
			 * following a drop or restart.
			 */
			if (t4 == 0)
				err = R_SYNC;	/* unsynchronized */
			else if (pkt->org - peer->aorg > MAX)
				err = R_DELY;	/* delay error */
			peer->aorg = pkt->xmt;
			peer->dst = ++n;
			peer->borg = peer->dst;
		}
		if (err == R_OK) {
			if (t3 + 1 != t4)	
				err = R_FAIL;	/* undetected error */
			else
				meas++;
		}

	/*
	 * Basic client and symmetric modes
	 */
	} else if (peer->x == 0) {
		peer->xmt = pkt->xmt;
 		peer->rec = pkt->xmt;
		peer->dst = ++n;
		t1 = pkt->org;
		t2 = pkt->rec;
		t3 = pkt->xmt;
		t4 = peer->dst;

		/*
		 * Discard unsynchronized, protocol error
		 * and bogus packets.
		 */
		if (t1 == 0 && t2 == 0 && t3 != 0)
			err = R_SYNC;		/* unsynchronized */
		else if (t1 == 0 || t2 == 0 || t3 == 0)
			err = R_ERRR;			/* protocol violation */
		else if (t1 != peer->aorg)
			err = R_BOGS;		/* bogus packet */

	/*
	 * Interleaved symmetric mode
	 */
	} else {
		peer->xmt = pkt->xmt;
		if (peer->x > 0)
			t1 = peer->aorg;
		else if (peer->x < 0)
			t1 = peer->borg;
		t2 = peer->rec;
		t3 = pkt->xmt;
		t4 = peer->dst;
		peer->rec = pkt->rec;
		peer->dst = ++n;

		/*
		 * Discard unsynchronized, protocol error
		 * and bogus packets. 
		 */
		if ((pkt->org == 0 && pkt->rec == 0 && pkt->xmt == 0)
		    || (pkt->org == 0 && pkt->rec != 0 && pkt->xmt != 0)) {
			peer->flags |= F_SYNC;
			err = R_SYNC;		/* unsynchronized */
		} else if (!(peer->flags & F_SYNC)) {
			rst(peer);
			err = R_HOLD;		/* hold off */
		} else if (pkt->rec == 0 || pkt->xmt == 0) {
			rst(peer);
			err = R_ERRR;		/* protocol violation */
		} else if (t2 == 0) {
			err = R_SYNC;		/* unsynchronized */
		} else if (pkt->org != t4) {
			rst(peer);
			err = R_BOGS;		/* bogus packet */
		}
	
		/*
		 * Error checking is not for the faint of hearted.
		 */
		if (err == R_OK) {
			int d = (t4 - t1) - (t3 - t2);

			/*
			 * Correct behavior requires that the destination
			 * timestamp (t4) be later than the origin timestamp
			 * (t1) and the transmit timestamp (t3) be later than
			 * the receive timestamp (t2). This is called the
			 * valid test.
			 */
			if (t4 < t1 || t3 < t2)
				err = R_INVL;		/* invalid timestamps */

			/*
			 * If the delay (t4 - t1) - (t3 - t2) is less than
			 * zero or greater than the poll interval, the
			 * timestamps are invalid. This is called the
			 * delay test.
			 */
			else if (d < 0 || d > 2 * MAX)
				err = R_DELY;		/* delay error */


			/*
			 * If the packet order is t3, t1, t2, t4, it
			 * passes the delay test, but results in an offset
			 * spike in the order of a poll interval. The spike
			 * be nipped by the clock state machine. This is
			 * called the offset test.
			 */
			else if (abs(t2 - t1) > 1 || abs(t3 - t4) > 1)
				err = R_OFST;		/* offset error */

			/*
			 * We have tossed out as many errors as we can. To
			 * be valid, t3 must be one greater than t1 and t4
			 * must be one greater than t3. Otherwise, the
			 * packet order will be t2, t1, t3, t4. This
			 * results in a spurious offset near zero.
			 */
			else if (t1 + 1 != t2 || t3 + 1 != t4)
				err = R_FAIL;		/* undetected error */
		}
	}
	if (err != R_OK)
		errs++;
	else
		meas++;
	errv[err]++;
	if (!debug)
		return;

	/*
	 * Display one line of the trace.
	 *
	 * nnnnn	activation time
	 * pkt		org rec xmt
	 * st		rec xmt dst aorg borg
	 * flags	see xlev.h
	 * ts		t1 t2 r3 r4
	 * tally	see xlev.h
	 */ 
	printf(
		"%5d %c pkt %2d %2d %2d st %2d %2d %2d %2d %2d %x ts %2d %2d %2d %2d %s\n",
		peer->next, peer->id, pkt->org, pkt->rec, pkt->xmt,
		peer->rec, peer->xmt, peer->dst, peer->aorg, peer->borg,
		peer->flags, t1, t2, t3, t4, tally[err]);
}


/*
* rst() - protocol reset in interleaved symmetric mode
*/
void rst(
	struct peer *peer	/* peer structure */
	)
{
	peer->flags &= ~F_SYNC;
	peer->rec = peer->xmt = peer->dst =
        peer->aorg = peer->borg = 0;
}


/*
 * prob() - probabilistic event generator
 */
int prob(
	double	thresh		/* probability threshold */
	)
{
	double	noise;

	noise = (double)(random() & 0x3fffffff) / 0x3fffffff;
	return (noise < thresh);
}
