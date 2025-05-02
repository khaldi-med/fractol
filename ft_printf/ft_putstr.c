/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:22:15 by mohkhald          #+#    #+#             */
/*   Updated: 2024/12/25 22:41:51 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
