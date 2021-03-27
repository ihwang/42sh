/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 01:11:23 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 01:11:55 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_line_containing_tab(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t')
			return (1);
	return (0);
}

void	replace_line_containing_tab_with_space(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '\t')
			str[i] = ' ';
}
