/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:24:04 by hes-saou          #+#    #+#             */
/*   Updated: 2025/02/16 01:00:39 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = 0;
	static	int	pid;
	(void)context;

	if (pid != info->si_pid)
	{
		c = 0;
		bit = 0;
	}
	c = (c << 1) | (sig == SIGUSR2);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
		{
			ft_printf("\n");
			// exit(1);
		}
		else
			ft_printf("%c", c);
		c = 0;
		bit = 0;
	}
	pid = info->si_pid;
}
int main()
{
	struct sigaction sa;
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Receiver PID: %d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}
