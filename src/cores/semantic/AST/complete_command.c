/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 11:17:31 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 19:01:05 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** complete_command : list separator	1
**                	| list				2
*/

t_astnode	*complete_command2(t_token **token)
{
	return (list(token));
}

t_astnode	*complete_command1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*lnode;
	char		*operator;

	if ((lnode = list(token)) == NULL)
		return (NULL);
	if (!*token ||
		((*token)->type != TOKEN_APS && (*token)->type != TOKEN_SEMI))
		return (clear_ast(lnode));
	operator = (*token)->data;
	*token = (*token)->next;
	node = build_node(AST_complete_command);
	node->data = ft_strdup(operator);
	node->left = lnode;
	return (node);
}

t_astnode	*complete_command(t_token **token)
{
	t_astnode	*node;
	t_token		*reset;

	reset = *token;
	if ((node = complete_command1(token)) != NULL)
		return (node);
	*token = reset;
	if ((node = complete_command2(token)) != NULL)
		return (node);
	return (NULL);
}
