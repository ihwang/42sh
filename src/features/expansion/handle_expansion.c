/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 06:04:39 by dthan             #+#    #+#             */
/*   Updated: 2021/01/08 15:16:36 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
char *find_tilde_prefix(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i + 1] == '/')
			break;
		i++;
	}
	return (ft_strndup(str, i + 1));
}

char *find_tilde_suffix(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i + 1] == '/')
			break;
		i++;
	}
	if (!str[i + 1])
		return (NULL);
	return (ft_strdup(&str[i + 1]));
}

char *get_home_without_user(void)
{
	char *original_home;
	char home_without_user_builder[255];
	char *home_without_user;

	original_home = ft_getenv("HOME");
	ft_bzero(home_without_user_builder);
	return (home_without_user);
}

char *get_tilde_with_user(char *tilde_prefix, char *tilde_suffix)
{
	char *str;
	char *original_home;
	char *user;
	char new_home[255];

	ft_bzero(new_home, 255);
	original_home = ft_getenv("HOME");
	user = ft_strdup(&tilde_prefix[1]);
	new_home[0] = '/';

	free(user);
	free(original_home);
	return (str);
}

char *replace_tilde(char *str)
{
	char *tilde_prefix;
	char *tilde_suffix;
	char *replaced_tilde_prefix;
	char *new_str;

	tilde_prefix = find_tilde_prefix(str);
	tilde_suffix = find_tilde_suffix(str);
	if (ft_strequ(tilde_prefix, "~"))
		new_str = ft_strjoin_and_free_string1(ft_getenv("HOME"), tilde_suffix);
	else if (ft_strequ(tilde_prefix, "~+"))
		new_str = ft_strjoin_and_free_string1(ft_getenv("PWD"), tilde_suffix);
	else if (ft_strequ(tilde_prefix, "~-"))
		new_str = ft_strjoin_and_free_string1(ft_getenv("OLDPWD"), tilde_suffix);
	else
		new_str = get_tilde_with_user(tilde_prefix, tilde_suffix);
	if (tilde_prefix)
		free(tilde_prefix);
	if (tilde_suffix)
		free(tilde_suffix);
	return (new_str);
}

int is_quoted(char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if (str[i] == '"' || str[i] == '\'')
			return (1);
	return (0);
}


char *ft_getenv(const char *name)
{
	int i;
	int len;

	i = -1;
	while (g_shell.env[++i])
	{
		len = ft_strlen(name);
		if (ft_strnequ(g_shell.env[i], name, len))
			return (ft_strdup(&g_shell.env[i][len + 1]));
	}
	return (NULL);
}

int is_valid_user(char *user)
{
	char *home_directory;
	char home_directory_with_user[255];
	int i;
	struct stat sb;
	int ret;

	if ((home_directory = ft_getenv("HOME")) == NULL)
		return (0);
	ft_bzero(home_directory_with_user, 255);
	i = 0;
	ret = 1;
	home_directory_with_user[0] = '/';
	while (home_directory[++i] && home_directory[i] != '/')
		home_directory_with_user[i] = home_directory[i];		
	home_directory_with_user[i] = '/';
	ft_strcat(home_directory_with_user, user);
	if (stat(home_directory_with_user, &sb) == -1)
		ret = 0;
	free(home_directory);
	return (ret);
}

int is_valid_for_tilde_expansion(char *str)
{
	int i;
	char *tilde_prefix;
	int ret;

	i = 0;
	if (str[i++] != '~')
		return (0);
	ret = 1;
	tilde_prefix = find_tilde_prefix(str);
	if (is_quoted(tilde_prefix))
		ret = 0;
	else if ((!ft_strequ(tilde_prefix, "~") || \
		!ft_strequ(tilde_prefix, "~+") || \
		!ft_strequ(tilde_prefix, "~-")) && \
		!is_valid_user(&tilde_prefix[1]))
		ret = 0;
	free(tilde_prefix);
	return (ret);
}

void tilde_expansion_in_redi(t_process *p)
{
	t_list *redi_ptr;
	t_redi *redi;

	redi_ptr = p->redi;
	while(redi_ptr)
	{
		redi = (t_redi*)(redi_ptr->content);
		if (is_valid_for_tilde_expansion(redi->word))
			redi->word = replace_tilde(redi->word);
		redi_ptr = redi_ptr->next;
	}
}

int tilde_expansion(t_process *p)
{
	tilde_expansion_in_redi(p);
	tilde_expansion_in_av(p);
	return (EXIT_SUCCESS);
}
*/

int is_parameter_expansion(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '{' && is_real_parameter_expansion(str, i))
			return (1);
	}
	return (0);
}

char *replace_replace(char *target, char *needle, char *replacement)
{
	char buffer[1024];
	char *tmp;
	char *insert_point;
	char *p;

	ft_bzero(buffer, 1024);
	tmp = target;
	insert_point = &buffer[0];
	while(1) {
		p = ft_strstr(tmp, needle);
		if (p == NULL)
		{
			ft_strcpy(insert_point, tmp);
			break;
		}
		ft_memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;
		ft_memcpy(insert_point, replacement, ft_strlen(replacement));
		insert_point += ft_strlen(replacement);
		tmp = p + ft_strlen(needle);
	}
	return (strdup(buffer));
}

int parameter_expansion_replace_redi(t_redi *redi)
{
	char *temp;
	char *replacement;

	temp = redi->word;
	replacement = ft_itoa(g_shell.exit_status);
	redi->word = replace_replace(temp, "${?}", replacement);
	free(replacement);
	free(temp);
	if (is_parameter_expansion(redi->word))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parameter_expansion_in_redi(t_process *p)
{
	t_redi *redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (is_parameter_expansion(redi_ptr->word))
			if (parameter_expansion_replace_redi(redi_ptr) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		redi_ptr = redi_ptr->next;
	}
	return (EXIT_SUCCESS);
}

int parameter_expansion_replace_av(char **av, int i)
{
	char *temp;
	char *replacement;

	temp = av[i];
	replacement = ft_itoa(g_shell.exit_status);
	av[i] = replace_replace(temp, "${?}", replacement);
	free(replacement);
	free(temp);
	if (is_parameter_expansion(av[i]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int parameter_expansion_in_av(t_process *p)
{
	int i;

	i = -1;
	while (p->av[++i])
	{
		if (is_parameter_expansion(p->av[i]))
			if (parameter_expansion_replace_av(p->av, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int parameter_expansion(t_process *p)
{
	if (parameter_expansion_in_redi(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (parameter_expansion_in_av(p));
}


int handle_expansion(t_process *p)
{
	// if (!tilde_expansion(p))
	// 	return (EXIT_FAILURE);
	if (parameter_expansion(p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	// if (!command_substitution())
	// 	return (EXIT_FAILURE);
	// if (!arithmetic_expasion())
	// 	return (EXIT_FAILURE);
	if (quote_removal(p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
