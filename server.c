/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:31:19 by tmurua            #+#    #+#             */
/*   Updated: 2024/01/31 19:59:09 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* pid: Process ID of the server process (get with getpid function)
deal with 'unused variable warning' with (void)argv;
deal with user inputing more than just the name of the program (server)
handle wrong input by user when starting the process with error message
starts process printing process PID and confirming that program is waiting
infite loop to continuosly listen for signals
set signal handler for SIGUSR1 (the 1 bit) and SIGUSR2 (the 0 bit)
pause execution until a signal is received for handling with the signal ft
*/
int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: wrong format, too many parameters\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	pid = getpid();
	ft_printf("PID %d\n", pid);
	ft_printf("Waiting for a message...\n");
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler);
		signal(SIGUSR2, ft_handler);
		pause();
	}
	return (0);
}

/* Signal handler function for handling incoming signals
bit: tracks current bit position being received, because it's static, bit = 0
i: accumulator for constructing the ASCII value, because it's static i = 0
if received signal is SIGUSR1, the corresponding bit in 'i' is set
for each signal received, 'bit' is incremented
after processing 8 bits (a complete char), the char is printed and
'bit' and 'i' are reset to 0 for the next char
 */
void	ft_handler(int signal)
{
	static int	bit;
	static int	i;

	if (signal == SIGUSR1)
		i |= (00000001 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
}
