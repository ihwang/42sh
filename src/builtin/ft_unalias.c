/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		find_alias(char *alias)
{
	int		i;
	char	*alias_name;

	i = 0;
	while (g_alias[i] != NULL)
	{
		if (ft_strcmp(g_alias[i]->name, (alias_name = set_name(alias))) == 0)
		{
			free(alias_name);
			return (0);
		}
		free(alias_name);
		i++;
	}
	ft_printf("42sh: unalias: %s: not found\n", alias);
	return (1);
}

int		count_arr(t_alias **g_alias)
{
	int i;

	i = 0;
	while (g_alias[i] != NULL)
		i++;
	return (i);
}

int		remove_alias(char *alias, t_alias ***aliaslist, int count)
{
	t_alias	**new;
	char	*a_name;
	int		j;
	int		i;

	j = 0;
	i = 0;
	if (!(new = (t_alias**)malloc(count * sizeof(t_alias*) + 1)))
		return (-1);
	while (j < count)
	{
		if (ft_strcmp((*aliaslist)[i]->name, (a_name = set_name(alias))) == 0)
			i++;
		free(a_name);
		if (!(new[j] = (t_alias*)malloc(sizeof(t_alias))))
			return (-1);
		new[j]->name = ft_strdup((*aliaslist)[i]->name);
		new[j]->value = ft_strdup((*aliaslist)[i]->value);
		j++;
		i++;
	}
	new[j] = NULL;
	free((*aliaslist));
	(*aliaslist) = new;
	return (0);
}

void	remove_all(t_alias ***aliaslist)
{
	int i;

	i = 0;
	while ((*aliaslist)[i] != NULL)
	{
		free((*aliaslist)[i]->name);
		free((*aliaslist)[i]->value);
		free((*aliaslist)[i]);
		i++;
	}
	free((*aliaslist));
	(*aliaslist) = (t_alias**)malloc(sizeof(t_alias*) + 1);
	(*aliaslist)[0] = NULL;
}

int		ft_unalias(t_process *c)
{
	int i;
	int status;
	int count;

	i = 1;
	status = 0;
	count = 0;
	if (c->ac == 1)
		ft_printf("unalias: usage: unalias [-a] name [name...]\n");
	else
	{
		while (c->av[i] != NULL)
		{
			if (ft_strcmp(c->av[i], "-a") == 0)
				remove_all(&g_alias);
			else if (find_alias(c->av[i]) == 0)
			{
				count = count_arr(g_alias) - 1;
				status = remove_alias(c->av[i], &g_alias, count);
			}
			i++;
		}
	}
	return (status);
}