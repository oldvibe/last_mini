/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:50 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/22 17:37:51 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_malloc(const char *s)
{
	int		len;
	char	*d;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	d = gc_malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strdup(const char *s)
{
	int		len;
	char	*d;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen((char *)s);
	d = gc_malloc(sizeof(char) * (len + 1));
	if (!d)
		return (NULL);
	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

void	sig_quit(int sig)
{
	(void)sig;
}

void	signinthandler(int sig)
{
	t_sig	*stats;

	(void)sig;
	stats = sig_handler();
	rl_on_new_line();
	rl_replace_line("", 0);
	if (stats->executing == 0 && !stats->reading_from_here_doc)
		rl_redisplay();
	set_exit_status(130);
}
