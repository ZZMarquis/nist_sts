#include "include/stat_fncs.h"

static unsigned char _compute(unsigned char b, unsigned char factor)
{
    if ((factor & b) == factor) {
        return 0x01;
    } else {
        return 0x00;
    }
}

int BytesToBitSequence(unsigned char *in, int inl, BitSequence *outbuf, int bufsize)
{
    int j = 0, i = 0;
    if (bufsize < inl * 8) {
        return 0;
    }

    for (i = 0; i < inl; ++i) {
        j = i * 8;
        outbuf[j] = (BitSequence) (_compute(in[i], 0x80));
        outbuf[j + 1] = (BitSequence) (_compute(in[i], 0x40));
        outbuf[j + 2] = (BitSequence) (_compute(in[i], 0x20));
        outbuf[j + 3] = (BitSequence) (_compute(in[i], 0x10));
        outbuf[j + 4] = (BitSequence) (_compute(in[i], 0x08));
        outbuf[j + 5] = (BitSequence) (_compute(in[i], 0x04));
        outbuf[j + 6] = (BitSequence) (_compute(in[i], 0x02));
        outbuf[j + 7] = (BitSequence) (_compute(in[i], 0x01));
    }
}
