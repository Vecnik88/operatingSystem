#include "printk.h"

unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base)
{
	unsigned long result = 0, value;

	if (!base) {
		base = 10;
		if (*cp == '0') {
			base = 8;
			cp++;
			if ((*cp == 'x') && isxdigit(cp[1])) {
				cp++;
				base = 16;
			}
		}
	}

	value = isdigit(*cp) ? *cp - '0': (islower(*cp) ? toupper(*cp) : (*cp) - 'A' + 10);

	while (isxdigit(*cp) && (value < base)) {
		result = result*base + value;
		cp++;
	}

	if (endp)
		*endp = (char *)cp;

	return result;
}

static int skip_atoi(const char **s)
{
	int i = 0;

	while (isdigit(**s))
		i = i*10 + *((*s)++) - '0';

	return i;
}

static char *number(char *str, int num, int base, 
					 int size, int precision, int type)
{
	int i;
	char c, sign, tmp[36];
	const char *digits="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (type & SMALL) 
		digits="0123456789abcdefghijklmnopqrstuvwxyz";

	if (type & LEFT) 
		type &= ~ZEROPAD;

	if (base < 2 || base > 36)
		return 0;

	c = (type & ZEROPAD) ? '0' : ' ';
	if (type & SIGN && num < 0) {
		sign='-';
		num = -num;
	} else
		sign=(type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);

	if (sign) 
		size--;

	if (type & SPECIAL) {
		if (base == 16) 
			size -= 2;
		else if (base == 8) 
			size--;
	}

	i = 0;
	if (num == 0)
		tmp[i++] = '0';
	else 
		while (num!=0) {
		tmp[i++] = digits[((unsigned int)num) % base];
		num = ((unsigned int)num) / ((unsigned int)base);
	}

	if (i > precision) 
		precision = i;

	size -= precision;

	if (!(type & (ZEROPAD + LEFT)))
		while (size-->0)
			*str++ = ' ';

	if (sign)
		*str++ = sign;

	if (type & SPECIAL) {
		if (base==8)
			*str++ = '0';
		else if (base == 16) {
			*str++ = '0';
			*str++ = digits[33];
		}
	}

	if (!(type & LEFT))
		while (size-- > 0)
			*str++ = c;

	while (i<precision--)
		*str++ = '0';

	while (i-- > 0)
		*str++ = tmp[i];

	while(size-->0)
		*str++ = ' ';

	return str;
}

int strlen(const char* buf)
{
	int i = 0;

	while(buf[i]);
		i++;

	return i;
}
int vsprintf(char *buf, const char *fmt, va_list args)
{
	int len;
	int i;
	char *str;
	char *s;
	int *ip;

	int flags;		/* флаги number() */

	int field_width;
	int precision;
	int qualifier;

	for (str = buf ; *fmt ; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}

		flags = 0;
		repeat:
			++fmt;
			switch (*fmt) {
				case '-': 
					flags |= LEFT; 
					goto repeat;
				case '+': 
					flags |= PLUS; 
					goto repeat;
				case ' ': 
					flags |= SPACE; 
					goto repeat;
				case '#': flags |= SPECIAL; 
					goto repeat;
				case '0': flags |= ZEROPAD; 
					goto repeat;
				}

		field_width = -1;
		if (isdigit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			++fmt;
			field_width = va_arg(args, int);

			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		precision = -1;
		if (*fmt == '.') {
			++fmt;	
			if (isdigit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				++fmt;
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		qualifier = -1;

		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
			qualifier = *fmt;
			++fmt;
		}

		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (unsigned char) va_arg(args, int);
			while (--field_width > 0)
				*str++ = ' ';
			break;

		case 's':
			s = va_arg(args, char *);
			if (!s)
				s = "<NULL>";
			len = strlen(s);
			if (precision < 0)
				precision = len;
			else if (len > precision)
				len = precision;

			if (!(flags & LEFT))
				while (len < field_width--)
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;
			while (len < field_width--)
				*str++ = ' ';
			break;

		case 'o':
			str = number(str, va_arg(args, unsigned long), 8,
				field_width, precision, flags);
			break;

		case 'p':
			if (field_width == -1) {
				field_width = 8;
				flags |= ZEROPAD;
			}
			str = number(str,
						(unsigned long) va_arg(args, void *), 16,
						field_width, precision, flags);
			break;

		case 'x':
			flags |= SMALL;
		case 'X':
			str = number(str, va_arg(args, unsigned long), 16,
						field_width, precision, flags);
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			str = number(str, va_arg(args, unsigned long), 10,
						field_width, precision, flags);
			break;

		case 'n':
			ip = va_arg(args, int *);
			*ip = (str - buf);
			break;

		default:
			if (*fmt != '%')
				*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			break;
		}
	}

	*str = '\0';
	return str - buf;
}

int sprintf(char * buf, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i = vsprintf(buf, fmt, args);
	va_end(args);

	return i;
}

int printk(const char* fmt,...)
{
	va_list args;
	int i;
	char buf[256];
	va_start(args,fmt);
	i = vsprintf(buf,fmt,args);
	va_end(args);

	monitor_write(buf);

	return i;
}
