/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_index_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:30:29 by rklein            #+#    #+#             */
/*   Updated: 2021/03/19 22:40:23 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**Calculates the row in which the given index
*/

int		ft_y_pos(t_l *l, int index)
{
	int i;
	int	count;
	int	row;

	count = l->pmpt;
	i = 0;
	row = 1;
	while (l->line[i] && i <= index)
	{
		count++;
		if (l->line[i] == '\n')
		{
			row++;
			count = 0;
		}
		else if (count == l->co)
		{
			row++;
			count = 0;
		}
		i++;
	}
	return (row);
}

/*
** calculates the index of l->line on which the cursor is
*/

int		ft_index_calc(t_l *l)
{
	int	i;
	int len;

	len = l->x;
	i = l->y;
	while (--i >= 0)
	{
		len += ft_atoi(l->lc[i]);
	}
	return (len - l->pmpt);
}

/*
** calculates the x position of cursor for history command
*/

int		ft_cursor_x(t_l *l)
{
	int	i;

	ft_line_count(l);
	i = 0;
	while (l->lc[i])
		i++;
	return (ft_atoi(l->lc[i - 1]));
}
