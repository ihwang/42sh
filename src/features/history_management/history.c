/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/20 18:29:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	read_history_file(int fd)
{
	char	*line;
	char	buffer[2][4096];
	int		i;
	int		end_pos;

	ft_bzero(buffer[0], 4096);
	i = 0;
	while (get_next_line(fd, &line) && i < HISTFILESIZE)
	{
		ft_strcat(buffer[0], line);
		if ((end_pos = ft_check_continue_hist(buffer[0])) != -1)
		{
			ft_bzero(buffer[1], 4096);
			ft_strncpy(buffer[1], buffer[0], end_pos + 1);
			ft_strcat(buffer[1], "\n");
			g_shell.history->hist[i++] = ft_strdup(buffer[1]);
			g_shell.history->curr = i;
			ft_strcpy(buffer[0], &buffer[0][end_pos]);
		}
		else
			ft_strcat(buffer[0], "\n");
		free(line);
	}
	return (i);
}

void		get_history(int fd)
{
	int		i;

	fd = open(g_shell.history->savedfile, O_RDWR | O_CREAT, 0644);
	i = read_history_file(fd);
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
	if (ft_strequ(g_shell.history->tmp, "\n"))
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
