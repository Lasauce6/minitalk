/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:01:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 16:38:04 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	send_char(int pid, unsigned char c)
{
	int				i;
	unsigned char	tmp;

	i = 8;
	tmp = c;
	while (i > 0)
	{
		i--;
		tmp = c >> i;
		if (tmp % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
	}
}

static void	handle_signal(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("Message transmited\n");
		exit(0);
	}
}

static void	send_pid(int pid)
{
	char	*s_pid;

	s_pid = ft_itoa(getpid());
	while (*s_pid)
	{
		send_char(pid, (unsigned char) *s_pid);
		s_pid++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc == 3)
	{
		ft_printf("%d\n", getpid());
		signal(SIGUSR1, handle_signal);
		pid = ft_atoi(argv[1]);
		while (*argv[2])
		{
			send_char(pid, (unsigned char) *argv[2]);
			(argv[2])++;
		}
		send_char(pid, '\0');
		send_pid(pid);
		pause();
		return (0);
	}
	else
		ft_putstr_fd("Error: usage ./client <server pid> <str to send>\n",
			STDERR_FILENO);
	return (1);
}
