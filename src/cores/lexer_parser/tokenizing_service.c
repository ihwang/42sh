/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_service.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 13:47:57 by dthan             #+#    #+#             */
/*   Updated: 2021/04/06 20:18:25 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_lex_value	lex_value(t_token *tk, t_lex_value prev_lex_value)
{
	if (tk == NULL)
		return (prev_lex_value == LEX_CMD) ? LEX_SUCCESS : prev_lex_value;
	if (tk->type == TOKEN_AND_IF)
		return (LEX_CMDAND);
	else if (tk->type == TOKEN_OR_IF)
		return (LEX_CMDOR);
	else if (tk->type == TOKEN_PIPE)
		return (LEX_PIPE);
	return (LEX_SUCCESS);
}

static t_lex_value	lexical_and_syntax_analysis(
	t_lex_value prev_lex_value, char *input, t_token **tk_lst)
{
	t_token *token_stream;

	token_stream = lexical_analysis_service(input, NULL, 0, NULL);
	if (syntax_analysis_service(token_stream) == EXIT_FAILURE)
	{
		clear_token(token_stream);
		(*tk_lst) ? clear_token(*tk_lst) : 0;
		*tk_lst = NULL;
		return (LEX_FAILURE);
	}
	add_token_into_token_list(tk_lst, token_stream);
	return (lex_value(find_prev_token_in_new_stream(token_stream),
		prev_lex_value));
}

void				init_tokenizing_service_struct(t_tokennizing_service *self)
{
	self->whole_cmd = NULL;
	self->single_cmd = NULL;
	self->token_stream = NULL;
	self->lex_value = LEX_CMD;
}

void				tokenizing_service_helper(t_tokennizing_service *self)
{
	self->lex_value = lexical_and_syntax_analysis(self->lex_value,
		self->single_cmd, &(self->token_stream));
	self->whole_cmd = ft_strjoin_and_free_2strings(
		self->whole_cmd, self->single_cmd);
}

t_token				*tokenizing_service(void)
{
	t_tokennizing_service instance;

	init_tokenizing_service_struct(&instance);
	while (instance.lex_value != LEX_SUCCESS &&
		instance.lex_value != LEX_FAILURE)
	{
		if ((instance.single_cmd = get_command(instance.lex_value)) == NULL)
		{
			(instance.token_stream) ? clear_token(instance.token_stream) : 0;
			instance.token_stream = NULL;
			break ;
		}
		tokenizing_service_helper(&instance);
	}
	if (instance.whole_cmd)
		g_shell.history->tmp = instance.whole_cmd;
	return (instance.token_stream);
}
