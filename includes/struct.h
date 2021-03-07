/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:18:23 by dthan             #+#    #+#             */
/*   Updated: 2021/03/07 03:32:52 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <sys/types.h>
# include <termios.h>
# include "libft.h"

# define BUFF_LINE_EDITION 8

/*
** ============================== CORE STRUCT =================================
*/

typedef enum
{
	TOKEN_APS, // &		control op
	TOKEN_SEMI, // ;	control op
	TOKEN_PIPE, // |	control	op
	TOKEN_OB, // (  // not support
	TOKEN_CB, // )   //not support
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD, //not support
	TOKEN_NAME, // not support
	TOKEN_NEWLINE, // not yet, it depends
	TOKEN_IO_NUMBER,
	TOKEN_AND_IF, // &&		control op
	TOKEN_OR_IF, // ||		control op
	TOKEN_DSEMI, // ;;  // not support
	TOKEN_GREAT, // >						reidrect op
	TOKEN_DGREAT, // >>						redirect op
	TOKEN_LESS, // <						redirect op
	TOKEN_DLESS, // <<						redirect op
	TOKEN_LESSAND, // <&					redirect op
	TOKEN_GREATAND, // >&					redirect op
	TOKEN_LESSGREAT, // <>  // not support
	TOKEN_DLESSDASH, // <<- // not support
	TOKEN_CLOBBER, // >|  // not support
	TOKEN_EOF, //eof only
	TOKEN_BROKEN, // a string with quote contain eof, and quote is not closed
}	t_token_type;

