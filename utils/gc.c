/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:38 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:37:39 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct s_gc	**get_gc(void)
{
	static struct s_gc	*g_head;

	return (&g_head);
}

void	add_to_gc(void *addr)
{
	struct s_gc	*mem_node;

	mem_node = malloc(sizeof(struct s_gc));
	if (!mem_node)
		return (free_all_in_gc(), exit(1));
	mem_node->p = addr;
	mem_node->next = *get_gc();
	*get_gc() = mem_node;
}

void	*gc_malloc(size_t bytes)
{
	void	*p;

	p = malloc(bytes);
	if (!p)
		return (free_all_in_gc(), exit(1), NULL);
	add_to_gc(p);
	return (p);
}

void	free_all_in_gc(void)
{
	struct s_gc	*current;
	struct s_gc	*temp;

	current = *get_gc();
	while (current)
	{
		free(current->p);
		temp = current;
		current = current->next;
		free(temp);
	}
	*get_gc() = NULL;
}
