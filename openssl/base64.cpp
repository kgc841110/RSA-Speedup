#include "base64.h"

unsigned char *base64_decode(unsigned char *buf, size_t *len, int strict, int *err)
{
	unsigned char *outbuf;

	outbuf = (unsigned char *)malloc(3 * (strlen((char *)buf) / 4 + 1));
	if (!outbuf)
	{
		*err = -3;
		*len = 0;
		return 0;
	}

	*len = raw_base64_decode(buf, outbuf, strict, err);

	if (*err)
	{
		free(outbuf);
		*len = 0;
		outbuf = 0;
	}
	return outbuf;
}
unsigned char *base64_encode(unsigned char *input, size_t len, int wrap)
{
	unsigned char *output, *p;
	size_t        i = 0, mod = len % 3, toalloc;

	toalloc = (len / 3 + (mod ? 1 : 0)) * 4;
	if (wrap)
	{
		toalloc += len / 48;
		if (len % 48) toalloc++;
	}
	toalloc ++;

	p = output = (unsigned char *)malloc(toalloc);
	if (!p) return 0;

	while (i < len - mod)
	{
		*p++ = b64table[input[i++] >> 2];
		*p++ = b64table[((input[i - 1] << 4) | (input[i] >> 4)) & 0x3f];
		*p++ = b64table[((input[i] << 2) | (input[i + 1] >> 6)) & 0x3f];
		*p++ = b64table[input[i + 1] & 0x3f];
		i += 2;
		if (wrap && !(i % 48)) *p++ = '\n';
	}

	if (!mod)
	{
		*p = 0;
		return output;
	}
	else
	{
		*p++ = b64table[input[i++] >> 2];
		if (mod == 1)
		{
			*p++ = b64table[(input[i - 1] << 4) & 0x3f];
			*p++ = '=';
			*p++ = '=';
			//            if (wrap) *p++ = '\n';
			*p = 0;
			return output;
		}
		else
		{
			*p++ = b64table[((input[i - 1] << 4) | (input[i] >> 4)) & 0x3f];
			*p++ = b64table[(input[i] << 2) & 0x3f];
			*p++ = '=';
			//            if (wrap) *p++ = '\n';
			*p = 0;
			return output;
		}
	}
}
static unsigned int raw_base64_decode(unsigned char *in, unsigned char *out, 
	int strict, int *err) {
		unsigned int  result = 0, x;
		unsigned char buf[3], *p = in, pad = 0;

		*err = 0;
		while (!pad)
		{
			switch ((x = b64revtb[*p++]))
			{
			case -3: /* NULL TERMINATOR */
				if (((p - 1) - in) % 4) *err = 1;
				return result;
			case -2: /* PADDING CHARACTER. INVALID HERE */
				if (((p - 1) - in) % 4 < 2)
				{
					*err = 1;
					return result;
				}
				else if (((p - 1) - in) % 4 == 2)
				{
					/* Make sure there's appropriate padding */
					if (*p != '=')
					{
						*err = 1;
						return result;
					}
					buf[2] = 0;
					pad = 2;
					result++;
					break;
				}
				else
				{
					pad = 1;
					result += 2;
					break;
				}
				return result;
			case -1:
				if (strict)
				{
					*err = 2;
					return result;
				}
				break;
			default:
				switch (((p - 1) - in) % 4)
				{
				case 0:
					buf[0] = x << 2;
					break;
				case 1:
					buf[0] |= (x >> 4);
					buf[1] = x << 4;
					break;
				case 2:
					buf[1] |= (x >> 2);
					buf[2] = x << 6;
					break;
				case 3:
					buf[2] |= x;
					result += 3;
					for (x = 0;  x <(unsigned int)(3 - pad);  x++) *out++ = buf[x];
					break;
				}
				break;
			}
		}
		for (x = 0;  x < (unsigned int)(3 - pad);  x++) *out++ = buf[x];
		return result;
}

