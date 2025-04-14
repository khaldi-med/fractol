/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 01:13:45 by mohkhald          #+#    #+#             */
/*   Updated: 2024/12/25 22:37:24 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putnbr(int n);
int	ft_putchar(char c);
int	ft_printf(const char *format, ...);
int	ft_putnbr_base(unsigned long n, int base, char *format);
int	ft_put_pointer(unsigned long n);
int	ft_putstr(char *s);

#endif
