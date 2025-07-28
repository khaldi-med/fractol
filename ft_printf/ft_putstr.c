
#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	count;
	int	ret;

	count = 0;
	if (!s)
		s = "(null)";
	while (s[count])
	{
		ret = ft_putchar(s[count]);
		if (ret == -1)
			return (-1);
		count++;
	}
	return (count);
}
