/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:40:02 by tmurua            #+#    #+#             */
/*   Updated: 2023/12/14 20:23:11 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

/*  */
int	ft_print_char(char c);
int	ft_print_str(char *str);
int	ft_print_int(int n);
int	ft_print_unsigned_int(long nb);
int	ft_print_hex(unsigned long nb, const char convert);
int	ft_print_pointer(void *ptr, const char convert);
int	ft_printf(const char *str, ...);

#endif
