/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:27 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:46:13 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_itoa2(char *d, int len, long nb)
{
	d[len] = '\0';
	if (nb == 0)
	{
		d[0] = '0';
		return (d);
	}
	if (nb < 0)
	{
		nb = -nb;
		d[0] = '-';
	}
	while (nb > 0)
	{
		d[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (d);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*d;

	nb = n;
	len = 0;
	if (n <= 0)
		len++;
	if (n == 0)
		return (ft_strdup("0"));
	while (n)
	{
		len++;
		n /= 10;
	}
	d = gc_malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	d = ft_itoa2(d, len, nb);
	return (d);
}
