/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2021/03/20 15:44:30 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			ft_check_continue_hist(char buf[])
{
	int	i;
	int	ch;

	ch = 0;
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == 4)
			return (i);
		if (is_inhibitors(&buf[i], i, buf[i]))
		{
			if (jump_quote(buf, &i, buf[i]) == EXIT_FAILURE)
				return (-1);
		}
		else if (ft_strnequ(&buf[i], "&&", 2) || ft_strnequ(&buf[i], "||", 2))
		{
			ch = ch ? 0 : 1;
			i++;
		}
		else if (buf[i] == '|')
			ch = ch ? 0 : 1;
		else if (ch && !ft_isspace(buf[i]))
			ch = 0;
	}
	return (i == 0 || ch == 1 ? -1 : i);
}
