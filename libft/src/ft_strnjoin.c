/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:54:43 by tango             #+#    #+#             */
/*   Updated: 2021/03/10 16:26:33 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*fresh;

	fresh = (char*)malloc(ft_strlen(s1) + n + 1);
	if (!fresh)
		return (NULL);
	ft_strcpy(fresh, s1);
	fresh = ft_strncat(fresh, s2, n);
	return (fresh);
}
