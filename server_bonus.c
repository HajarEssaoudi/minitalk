/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:14:38 by hes-saou          #+#    #+#             */
/*   Updated: 2025/02/16 23:08:46 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void write_kill(pid_t pid)
{
	write(1, "\n", 1);
	kill(pid, SIGUSR2);
}


void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 0;
	static pid_t	pid;

	(void)context;
	if (pid != info->si_pid)
	{
		c = 0;
		bit = 0;
	}
	pid = info->si_pid;
	c = (c << 1) | (sig == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			write_kill(pid);
		}
		else
			write(1, &c, 1);
		c = 0;
		bit = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "Mon pid est = ", 14);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
