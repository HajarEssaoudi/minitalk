/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hes-saou <hes-saou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:39 by hes-saou          #+#    #+#             */
/*   Updated: 2025/02/17 16:02:57 by hes-saou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_flag = 0;

void	handle_msg(int sig)
{
	if (sig == SIGUSR2)
		write(1, "message bien reçu\n", 19);
}

void	handle_flag(int sig)
{
	if (sig == SIGUSR1)
		g_flag = 1;
}

void	send_char(pid_t pid, char c)
{
	int	bit;
	int	check;

	bit = 8;
	while (bit--)
	{
		if ((c >> bit) & 1)
			check = kill(pid, SIGUSR2);
		else
			check = kill(pid, SIGUSR1);
		if (check == -1)
		{
			write(2, "Process n'est pas actif ou PID incorrect\n", 41);
			exit(1);
		}
		while (g_flag == 0)
			;
		g_flag = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	if (ac != 3)
	{
		write(2, "Usage: ./client <PID> <message>\n", 32);
		return (1);
	}
	pid = ft_atoi(av[1]);
	i = 0;
	signal(SIGUSR1, handle_flag);
	signal(SIGUSR2, handle_msg);
	while (av[2][i])
		send_char(pid, av[2][i++]);
	send_char(pid, '\0');
	return (0);
}
