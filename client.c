/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:44:37 by tmurua            #+#    #+#             */
/*   Updated: 2024/01/31 20:07:44 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* pid: Process ID of the server process, needs to be argv[1], the 2nd argument
i: current char in the string argv[1], initialized to 0 to start the string
check if correct number of cli arguments is provide i.e. ./client PID MSG (3)
convert string PID, the 2nd argument (argv[1]), to integer
while loop to iterate through each char of the msg (argv[2]) and send its bits
send a newline character to mark the end of the message
if an incorrect number of cli arguents is provide, print error message
in this case also return 1, i.e. error
*/
int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1);
	}
	return (0);
}

/* Function to send individual bits of a character as signals
bit: 1 single bit from the char i (from argv[2][i]) being send as msg
for example, the char 'h' can be described as 01101000
while loop to iterate through each bit of the char
check if current bit of the char 'i' is a 0 or a 1
if current bit is 1, send (kill) the signal SIGUSR1, if it's 0, send SIGUSR2
small delay between signal transmissions preventing overlapping of signals
move to next bit repeating the process for all 8 bits of the char 'i'
*/
void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (00000001 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}
