/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:46:48 by ihwang            #+#    #+#             */
/*   Updated: 2020/09/27 04:39:03 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

void	ft_lstadd_tail(t_list **alst, t_list *new)
{
	t_list *ptr;
	#include <stdio.h>
	if (alst && new)
	{
		ptr = *alst;
		while(ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}