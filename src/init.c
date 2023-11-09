/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:08:24 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/18 17:08:24 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	init_time(char **av, int ac, t_times *time)
{
	struct	timeval	the_time;
	time->die = ft_atoi(av[2]) * 1000;
	time->eat = ft_atoi(av[3]) * 1000;
	time->sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		time->max_ml = ft_atoi(av[5]);
	else
		time->max_ml = 0;
	if (gettimeofday(&the_time, NULL) == 0)
		time->start = the_time.tv_sec * 1000000 + the_time.tv_usec;
	else 
		return (false);
	return (true);
}

bool	init_forks(int size, t_var *var)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (i % 2 == 1)
			var->fork[i] = 0;
		else
			var->fork[i] = 1;
		i++;
	}
	return (1);
}

bool	init_philosopher(int size, t_var *var, t_times time)
{
	int	i;

	i = 0;
	while (i < size)
	{
		var->philo[i].philo_id = i + 1;
		var->philo[i].meal = 0;
		var->philo[i].is_alive = &var->is_alive;
		var->philo[i].times = time;
		var->philo[i].lock = var->lock;
		var->philo[i].fork_l = &var->fork[i];
		var->philo[i].mutex_l = &var->mutex[i];
		printf("philo[%d]->is alive = %d \n", var->philo->philo_id, *var->philo->is_alive);
		if (i == 0)
		{
			var->philo[i].mutex_r = &var->mutex[size - 1];
			var->philo[i].fork_r = &var->fork[size - 1];
		}
		else
		{
			var->philo[i].fork_r = &var->fork[i - 1];
			var->philo[i].mutex_r = &var->mutex[i - 1];
		}
		i++;
	}
	return (1);
}