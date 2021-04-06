/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2021/04/06 23:33:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

/*
** External Lib
*/

# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>
# include <pwd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/ioctl.h>

/*
** Internal Lib
*/

# include "libft.h"
# include "ft_printf.h"

/*
** Project's header files
*/

# include "struct.h"
# include "arx.h"
# include "ast.h"
# include "token.h"
# include "utilities.h"
# include "line_edition.h"
# include "execution.h"
# include "builtin.h"
# include "constant.h"
# include "expansion.h"
# include "history.h"
# include "auto_completion.h"
# include "handle_signal.h"
# include "inhibitor.h"
# include "intern_and_environment_var.h"
# include "hash_table.h"

/*
** G_shell variable
*/

typedef struct		s_shell
{
	char			**env;
	t_var			**intern_var;
	char			signal_indicator;
	char			shell_terminal;
	char			interactive_shell;
	pid_t			shell_pgid;
	struct termios	shell_tmode;
	t_job			*first_job;
	t_heredoc		*first_heredoc;
	t_heredoc		*heredoc_lst;
	t_history		*history;
	t_alias			**alias;
	unsigned int	exit_status;
	t_hash			*hashtable[MAX_HASH];
	t_builtin		*builtins;
	int				pipe_indicator;
	char			*signal_msgs[SIGNAL_NUMBER_OSX];
}					t_shell;
t_shell				g_shell;

/*
** Init stuff
*/

int					init_terminal_stuff(void);
int					init_environment_variable_stuff(char **envp);
int					init_job_control_stuff(void);
int					init_history_stuff(void);
int					init_signal_and_other_stuff(void);

/*
** Tokenizing service
*/

t_token				*tokenizing_service(void);
void				tokenizing_service_helper(t_tokennizing_service *self);
void				init_tokenizing_service_struct(
	t_tokennizing_service *self);

/*
** Get user input
*/

char				*get_command(t_lex_value lex_value);
void				analyzing_phase(
	char *str, t_phase phase[], int *stack_pos);

/*
** Prompt stuff
*/

void				print_info(void);
void				print_prompt(t_prompt prompt_type);
int					prompt_len(t_prompt prompt_type);
t_prompt			choose_prompt_type(t_lex_value lex, t_phase phase);

/*
**	Lexer
*/

t_token				*lexical_analysis_service(
	char *input, char *fix_alias_name, int sub);

/*
**	Parser
*/

int					syntax_analysis_service(t_token *token_stream);
int					analyzing_pair_tokens(t_token *tk, t_token *prev_tk);
int					is_near_unexpected_token(
	t_token *cur_tk, t_token *prev_tk);

/*
** Semantic
*/

t_astnode			*semantic_analysis(t_token *token);

/*
** Executor
*/

void				executor(t_astnode *ast);

#endif
