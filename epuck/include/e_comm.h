#ifndef E_COMM_H
#define E_COMM_H 1

/* Constants */
#define  MAX_BUF_BT       512

/* I/O FSM states */
#define  ST_BEFOREPKT       0
#define  ST_INPKTID         1
#define  ST_INPKT           2
#define  ST_BYTESTUFF       3
#define  ST_PKTDONE         4
#define  ST_PKTERR         -1
#define  ST_PKTERR_END     -2

/* Special bytes */
#define  CONTROL1        0x10
#define  CONTROL2        0x03

/* Max pkt size */
#define  MAX_PKT_SIZE     256

typedef struct {
	int rxpkt;
	int rxbytes;
	int txpkt;
	int txbytes;
	int rxerr;
} commstat;

int countUARTrx(int uart);

/* Communications */
typedef struct {
	int state;
	int ctr;
	unsigned char buf[MAX_PKT_SIZE];
} pktRX;

int readPkt(unsigned char *retbuf);
void sendPkt(unsigned char *buf, int ctr);
void initComm(void);
int addPktByte(unsigned char ch, pktRX *pr);

#endif
