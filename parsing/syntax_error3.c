/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:08 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:46:55 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	check_single_op1(char *str, int *i, int *found_op)
{
	if (is_operator(str[*i]))
	{
		if (*found_op)
			return (1);
		*found_op = 1;
		(*i)++;
	}
	else if (str[*i])
	{
		*found_op = 0;
		(*i)++;
	}
	return (0);
}

int	handle_quotes1(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (!str[*i])
		return (0);
	(*i)++;
	return (1);
}

int	check_double_op1(char *str, int *i, int *found_op)
{
	if ((str[*i] == '>' && str[*i + 1] == '>') || (str[*i] == '<' && str[*i
				+ 1] == '<'))
	{
		if (*found_op)
			return (1);
		*found_op = 1;
		*i += 2;
	}
	return (0);
}
