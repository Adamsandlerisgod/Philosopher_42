/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:33:27 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/21 20:41:55 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

bool	thread_creator(t_var *var, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		if ((pthread_create(&var->thd[i], NULL, &routine, &var->philo[i])))
		{
			free_all(var, nb);
			return (0);
		}
		i++;
	}
	while (nb - i < nb)
	{
		if ((pthread_join(var->thd[nb - i], NULL)))
		{
			free_all(var, nb);
			return (0);
		}
		i--;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_times	time;
	t_var	vars;

	if (ac > 6 || ac < 4)
		exit(1);
	if (!(arg_check(ac, av)))
		exit(1);
	if (!(init_time(av, ac, &time)))
		exit(1);
	if (!(mallocer(ft_atoi(av[1]), &vars)))
		exit(1);
	init_forks(ft_atoi(av[1]), &vars);
	init_philosopher(ft_atoi(av[1]), &vars, time);
	if (!(thread_creator(&vars, ft_atoi(av[1]))))
	{
		free_all(&vars, ft_atoi(av[1]));
		exit(1);
	}
	free_all(&vars, ft_atoi(av[1]));
	return (0);
}
