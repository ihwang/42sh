/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 13:52:13 by dthan             #+#    #+#             */
/*   Updated: 2021/03/28 12:25:16 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	quote_removal_in_av(t_process *p)
{
	int i;

	i = -1;
	while (p->av[++i] && i < MAX_ARGV)
	{
		if (is_quoted(p->av[i]))
			p->av[i] = remove_quote(p->av[i]);
	}
}

static void	quote_removal_in_redi(t_process *p)
{
	t_redi *redi_ptr;

	redi_ptr = p->first_redi;
	while (redi_ptr)
	{
		if (!ft_strequ(redi_ptr->op, "<<") && is_quoted(redi_ptr->word))
			redi_ptr->word = remove_quote(redi_ptr->word);
		redi_ptr = redi_ptr->next;
	}
}

static void	quote_removal_in_assignment_word(t_process *p)
{
	t_assignment *ptr;

	ptr = p->first_assignment;
	while (ptr)
	{
		if (is_quoted(ptr->data))
			ptr->data = remove_quote(ptr->data);
		ptr = ptr->next;
	}
}

int			quote_removal(t_process *p)
{
	quote_removal_in_av(p);
	quote_removal_in_redi(p);
	quote_removal_in_assignment_word(p);
	return (EXIT_SUCCESS);
}
