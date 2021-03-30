/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stopped_and_terminated_jobs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 02:37:24 by dthan             #+#    #+#             */
/*   Updated: 2021/03/30 20:17:31 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	mark_process_status_exit(t_process *p, int status)
{
	ft_putchar('\n');
	p->stopped = 1;
	g_shell.exit_status = 128 + WSTOPSIG(status);
}

void	set_job_complete_because_of_signal(t_job *j)
{
	t_process *p_ptr;

	p_ptr = j->first_process;
	while (p_ptr)
	{
		if (!p_ptr->completed)
		{
			kill(p_ptr->pid, SIGTERM);
			p_ptr->completed = 1;
		}
		p_ptr = p_ptr->next;
	}
}

void	print_signal(char *sig_message, int sig_number, t_job *j)
{
	char msgs[256];
	char *numb;

	numb = ft_itoa(sig_number);
	ft_strcpy(msgs, sig_message);
	ft_strcat(msgs, ": ");
	ft_strcat(msgs, numb);
	(numb) ? free(numb) : 0;
	if (j->foreground && !job_is_stopped(j))
		ft_printf("%s\n", msgs);
	else
	{
		format_job_info(j, msgs, 0);
		set_job_complete_because_of_signal(j);
	}
}

void	mark_process_status_signal(t_process *p, int status, t_job *j)
{
	static char *sig_msgs[SIGNAL_NUMBER_OSX];

	p->completed = 1;
	if (!ft_strequ(sig_msgs[0], SIGHUP_MSG))
		init_signal_messages(sig_msgs);
	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_shell.exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) - 1 <= SIGNAL_NUMBER_OSX &&
			WTERMSIG(status) > 0)
		{
			if (is_signal_should_print(WTERMSIG(status)))
				print_signal(sig_msgs[WTERMSIG(status) - 1], WTERMSIG(status), j);
		}
		else
			ft_printf("%s: Unknown signal%d\n", SHELL_NAME, WTERMSIG(status));
	}
}

int		mark_process_status_helper(
	t_process *first_process, pid_t pid, int status, t_job *j)
{
	t_process *p_ptr;

	p_ptr = first_process;
	while (p_ptr)
	{
		if (p_ptr->pid == pid)
		{
			p_ptr->status = status;
			if (WIFSTOPPED(status))
				mark_process_status_exit(p_ptr, status);
			else
				mark_process_status_signal(p_ptr, status, j);
			return (0);
		}
		p_ptr = p_ptr->next;
	}
	return (1);
}

int		mark_process_status(t_job *j, pid_t pid, int status)
{
	t_job	*j_ptr;
	int		ret;

	if (pid > 0)
	{
		j_ptr = j;
		while (j_ptr)
		{
			ret = mark_process_status_helper(j_ptr->first_process, pid, status, j);
			if (ret == 0)
				return (0);
			j_ptr = j_ptr->next;
		}
	}
	return (1);
}
