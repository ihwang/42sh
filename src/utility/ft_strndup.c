/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 00:18:18 by dthan             #+#    #+#             */
/*   Updated: 2020/09/24 02:09:42 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(char *str, size_t len)
{
	char	*new;
	int		i;

	new = ft_strnew(len);
	i = 0;
	while (len > 0)
	{
		new[i] = str[i];
		len--;
		i++;
	}
	return (new);
}
