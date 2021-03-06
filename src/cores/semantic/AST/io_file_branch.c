/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_file_branch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dthan <dthan@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 10:16:43 by dthan             #+#    #+#             */
/*   Updated: 2020/12/26 19:36:46 by dthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_astnode	*io_file(t_token **token)
{
	if (*token == NULL)
		return (NULL);
	if ((*token)->type == TOKEN_LESS)
		return (io_file1(token));
	if ((*token)->type == TOKEN_LESSAND)
		return (io_file2(token));
	if ((*token)->type == TOKEN_GREAT)
		return (io_file3(token));
	if ((*token)->type == TOKEN_GREATAND)
		return (io_file4(token));
	if ((*token)->type == TOKEN_DGREAT)
		return (io_file5(token));
	return (NULL);
}
