/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2020/09/14 21:40:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

char	**add_env(char *arg, char **env_list);
int		is_open_dquote(char *input, int level, char *quote);
int		is_made_of_digits(char *data);
int		input_contain_dquote(char *input);
char	*ft_strjoin_and_free_string2(char *string1, char *string2);
char	*ft_strjoin_and_free_string1(char *string1, char *string2);
int 	set_oldpwd(char pwd[PATH_MAX]);
void	increment_shlvl(void);

#endif
