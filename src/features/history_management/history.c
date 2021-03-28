/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/28 15:32:13 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		get_history(int fd)
{
	int		i;
	char	**ptr_container;

	fd = open(g_shell.history->savedfile, O_RDWR | O_CREAT, 0644);
	ptr_container = g_shell.history->hist;
	i = read_commands_from_a_file(fd, ptr_container);
	g_shell.history->curr = i;
	g_shell.history->hst = g_shell.history->curr;
	g_shell.history->hist[i++] = ft_strnew(0);
	g_shell.history->hist[i] = NULL;
	g_shell.history->hstsize = HISTFILESIZE;
	close(fd);
}

static void	append_history_realloc(void)
{
	char	**tmp;
	int		i;

	g_shell.history->hstsize += HISTFILESIZE;
	tmp = (char**)ft_memalloc(sizeof(char*) * (g_shell.history->hstsize + 2));
	i = -1;
	while (++i < g_shell.history->curr)
		tmp[i] = ft_strdup(g_shell.history->hist[i]);
	tmp[i++] = g_shell.history->tmp;
	g_shell.history->curr = i;
	tmp[i++] = ft_strnew(0);
	tmp[i] = NULL;
	ft_arraydel(g_shell.history->hist);
	g_shell.history->hist = tmp;
}

void		append_history(void)
{
	if (ft_isspace_str(g_shell.history->tmp))
	{
		free(g_shell.history->tmp);
		g_shell.history->tmp = NULL;
		return ;
	}
	if (g_shell.history->curr < g_shell.history->hstsize)
	{
		if (g_shell.history->hist[g_shell.history->curr])
			free(g_shell.history->hist[g_shell.history->curr]);
		g_shell.history->hist[g_shell.history->curr] = g_shell.history->tmp;
		if (g_shell.history->tmp)
		{
			g_shell.history->curr++;
			g_shell.history->hist[g_shell.history->curr] = ft_strnew(0);
			g_shell.history->hist[g_shell.history->curr + 1] = NULL;
		}
	}
	else
		append_history_realloc();
	g_shell.history->hst = g_shell.history->curr;
	g_shell.history->tmp = NULL;
}

void		delete_save_history(void)
{
	int		i;
	int		fd;

	if (g_shell.history->curr == 0)
		return ;
	fd = open(g_shell.history->savedfile, O_TRUNC | O_WRONLY | O_CREAT);
	i = (g_shell.history->curr > HISTFILESIZE) ? \
	g_shell.history->curr - HISTFILESIZE - 1 : -1;
	while (++i < g_shell.history->curr)
		ft_dprintf(fd, "%s", g_shell.history->hist[i]);
	close(fd);
}
