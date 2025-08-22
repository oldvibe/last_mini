/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:36:18 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:36:19 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_non_quote(char *s, int i)
{
	while (s[i] && (s[i] != '\'' && s[i] != '"'))
		i++;
	return (i);
}

static void	handle_non_quote_case(char *s, t_quote_pos *arr, int *i, int *j)
{
	int	start;
	int	end;

	start = -1;
	if ((*i > 0 && s[*i - 1]) && ((s[*i - 1] == '\'' || s[*i - 1] == '"')))
		start = *i - 1;
	*i = process_non_quote(s, *i);
	end = *i;
	arr[*j].start = start;
	arr[*j].end = end;
	(*j)++;
}

void	find_quote_positions(char *s, t_quote_pos *arr)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	while (s[i])
	{
		found = 0;
		if (s[i] == '\'' || s[i] == '"')
			handle_quote_case(s, arr, &i, &j);
		else
		{
			handle_non_quote_case(s, arr, &i, &j);
			found = 1;
		}
		if (!found)
			i++;
	}
}
