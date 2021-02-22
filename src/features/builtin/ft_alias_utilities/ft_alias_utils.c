/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/12/26 11:44:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_valid_alias_char(int c)
{
	if (c == '/' || c == '$' || c == '`' || c == '=' || c == '"' || c == '\'' || c == '\\' || is_metacharacter(c) == 1)
	{
		ft_printf("42sh: alias: %c: invalid alias name\n", c);
		return (0);
	}
	return (1);
}

int		is_valid_alias_name(char *name, char *alias)
{
	int i;

	i = 0;
	if ((ft_strcmp(name, "\0") == 0) || name == NULL)
	{
		ft_printf("42sh: alias: %s: not found\n", alias);
		return (-1);
	}
	while (name[i] != '\0')
	{
		if (is_valid_alias_char(name[i]) != 1)
			return (-1);
		i++;
	}
	return (0);
}

char	*set_value(char *argv)
{
	int		i;
	char	*value;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	value = ft_strsub(argv, i + 1, ft_strlen(argv) - (i + 1));
	return (value);
}

char	*set_name(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	while (argv[i] != '\0' && argv[i] != '=')
		i++;
	name = ft_strsub(argv, 0, i);
	return (name);
}

void	sort_alias_list(t_alias **aliaslist)
{
	int		i;
	int		j;
	t_alias	*tmp;

	i = 0;
	while (aliaslist[i] != NULL)
	{
		j = i;
		while (aliaslist[j + 1] != NULL)
		{
			if (ft_strcmp(aliaslist[i]->name, aliaslist[j + 1]->name) > 0)
			{
				tmp = aliaslist[i];
				aliaslist[i] = aliaslist[j + 1];
				aliaslist[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
