/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:42:55 by tango             #+#    #+#             */
/*   Updated: 2020/09/28 03:00:19 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode		*io_file1(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if ((childnode = filename(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_file);
	node->data = ft_strdup("<");
	node->left = childnode;
	return (node);
}

t_astnode		*io_file2(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if (*token == NULL)
		return (NULL);
	if ((childnode = filename(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_file);
	node->data = ft_strdup("<&");
	node->left = childnode;
	return (node);
}

t_astnode		*io_file3(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if ((childnode = filename(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_file);
	node->data = ft_strdup(">");
	node->left = childnode;
	return (node);
}

t_astnode		*io_file4(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if ((childnode = filename(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_file);
	node->data = ft_strdup(">&");
	node->left = childnode;
	return (node);
}

t_astnode		*io_file5(t_token **token)
{
	t_astnode	*node;
	t_astnode	*childnode;

	*token = (*token)->next;
	if ((childnode = filename(token)) == NULL)
		return (NULL);
	node = build_node(AST_io_file);
	node->data = ft_strdup(">>");
	node->left = childnode;
	return (node);
}
