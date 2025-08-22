/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:46 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:37:47 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	return (0);
}

char	*append_str(char c)
{
	char	*s;

	s = gc_malloc(sizeof(char) * 2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f')
		return (1);
	return (0);
}
