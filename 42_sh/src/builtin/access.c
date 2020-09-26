/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/06 15:01:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				possible_to_access_dir(t_exe *c)
{
	t_stat		sb;

	stat(c->av[1], &sb);
	if (access(c->av[1], F_OK))
	{
		error_monitor("cd: ", c->av[1], \
			": No such file or directory", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	else if ((sb.st_mode & F_TYPE_MASK) != S_IFDIR)
	{
		error_monitor("cd: ", c->av[1], \
			": Not a directory", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	else if (access(c->av[1], X_OK))
	{
		error_monitor("cd: ", c->av[1], \
			": Permission denied", EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				possible_to_access_file(t_exe *c)
{
	if (c->av[0][0] == '.' || c->av[0][0] == '/')
	{
		if (access(c->av[0], F_OK))
		{
			error_monitor(c->av[0], ":No such file or dirrectory" \
			, NULL, EXIT_FAILURE);
			return (0);
		}
		else if (access(c->av[0], X_OK))
		{
			error_monitor(c->av[0], ": Permission denied" \
			, NULL, EXIT_FAILURE);
			return (0);
		}
		else
			return (1);
	}
	else
		return (0);
}
