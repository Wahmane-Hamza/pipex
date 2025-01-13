/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:47:22 by hwahmane          #+#    #+#             */
/*   Updated: 2024/12/06 19:29:09 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_form(char spec, va_list vf)
{
	int	count;

	count = 0;
	if (spec == 'c')
		count += (ft_print_char(va_arg(vf, int)));
	else if (spec == 's')
		count += (ft_print_str(va_arg(vf, char *)));
	else if (spec == 'd' || spec == 'i')
		count += (ft_print_nbr(va_arg(vf, int)));
	else if (spec == 'u')
		count += (ft_print_unsig_nbr(va_arg(vf, unsigned int)));
	else if (spec == 'x')
		count += (ft_print_hexa(va_arg(vf, unsigned int), "0123456789abcdef"));
	else if (spec == 'X')
		count += (ft_print_hexa(va_arg(vf, unsigned int), "0123456789ABCDEF"));
	else if (spec == 'p')
		count += (ft_print_ptr(va_arg(vf, void *)));
	else if (spec == '%')
		count += ft_print_char('%');
	else
		count += (ft_print_char('%') + ft_print_char(spec));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	vf;
	int		count_len;

	if (!format || write(1, "", 0) == -1)
		return (-1);
	va_start(vf, format);
	count_len = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1))
			count_len += ft_print_form(*(++format), vf);
		else if (*format != '%')
			count_len += ft_print_char(*format);
		else
			return (-1);
		format++;
	}
	va_end(vf);
	return (count_len);
}

