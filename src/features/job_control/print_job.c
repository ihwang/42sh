/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 16:53:57 by dthan             #+#    #+#             */
/*   Updated: 2021/03/30 19:40:53 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	format_job_info(t_job *j, const char *status, int opt)
{
	ft_printf("[%d]", j->id);
	if (is_the_current_job(j))
		ft_printf("%-3c", '+');
	else if (is_the_last_job(j))
		ft_printf("%-3c", '-');
	else
		ft_putstr("   ");
	ft_printf("%-24s%s", status, j->command);
	if (opt)
		(!j->foreground) ? ft_putstr(" &") : 0;
	ft_putchar('\n');
}

void	do_job_notification_completed_job(t_job *j, t_job *jlast, t_job *jnext)
{
	if (!j->foreground)
		format_job_info(j, "Done", 0);
	if (jlast)
		jlast->next = jnext;
	else
		g_shell.first_job = jnext;
	delete_job(j, 0);
}

void	do_job_notification_stopped_job(t_job *j, t_job *jlast)
{
	format_job_info(j, "Stopped(SIGTSTP)", 0);
	j->notified = 1;
	jlast = j;
}

void	do_job_notification(void)
{
	t_job *j;
	t_job *jlast;
	t_job *jnext;

	if (g_shell.first_job == NULL)
		return ;
	update_status();
	jlast = NULL;
	j = g_shell.first_job;
	while (j)
	{
		jnext = j->next;
		if (job_is_completed(j))
			do_job_notification_completed_job(j, jlast, jnext);
		else if (job_is_stopped(j) && !j->notified)
			do_job_notification_stopped_job(j, jlast);
		else
			jlast = j;
		j = jnext;
	}
}
