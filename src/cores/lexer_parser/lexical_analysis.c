/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 08:37:27 by dthan             #+#    #+#             */
/*   Updated: 2021/04/06 21:06:49 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	init_lexical_service_struct(
	t_lexical_service *self, t_token *prev_token)
{
	self->i = 0;
	self->stream = NULL;
	self->tk = NULL;
	self->prev_tk = (prev_token) ? prev_token : NULL;
	self->keep_alias_substitution = 0;
}

int		alias_requirement(t_lexical_service self, int sub)
{
	if (sub == 0 &&
		self.tk->type == TOKEN_WORD &&
		is_alias(self.tk->data, self.prev_tk))
		return (1);
	if (self.keep_alias_substitution &&
		sub == 0 &&
		self.tk->type == TOKEN_WORD &&
		find_alias2(self.tk->data) != NULL)
		return (1);
	return (0);
}

t_token	*alias_infinite_loop(t_lexical_service *self, char *fix_alias_name)
{
	free(self->tk->data);
	self->tk->data = ft_strdup(fix_alias_name);
	self->prev_tk = self->tk;
	return (self->tk);
}

t_token	*lexical_analysis_service(
	char *input, char *fix_alias_name, int sub, t_token *prev_token)
{
	t_lexical_service self;

	init_lexical_service_struct(&self, prev_token);
	while (input[self.i])
	{
		if ((self.tk = token_creator_service(
			input, &(self.i), self.prev_tk)) == NULL)
			continue ;
		if (alias_requirement(self, sub))
		{
			if (fix_alias_name && ft_strequ(fix_alias_name, self.tk->data))
				self.tk = alias_infinite_loop(&self, fix_alias_name);
			else
			{
				self.tk = alias_substitution(&self, (fix_alias_name == NULL) ?
				(self.tk)->data : fix_alias_name);
				if (self.tk == NULL)
					continue ;
			}
		}
		add_token_into_token_list(&(self.stream), self.tk);
		self.prev_tk = find_current_token_in_new_stream(self.tk);
	}
	return (self.stream);
}
