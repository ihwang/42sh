/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:01:10 by dthan             #+#    #+#             */
/*   Updated: 2021/03/30 18:40:55 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		job_is_stopped(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		if (!p_ptr->completed && !p_ptr->stopped)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

int		job_is_completed(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		if (!p_ptr->completed)
			return (0);
		p_ptr = p_ptr->next;
	}
	return (1);
}

void	update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!mark_process_status(g_shell.first_job, pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

void	wait_for_job(t_job *j, int opt)
{
	int pid;
	int status;

	pid = waitpid(-j->pgid, &status, opt);
	while (!mark_process_status(j, pid, status) &&
		!job_is_stopped(j) &&
		!job_is_completed(j))
		pid = waitpid(-j->pgid, &status, opt);
}

void	delete_all_jobs_before_exit(t_job *first_job)
{
	t_job *ptr;
	t_job *temp;

	update_status();
	if (first_job == NULL)
		return ;
	ptr = first_job;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		delete_job(temp, 1);
		temp = NULL;
	}
}
