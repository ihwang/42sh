/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 00:22:24 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/28 15:27:45 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*

typedef s_read_history_file
{
	char *line_read;
	char buff_read[4096];
	char buff_write[4096];
	int  pos;
	int  cont;
}		t_read_history_file;

void init_read_history_struct(t_read_history_file *self)
{
	self->line_read = null;
	ft_bzero(self->buff_read, 4096);
	ft_bzero(self->buff_write, 4096);
	self->pos = 0;
	self->cont = 0;
}

Algorithm for reading history file:
	1. getting everyline from the history file, which is without '\n'
	2. copy the line into the buff_read and copy a line break there too, so we dont have to make condition checking
	   to add line break since, at the end of every line is a line break
	3. check if return value of function check_continue_read_line
		if instance.cont == 1 --> continue read and add into the buff_read
		else instance.cont == 0 --> add into the history container
				To add into the history container:
				a, reset buff_write
				b, using strncpy to copy the buff_read to buff_write with n = instance.pos + 1
				c, add into the history container
				d, cut the rest of the buff_read, start with instance.pos + 1
				e, now we start copy into buff_read again and now instance.pos reset to 0

	4. free the instance.line to keep reading new line

DEMO
read_history_file()
{
	t_read_history_file instance;

	init_read_history_struct(&instance);
	while (get_next_line(fd, &(instance->line)) && ...)
	{
		ft_strcat(buff_read, line);
		ft_strcat(buff_read, "\n");
		if ((instance.cont = is_continuing_read_line(instance.buff_read, &(instance.pos), instance.cont)) == 0)
		{
			ft_bzero(instance->buff_write, 4096);
			ft_strncpy(instance.buff_read, instance.buff_write, instance.pos + 1);
			g_shell.history->hist[i++] = ft_strdup(instance.buff_write);
			g_shell.history->curr = i;
			ft_strcpy(instance.buff_read, &buff_read[instance.pos + 1]);
			instance.pos = 0;
			if (instance.buff_write[ft_strlen(instance.buff_write)] == 4)
				need to copy the nex one to the history, since there is sth still in the buff_write like that abc\n
				so we take it into the history container, becarefull well checking with the return i for history container
				since it could be making +i more for i
		}
		else
		{
			if (instance.buf_read[instance.pos] != '\0')   ---> for checking error
			{
				instance.pos++;
			}
		}
		(instance.line) ? free(instance.line) : 0;
	}
}

----------------------------------------------------------------
Algorithm for is_continuing_read_line function:
we keep reading the buff_read from the pos since we cant keep reading from 0, it has to be
where we left off, since at every loop of get_next_line we already add a line_break
	if (buff_read[*pos] == 4)
		check_continue_read_line return 1
	if (buff_read[pos] == '\n')
		if isContinue == 1
			check_continue_read_line return 1
		else
			check_continue_read_line return 0
	if jump_quote == EXIT_FAILURE
		check_continue_read_line return 1



int is_logical_operators_or_pipe_operator(char *str, int *i)
{
	if (ft_strnequ(str, "&&", 2) || ft_strnequ(str, "||", 2))
	{
		(*i)++;
		return 1;
	}
	else if (ft_strnequ(str, "|", 1))
	{
		return 1;
	}
	return 0;
}


DEMO
int is_continuing_read_line(char *buff_read, int *pos, int isContinue)
{
	while (str[(*pos)])
	{
		if (buff_read[*pos] == 4)
		{
			return 0;
		}
		else if (buff_read[*pos] == '\n')
		{
			return (isContinue) ? 1 : 0;
		}
		else if (is_inhibitor(buff_read, *pos, buff_read[*pos]))
		{
			if (jump_quote(buff_read, pos, buff_read[*pos]) == EXIT_FAILURE)
			{
				return 0;
			}
			if (isContinue)
			{
				isContinue = 0;
			}
		}
		else if (is_logical_operators_or_pipe_operator(&buf_read[*pos], pos))
		{
			isContinue = 1;
		}
		else if (!ft_isspace(buff_read[*pos]))
		{
			if (isContinue)
			{
				isContinue = 0;
			}
		}
		(*pos)++;
	}
	return (isContinue);
}

*/

typedef struct s_read_history_file
{
	char	*line_read;
	char	buff_read[4096];
	char	buff_write[4096];
	int		pos;
	int		cont;
	int		hst_size;
	char	quote_type;
}		t_read_history_file;

void init_read_history_struct(t_read_history_file *self)
{
	self->line_read = NULL;
	ft_bzero(self->buff_read, 4096);
	ft_bzero(self->buff_write, 4096);
	self->pos = 0;
	self->cont = 1;
	self->hst_size = 0;
	self->quote_type = '\0';
}

int is_logical_operators_or_pipe_operator(char *str, int *i)
{
	if (ft_strnequ(str, "&&", 2) || ft_strnequ(str, "||", 2))
	{
		(*i)++;
		return 1;
	}
	else if (ft_strnequ(str, "|", 1))
	{
		return 1;
	}
	return 0;
}

