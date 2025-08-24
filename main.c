/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanait-e <yanait-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 17:37:58 by yanait-e          #+#    #+#             */
/*   Updated: 2025/08/24 18:42:57 by yanait-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int sig_num)
{
	(void)sig_num;
	signal(SIGQUIT, SIG_IGN);
}

void	init_executor(t_exec *executor, char **envp, t_env *my_env)
{
	unlink("here_doc");
	executor->core = 0;
	executor->has_here_doc = 0;
	executor->envp = envp;
	executor->path = NULL;
	executor->env = my_env;
	executor->here_doc_oho = 0;
	executor->pids = NULL;
	executor->commands_list = NULL;
	*(int *)(here_doc_flag()) = 0;
}

void	shell_loop(t_exec *executor, char **envp, t_env *my_env,
		t_sig *sig_state)
{
	char	*s;

	s = NULL;
	while (1)
	{
		sig_state->executing = 0;
		init_executor(executor, envp, my_env);
		signal(SIGINT, handle_ctrlc);
		signal(SIGQUIT, SIG_IGN);
		s = readline("minishell $ ");
		if (!s)
		{
			printf("exit\n");
			break ;
		}
		if (simple_parsing(s, executor) == 0)
			exceute_cmds(executor);
		free(s);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_exec	executor;
	t_env	*my_env;
	t_sig	*sig_state;

	(void)av;
	if (ac != 1)
		return (1);
	my_env = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_ctrlc);
	init_env(&my_env, envp);
	sig_state = sig_handler();
	executor.last_pwd = NULL;
	shell_loop(&executor, envp, my_env, sig_state);
	free_all_in_gc();
	return (clear_history(), get_exit_status());
}
