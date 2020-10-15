/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 21:44:40 by ihwang            #+#    #+#             */
/*   Updated: 2020/10/11 14:58:52 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDITION_H
# define LINE_EDITION_H

# include "auto_completion.h"
# include "line_auto_structs.h"
# include "line_edition_utilities.h"
# include "copy_paste.h"
# include "add_key.h"
# include "get_prompt.h"

/*
** # ifdef __APPLE__
** #  if __MAC_OS_X_VERSION_MIN_REQUIRED <= 101200
** #   define OS "sierra"
** #   define LEFT "#4"
** #  else
** #   define LEFT "#4"
** #   define OS "not_sierra"
** #  endif
** # else
** #  define LEFT "#4"
** #  define OS "not_apple"
** # endif
*/

# define LEFT "#4"

# define BUFF_LINE_EDITION 8
# define LINE_TYPE_SINGLE 0
# define LINE_TYPE_DQUOTE 1
# define LINE_TYPE_HEREDOC 2

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

typedef struct termios	t_term;

typedef struct			s_h
{
	char				*data;
	struct s_h			*next;
	short				nb;
	int					len;
}						t_h;

t_h						*g_h;

void					ft_get_line(t_l *l, t_h **h);

/*
** Available keys
*/

int						bs_key(t_l *l);
int						home_key(t_l *l);
int						end_key(t_l *l);
int						auto_complete(t_l *l);
void					up_down(t_l *l, t_h **h, char t[]);
void					right_key(t_l *l);
void					left_key(t_l *l);
void					ctrl_left(t_l *l, int y_dec);
void					ctrl_right(t_l *l);
void					ctrl_up(t_l *l);
void					ctrl_down(t_l *l);
void					carriage_return_key(t_l *l, t_h **h);


/*
** History
*/

void					delete_save_history(t_h **g_h);
void					append_history(t_l *l, t_h **g_h);
void					get_history(t_h **g_h, int fd);

/*
** Term_attr
*/

void					init_term(t_l *l);
t_term					get_set_default_term(t_term *t);
void					restore_term(t_l *l);
void					get_new_term_cursor(t_l *l);

#endif
