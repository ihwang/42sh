/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:23:45 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 02:03:02 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "struct.h"

/*
** ========================== builtin functions ============================
*/

int				ft_env(void);
int				ft_echo(t_process *c);
int				ft_exit(t_process *p);
int				ft_cd(t_process *c);
int				ft_type(t_process *c);
int				ft_jobs(t_process *p);
int				ft_fg(t_process *p);
int				ft_bg(t_process *p);
int				ft_export(int ac, char **av);
int				ft_set(void);
int				ft_unset(int ac, char **av);
int				ft_fc(t_process *p, int foreground);
int				ft_hash(t_process *c);
int				ft_alias(t_process *c);
int				ft_unalias(t_process *c);

/*
**	Built-in functions for child shell
*/

int				ft_bg_child();
int				ft_fg_child();

/*
** Built-in functions no longer in use
*/

int				ft_setenv(t_process *c);
int				ft_unsetenv(t_process *c);

/*
** Exit built-in
*/

int				ft_exit_internal(int opt);

/*
**	Export built-in
*/

int				export_parse_av(t_export *export, char **av);

/*
** Cd built-in
*/

# define FT_CD_NULL_LEN 1

int				ft_cd_search_cdpath(t_cd *cd);
char			ft_cd_get_curpath_from_dir(t_cd *cd);
int				ft_cd_append_slash_to_curpath(t_cd *cd);
int				ft_cd_prune_dotdot_dot_slash(t_cd *cd);
int				ft_cd_compress_curpath(t_cd *cd);
int				ft_cd_change_dir(t_cd *cd);

/*
** Fc built-in
*/

# define FC_MODE_LISTING
# define FC_MODE_EDITING
# define DEFAULT_EDITOR "vim"
# define FC_EDITING_FILE "/tmp/fc_42sh"
# define FC_L_OP 1
# define FC_N_OP 2
# define FC_R_OP 4
# define FC_S_OP 8
# define FC_E_OP 16
# define FIRST 0
# define LAST 1
# define REPLACE 2

void			init_ft_fc_struct(t_ft_fc *self);
void			clean_up_ft_fc_struct(t_ft_fc instance);

int				fc_parse_input(t_process *p, t_ft_fc *self);
int				fc_error_no_command_found(void);
int				fc_error_history_specification_out_of_range(void);
int				fc_error_invalid_option(char op);
int				fc_error_option_requires_an_argument(void);
int				fc_range(char *str);
int				fc_s_op(char *replace, char *first);
int				fc_e_op(int ops, char *editor, char *first, char *last);
void			fc_e_build_cmd(char **container);
int				fc_list(int ops, char *first, char *last);
void			ft_fc_execute(char *cmd);
int				fc_check_editor(char *editor);
char			*fc_return_cmd(char *str);
void			write_history_commands_into_editor(int fd, int *r_ind);

/*
** End of Fc built-in
*/

/*
** Alias built-in
*/

int				is_alias(char *str, t_token *prev_token);
t_token			*alias_substitution(
	t_lexical_service *lex, char *fix_alias_name);
char			*find_alias_str(char *str);
t_alias			*find_alias2(char *str);
int				remove_all(t_alias ***aliaslist);
void			set_aliastable(void);
int				print_all(void);
int				count_arr(void);
char			*set_value(char *argv);
char			*set_name(char *argv);
void			sort_alias_list(t_alias **aliaslist);

/*
** Hash built-in
*/

void			add_hashentry(char *name, char *path, int hits);
unsigned int	hash_index(char *name);
int				remove_hashentries(void);
t_hash			*create_hash_node(char *name, char *path, int hits);
unsigned int	hash_index(char *name);
int				exists_in_hashtable(char *name, char *path, int index);

/*
** Type built-inmake_child_path_sub
*/

t_builtin		*set_builtin_commands(void);
void			delete_builtin_commands(void);

/*
** ============================= Other Utils ==================================
*/

int				exec_file(t_process *c);
int				exec_file_in_path(t_process *c, char buf[]);
char			*find_executable(char *name);
void			destroy_arr(char **arr);
void			ft_cd_pwd_check_builtin_opts(char **av, t_opt *opt);
void			ft_cd_pwd_init_opt(t_opt *opt, const char *opt_set);
char			is_root_dir(char *path);
int				is_valid_alias_name(char *alias);

#endif
