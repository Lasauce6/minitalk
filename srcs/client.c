/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:01:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 15:05:30 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i > 0)
	{
		i--;
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_putstr_fd("Error: signal failed\n", STDERR_FILENO);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_putstr_fd("Error: signal failed\n", STDERR_FILENO);
		}
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (*argv[2])
		{
			send_char(pid, (unsigned char)*argv[2]);
			(argv[2])++;
		}
		send_char(pid, '\0');
		return (0);
	}
	else
		ft_putstr_fd("Error: usage ./client <server pid> <str to send>\n",
			STDERR_FILENO);
	return (1);
}
