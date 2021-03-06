/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:14:39 by dthan             #+#    #+#             */
/*   Updated: 2021/01/27 12:47:44 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_var	**set_var(char **envp)
{
	t_var	**table;
	int		len;
	int		i;

	len = ft_arraylen(envp) + 1;
	i = -1;
	table = (t_var**)ft_memalloc(sizeof(t_var*) * len);
	while (envp[++i])
	{
		table[i] = (t_var*)ft_memalloc(sizeof(t_var));
		table[i]->name =
			ft_strndup(envp[i], ft_strchr(envp[i], '=') - &envp[i][0]);
		table[i]->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		table[i]->exported = 1;
	}
	table[i] = NULL;
	return (table);
}

t_var	*ft_getvar(char *name)
{
	int i;

	if (name == NULL)
		return (NULL);
	i = -1;
	while (g_shell.intern_var[++i])
		if (ft_strequ(name, g_shell.intern_var[i]->name))
			return (g_shell.intern_var[i]);
	return (NULL);
}

void	update_intern_var(t_var *intern_var)
{
	int i;

	i = -1;
	while (g_shell.intern_var[++i])
	{
		if (ft_strequ(intern_var->name, g_shell.intern_var[i]->name))
		{
			if (intern_var->value == NULL &&
				g_shell.intern_var[i]->value != NULL)
				intern_var->value = ft_strdup(g_shell.intern_var[i]->value);
			clear_intern_var(g_shell.intern_var[i]);
			g_shell.intern_var[i] = intern_var;
			if (is_eligible_to_export_to_env(*intern_var))
				add_update_environment_var(intern_var->name, intern_var->value);
			break ;
		}
	}
}

void	add_intern_var(t_var *new_var)
{
	t_var	**new_table;
	int		size;
	int		i;

	size = count_intern_var_table(g_shell.intern_var) + 2;
	new_table = (t_var**)ft_memalloc(sizeof(t_var*) * size);
	i = -1;
	while (g_shell.intern_var[++i])
		new_table[i] = g_shell.intern_var[i];
	new_table[i++] = new_var;
	new_table[i] = NULL;
	free(g_shell.intern_var);
	g_shell.intern_var = new_table;
	if (is_eligible_to_export_to_env(*new_var))
		add_update_environment_var(new_var->name, new_var->value);
}

void	delete_intern_var(char *name)
{
	t_var	**new_table;
	int		i;
	int		j;

	if (name == NULL || count_intern_var_table(g_shell.intern_var) == 0)
		return ;
	new_table = (t_var**)ft_memalloc(sizeof(t_var*) *
		count_intern_var_table(g_shell.intern_var));
	i = -1;
	j = 0;
	while (g_shell.intern_var[++i])
	{
		if (ft_strequ(g_shell.intern_var[i]->name, name))
		{
			clear_intern_var(g_shell.intern_var[i]);
			continue;
		}
		new_table[j++] = g_shell.intern_var[i];
	}
	new_table[j] = NULL;
	free(g_shell.intern_var);
	g_shell.intern_var = new_table;
	if (ft_getenv(name))
		delete_environment_var(name);
}
