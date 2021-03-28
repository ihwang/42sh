/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_utilities2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:27:09 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 02:05:14 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	fc_is_accessible_editor(char *editor, char **options)
{
	int		i;
	char	path[4096];

	i = -1;
	ft_bzero(path, 4096);
	while (options && options[++i])
	{
		ft_strcpy(path, options[i]);
		ft_strcat(path, "/");
		ft_strcat(path, editor);
		if (access(path, F_OK) == 0)
			return (1);
	}
	return (0);
}

int			fc_check_editor(char *editor)
{
	char **options;

	options = ft_strsplit(ft_getenv("PATH"), ':');
	if (!fc_is_accessible_editor(editor, options))
	{
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, editor);
		ft_arraydel(options);
		return (EXIT_FAILURE);
	}
	ft_arraydel(options);
	return (EXIT_SUCCESS);
}

char		*fc_return_cmd(char *str)
{
	int pos;

	pos = fc_range(str);
	if (pos == 0)
		return (NULL);
	return (ft_strdup(g_shell.history->hist[pos - 1]));
}

void		write_history_commands_into_editor(int fd, int *r_ind)
{
	if (g_shell.history->hist[r_ind[0] - 1]
		[ft_strlen(g_shell.history->hist[r_ind[0] - 1]) - 1] == 4)
	{
		write(fd,
			g_shell.history->hist[r_ind[0] - 1],
			ft_strlen(g_shell.history->hist[r_ind[0] - 1]) - 1);
	}
	else
	{
		ft_dprintf(fd, "%s", g_shell.history->hist[r_ind[0] - 1]);
	}
}
