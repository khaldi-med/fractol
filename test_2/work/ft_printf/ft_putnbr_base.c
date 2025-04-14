/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 05:22:13 by mohkhald          #+#    #+#             */
/*   Updated: 2024/12/26 01:44:59 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned long n, int base, char *format)
{
	int		count;
	int		i;
	char	buffer[19];

	count = 0;
	i = 0;
	if (n == 0)
		return (ft_putchar('0'));
	while (n)
	{
		buffer[i++] = format[n % base];
		n /= base;
	}
	while (i--)
	{
		ft_putchar(buffer[i]);
		count++;
	}
	return (count);
}