typedef struct			s_token
{
	char				*data;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum
{
	AST_complete_command = 1,
	AST_list,
	AST_and_or,
	AST_pipeline,
	AST_pipe_sequence,
	AST_command,
	AST_simple_command,
	AST_cmd_name,
	AST_cmd_prefix,
	AST_cmd_suffix,
	AST_io_redirect,
	AST_io_file,
	AST_io_here,
	AST_filename,
	AST_WORD,
	AST_ASSIGNMENT_WORD,
}	t_astnode_type;

typedef struct			s_astnode
{
	int					type;
	char				*data;
	struct s_astnode	*left;
	struct s_astnode	*right;
	struct s_astnode	*middle;
}						t_astnode;

/*
**============================= FEATURE STRUCT ================================
*/

/*
** Job, process, redi, heredoc struct
*/

typedef struct			s_heredoc
{
	char				*doc;
	struct s_heredoc	*next;
}						t_heredoc;

typedef	struct			s_redi
{
	char				*op;
	char				*n;
	char				*word;
	struct s_redi		*next;
}						t_redi;

typedef struct			s_assignment
{
	char				*data;
	struct s_assignment	*next;
}						t_assignment;

typedef struct			s_process
{
	int					ac;
	char				**av;
	pid_t				pid;
	int					stdin;
	int					stdout;
	int					stderr;
	t_redi				*first_redi;
	t_assignment		*first_assignment;
	char				completed;
	char				stopped;
	int					status;
	struct s_process	*next;
}						t_process;

typedef struct			s_job
{
	char				*command;
	pid_t				pgid;
	char				notified;
	struct termios		term;
	t_process			*first_process;
	int					stdin;
	int					stdout;
	int					stderr;
	int					foreground;
	char				forked;
	int					id;
	int					pipe_fd_closer[2];
	struct s_job		*next;
}						t_job;

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

/*
** Line Edit struct
*/

typedef enum
{
	CLIP_SAVE = 0,
	CLIP_TAKE,
	CLIP_DELT
}	t_clipping_options;

typedef enum
{
	PROMPT_CMD = 0,
	PROMPT_CMD_AND,
	PROMPT_CMD_OR,
	PROMPT_PIPE,
	PROMPT_HEREDOC,
	PROMPT_DQUOTE,
	PROMPT_QUOTE,
	PROMPT_BACKSLASH,
	PROMPT_CMDSUBST,
	PROMPT_BRACEPARAM
}	t_prompt;

typedef enum
{
	PHASE_CMD = 0,
	PHASE_DQUOTE,
	PHASE_QUOTE,
	PHASE_BACKSLASH,
	PHASE_CMDSUBST,
	PHASE_BRACEPARAM,
	PHASE_STOP,
	PHASE_HEREDOC // temp
}	t_phase;

typedef enum
{
	LEX_SUCCESS = 0,
	LEX_FAILURE,
	LEX_CMD,
	LEX_CMDAND,
	LEX_CMDOR,
	LEX_PIPE,
	LEX_HEREDOC,
}	t_lex_value;

/*
** Line edition struct:
** 	char 	*line		: the line
**	int		co			: number of column in a line
**	int		starting_row: total_row - current_row
**	int		total_row	: number of line on screen or page
**	int		nb			: number of char in the line
**	int		x			: x cursor position
**	int		y			: y cursor position
**	int		pmpt		: length of prompt
**	char	*rev_sr		:
**	int		rs			:
**	int		rs_i		:
**	char	phase		:
**	t_auto	auto_com	:
*/

typedef struct			s_l
{
	char				*line;
	int					nb;
	int					co;
	int					total_row;
	int					starting_row;
	int					pmpt;
	int					x;
	int					y;
	t_prompt			promp_type;
	char				phase;
	// int					down; // sanitized
	// int					eof_flag; // sanitized
	char				*rev_sr;
	int					rs;
	int					rs_i;
	// t_auto				auto_com; // delete this later
}						t_l;

typedef struct termios	t_term;

/*
** Auto completion
*/

typedef enum
{
	AUTO_ROLE_FULFILL_ALL,
	AUTO_ROLE_FULFILL_UPTO,
	AUTO_ROLE_PRINT,
	AUTO_ROLE_OPEN_LIST,
	AUTO_ROLE_ERR
}	t_auto_com_role;

typedef enum
{
	AUTO_STAT_NEW_POS = (1 << 0),
	AUTO_STAT_COMPLETED = (1 << 1),
	AUTO_STAT_DIR = (1 << 2),
	AUTO_STAT_LIST = (1 << 3),
	AUTO_STAT_OVER_TERM_SIZE = (1 << 4)
}	t_auto_com_stat;

/*
** struct auto
**	t_list			*list					: list of the options
**	size_t			largest_content_size	:
**	void			*largest_content		:
**	size_t			count_list				: number of item in list
**	char			cwd[]					: current working dir
**	char			full_path[]				:
**	char			*typed_str				: str which will be diagnosed to
											specify the target for
											auto_completion
**	char			*target_str				: the extracted str from
											typed_str in
											auto_completion context
**	char			*path_env				:
**	long			status					:
*/

typedef struct			s_auto
{
	t_list				*list;
	size_t				largest_content_size;
	void				*largest_content;
	size_t				count_list;
	char				cwd[PATH_MAX];
	char				full_path[PATH_MAX];
	char				*typed_str;
	char				*target_str;
	char				*path_env;
	long				status;
	t_l					*editor;
}						t_auto;

typedef struct			s_auto_grid
{
	size_t				longest_col_len;
	size_t				term_col_len;
	size_t				col_count;
	size_t				file_count;
	size_t				start_row;
	size_t				end_row;
	size_t				filled_col_count;
}						t_auto_grid;

/*
**  History struct
**		char **hist	: history of commands
**		int  hst	: keep track of the position in the array while navigating
**					  throught the history with the up and down keys
**		int  curr	: the index position after the most recent history event
**					: and always contain null characters
**		int  size   : to keep track the growing max size
*/

typedef struct			s_history
{
	char		**hist;
	char		*tmp;
	int			hst;
	int			curr;
	int			hstsize;
	char		savedfile[256];
}						t_history;

/*
** struct for options in builtin
*/

# define BUILTIN_NO_OPT (unsigned int) 0
# define BUILTIN_INVALID_OPT (unsigned int) -1

typedef struct			s_builtin_options
{
	char			*opt_set;
	char			set_len;
	unsigned int	operand_count;
	unsigned long	applied;
	char			invalid_opt;
	int				opt;
}						t_opt;

typedef struct			s_var
{
	char *name;
	char *value;
	char exported;
}						t_var;

/*
** export struct
*/

# define BUILTIN_EXPORT_OPT_SET "p"
# define EXPORT_OPT_P 1

typedef	struct			s_export
{
	char			*opt_set;
	int				opt;
	char			synopsis;
	char			*av[4096];
}						t_export;

/*
** cd struct
*/

# define BUILTIN_CD_OPT_SET "PL"

typedef enum
{
	BUILTIN_CD_OPT_P = (1 << 0),
	BUILTIN_CD_OPT_L = (1 << 1)
}	t_cd_opts;

typedef struct			s_cd
{
	char			*directory;
	char			*curpath;
	char			*prev_curpath;
	char			print_info;
	t_opt			opt;
}						t_cd;

/*
** pwd struct
*/

# define BUILTIN_PWD_OPT_SET BUILTIN_CD_OPT_SET

typedef enum
{
	BUILTIN_PWD_OPT_P = BUILTIN_CD_OPT_P,
	BUILTIN_PWD_OPT_L = BUILTIN_CD_OPT_L
}	t_pwd_opts;

/*
** Alias struct
*/

typedef struct			s_alias
{
	char *value;
	char *name;
}						t_alias;

/*
** Parameter expansion struct
*/

typedef struct			s_parameter_expansion
{
	char				**valid_delimeter;
	char				replacement[256];
	char				expression[256];
	char				parameter[256];
	char				delimeter[3];
	char				word[256];
	char				needle[256];
}						t_parameter_expansion;

typedef enum
{
	PE_SET_AND_NOT_NULL,
	PE_SET_BUT_NULL,
	PE_UNSET
}	t_parameter_expansion_type;

/*
** Hash struct
*/

typedef struct			s_hash
{
	char			*name;
	char			*path;
	int				hits;
	struct s_hash	*next;
	struct s_hash	*prev;
}						t_hash;

/*
**	Builtin commands list
*/

typedef struct			s_builtin
{
	const char			*name;
	void				*func;
	struct s_builtin	*next;
}						t_builtin;


// new
typedef struct s_tokennizing_service // move later
{
	char *whole_cmd;
	char *single_cmd;
	int ret;
	t_token *token_stream;
	t_lex_value lex_value;
}	t_tokennizing_service;

typedef struct s_lexical_service
{
	int i;
	t_token *stream;
	t_token *tk;
	t_token *prev_tk;
}	t_lexical_service;

typedef struct s_syntax_service
{
	t_token *cur_tk;
	t_token *prev_tk;
}	t_syntax_service;

typedef struct s_get_command_service
{
	t_phase phase[20];
	int i;
	char *cmd;
	char *line;
	t_prompt prompt_type;	
}	t_get_command_service;

typedef struct get_line_service
{
	t_l	line_edition;
	char	buf[BUFF_LINE_EDITION];
}	t_get_line_service;

#endif
