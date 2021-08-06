/*
 * Basic/interleaved protocol simulator
 */ 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*
 * Modes
 */
#define	M_ACTV	1	/* symmetric active */
#define	M_PASV	2	/* symmetric passive */
#define	M_CLNT	3	/* client */
#define	M_SERV	4	/* server */
#define	M_BCST	5	/* broadcast server */
#define	M_BCLT	8	/* broadcast client */

/*
 * Flag bits
 */
#define	F_XLEV	0x1	/* interleaved mode */
#define	F_ENAB	0x2	/* receive enable */
#define	F_SYNC	0x4	/* synchronized */

/*
 * Tally codes
 */
#define	R_OK	0	/* okay */
#define	R_DUPE	1	/* duplicate packet */
#define	R_BOGS	2	/* bogus packet */
#define	R_SYNC	3	/* unsynchronized */
#define	R_HOLD	4	/* hold off */
#define	R_DROP	5	/* dropped packet */
#define	R_ENAB	6	/* not ready */
#define	R_INVL	7	/* invalid timestamps */
#define	R_ERRR	8	/* protocol violation */
#define	R_FAIL	9	/* udetected error */
#define	R_DELY	10	/* delay error */
#define	R_OFST	11	/* offset error */

#define	MAX	1	/* maximum one-way delay */

char	*tally[] = {
	"ok",		/* 0 */
	"duplicate",	/* 1 */
	"bogus",	/* 2 */
	"sync",		/* 3 */
	"hold off",	/* 4 */
	"dropped",	/* 5 */
	"not ready",	/* 6 */
	"invalid",	/* 7 */
	"protocol",	/* 8 */
	"error",	/* 9 */
	"delay",	/* 10 */
	"offset"	/* 11 */
};

/*
 * Packet header variables
 */
struct pkt {
	int	mode;	/* mode */
	int	org;	/* origin timestamp */
	int	rec;	/* receive timestamp */
	int	xmt;	/* transmit timestamp */
};

/*
 * Peer state variables
 */
struct peer {
	struct pkt pkt;	/* packet */
	struct pkt opkt; /* old packet */
	int	rec;	/* receive timestamp */
	int	xmt;	/* transmit timestamp */
	int	dst;	/* destination timestamp */
	int	aorg;	/* a origin */
	int	borg;	/* b origin */
	int	x;	/* transmit origin switch */
	int	flags;	/* flag bits */
	int	next;	/* wakeup time */
	int	poll;	/* poll interval */
	char	id;	/* ident */
};

/*
 * Global prototypes
 */
struct peer *init(char, int, int, int, int);
void	trans(struct peer *);	/* transmit routine */
void	recv(struct peer *, struct pkt *);	/* receive routine */
void	rst(struct peer *);
int	prob(double);
