/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 20:44:37 by tmurua            #+#    #+#             */
/*   Updated: 2024/01/29 15:17:22 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	/* Check if the correct number of command-line arguments is provided */
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]); // Convert the string PID to integer
		/* Iterate through each character of the message and send its bits */
		while (argv[2][i] != '\0')
		{
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
			// Send a newline character to mark the end of the message
	}
	else
	{
		/* Print an error message for incorrect command-line format */
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1); // Return an error code
	}
	return (0); // Return success code
}

/* Function to send individual bits of a character as signals */
void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	/* Iterate through each bit of the character */
	while (bit < 8)
	{
		/* Check if the current bit is 1 and send SIGUSR1, else send SIGUSR2 */
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100); // Introduce a small delay between signal transmissions
		bit++;       // Move to the next bit
	}
}
