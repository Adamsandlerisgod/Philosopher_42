/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:12:14 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/09 17:20:35 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

bool	malloc_mutex(int size, t_var *var)
{
	int	i;

	i = 0;
	var->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!(var->mutex))
		return (false);
	while (i < size)
	{
		pthread_mutex_init(&var->mutex[i], NULL);
		i++;
	}
	var->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!(var->lock))
		return (false);
	pthread_mutex_init(var->lock, NULL);
		// return (printf("fail \n"), false);
	return (true);

}

bool	mallocer(int size, t_var *var)
{
	var->philo = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!var->philo)
		return (false);
	var->fork = (int *)malloc(sizeof(int) * size);
	if (!var->fork)
		return (false);
	var->thd = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!var->thd)
		return (false);
	if (!(malloc_mutex(size, var)))
		return (false);
	// var->is_alive = (int *)malloc(sizeof(int) * size);
	// if (var->is_alive))
		// return (false);
	var->is_alive = 1;
	return (true);
}