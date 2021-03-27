/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 11:35:45 by dthan             #+#    #+#             */
/*   Updated: 2021/03/27 20:26:01 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H
# include "libft.h"

char		*ft_getcwd_logical(void);
int			is_made_of_digits(char *data);
char		*ft_strjoin_and_free_string2(char *string1, char *string2);
char		*ft_strjoin_and_free_string1(char *string1, char *string2);
char		*ft_strjoin_and_free_2strings(char *string1, char *string2);
void		increment_shlvl(void);
char		*get_var(char *name, char **lst_var, int keyval);
int			ft_isspace(int c);
char		*ft_strndup(char *str, size_t len);
void		ft_arraydel(char **string_array);
int			ft_strstr_int(const char *haystack, const char *needle);
int			ft_strchr_int(char *str, int c);
int			ft_num_check(char *str);
void		ft_swap(int *nums);
int			ft_lstlen(t_list *head);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strbuilder(int argc, char *str, ...);
char		*ft_strbuilder_char(char *old, char c);
int			ft_tcsetpgrp (int fd, pid_t pgrp_id);
pid_t		ft_tcgetpgrp (int fd);
int			ft_isspace(int c);
int			ft_arraylen(char **array);
void		ft_lstdel_strdel(t_list **alst);
char		*ft_llitoa(long long n);
long long	ft_atolli(const char *str);
long long	ft_atolli_check(const char *str, char *stat);
int			is_number_str(char *str);
char		*ft_strrev(char *str);
int			ft_findchr(char *str, int c);
int			ft_isspace_str(char *str);

#endif
