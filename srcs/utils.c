/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:41:54 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 15:42:43 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*ft_strjoin_char(char const *s1, char ch)
{
	char	*str;
	size_t	i;
	size_t	c;

	if (ch)
		str = malloc(ft_strlen(s1) + 2);
	else
		str = malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	c = 0;
	i = 0;
	if (s1)
	{
		while (s1[i])
			str[c++] = s1[i++];
	}
	i = 0;
	if (ch)
		str[c++] = ch;
	str[c] = '\0';
	return (str);
}
