/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:48:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/09 14:32:12 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	handle_char(unsigned char c)
{
	static char	*buff;
	char		*tmp;

	tmp = buff;
	if (!buff)
		buff = NULL;
	buff = ft_strjoin(buff, (char *) &c);
	if (tmp)
		free(tmp);
	if (!buff)
		(ft_printf("Malloc error"), exit(1));
	if (c == '\0')
	{
		if (!ft_strncmp(buff, "exit", 9))
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
	static unsigned char	c;
	static int				i;

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
