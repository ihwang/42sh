/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 07:42:54 by vgrankul          #+#    #+#             */
/*   Updated: 2021/03/12 22:29:35 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		expand_tilde(char **word)
{
	int		i;
	char	*t_prefix;
	char	*value;
	char	*tmp;

	value = NULL;
	i = tilde_prefix_len((*word));
	if ((t_prefix = ft_strsub((*word), 0, i)) != NULL)
	{
		if ((value = get_value(t_prefix)) != NULL)
		{
			if ((tmp = ft_strjoin(value, &(*word)[i])) != NULL)
			{
				free(*word);
				(*word) = tmp;
			}
			free(value);
		}
		free(t_prefix);
	}
	return (EXIT_SUCCESS);
}

void	expand_assignment_variables(char **final, char ***variables, char *name)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	while ((*variables)[i] != NULL)
	{
		if ((*variables)[i][0] == '~')
			expand_tilde(&(*variables)[i]);
		if (i == 0)
			(*final) = ft_strjoin(name, (*variables)[i]);
		else
		{
			tmp = ft_strjoin(":", (*variables)[i]);
			tmp2 = (*final);
			(*final) = ft_strjoin(tmp2, tmp);
			free(tmp);
			free(tmp2);
		}
		i++;
	}
}

int		expand_assignments(char **assignment)
{
	int		i;
	char	*name;
	char	*final;
	char	**variables;

	i = 0;
	final = NULL;
	while ((*assignment)[i] != '\0' && (*assignment)[i] != '=')
		i++;
	variables = ft_strsplit(&(*assignment)[i + 1], ':');
	if (variables[0] != NULL)
	{
		name = ft_strsub((*assignment), 0, i + 1);
		expand_assignment_variables(&final, &variables, name);
		free(name);
		free((*assignment));
		(*assignment) = final;
	}
	destroy_arr(variables);
	return (EXIT_SUCCESS);
}

int		expand_internal_variables(t_process *p)
{
	t_assignment	*assign_tmp;
	int				status;

	assign_tmp = p->first_assignment;
	status = 0;
	while (assign_tmp != NULL)
	{
		if (ft_strchr(assign_tmp->data, '=') != NULL)
			status = expand_assignments(&assign_tmp->data);
		assign_tmp = assign_tmp->next;
	}
	return (status);
}

int		tilde_expansion(t_process *p)
{
	int		i;
	int		status;
	t_redi	*tmp;

	i = 0;
	status = 0;
	tmp = p->first_redi;
	while (p->av[i] != NULL)
	{
		if (p->av[i][0] == '~')
			status = expand_tilde(&p->av[i]);
		if (ft_strchr(p->av[i], '=') != NULL)
			status = expand_assignments(&p->av[i]);
		i++;
	}
	while (tmp != NULL)
	{
		if (tmp->word != NULL && tmp->word[0] == '~')
			status = expand_tilde(&tmp->word);
		tmp = tmp->next;
	}
	status = expand_internal_variables(p);
	return (status);
}
