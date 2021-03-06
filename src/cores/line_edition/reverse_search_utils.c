/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_search_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 16:47:47 by dthan             #+#    #+#             */
/*   Updated: 2021/03/29 15:44:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		ft_rs_print(void)
{
	char	tmp[4096];
	int		len;
	int		d;

	if (g_shell.history->hist[g_shell.history->hst][0])
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);
		d = 1;
		ft_bzero(tmp, 4096);
		ft_strncpy(tmp, g_shell.history->hist[g_shell.history->hst], len - d);
		ft_putstr(tmp);
	}
	else
		ft_putstr(g_shell.history->hist[g_shell.history->hst]);
}

void		ft_reverse_search_clear(t_l *l)
{
	int	i;
	int	line_rows;
	int	starting_row_from_top;
	int	new_starting_row;

	line_rows = l->rs ? ft_row_count_rs(l) : ft_row_count(l);
	if (!l->rs)
	{
		l->y = line_rows - 1;
		l->x = ft_cursor_x(l);
		l->nb = ft_strlen(l->line);
	}
	new_starting_row = l->starting_row;
	if (l->starting_row < line_rows)
		new_starting_row = line_rows;
	starting_row_from_top = l->total_row - l->starting_row;
	i = get_current_row() - starting_row_from_top;
	while (i-- > 0)
		apply_termcap_str("up", 0, 0);
	apply_termcap_str("ch", 0, 0);
	apply_termcap_str("cd", 0, 0);
	l->starting_row = new_starting_row;
}

int			ft_reverse_search_reset(t_l *l)
{
	int	len;
	int	d;

	free(l->rev_sr);
	l->rs = 0;
	free(l->line);
	if (g_shell.history->hist[g_shell.history->hst][0])
	{
		len = ft_strlen(g_shell.history->hist[g_shell.history->hst]);
		d = 1;
		l->line = ft_strndup(g_shell.history->hist[g_shell.history->hst], \
		len - d);
	}
	else
		l->line = ft_strnew(0);
	ft_reverse_search_clear(l);
	print_prompt(l->promp_type);
	ft_putstr(l->line);
	ft_line_count(l);
	return (home_key(l));
}
