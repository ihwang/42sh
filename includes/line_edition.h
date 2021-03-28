/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 21:44:40 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 03:48:17 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H
# include "struct.h"

# define LEFT "#4"
# define ERR_EOF 1

# define INIT "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREN "\033[32m"
# define YELW "\033[33m"
# define BLUE "\033[34m"
# define MGTA "\033[35m"
# define CYAN "\033[36m"
# define GRSS "\033[92m"
# define TMGT "\033[95m"
# define SKYB "\033[96m"

# define BACKSLASH_KEY "\x7F"
# define CUT_KEY "\v"
# define HOME_KEY "\033[H"
# define END_KEY "\033[F"
# define PASTE_KEY "\f"
# define UP_ARROW_KEY "\033[A"
# define DOWN_ARROW_KEY "\033[B"
# define LEFT_ARROW_KEY "\033[D"
# define RIGHT_ARROW_KEY "\033[C"
# define CTRL_UP_KEY "\x1b[1;5A"
# define CTRL_DOWN_KEY "\x1b[1;5B"
# define CTRL_LEFT_KEY "\x1b[1;5D"
# define CTRL_RIGHT_KEY "\x1b[1;5C"
# define ENTER_KEY "\n"

# define CTRL_C_KEY "\x03"
# define CTRL_D_KEY "\x04"
# define EOF_VALUE "\x04"

# define TAB_KEY "\t"
# define CTRL_R_KEY "\x12"
# define ESC_KEY "\x1b"

char	*ft_get_line(t_phase *phase, t_prompt prompt_type, \
t_lex_value lex_value);
void	ft_read_input(t_get_line_service *self, t_phase *phase, \
t_lex_value lex_value);
int		parse_key(char buf[BUFF_LINE_EDITION], t_l *line_edition);

/*
** Parse key
*/
int		is_line_edition_key(char buf[BUFF_LINE_EDITION]);
int		parse_line_edition_key2(char buf[BUFF_LINE_EDITION], t_l *line_edition);
int		parse_line_edition_key(char buf[BUFF_LINE_EDITION], t_l *line_edition);
int		is_feature_key(char buf[BUFF_LINE_EDITION]);
int		parse_feature_key(char buf[BUFF_LINE_EDITION], t_l *line_edition);

/*
** Available keys
*/
int		up_down(t_l *l, char t[]);
int		right_key(t_l *l);
int		left_key(t_l *l);
int		bs_key(t_l *l);
int		home_key(t_l *l);
int		end_key(t_l *l);
int		ctrl_k(t_l *l, int y_dec);
int		ctrl_l(t_l *l, int clip_len, int i);
int		ctrl_left(t_l *l);
int		ctrl_right(t_l *l);
int		ctrl_up(t_l *l);
int		ctrl_down(t_l *l);
int		auto_complete(t_l *l);

/*
** Term_attr
*/
void	init_term(void);
void	restore_term(t_l *l);
void	get_new_term_cursor(t_l *l);

/*
** add key
*/
int		add_key(char t[], t_l *l);

/*
** Copy & Paste
*/
int		cutting(t_l *l);
void	cutting_clipping(t_l *l, int i, int j);
char	*clipboard(char *str, int opt);
int		paste(t_l *l, char raw_clip[], char *autocom_clip);
char	*get_clip_external(char raw_clip[]);
char	*get_clip_autocom(t_auto *auto_com);
void	paste_background(t_l *l, int clip_len);

/*
** Line Edition Utilities
*/
void	apply_termcap_str(char *str, int x, int y);
size_t	get_current_row(void);
size_t	get_current_column(void);
int		ft_count_rows(t_l *l);

/*
** Row count
*/
int		ft_row_count(t_l *l);
void	ft_line_count(t_l *l);

/*
** Cursor and index position
*/
int		ft_y_pos(t_l *l, int index);
int		ft_index_calc(t_l *l);
int		ft_cursor_x(t_l *l);

#endif
