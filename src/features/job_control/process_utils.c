/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:05:30 by dthan             #+#    #+#             */
/*   Updated: 2021/04/07 00:05:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	put_to_plist(t_process *new_process, t_process **first_process)
{
	t_process *p_ptr;

	if (*first_process == NULL)
		*first_process = new_process;
	else
	{
		p_ptr = *first_process;
		while (p_ptr->next)
			p_ptr = p_ptr->next;
		p_ptr->next = new_process;
	}
}

t_process	*create_process(t_job *j)
{
	t_process *process;

	process = (t_process*)ft_memalloc(sizeof(t_process));
	process->av = (char**)ft_memalloc(sizeof(char*) * MAX_ARGV);
	process->ac = 0;
	process->pid = 0;
	process->stdin = j->stdin;
	process->stdout = j->stdout;
	process->stderr = j->stderr;
	process->first_redi = NULL;
	process->first_assignment = NULL;
	process->completed = NOT_COMPLETED;
	process->stopped = NOT_STOPPED;
	process->status = UNAVAILABLE_STATUS;
	process->notified = 0;
	put_to_plist(process, &j->first_process);
	return (process);
}

int			last_process_status(t_job *job)
{
	t_process *p_ptr;

	p_ptr = job->first_process;
	if (p_ptr == NULL)
		return (0);
	while (p_ptr && p_ptr->next)
		p_ptr = p_ptr->next;
	return (p_ptr->status);
}
