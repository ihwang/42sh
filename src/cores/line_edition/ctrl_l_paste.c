/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_l_paste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 01:37:15 by tango             #+#    #+#             */
/*   Updated: 2021/03/19 22:01:04 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	paste_apply_screen(t_l *l, char *clip, int i)
{
	apply_termcap_str("cd", 0, 0);
	ft_putstr(clip);
	apply_termcap_str("sc", 0, 0);
	if (l->line)
		ft_putstr(&l->line[i]);
	apply_termcap_str("rc", 0, 0);
}

static void	wind_up_cursor(t_l *l)
{
	int		starting_row_from_top;
	int		row_position;
	int		nb_rewind;
	int		gap_between_begin_end;

	l->starting_row = ft_row_count(l) - 1;
	starting_row_from_top = l->total_row - l->starting_row;
	gap_between_begin_end = ft_y_pos(l, ft_index_calc(l));
	row_position = starting_row_from_top + gap_between_begin_end;
	nb_rewind = get_current_row() - row_position;
	while (nb_rewind-- > 0)
	{
		apply_termcap_str("up", 0, 0);
	}
}

static char	*get_clip(char raw_clip[], char *autocom_clip)
{
	char	*clip;

	if (autocom_clip)
		clip = ft_strdup(autocom_clip);
	else if (raw_clip)
		clip = get_clip_external(raw_clip);
	else
	{
		if (!(clip = clipboard(NULL, CLIP_TAKE)))
			return (EXIT_SUCCESS);
		clip = ft_strdup(clip);
	}
	return (clip);
}

int			paste(t_l *l, char raw_clip[], char *autocom_clip)
{
	char			*clip;
	char			*tmp;
	int				i;
	int				clip_len;

	clip = get_clip(raw_clip, autocom_clip);
	if (clip == NULL)
		return (EXIT_SUCCESS);
	clip_len = ft_strlen(clip);
	i = ft_index_calc(l);
	paste_apply_screen(l, clip, i);
	tmp = ft_strnew(l->nb + clip_len);
	if (l->line)
		tmp = ft_strncpy(tmp, l->line, i);
	tmp = ft_strcat(tmp, clip);
	if (l->line)
		tmp = ft_strcat(tmp, &l->line[i]);
	ft_strdel(&l->line);
	l->line = tmp;
	if (l->starting_row < ft_row_count(l) - 1)
		wind_up_cursor(l);
	paste_background(l, clip_len);
	ft_strdel(&clip);
	return (EXIT_SUCCESS);
}
