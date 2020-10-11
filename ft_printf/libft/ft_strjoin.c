/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:55:44 by dthan             #+#    #+#             */
/*   Updated: 2020/09/26 02:59:01 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *string1, char const *string2)
{
	char	*jointstring;
	size_t	jointstringsize;

	if (string1 && string2)
		jointstringsize = (size_t)(ft_strlen(string1) + ft_strlen(string2));
	else if (string1)
		jointstringsize = (size_t)(ft_strlen(string1));
	else if (string2)
		jointstringsize = (size_t)(ft_strlen(string2));
	else
		return (NULL);
	if (!(jointstring = ft_memalloc(jointstringsize + 1)))
		return (NULL);
	if (string1)
		jointstring = ft_strcpy(jointstring, (char*)string1);
	else if (string2)
		jointstring = ft_strcpy(jointstring, (char*)string2);
	if (string1 && string2)
		jointstring = ft_strcat(jointstring, (char*)string2);
	return (jointstring);
}

char	*ft_strjoin_and_free_string2(char *string1, char *string2)
{
	char	*jointstring;
	size_t	jointstringsize;

	if (string1 && string2)
		jointstringsize = (size_t)(ft_strlen(string1) + ft_strlen(string2));
	else if (string1)
		jointstringsize = (size_t)(ft_strlen(string1));
	else if (string2)
		jointstringsize = (size_t)(ft_strlen(string2));
	else
		return (NULL);
	if (!(jointstring = ft_memalloc(jointstringsize + 1)))
		return (NULL);
	if (string1)
		jointstring = ft_strcpy(jointstring, (char*)string1);
	else if (string2)
		jointstring = ft_strcpy(jointstring, (char*)string2);
	if (string1 && string2)
		jointstring = ft_strcat(jointstring, (char*)string2);
	free(string2);
	return (jointstring);
}

char	*ft_strjoin_and_free_string1(char *string1, char *string2)
{
	char	*jointstring;
	size_t	jointstringsize;

	if (string1 && string2)
		jointstringsize = (size_t)(ft_strlen(string1) + ft_strlen(string2));
	else if (string1)
		jointstringsize = (size_t)(ft_strlen(string1));
	else if (string2)
		jointstringsize = (size_t)(ft_strlen(string2));
	else
		return (NULL);
	if (!(jointstring = ft_memalloc(jointstringsize + 1)))
		return (NULL);
	if (string1)
		jointstring = ft_strcpy(jointstring, (char*)string1);
	else if (string2)
		jointstring = ft_strcpy(jointstring, (char*)string2);
	if (string1 && string2)
		jointstring = ft_strcat(jointstring, (char*)string2);
	free(string1);
	return (jointstring);
}
