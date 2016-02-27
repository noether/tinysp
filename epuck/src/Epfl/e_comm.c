#include "misc.h"
#include "e_comm.h"
#include "e_led.h"
#include "e_uart_char.h"

pktRX    pktrx;
commstat commStat={0,0,0,0,0};

void initComm(void)
{
	pktrx.state = ST_BEFOREPKT;
	pktrx.ctr = 0;
}

int readPkt(unsigned char *retbuf)
{
	int i;
    unsigned char msg;

	while (pktrx.ctr < MAX_PKT_SIZE && e_getchar_uart1(&msg)) {
		if (addPktByte(msg, &pktrx) > 0) {
			pktrx.state = ST_BEFOREPKT;
			for (i = 0; i < pktrx.ctr; i++)
				retbuf[i] = pktrx.buf[i];
			pktrx.ctr = 0;
			commStat.rxpkt++;
			return i;
		}
	}

	if (pktrx.ctr >= MAX_PKT_SIZE) {
		pktrx.ctr = 0;
		pktrx.state = ST_BEFOREPKT;
	}
	return 0;
}

int addPktByte(unsigned char ch, pktRX *pr)
{
	switch(pr->state) {
	case ST_BEFOREPKT:
		if(ch == CONTROL1)
			pr->state = ST_INPKTID;
		break;
	case ST_INPKTID:
		pr->buf[pr->ctr++] = ch;
		pr->state = ST_INPKT;
		break;
	case ST_INPKT:
		if (ch == CONTROL1)
			pr->state = ST_BYTESTUFF;
		else
			pr->buf[pr->ctr++] = ch;
		break;
	case ST_BYTESTUFF:
		if(ch == CONTROL1) {
			pr->buf[pr->ctr++] = ch;
			pr->state = ST_INPKT;
		} else if (ch == CONTROL2)
			pr->state = ST_PKTDONE;
		else
			pr->state = ST_PKTERR;
		break;
	case ST_PKTERR:
		if (ch == CONTROL1)
			pr->state = ST_PKTERR_END;
		else
			pr->state = ST_PKTERR;
		break;
	case ST_PKTERR_END:
		if (ch == CONTROL2)
			pr->state = ST_BEFOREPKT;
		else
			pr->state = ST_PKTERR;
		break;
	default:
		pr->state = ST_PKTERR;
		break;
	}


	if (pr->state == ST_PKTERR
			|| pr->state == ST_PKTERR_END
			|| pr->state == ST_BEFOREPKT)
		return -1;
	else if (pr->state == ST_PKTDONE) {
		pr->state = ST_BEFOREPKT;
		return pr->ctr;
	}
	else
		return 0;
}

void sendPkt(unsigned char *buf, int ctr)
{
	int i = 0, j = 0;
    unsigned char b2[128];

	b2[j++] = CONTROL1;
	while (i < ctr) {
		if (buf[i] == CONTROL1)
			b2[j++] = CONTROL1;
		b2[j++] = buf[i++];
	}

	b2[j++] = CONTROL1;
	b2[j++] = CONTROL2;

    e_send_uart1_char(b2, j);

	commStat.txbytes += j;
	commStat.txpkt++;
}
