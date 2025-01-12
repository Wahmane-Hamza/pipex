/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwahmane <hwahmane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:29:32 by hwahmane          #+#    #+#             */
/*   Updated: 2025/01/12 18:00:42 by hwahmane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *copy_str(char *str)
{
	char *str2;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	
	str2 = malloc(i + 1);

	i = 0;
	while (str[i] && str[i] != ' ')
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

int	ft_strncmp(char *s1,char s2)
{
	if (!s1)
		return (0);
	if (s1[0] != s2)
	{
		return (1);
	}
	return (0);
}