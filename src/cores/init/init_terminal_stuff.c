/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal_stuff.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 23:20:08 by dthan             #+#    #+#             */
/*   Updated: 2021/04/07 18:29:26 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_terminal_stuff(void)
{
	g_shell.shell_terminal = STDIN_FILENO;
	g_shell.interactive_shell = isatty(STDIN_FILENO);
	if (!g_shell.interactive_shell)
		return (EXIT_FAILURE);
	while (ft_tcgetpgrp(g_shell.shell_terminal) !=
			(g_shell.shell_pgid = getpgrp()))
		kill(-g_shell.shell_pgid, SIGTTIN);
	return (EXIT_SUCCESS);
}

int	init_environment_variable_stuff(char **envp)
{
	g_shell.env = set_env(envp);
	g_shell.intern_var = set_var(envp);
	if (!(ft_getenv("TERM")))
	{
		ft_putstr_fd("Environment variable 'TERM' not set\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_job_control_stuff(void)
{
	g_shell.shell_pgid = getpgrp();
	if (setpgid(g_shell.shell_pgid, g_shell.shell_pgid) == -1)
		return (EXIT_FAILURE);
	ft_tcsetpgrp(STDIN_FILENO, g_shell.shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell.shell_tmode);
	return (EXIT_SUCCESS);
}

int	init_signal_and_other_stuff(void)
{
	g_shell.alias = NULL;
	g_shell.signal_indicator = 0;
	g_shell.first_heredoc = NULL;
	g_shell.heredoc_lst = NULL;
	g_shell.exit_status = 1;
	g_shell.builtins = set_builtin_commands();
	sig_controller(PARENT);
	init_signal_messages(g_shell.signal_msgs);
	return (EXIT_SUCCESS);
}

int	init_history_stuff(void)
{
	g_shell.history = (t_history*)malloc(sizeof(t_history));
	g_shell.history->hist = (char**)malloc(sizeof(char*) * (HISTFILESIZE + 2));
	g_shell.history->tmp = NULL;
	g_shell.history->curr = 0;
	ft_bzero(g_shell.history->savedfile, 256);
	getcwd(g_shell.history->savedfile, 256);
	ft_strcat(g_shell.history->savedfile, "/.history");
	if (get_history(0) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
