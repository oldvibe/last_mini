/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_export2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:36:24 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:36:25 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand_params	init_params(t_exec *executor, char *s, int *i, int *arr)
{
	t_expand_params	params;

	params.s = s;
	params.i = i;
	params.counter = 0;
	params.arr = arr;
	params.was_quoted = 0;
	params.executor = executor;
	params.quote_char = 0;
	return (params);
}

char	*handle_digit(t_expand_params *params)
{
	if (is_in_arr(params->counter, params->arr) || params->was_quoted)
	{
		*(params->i) += 2;
		return (ft_strdup(""));
	}
	(*(params->i))++;
	return (append_str(params->s[*(params->i) - 1]));
}

char	*handle_exit_status_exp(int *i)
{
	int	e;

	e = get_exit_status();
	*i += 2;
	return (ft_itoa(e));
}
