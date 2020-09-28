/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_is_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:58:41 by marvin            #+#    #+#             */
/*   Updated: 2020/09/28 22:46:35 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

char        auto_is_dir(char *path, char *filename)
{
    t_stat  sb;
    char    full_path[PATH_MAX];

	if (!path || !filename)
		return (FALSE);
    ft_strcpy(full_path, path);
    ft_strcat(full_path, "/");
    ft_strcat(full_path, filename);
    lstat(full_path, &sb);
    if (sb.st_mode & S_IFDIR)
        return (TRUE);
    else
        return (FALSE);
}

