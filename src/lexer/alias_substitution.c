/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrankul <vgrankul@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 23:35:55 by vgrankul          #+#    #+#             */
/*   Updated: 2020/10/05 04:14:12 by vgrankul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_tokens_with_alias(t_token *current_token,
t_token **prev_token, t_token **token_lst, char *alias_substr)
{
	t_token *lst;

	lst = NULL;
	free(g_last_alias);
	g_last_alias = ft_strdup(current_token->data);
	clear_token(current_token);
	if (ft_strlen(alias_substr) != 0)
	{
		lst = lexer_and_parser(alias_substr);
		while (lst != NULL)
		{
			add_token_into_token_list(token_lst, lst);
			if (!parser(lst, *(prev_token)))
				clear_token(lst);
			*prev_token = lst;
			lst = lst->next;
		}
		print_token(*token_lst);
	}
}

char	*is_alias(char *str)
{
	int i;

	i = 0;
	while (g_alias[i] != NULL)
	{
		if (ft_strcmp(g_alias[i]->name, str) == 0)
			return (g_alias[i]->value);
		i++;
	}
	return (NULL);
}

int		alias_substitution(t_token *current_token,
t_token **prev_token, t_token **token_lst)
{
	char	*alias_substr;

	alias_substr = NULL;
	if (g_last_alias != NULL &&
	ft_strcmp(g_last_alias, current_token->data) == 0)
		return (0);
	if ((*prev_token) == NULL || ((*prev_token) != NULL &&
	is_control_op_not_newline((*prev_token)->type) == 1))
	{
		if (g_last_alias != NULL)
			free(g_last_alias);
		g_last_alias = NULL;
		if ((alias_substr = is_alias(current_token->data)) != NULL)
		{
			update_tokens_with_alias(current_token,
			prev_token, token_lst, alias_substr);
			return (1);
		}
	}
	return (0);
}