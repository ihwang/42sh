/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_exec_e2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 02:02:03 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 02:04:48 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	fc_e_build_cmd(char **container)
{
	int	fd;

	fd = open(FC_EDITING_FILE, O_RDONLY, 0644);
	read_commands_from_a_file(fd, container);
	close(fd);
}
