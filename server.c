/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurua <tmurua@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:31:19 by tmurua            #+#    #+#             */
/*   Updated: 2024/01/29 15:17:22 by tmurua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv; // Suppress unused variable warning
	/* Check for incorrect command-line arguments */
	if (argc != 1)
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./server\n");
		return (0);
	}
	pid = getpid(); // Get the PID of the server process
	/* Print server information */
	ft_printf("PID %d\n", pid);
	ft_printf("Waiting for a message...\n");
	/* Infinite loop to continuously listen for signals */
	while (argc == 1)
	{
		signal(SIGUSR1, ft_handler); // Set signal handler for SIGUSR1
		signal(SIGUSR2, ft_handler); // Set signal handler for SIGUSR2
		pause();                     // Wait for signals
	}
	return (0);
}

/* Signal handler function for handling incoming signals */
void	ft_handler(int signal)
{
	static int	bit; // Track the current bit position
	static int	i;   // Accumulator for constructing the ASCII value
	/* Check if the received signal is SIGUSR1 */
	if (signal == SIGUSR1)
		i |= (0x01 << bit); // Set the corresponding bit in the accumulator
	bit++; // Move to the next bit position
	/* Check if all 8 bits have been received */
	if (bit == 8)
	{
		ft_printf("%c", i);
			// Print the character represented by the accumulated bits
		bit = 0;            // Reset bit position for the next character
		i = 0;              // Reset accumulator for the next character
	}
}
