/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:55:32 by rklein            #+#    #+#             */
/*   Updated: 2021/03/24 14:08:02 by marvin           ###   ########.fr       */
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

void	ft_check_ctrld_hist(char **line, char buffer[])
{
	int		len;
	char	*ptr;
	char	*tmp;

	tmp = *line;
	/*if (*line[0] == 4)
	{
		ft_bzero(buffer, 4096);
		len = ft_strlen(&tmp[1]);
		ft_memmove(tmp, &tmp[1], len);
		tmp[len] = '\0';
	}*/
	if ((ptr = ft_strchr(tmp, 4)))
	{	
		ptr++;
		ft_bzero(buffer, 4096);
		len = ft_strlen(ptr);
		ft_memmove(tmp, ptr, len);
		tmp[len] = '\0';
	}
	*line = tmp;
}

/*void	ft_check_ctrld_hist(char **line, char buffer[], int *index)
{
	int		len;
	int		i;
	char	*ptr;
	char	*tmp;

	tmp = *line;
	i = *index;

	if (*line[0] == 4)
	{
		ft_strcat(buffer, "\x04\n");
		g_shell.history->hist[i++] = ft_strdup(buffer);
		g_shell.history->curr = i;
		ft_bzero(buffer, 4096);
		len = ft_strlen(&tmp[1]);
		ft_memmove(tmp, &tmp[1], len);
		tmp[len] = '\0';
	}
	if ((ptr = ft_strchr(tmp, 4)))
	{	
		ptr++;
		ft_strncat(buffer, tmp, (ptr - tmp) - 1);
		ft_strcat(buffer, "\x04\n");
		g_shell.history->hist[i++] = ft_strdup(buffer);
		g_shell.history->curr = i;
		ft_bzero(buffer, 4096);
		len = ft_strlen(ptr);
		ft_memmove(tmp, ptr, len);
		tmp[len] = '\0';
		if (tmp[len - 1] ==  4)
			write(1, "!!END!!", 7); 
	}
	*index = i;
	*line = tmp;
}*/
