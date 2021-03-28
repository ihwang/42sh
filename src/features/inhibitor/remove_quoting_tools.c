/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quoting_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:37:30 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 21:06:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 3 types of quoting
** backslah
** single quote
** double quote
**
** algorithm for removing quote
** if it is backslash
** if it is dquote and quote
*/

char	*remove_quoting(char *str, int *i)
{
	char	quote;
	char	buffer[4096];
	int		j;

	ft_bzero(buffer, 4096);
	quote = str[*i];
	j = 0;
	while (str[++*i])
	{
		if (str[*i] == quote)
		{
			if (quote == '"' && is_real_character(str, *i))
				break ;
			else if (quote == '\'')
				break ;
		}
		if (str[*i] == '\\' && quote == '"')
			(*i)++;
		if (str[*i])
			buffer[j++] = str[*i];
	}
	return (ft_strdup(buffer));
}

char	*remove_quote(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = -1;
	new = ft_strnew(0);
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"') && is_real_character(str, i))
		{
			new = ft_strjoin_and_free_2strings(new, remove_quoting(str, &i));
			continue;
		}
		else if (str[i] == '\\')
			i++;
		new = ft_strbuilder_char(new, str[i]);
	}
	free(str);
	return (new);
}

char	*remove_quote2(char str[256])
{
	int i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '"' || str[i] == '\\') &&
			is_real_character(str, i))
			ft_strcpy(&str[i], &str[i + 1]);
	}
	return (str);
}
