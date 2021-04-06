/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2021/04/06 21:06:06 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*find_alias_str(char *str)
{
	int i;

	i = 0;
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strequ(g_shell.alias[i]->name, str))
			return (g_shell.alias[i]->value);
		i++;
	}
	return (NULL);
}

int		is_alias(char *str, t_token *prev_token)
{
	int i;

	i = 0;
	if (prev_token && (!is_control_op_not_newline(prev_token->type)) &&
		prev_token->type != TOKEN_ASSIGNMENT_WORD)
		return (0);
	if (g_shell.alias != NULL)
	{
		while (g_shell.alias[i] != NULL)
		{
			if (ft_strequ(g_shell.alias[i]->name, str))
				return (1);
			i++;
		}
	}
	return (0);
}

t_alias	*find_alias2(char *str)
{
	int i;

	i = 0;
	while (g_shell.alias[i] != NULL)
	{
		if (ft_strequ(g_shell.alias[i]->name, str))
			return (g_shell.alias[i]);
		i++;
	}
	return (NULL);
}

int		determine_sub_value(char *data, char *alias_value)
{
	if (!ft_strnequ(data, alias_value, ft_strlen(data)))
		return (0);
	if (!ft_isspace(alias_value[ft_strlen(data)]))
		return (0);
	return (1);
}

t_token	*alias_substitution(t_lexical_service *lex, char *fix_alias_name)
{
	t_token *new_stream;
	t_alias *alias;

	new_stream = NULL;
	alias = find_alias2(lex->tk->data);
	new_stream = lexical_analysis_service(
		alias->value, fix_alias_name, determine_sub_value(
			lex->tk->data, alias->value), lex->prev_tk);
	clear_token(lex->tk);
	if (new_stream == NULL)
		return (NULL);
	if (alias->value[ft_strlen(alias->value) - 1] == ' ' ||
		alias->value[ft_strlen(alias->value) - 1] == '\t')
		lex->keep_alias_substitution = 1;
	else
		lex->keep_alias_substitution = 0;
	return (new_stream);
}
