/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_exec_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:35 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 18:53:04 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	fc_e_init_range(int *r_ind, char *first, char *last)
{
	r_ind[0] = g_shell.history->curr;
	r_ind[1] = g_shell.history->curr;
	if (first)
	{
		r_ind[0] = fc_range(first);
		if (r_ind[0] == 0)
			return (fc_error_history_specification_out_of_range());
		r_ind[1] = r_ind[0];
		if (last)
		{
			r_ind[1] = fc_range(last);
			if (r_ind[1] == 0)
				return (fc_error_history_specification_out_of_range());
		}
	}
	return (EXIT_SUCCESS);
}

static void	fc_e_copy_lines_into_editor(int fd, int *r_ind)
{
	if (r_ind[0] < r_ind[1])
	{
		while (r_ind[0] < r_ind[1])
		{
			write_history_commands_into_editor(fd, r_ind);
			r_ind[0]++;
		}
	}
	else if (r_ind[0] > r_ind[1])
	{
		while (r_ind[0] > r_ind[1])
		{
			write_history_commands_into_editor(fd, r_ind);
			r_ind[0]--;
		}
	}
	write_history_commands_into_editor(fd, r_ind);
}

static void	fc_e_editing_process(char *editor)
{
	char	*av[3];
	char	*editor_path;
	int		pid;

	editor_path = find_executable(editor);
	av[0] = editor;
	av[1] = ft_strdup(FC_EDITING_FILE);
	av[2] = NULL;
	pid = fork();
	if (pid == 0)
		execve(editor_path, av, g_shell.env);
	wait(NULL);
	free(av[1]);
	free(editor_path);
}

/*
** FC with e option
**  SYNOPSIS: fc [-r] [-e editor] [first [last]]
**	@ops: the option to check if there is -r option
**	@editor: to check the editor
**	@first: to check the first block
**	@last: to check the last block
** 		1. Check the editor string value if the input editor is valid
**		if the editor is invalid, then return error with a command not
**		found message. If editor is valid move on to the next steps
**		2. Init the range of first and last
**		3. Swap if there is R option
**		4. execute the editor
**		5. build the command
**		6. execute and change the command with g_shell.history->tmp
*/

static void	fc_e_execution_loop(char *cmd[])
{
	int	i;

	i = -1;
	if (g_shell.history->tmp)
		ft_strdel(&(g_shell.history->tmp));
	while (cmd[++i])
	{
		g_shell.history->tmp = cmd[i];
		ft_printf("%s", cmd[i]);
		ft_fc_execute(cmd[i]);
		(g_shell.history->tmp != NULL) ? append_history() : 0;
	}
}

int			fc_e_op(int ops, char *editor, char *first, char *last)
{
	char	*cmd[52];
	int		r_ind[2];
	int		fd;

	if (fc_check_editor(editor) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (fc_e_init_range(r_ind, first, last) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ops & FC_R_OP)
		ft_swap_int(&r_ind[0], &r_ind[1]);
	fd = open(FC_EDITING_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	fc_e_copy_lines_into_editor(fd, r_ind);
	close(fd);
	fc_e_editing_process(editor);
	ft_bzero(cmd, sizeof(char*) * 52);
	fc_e_build_cmd(cmd);
	fc_e_execution_loop(cmd);
	return (EXIT_SUCCESS);
}
