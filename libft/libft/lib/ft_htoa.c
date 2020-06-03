/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_caract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmichel <hmichel@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:21:42 by seanseau          #+#    #+#             */
/*   Updated: 2020/05/28 03:59:06 by hmichel          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int		len(short n)
{
	int len;

	len = 1;
	while (n /= 10)
		len++;
	return (len);
}

static int		one(short n)
{
	if (n < 0)
		return (1);
	return (0);
}

char			*ft_htoa(short n)
{
	int		i;
	int		tmp2;
	char	*str;

	if (n == -32768)
	{
		str = ft_memalloc(7);
		str = ft_strcpy(str, "-32768");
		return (str);
	}
	tmp2 = one(n);
	if (n < 0)
		n = -n;
	i = len(n);
	if (!(str = ft_memalloc(i + tmp2)))
		return (0);
	tmp2 == 1 ? str[0] = '-' : 0;
	while (i--)
	{
		str[i + tmp2] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
