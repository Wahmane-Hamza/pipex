/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:15:00 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/23 15:35:57 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	before_n_stack(char *stack)
{
	int	i;

	i = 0;
	while (stack[i] != '\n' && stack[i] != '\0')
		i++;
	return (i);
}

int	after_n_stack(char *stack, int i)
{
	int	j;

	j = 0;
	while (stack[i])
	{
		i++;
		j++;
	}
	return (j);
}
