/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 20:14:36 by ihwang            #+#    #+#             */
/*   Updated: 2021/04/07 18:31:59 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	reset_value(t_token **tk_lst, t_astnode **ast)
{
	(*tk_lst != NULL) ? clear_token((*tk_lst)) : 0;
	(*ast != NULL) ? clear_ast(*ast) : 0;
	(g_shell.heredoc_lst != NULL) ? clear_heredoc(g_shell.heredoc_lst) : 0;
	(g_shell.history->tmp != NULL) ? append_history() : 0;
	*tk_lst = NULL;
	*ast = NULL;
	g_shell.heredoc_lst = NULL;
	g_shell.first_heredoc = NULL;
	g_shell.signal_indicator = 0;
	g_shell.pipe_indicator = 0;
}

static int	shell(void)
{
	t_token		*tk_lst;
	t_astnode	*ast;

	tk_lst = NULL;
	ast = NULL;
	while ("shell is interactive")
	{
		reset_value(&tk_lst, &ast);
		do_job_notification();
		print_info();
		if ((tk_lst = tokenizing_service()) == NULL)
			continue ;
		if ((ast = semantic_analysis(tk_lst)) == NULL)
			continue ;
		if (find_heredoc(ast) == EXIT_FAILURE)
			continue ;
		g_shell.first_heredoc = g_shell.heredoc_lst;
		executor(ast);
	}
	return (0);
}

static int	init_shell(char **envp)
{
	if (init_terminal_stuff() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_environment_variable_stuff(envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_job_control_stuff() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_history_stuff() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_signal_and_other_stuff();
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (init_shell(envp) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	increment_shlvl();
	return (shell());
}
