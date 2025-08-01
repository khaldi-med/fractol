
#include "ft_printf.h"

int	ft_put_pointer(unsigned long n)
{
	int	count;

	count = ft_putstr("0x");
	if (n == 0)
	{
		ft_putchar('0');
		count++;
	}
	else
	{
		count += ft_putnbr_base(n, 16, "0123456789abcdef");
	}
	return (count);
}
