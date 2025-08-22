/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:11:55 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/21 17:11:56 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	equal_signe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	equal_flag(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

int	env_size(t_env *env)
{
	t_env	*temp;
	int		size;

	if (!env)
		return (0);
	temp = env;
	size = 0;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	init_env(t_env **my_env, char **env)
{
	t_env	*new;
	int		i;

	i = 0;
	while (env[i])
	{
		new = new_env(env[i]);
		if (new)
			add_back_env(my_env, new);
		i++;
	}
}
