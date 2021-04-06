/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_messages.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:49:44 by tango             #+#    #+#             */
/*   Updated: 2021/04/06 23:30:33 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

char		is_signal_should_print(int sig)
{
	if (sig == SIGINT || sig == SIGPIPE || sig == SIGURG || sig == SIGCONT \
	|| sig == SIGCHLD || sig == SIGIO || sig == SIGXFSZ || sig == SIGWINCH \
	|| sig == SIGINFO)
	{
		return (0);
	}
	return (1);
}

static void	init_signal_messages2(char *sig_msgs[SIGNAL_NUMBER_OSX])
{
	sig_msgs[16] = ft_strdup(SIGSTOP_MSG);
	sig_msgs[17] = ft_strdup(SIGTSTP_MSG);
	sig_msgs[18] = ft_strdup(SIGCONT_MSG);
	sig_msgs[19] = ft_strdup(SIGCHLD_MSG);
	sig_msgs[20] = ft_strdup(SIGTTIN_MSG);
	sig_msgs[21] = ft_strdup(SIGTTOU_MSG);
	sig_msgs[22] = ft_strdup(SIGIO_MSG);
	sig_msgs[23] = ft_strdup(SIGXCPU_MSG);
	sig_msgs[24] = ft_strdup(SIGXFSZ_MSG);
	sig_msgs[25] = ft_strdup(SIGVTALRM_MSG);
	sig_msgs[26] = ft_strdup(SIGPROF_MSG);
	sig_msgs[27] = ft_strdup(SIGWINCH_MSG);
	sig_msgs[28] = ft_strdup(SIGINFO_MSG);
	sig_msgs[29] = ft_strdup(SIGUSR1_MSG);
	sig_msgs[30] = ft_strdup(SIGUSR2_MSG);
}

void		init_signal_messages(char *sig_msgs[SIGNAL_NUMBER_OSX])
{
	sig_msgs[0] = ft_strdup(SIGHUP_MSG);
	sig_msgs[1] = ft_strdup(SIGINT_MSG);
	sig_msgs[2] = ft_strdup(SIGQUIT_MSG);
	sig_msgs[3] = ft_strdup(SIGILL_MSG);
	sig_msgs[4] = ft_strdup(SIGTRAP_MSG);
	sig_msgs[5] = ft_strdup(SIGABRT_MSG);
	sig_msgs[6] = ft_strdup(SIGEMT_MSG);
	sig_msgs[7] = ft_strdup(SIGFPE_MSG);
	sig_msgs[8] = ft_strdup(SIGKILL_MSG);
	sig_msgs[9] = ft_strdup(SIGBUS_MSG);
	sig_msgs[10] = ft_strdup(SIGSEGV_MSG);
	sig_msgs[11] = ft_strdup(SIGSYS_MSG);
	sig_msgs[12] = ft_strdup(SIGPIPE_MSG);
	sig_msgs[13] = ft_strdup(SIGALRM_MSG);
	sig_msgs[14] = ft_strdup(SIGTERM_MSG);
	sig_msgs[15] = ft_strdup(SIGURG_MSG);
	return (init_signal_messages2(sig_msgs));
}
