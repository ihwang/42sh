/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameter_expansion_struct_replacement.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:34:44 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 13:47:12 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	int i;
	char temp[256];

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

int							simple_parameter_expansion(
	char replacement[256], char parameter[256])
{
	char	*temp;
	t_var	*var;

	if (ft_strequ("?", parameter))
	{
		temp = ft_itoa(g_shell.exit_status);
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (parameter[0] == '#')
	{
		temp = (ft_getvar(&parameter[1])) ?
		ft_itoa(ft_strlen(ft_getvar(&parameter[1])->value)) : ft_strdup("0");
		ft_strcpy(replacement, temp);
		free(temp);
	}
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
		{
			ft_strcpy(replacement, var->value);
			if (is_replacement_has_quotation(replacement))
				add_back_slash_in_front(replacement);
		}
	}
	return (EXIT_SUCCESS);
}

t_parameter_expansion_type	find_parameter_replacement_type(
	char parameter[256])
{
	t_var *var;

	var = NULL;
	if (ft_strequ("?", parameter))
		return (PE_SET_AND_NOT_NULL);
	else if (is_intern_var(parameter))
	{
		var = ft_getvar(parameter);
		if (var->value)
			return (PE_SET_AND_NOT_NULL);
		return (PE_SET_BUT_NULL);
	}
	return (PE_UNSET);
}

int							complex_parameter_expansion(
	t_parameter_expansion *self)
{
	t_parameter_expansion_type type;

	type = find_parameter_replacement_type(self->parameter);
	if (ft_strequ(self->delimeter, ":-"))
		return (parameter_expansion_colon_minus_case(self, type));
	else if (ft_strequ(self->delimeter, ":="))
		return (parameter_expansion_colon_equal_case(self, type));
	else if (ft_strequ(self->delimeter, ":?"))
		return (parameter_expansion_colon_question_case(self, type));
	else if (ft_strequ(self->delimeter, ":+"))
		return (parameter_expansion_colon_plus_case(self, type));
	else if (ft_strequ(self->delimeter, "%") ||
			ft_strequ(self->delimeter, "%%"))
		return (parameter_expansion_percent_case(self, type));
	else if (ft_strequ(self->delimeter, "#") ||
			ft_strequ(self->delimeter, "##"))
		return (parameter_expansion_h(self, type));
	return (EXIT_SUCCESS);
}

int							parameter_expansion_struct_replacement(
	char replacement[256], t_parameter_expansion *self)
{
	if (ft_strlen(self->delimeter) == 0)
		return (simple_parameter_expansion(replacement, self->parameter));
	return (complex_parameter_expansion(self));
}
