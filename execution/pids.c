/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:35:59 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:36:00 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pids	*new_pid(pid_t pid_value)
{
	t_pids	*new;

	new = gc_malloc(sizeof(t_pids));
	if (!new)
		return (NULL);
	new->pid = pid_value;
	new->next = NULL;
	return (new);
}

void	add_back_pid(t_pids **pids, t_pids *new)
{
	t_pids	*temp;

	if (!new || !pids)
		return ;
	if (!(*pids))
		(*pids) = new;
	else
	{
		temp = (*pids);
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

int	size_pids(t_pids *pids)
{
	t_pids	*temp;
	int		size;

	if (!pids)
		return (0);
	size = 0;
	temp = pids;
	while (temp)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}
