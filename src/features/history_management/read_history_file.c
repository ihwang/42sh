/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 23:37:02 by dthan             #+#    #+#             */
/*   Updated: 2021/03/27 00:17:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** typedef s_read_history_file
** {
**	char	*line_read;			--> NULL		from ft_get_line
**	char	buff_read[4096];	--> ft_bzero	container for line_read
**	char	buff_write[4096];	--> ft_bzero	cmd to add to history
**	int		pos;				--> 0			position
**	int		cont;				--> 1			check if continue adding or not
**	int		hst_size;			--> 0			the history size
**	char	quote_type;			--> '\0'		check if in quotation
** }		t_read_history_file;
**
** Algorithm for reading history file:
**	1. getting everyline from the history file, which is without '\n'
**	2. copy the line into the buff_read and copy a line break there too, so we
**		dont have to make condition checking
**		to add line break since, at the end of every line is a line break
**	3. check if return value of function check_continue_read_line
**		if instance.cont == 1 --> continue read and add into the buff_read
**		else instance.cont == 0 --> add into the history container
**				To add into the history container:
**				a, reset buff_write
**				b, using strncpy to copy the buff_read to buff_write with
**					n = instance.pos + 1
**				c, add into the history container
**				d, cut the rest of the buff_read, start with instance.pos + 1
**				e, now we start copy into buff_read again and now instance.pos
**					reset to 0
**
**	4. free the instance.line to keep reading new line
** ----------------------------------------------------------------
** Algorithm for is_continuing_read_line function:
**	2 cases:
**		case 1: in the quotation
**			3 cases:
**				a, it hit the '\0' return 1 to keep adding line
**				b, it hit the ^D   return 0 and reset quote_type to add into
**									history
**				c, it hit the quote type: reset quote type and keep reading
**		case 2: not in the quotation --> read_line_not_inside_quotation()
**
** Algorithm for read_line_not_inside_quotation()
** we keep reading the buff_read from the pos since we cant keep reading from
** 0, it has to be where we left off, since at every loop of get_next_line we
** already add a line_break
**
**	if (buff_read[*pos] == 4)
**		check_continue_read_line return 1
**	if (buff_read[pos] == '\n')
**		if is_continue == 1
**			check_continue_read_line return 1
**		else
**			check_continue_read_line return 0
**	if jump_quote == EXIT_FAILURE
**		check_continue_read_line return 1
**		remember to save and reset quote_type
**	if logical operator and pipe
**		is_continue = 1;
**	else
**		is_continue = 0;
*/

static void	add_command_into_history(t_read_history_file *self)
{
	ft_bzero(self->buff_write, 4096);
	ft_strncpy(self->buff_write, self->buff_read, self->pos + 1);
	g_shell.history->hist[self->hst_size++] = ft_strdup(self->buff_write);
	g_shell.history->curr = self->hst_size;
	ft_strcpy(self->buff_read, &(self->buff_read)[self->pos + 1]);
	self->pos = 0;
}

static int	read_line_not_inside_quotation(
	char *buff_read, int *pos, int is_continue, char in_quotation[1])
{
	while (buff_read[(*pos)])
	{
		if (buff_read[*pos] == 4)
			return (0);
		else if (buff_read[*pos] == '\n')
			return (is_continue) ? 1 : 0;
		else if (is_inhibitors(buff_read, *pos, buff_read[*pos]))
		{
			in_quotation[0] = buff_read[*pos];
			if (jump_quote2(buff_read, pos, buff_read[*pos]) == EXIT_FAILURE)
				return (1);
			is_continue = 0;
			in_quotation[0] = '\0';
		}
		else if (is_logical_operators_or_pipe_operator(&buff_read[*pos], pos))
			is_continue = 1;
		else if (!ft_isspace(buff_read[*pos]) && is_continue)
			is_continue = 0;
		(*pos)++;
	}
	return (is_continue);
}

static int	is_continuing_read_line(
	char *buff_read, int *pos, int is_continue, char in_quotation[1])
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
		is_continue = 0;
		in_quotation[0] = '\0';
		(*pos)++;
	}
	return (read_line_not_inside_quotation(
		buff_read, pos, is_continue, in_quotation));
}

static void	read_line_from_history_file(t_read_history_file *self)
{
	ft_strcat(self->buff_read, self->line_read);
	ft_strcat(self->buff_read, "\n");
	if ((self->cont = is_continuing_read_line(
		self->buff_read, &(self->pos), self->cont, &(self->quote_type))) == 0)
	{
		add_command_into_history(self);
		if (self->buff_write[ft_strlen(self->buff_write) - 1] == 4)
		{
			if ((self->cont = is_continuing_read_line(
					self->buff_read, &(self->pos),
					self->cont, &(self->quote_type))) == 0)
				add_command_into_history(self);
			else if (self->buff_read[self->pos] != '\0')
				(self->pos)++;
		}
	}
	else if (self->buff_read[self->pos] != '\0')
		(self->pos)++;
	ft_strdel(&(self->line_read));
}

int			read_history_file(int fd)
{
	t_read_history_file instance;

	init_read_history_struct(&instance);
	while (get_next_line(fd, &(instance.line_read)) &&
			instance.hst_size < (HISTFILESIZE - 1))
	{
		read_line_from_history_file(&instance);
	}
	(instance.line_read) ? free(instance.line_read) : 0;
	return (instance.hst_size);
}