int		jump_quote2(char *input, int *i, char quote_type)
{
	if (quote_type == '\\')
		(*i)++;
	else if (quote_type == '"' || quote_type == '\'')
	{
		(*i)++;
		while (input[*i])
		{
			if (input[*i] == quote_type && is_real_character(input, *i))
				break ;
			(*i)++;
		}
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		jump_quote3(char *input, int *i, char quote_type)
{
	while (input[*i])
	{
		if (input[*i] == quote_type && is_real_character(input, *i))
			break ;
		else if (input[*i] == 4)
			return (EXIT_FAILURE);
		(*i)++;
	}
	if (input[*i] == '\0')
		return (2);
	return (EXIT_SUCCESS);
}

int read_line_not_inside_quotation(char *buff_read, int *pos, int isContinue, char in_quotation[1])
{
	while (buff_read[(*pos)])
	{
		if (buff_read[*pos] == 4)
			return 0;
		else if (buff_read[*pos] == '\n')
			return (isContinue) ? 1 : 0;
		else if (is_inhibitors(buff_read, *pos, buff_read[*pos]))
		{
			in_quotation[0] = buff_read[*pos];
			if (jump_quote2(buff_read, pos, buff_read[*pos]) == EXIT_FAILURE)
				return 1;
			isContinue = 0;
			in_quotation[0] = '\0';
		}
		else if (is_logical_operators_or_pipe_operator(&buff_read[*pos], pos))
			isContinue = 1;
		else if (!ft_isspace(buff_read[*pos]) && isContinue)
			isContinue = 0;
		(*pos)++;
	}
	return (isContinue);
}

int is_continuing_read_line(char *buff_read, int *pos, int isContinue, char in_quotation[1])
{
	int ret;

	if (in_quotation[0])
	{
		ret = jump_quote3(buff_read, pos, in_quotation[0]);
		if (ret == EXIT_FAILURE)
		{
			in_quotation[0] = '\0';
			return (0);
		}
		else if (ret == 2)
		{
			return (1);
		}
		isContinue = 0;
		in_quotation[0] = '\0';
		(*pos)++;
	}
	return read_line_not_inside_quotation(buff_read, pos, isContinue, in_quotation);
}

void add_command_into_history(t_read_history_file *self)
{
	ft_bzero(self->buff_write, 4096);
	ft_strncpy(self->buff_write, self->buff_read, self->pos + 1);
	g_shell.history->hist[self->hst_size++] = ft_strdup(self->buff_write);
	g_shell.history->curr = self->hst_size;
	ft_strcpy(self->buff_read, &(self->buff_read)[self->pos + 1]);
	self->pos = 0;
}

int read_history_file(int fd)
{
	t_read_history_file instance;

	init_read_history_struct(&instance);
	while (get_next_line(fd, &(instance.line_read)) && instance.hst_size < (HISTFILESIZE - 1))
	{
		ft_strcat(instance.buff_read, instance.line_read);
		ft_strcat(instance.buff_read, "\n");
		if ((instance.cont = is_continuing_read_line(instance.buff_read, &(instance.pos), instance.cont, &instance.quote_type)) == 0)
		{
			add_command_into_history(&instance);
			if (instance.buff_write[ft_strlen(instance.buff_write) - 1] == 4)
			{
				if ((instance.cont = is_continuing_read_line(instance.buff_read, &(instance.pos), instance.cont, &instance.quote_type)) == 0)
					add_command_into_history(&instance);
				else if (instance.buff_read[instance.pos] != '\0')
					instance.pos++;
			}
		}
		else if (instance.buff_read[instance.pos] != '\0')
			instance.pos++;
		free(instance.line_read);
		instance.line_read = NULL;
	}
	(instance.line_read) ? free(instance.line_read) : 0;
	return (instance.hst_size);
}

// static int	read_history_file(int fd)
// {
// 	char	*line;
// 	char	buffer[2][4096];
// 	int		i;
// 	int		end_pos;

// 	ft_bzero(buffer[0], 4096);
// 	i = 0;
// 	while (get_next_line(fd, &line) && i < HISTFILESIZE)
// 	{
// 		ft_strcat(buffer[0], line);
// 		if ((end_pos = ft_check_continue_hist(buffer[0])) != -1)
// 		{
// 			ft_bzero(buffer[1], 4096);
// 			ft_strncpy(buffer[1], buffer[0], end_pos + 1);
// 			if (buffer[0][end_pos] != 4 && buffer[0][end_pos] != '\n')
// 				ft_strcat(buffer[1], "\n");
// 			g_shell.history->hist[i++] = ft_strdup(buffer[1]);
// 			g_shell.history->curr = i;
// 			ft_strcpy(buffer[0], &buffer[0][end_pos + 1]);
// 		}
// 		ft_strcat(buffer[0], "\n");
// 		free(line);
// 	}
// 	return (i);
// }

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
