/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_key.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihwang <ihwang@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 22:31:13 by marvin            #+#    #+#             */
/*   Updated: 2020/10/11 14:58:44 by ihwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_KEY
# define ADD_KEY

# include <sys/ioctl.h>
# include <term.h>
# include "line_auto_structs.h"
# include "line_edition_utilities.h"
# include "libft.h"

void				add_key(char t[], t_l *l);

#endif
