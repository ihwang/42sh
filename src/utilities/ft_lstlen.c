/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 05:31:40 by dthan             #+#    #+#             */
/*   Updated: 2020/10/12 05:33:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int ft_lstlen(t_list *head)
{
	int i;
	t_list *ptr;

	i = 0;
	ptr = head;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}