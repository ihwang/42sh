/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:07:00 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 21:08:09 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "struct.h"

int						quote_removal(t_process *p);
int						handle_expansion(t_process *p);

/*
** ========================= parameter expansion ==============================
*/

int						parameter_expansion_in_redi(t_process *p);
int						parameter_expansion_in_av(t_process *p);
int						parameter_expansion_in_assignment(t_process *p);

/*
** parameter expansion struct
*/

t_parameter_expansion	*constructor_parameter_expansion_struct(
	char *str);
void					destructor_parameter_expansion_struct(
	t_parameter_expansion *self);
void					parameter_expansion_struct_split(
	t_parameter_expansion *self);
int						parameter_expansion_syntax_analysis(
	t_parameter_expansion *self);
int						parameter_expansion_struct_replacement(
	char replacement[256], t_parameter_expansion *self);

/*
** parameter expansion tools
*/
int						parameter_expansion_for_word(char word[256]);

char					*parameter_expansion_tool_replace(
						char *target, char *needle, char *replacement);
int						jump_expansion(
						char *str, int *i, char expansion_type, char temp[2]);
int						is_parameter_expansion(char *str);
void					substitute_parameter(
						char parameter[256], char replacement[256]);
void					substitute_word(
						char word[256], char replacement[256]);
void					assign_word(
	char parameter[256], char word[256]);
int						parameter_expansion_for_word(char word[256]);
int						is_replacement_has_quotation(char replacement[256]);
void					add_back_slash_in_front(char replacement[256]);

/*
** parameter expansion complex
*/

int						parameter_expansion_colon_minus_case(
	t_parameter_expansion *self, t_parameter_expansion_type type);
int						parameter_expansion_colon_equal_case(
	t_parameter_expansion *self, t_parameter_expansion_type type);
int						parameter_expansion_colon_question_case(
	t_parameter_expansion *self, t_parameter_expansion_type type);
int						parameter_expansion_colon_plus_case(
	t_parameter_expansion *self, t_parameter_expansion_type type);
int						parameter_expansion_percent_case(
	t_parameter_expansion *self, t_parameter_expansion_type type);
int						parameter_expansion_h(
	t_parameter_expansion *self, t_parameter_expansion_type type);
void					remove_smallest_or_largest_suffix_pattern(
	t_parameter_expansion *self);
void					remove_smallest_or_largest_prefix_pattern(
	t_parameter_expansion *self);
int						remove_largest_prefix_pattern(
	char replacement[256], char word[256]);
int						remove_smallest_prefix_pattern(
	char replacement[256], char word[256]);

/*
** tilde expansion
*/

int						tilde_expansion(t_process *p);
char					*get_login_value(char *t_prefix);
int						tilde_prefix_len(char *word);

#endif
