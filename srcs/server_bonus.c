/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaticle <rbaticle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:48:07 by rbaticle          #+#    #+#             */
/*   Updated: 2025/01/09 15:08:26 by rbaticle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	handle_char(unsigned char c, int *client_pid)
{
	static char	*buff;
	char		*tmp;

	tmp = buff;
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
			kill(*client_pid, SIGUSR1);
			exit(0);
		}
		ft_printf("%s\n", buff);
		free(buff);
		buff = NULL;
		kill(*client_pid, SIGUSR1);
		*client_pid = 0;
	}
}

static void	get_message(int sig, int *client_pid)
{
	static unsigned char	c;
	static int				i;

	c |= (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		handle_char(c, client_pid);
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

static void	get_client_pid(int sig, int *client_pid)
{
	static unsigned char	c;
	static int				i;
	static char				buff[8];
	static int				count;

	c |= (sig == SIGUSR1);
	i++;
	if (i == 8)
	{
		if (c == '\0')
		{
			buff[count] = '\0';
			*client_pid = ft_atoi(buff);
			ft_printf("%d\n\n", *client_pid);
		}
		buff[count++] = c;
		i = 0;
		c = 0;
	}
	else
		c <<= 1;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	client_pid;

	(void) context;
	(void) info;
	if (client_pid == 0)
		get_client_pid(sig, &client_pid);
	else
		get_message(sig, &client_pid);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
