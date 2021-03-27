/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_exec_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:35 by dthan             #+#    #+#             */
/*   Updated: 2021/03/27 16:27:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*fc_e_build_cmd(void)
{
	int		fd;
	char	*line;
	char	buffer[2][4096];
	int		end_pos;

	ft_bzero(buffer[0], 4096);
	ft_bzero(buffer[1], 4096);
	fd = open(FC_EDITING_FILE, O_RDONLY, 0644);
	while (get_next_line(fd, &line))
	{
		ft_strcat(buffer[0], line);
		if ((end_pos = ft_check_continue_hist(buffer[0])) != -1 && line[0])
		{
			if (buffer[1][0])
				ft_strcat(buffer[1], ";");
			ft_strncat(buffer[1], buffer[0], end_pos + 1);
			ft_strcpy(buffer[0], &buffer[0][end_pos]);
		}
		else if (line[0])
			ft_strcat(buffer[0], "\n");
		free(line);
	}
	close(fd);
	ft_strcat(buffer[1], "\n");
	return (ft_strdup(buffer[1]));
}

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
	char	*format;

	if (r_ind[0] < r_ind[1])
	{
		while (r_ind[0] < r_ind[1])
		{
			format = ft_strndup(g_shell.history->hist[r_ind[0] - 1], \
			(int)ft_strlen(g_shell.history->hist[r_ind[0] - 1]) - 1);
			ft_dprintf(fd, "%s\n", format);
			ft_strdel(&format);
			r_ind[0]++;
		}
	}
	else if (r_ind[0] > r_ind[1])
	{
		while (r_ind[0] > r_ind[1])
		{
			format = ft_strndup(g_shell.history->hist[r_ind[0] - 1], \
			(int)ft_strlen(g_shell.history->hist[r_ind[0] - 1]) - 1);
			ft_dprintf(fd, "%s\n", format);
			ft_strdel(&format);
			r_ind[0]--;
		}
	}
	ft_dprintf(fd, "%s", g_shell.history->hist[r_ind[0] - 1]);
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

static void		fc_e_execution_loop(char *cmd[])
{
	int	i;

	i = -1
	while (cmd[++i])
	{
		if (g_shell.history->tmp)
			free(g_shell.history->tmp);
		g_shell.history->tmp = cmd[i];
		ft_printf("%s", cmd[i]);
		ft_fc_execute(cmd[i]);
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
	fc_e_build_cmd(cmd);
	fc_e_execution_loop(cmd);
	return (EXIT_SUCCESS);
}

/*int			fc_e_op(int ops, char *editor, char *first, char *last)
{
	char	*cmd;
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
	cmd = fc_e_build_cmd();
	if (g_shell.history->tmp)
		free(g_shell.history->tmp);
	g_shell.history->tmp = cmd;
	ft_printf("%s", cmd);
	ft_fc_execute(cmd);
	return (EXIT_SUCCESS);
}*/
