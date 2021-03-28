/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 17:12:19 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 21:35:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*delete_back_slash_and_line_feed(char *cmd)
{
	char *new;

	new = ft_strndup(cmd, ft_strlen(cmd) - 2);
	free(cmd);
	return (new);
}

int		jump_quote(char *input, int *i, char quote_type)
{
	if (quote_type == '\\')
		(*i)++;
	else if (quote_type == '"' || quote_type == '\'')
	{
		(*i)++;
		while (input[*i])
		{
			if (input[*i] == quote_type)
			{
				if (quote_type == '"' && is_real_character(input, *i))
					break ;
				else if (quote_type == '\'')
					break ;
			}
			(*i)++;
		}
	}
	if (input[*i] == '\0')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		is_quoted(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\\' || str[i] == '\'' || str[i] == '"')
			return (1);
	return (0);
}
