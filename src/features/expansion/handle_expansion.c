/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 06:04:39 by dthan             #+#    #+#             */
/*   Updated: 2021/02/28 12:58:37 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	parameter_expansion(t_process *p)
{
	if (parameter_expansion_in_redi(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parameter_expansion_in_av(p) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (parameter_expansion_in_assignment(p));
}

/*
** tilde expansion -> parameter expansion -> command substitution (no) ->
** arthimetic expansion -> quote removal
*/

int	handle_expansion(t_process *p)
{
	if (tilde_expansion(p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (parameter_expansion(p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if ((ft_arx(p)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (quote_removal(p) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
