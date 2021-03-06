/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhibitor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 19:22:41 by dthan             #+#    #+#             */
/*   Updated: 2021/03/12 22:38:59 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INHIBITOR_H
# define INHIBITOR_H

int		is_quoting_phase(t_phase cur_phase);
int		is_real_character(char *str, int i);
char	*delete_back_slash_and_line_feed(char *cmd);
int		jump_quote(char *input, int *i, char quote_type);
int		is_quoted(char *str);
char	*remove_quote(char *str);
char	*remove_quote2(char *str);

#endif
