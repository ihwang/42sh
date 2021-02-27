/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 05:54:54 by tango             #+#    #+#             */
/*   Updated: 2021/02/04 23:40:10 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/signal.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <term.h>
# include <termios.h>

//#define _POSIX_SOURCE
# include <stdio.h> // for perror, need to be delete when replacing the error management

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

# define F_TYPE_MASK 0170000
# define KEY 1
# define VAL 0
# define TRUE 1
# define FALSE 0

typedef struct			s_shell
{
	char				**env;
	t_var				**intern_var;
	char				signal_indicator;
	char				shell_terminal;
	char				interactive_shell;
    pid_t               shell_pgid;
    struct termios      shell_tmode;
	t_job				*first_job;
	t_heredoc			*first_heredoc;
	t_heredoc			*heredoc_lst;
	t_history			*history;
	t_alias				**alias;
	unsigned int		exit_status;
	t_hash				*hashtable[MAX_HASH];
	t_builtin			*builtins;
}                       t_shell;

t_shell     g_shell;


/*
**	Lexer
*/

t_lex_value lexical_analysis_and_syntax_analysis(char *cmd, t_token **tk_lst, t_lex_value lex_value, int on_substition);
int get_user_token(t_token **tk_lst);
char *get_command(t_lex_value lex_value);

void print_prompt(t_prompt prompt_type);
int prompt_len(t_prompt prompt_type);

/*
**	Parser
*/

int			syntax_analysis(t_token *curr, t_token *prev);

/*
** Semantic
*/

t_astnode				*semantic_analysis(t_token *token);

/*
** Prompt
*/

size_t					get_prompt(void);

/*
** Executor
*/

void					executor(t_astnode *ast);


// new
void	print_info(void);
t_prompt choose_prompt_type(t_lex_value lex, t_phase phase);
#endif
