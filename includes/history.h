/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 04:00:14 by dthan             #+#    #+#             */
/*   Updated: 2021/03/29 21:12:03 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include "struct.h"

/*
** Constants:
**		HISTFILESIZE
**		HISTSIZE
** Un-declared constants:
**		HISTIGNORE
**		HISTTIMEFORMAT
**		HISTCMD
**		HISTCONTROL
*/

# define HISTFILESIZE 50
# define HISTSIZE 10

/*
** ================================ METHODS ====================================
*/

/*
** History
*/

void	delete_save_history(void);
void	append_history(void);
int		get_history(int fd);
char	*ft_process_history(t_l *l);
int		ft_check_cont(char *buffer);

/*
** Read history file
*/

int		read_commands_from_a_file(int fd, char **container);
void	init_read_history_struct(t_read_history_file *self);
int		is_logical_operators_or_pipe_operator(char *str, int *i);
int		jump_quote3(char *input, int *i, char quote_type);
int		jump_quote2(char *input, int *i, char quote_type);
int		is_line_containing_tab(char *str);
void	replace_line_containing_tab_with_space(char *str);

/*
** History expansion
*/

int		ft_hist_exp(char **line, t_prompt pr);
int		ft_str_search(char *str);
void	ft_hist_exp_quote(char c, int *q, t_prompt pr);

/*
** Reverse history search
*/

int		ft_reverse_search(t_l *l);
void	ft_reverse_search_add(char t[], t_l *l);
void	ft_reverse_search_bs(t_l *l);
int		ft_reverse_search_reset(t_l *l);
void	ft_reverse_search_clear(t_l *l);
void	ft_rs_print(void);
char	*ft_getenv(const char *name);
void	ft_swap_int(int *a, int *b);

#endif
