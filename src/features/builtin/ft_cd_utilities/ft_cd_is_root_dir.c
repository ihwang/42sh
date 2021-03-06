/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_is_root_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:27:29 by ihwang            #+#    #+#             */
/*   Updated: 2021/03/21 11:26:14 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	is_root_dir(char *path)
{
	t_stat root;
	t_stat path_stat;

	if (path == NULL || access(path, F_OK) != 0)
		return (FALSE);
	stat("/", &root);
	stat(path, &path_stat);
	if (root.st_dev != path_stat.st_dev ||
		root.st_ino != path_stat.st_ino)
		return (FALSE);
	return (TRUE);
}
