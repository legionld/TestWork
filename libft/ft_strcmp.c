/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschille <jschille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 19:29:59 by jschille          #+#    #+#             */
/*   Updated: 2018/12/10 17:05:36 by jschille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const	char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			a = s1[i];
			b = s2[i];
			return (a - b);
		}
		++i;
	}
	if (s2[i] != '\0')
	{
		b = s2[i];
		return (0 - b);
	}
	return (0);
}
