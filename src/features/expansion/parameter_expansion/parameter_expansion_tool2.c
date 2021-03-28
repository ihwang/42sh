/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_tool2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:55:59 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 21:08:35 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	substitute_parameter(char parameter[256], char replacement[256])
{
	char *temp;

	temp = NULL;
	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		if (temp)
			free(temp);
		return ;
	}
	temp = ft_getvar(parameter)->value;
	ft_strcpy(replacement, temp);
}

void	substitute_word(char word[256], char replacement[256])
{
	ft_strcpy(replacement, word);
}

void	assign_word(char parameter[256], char word[256])
{
	t_var	*intern_var;
	t_var	*ptr;

	intern_var = (t_var*)ft_memalloc(sizeof(t_var));
	intern_var->name = ft_strdup(parameter);
	intern_var->value = ft_strdup(word);
	if (ft_getenv(intern_var->name))
		intern_var->exported = 1;
	else if ((ptr = ft_getvar(intern_var->name)) != NULL && ptr->exported == 1)
		intern_var->exported = 1;
	else
		intern_var->exported = 0;
	if (is_intern_var(intern_var->name))
		update_intern_var(intern_var);
	else
		add_intern_var(intern_var);
}

int		is_replacement_has_quotation(char replacement[256])
{
	int i;

	i = -1;
	while (replacement[++i])
		if (replacement[i] == '"' || replacement[i] == '\\')
			return (1);
	return (0);
}

void	add_back_slash_in_front(char replacement[256])
{
	int		i;
	char	temp[256];

	i = -1;
	while (replacement[++i])
	{
		if (replacement[i] == '"' || replacement[i] == '\\')
		{
			ft_strcpy(temp, &replacement[i]);
			replacement[i] = '\\';
			replacement[i + 1] = '\0';
			ft_strcat(replacement, temp);
			i++;
		}
	}
}
