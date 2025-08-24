/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:36:59 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/24 17:47:38 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc_wait(t_sig *stats, int status)
{
	stats->reading_from_here_doc = 0;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			set_exit_status(130);
			return (1);
		}
	}
	else if (WIFEXITED(status))
	{
		set_exit_status(WEXITSTATUS(status));
		if (WEXITSTATUS(status) != 0)
			return (1);
	}
	return (0);
}

char	**append_tokens(char **tokens)
{
	char	**new_tokens;
	int		i;
	int		j;

	i = 0;
	while (tokens[i])
		i++;
	new_tokens = gc_malloc(sizeof(char *) * (i + 2));
	if (!new_tokens)
		return (NULL);
	j = 0;
	new_tokens[j++] = ft_strdup("");
	while (tokens[j - 1])
	{
		new_tokens[j] = tokens[j - 1];
		j++;
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}

int size_array(char **arr)
{
    int i = 0;
    while (arr[i]) 
        i++;
    return (i);
}

void add_to_args(t_list *cmd, t_list *lst)
{
    int size_cmd;
    int size_lst;
    int i;
    char **new_cmd;
    size_cmd = size_array(cmd->command);
    size_lst = size_array(lst->command);
    if (size_lst == 1)
        return ;
    new_cmd = gc_malloc((size_cmd + size_lst) * sizeof(char *));
    i = 0;
    while (i < size_cmd)
    {
        new_cmd[i] = cmd->command[i];
        i++;
    }
    i = 0;
    while (lst->command[i + 1])
    {
        new_cmd[size_cmd + i] = lst->command[i + 1];
        i++;
    }
    lst->command[1] = NULL;
    new_cmd[size_cmd + i] = NULL;
    cmd->command = new_cmd;
}

void first_args(t_list *lst, t_exec *exec)
{
    t_list *tmp;
    t_list *new;
    char **arr;
    
    tmp = lst->next;
    if (!tmp->type)
        return ;
    while (tmp)
    {
        if (tmp->type == 1)
           return ;
        if (tmp->type >= 2 && tmp->type <= 5 && size_array(tmp->next->command) > 1)
        {
            arr = gc_malloc(sizeof(char *));
            arr[0] = NULL;
            new = create_new_node(arr, 0, exec);
            new->next = lst->next;
            lst->next = new;
            return ;
        }
        tmp = tmp->next;
    }
}

void hi_ft(t_list *lst, t_exec *exec)
{
    int     i;
    t_list *cmd;
    first_args(lst, exec);
    
    lst = lst->next;
    cmd = lst;
    i = 0;
    while (lst)
    {
        if (lst->type == 5 || lst->type == 2 || lst->type == 3 || lst->type == 4)
        {
            lst = lst->next;
            add_to_args(cmd, lst);
        }
        lst = lst->next;
        if (lst && lst->type == 1)
        {
            lst = lst->next;
            cmd = lst;
        }
    }
}
int	parser(t_exec *executor, char *str)
{
	executor->tokens = ft_split_pipes(str);
	if (syntax_error(executor->tokens))
		return (1);
	executor->tokens = append_tokens(executor->tokens);
	executor->commands = ft_split_tokens(executor->tokens);
	executor->commands_list = parse_list(executor->commands, executor);
    hi_ft(executor->commands_list, executor);
	executor->commands_list = expand(executor, executor->commands_list);
	return (0);
}

int	here_doc(t_sig *stats, t_exec *executor)
{
	int	status;

	stats->reading_from_here_doc = 1;
	stats->pid = fork();
	if (!stats->pid)
		handle_here_doc(executor);
	else if (stats->pid > 0)
		return (waitpid(stats->pid, &status, 0), here_doc_wait(stats, status));
	return (0);
}

int	simple_parsing(char *s, t_exec *executor)
{
	t_sig	*stats;
	char	*str;

	stats = sig_handler();
	stats->executing = 0;
    str = s;
	if (str && !str[0])
		return (1);
	if (str && str[0])
		add_history(str);
	if (syntax_errors(str))
		return (set_exit_status(2), 1);
	if (parser(executor, str))
		return (set_exit_status(2), 1);
	if (!executor->commands_list)
		return (1);
	executor->here_doc_oho = *(int *)here_doc_flag();
	if (executor->has_here_doc)
		return (here_doc(stats, executor));
	return (0);
}
