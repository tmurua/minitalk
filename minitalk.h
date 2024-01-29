/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:36:32 by tmurua            #+#    #+#             */
/*   Updated: 2024/01/29 16:06:27 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "ft_printf/ft_printf.h"

/* server helper function */
void	ft_handler(int signal);

/* client helper function */
void	ft_send_bits(int pid, char i);

#endif
