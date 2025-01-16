/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:01:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/16 12:27:29 by rbaticle         ###   ########.fr       */
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
		usleep(300);
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
	int		i;

	s_pid = ft_itoa(getpid());
	if (!s_pid)
		(ft_putstr_fd("Error: malloc error\n", STDERR_FILENO),
			exit(1));
	i = 0;
	while (s_pid[i])
	{
		send_char(pid, (unsigned char) s_pid[i]);
		usleep(300);
		i++;
	}
	free(s_pid);
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
			usleep(300);
			(argv[2])++;
		}
		send_char(pid, '\0');
		usleep(300);
		send_pid(pid);
		pause();
		return (0);
	}
	else
		ft_putstr_fd("Error: usage ./client <server pid> <str to send>\n",
			STDERR_FILENO);
	return (1);
}
