/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:48:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/16 12:30:17 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	handle_char(unsigned char c)
{
	static char	*buff = NULL;
	char		*tmp;

	tmp = buff;
	buff = ft_strjoin_char(buff, c);
	if (tmp)
		free(tmp);
	if (!buff)
	{
		ft_printf("Malloc error\n");
		exit(1);
	}
	if (c == '\0')
	{
		if (!ft_strncmp(buff, "exit", 5))
		{
			free(buff);
			exit(0);
		}
		ft_printf("%s\n", buff);
		free(buff);
		buff = NULL;
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				i = 0;

	(void)context;
	(void)info;
	c = (c << 1) | (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		handle_char(c);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_printf("PID : %d\nSend \"exit\" to kill the server\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
