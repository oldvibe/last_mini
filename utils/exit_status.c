/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:24 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:37:25 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*exit_status(void)
{
	static int	ext_status;

	return (&ext_status);
}

void	set_exit_status(int status)
{
	*exit_status() = status;
}

int	get_exit_status(void)
{
	return (*exit_status());
}
