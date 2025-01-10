/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:48:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/10 16:36:31 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	print_message_or_exit(char **message, char **client_pid)
{
	if (!ft_strncmp(*message, "exit", 9))
	{
		kill(ft_atoi(*client_pid), SIGUSR1);
		free(*message);
		free(*client_pid);
		exit(0);
	}
	ft_printf("%s\n", *message);
	kill(ft_atoi(*client_pid), SIGUSR1);
	free(*message);
	free(*client_pid);
	*message = NULL;
	*client_pid = NULL;
}

static void	handle_char(unsigned char c)
{
	static char	*buff = NULL;
	static char	*message;

	buff = ft_strjoin_char(buff, c);
	if (!buff)
		(ft_printf("Malloc error"), exit(1));
	if (c == '\0')
	{
		if (!message)
		{
			message = buff;
			buff = NULL;
		}
		else
			print_message_or_exit(&message, &buff);
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 0;

	(void) context;
	(void) info;
	c |= (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		handle_char(c);
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	ft_printf("PID : %d\nSend \"exit\" to kill the server\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
