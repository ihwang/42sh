/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_add_list_at_spot.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:33:41 by marvin            #+#    #+#             */
/*   Updated: 2020/10/15 02:37:27 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void			auto_add_list_on_spot(t_auto *auto_com, t_list *node)
{
	t_list		*prev;
	t_list		*list;

	prev = NULL;
	list = auto_com->list;
	while (list)
	{
		if (ft_strcmp((char*)list->content, (char*)node->content) > 0)
		{
			node->next = list;
			if (prev)
				prev->next = node;
			else
				auto_com->list = node;
			return ;
		}
		prev = list;
		if (list->next)
			list = list->next;
		else
		{
			list->next = node;
			return ;
		}
	}
}