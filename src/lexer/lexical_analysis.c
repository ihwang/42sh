/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2020/09/08 12:43:45 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	void	word_jump(char *input, int *tail, t_token **lst_tokens)
{
	int			head;
	t_token		*node;
	char		quote;

	quote = 0;
	head = *tail;
	while (input[*tail] && !ft_isspace(input[*tail]) && \
			!is_separator_operator(input, *tail) && \
			!is_redirection_operator(input, *tail) && \
			!is_pipe_operator(input, *tail))
	{
		if (input[*tail] == '"')
			quote = jump_single_or_double_quote(input, tail, '"');
		else if (input[*tail] == '\'')
			quote = jump_single_or_double_quote(input, tail, '\'');
		(*tail)++;
	}
	node = get_token(ft_strndup(&input[head], *tail - head), quote);
	if (check_intern_var_syntax(node, *lst_tokens))
		node = breakdown_node_for_intern_var(node);
	push_node_into_ltoken(input, head, node, lst_tokens);
}

static	void	separator_operator_jump(char *input, \
		int *tail, t_token **lst_tokens)
{
	int			head;
	t_token		*node;

	head = *tail;
	while (input[*tail] && is_separator_operator(input, *tail))
		(*tail)++;
	node = get_token(ft_strndup(&input[head], *tail - head), 0);
	push_node_into_ltoken(input, head, node, lst_tokens);
}

static	void	redirection_operator_jump(char *input,\
		int *tail, t_token **lst_tokens)
{
	int			head;
	t_token		*node;

	head = *tail;
	while (input[*tail] && is_redirection_operator(input, *tail))
		(*tail)++;
	node = get_token(ft_strndup(&input[head], *tail - head), 0);
	push_node_into_ltoken(input, head, node, lst_tokens);
}

static	void	pipe_operator_jump(char *input, int *tail, t_token **lst_tokens)
{
	int			head;
	t_token		*node;

	head = *tail;
	while (input[*tail] && is_pipe_operator(input, *tail))
		(*tail)++;
	node = get_token(ft_strndup(&input[head], *tail - head), 0);
	push_node_into_ltoken(input, head, node, lst_tokens);
}

/*
** print_token(lst_tokens);
** debugging purpose in lexical_analysis
*/

void print_token(t_token *token)
{
	while (token)
	{
		ft_putchar('[');
		ft_putstr(token->data);
		ft_putstr("]->");
		token = token->next;
	}
	ft_putstr("NULL\n");
}

t_token			*lexical_analysis(char *input)
{
	t_token		*lst_tokens;
	int			i;

	i = 0;
	lst_tokens = NULL;
	while (input[i])
	{
		if (is_separator_operator(input, i))
			separator_operator_jump(input, &i, &lst_tokens);
		else if (is_redirection_operator(input, i))
			redirection_operator_jump(input, &i, &lst_tokens);
		else if (is_pipe_operator(input, i))
			pipe_operator_jump(input, &i, &lst_tokens);
		else if (!ft_isspace(input[i]))
			word_jump(input, &i, &lst_tokens);
		else
			i++;
	}
	print_token(lst_tokens);
	if (check_syntax(lst_tokens) == EXIT_FAILURE)
		deltoken(&lst_tokens);
	return (lst_tokens);
}
