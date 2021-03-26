/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_history_file_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 23:51:53 by dthan             #+#    #+#             */
/*   Updated: 2021/03/26 23:57:27 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

int		is_logical_operators_or_pipe_operator(char *str, int *i)
{
	if (ft_strnequ(str, "&&", 2) || ft_strnequ(str, "||", 2))
	{
		(*i)++;
		return (1);
	}
	else if (ft_strnequ(str, "|", 1))
	{
		return (1);
	}
	return (0);
}

void	init_read_history_struct(t_read_history_file *self)
{
	self->line_read = NULL;
	ft_bzero(self->buff_read, 4096);
	ft_bzero(self->buff_write, 4096);
	self->pos = 0;
	self->cont = 1;
	self->hst_size = 0;
	self->quote_type = '\0';
}
