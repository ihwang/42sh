/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlst_del.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 22:01:34 by tango             #+#    #+#             */
/*   Updated: 2020/09/28 14:31:19 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		ft_strlst_del(char ***target, int nb)
{

	while (0 <= --nb)
		ft_strdel(&(target[0][nb]));
	free(*target);
	*target = NULL;
}
