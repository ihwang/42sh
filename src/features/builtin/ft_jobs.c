/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 04:00:07 by dthan             #+#    #+#             */
/*   Updated: 2021/03/30 19:15:08 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_jobs_printing_with_argv(char **argv)
{
	int		i;
	t_job	*j;
	char	*status;

	i = -1;
	while (argv[++i])
	{
		if ((j = is_valid_job_id(argv[i])) == NULL)
			ft_dprintf(2, "%s: jobs: %s: no such job\n", SHELL_NAME, argv[i]);
		else
		{
			if (!job_is_completed(j))
			{
				status = job_is_stopped(j) ? "Stopped(SIGTSTP)" : "Running";
				format_job_info(j, status, 1);
				if (j->notified == 0)
					j->notified = 1;
			}
		}
	}
}

void	ft_jobs_printing_without_argv(void)
{
	t_job	*j_ptr;
	char	*status;

	j_ptr = g_shell.first_job;
	while (j_ptr)
	{
		if (!job_is_completed(j_ptr))
		{
			status = job_is_stopped(j_ptr) ? "Stopped(SIGTSTP)" : "Running";
			format_job_info(j_ptr, status, 1);
			if (j_ptr->notified == 0)
				j_ptr->notified = 1;
		}
		j_ptr = j_ptr->next;
	}
}

int		ft_jobs(t_process *p)
{
	update_status();
	if (p->av[1])
		ft_jobs_printing_with_argv(&p->av[1]);
	else
		ft_jobs_printing_without_argv();
	return (EXIT_SUCCESS);
}
