/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:07:23 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/29 14:47:03 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	if (philo->data->philos_num != 1)
	{
		statement(philo->data, philo->id, "is sleeping");
	}
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo->data->philos_num != 1)
	{
		statement(philo->data, philo->id, "is thinking");
		usleep(500);
	}
	return (0);
}

void	initial_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		statement(philo->data, philo->id, "has taken a fork");
		if (philo->data->philos_num != 1)
		{
			pthread_mutex_lock(philo->left_fork);
			statement(philo->data, philo->id, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		statement(philo->data, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		statement(philo->data, philo->id, "has taken a fork");
	}
}

int	philo_eat(t_philo *philo)
{
	int	i;

	i = philo->data->must_eat * philo->data->philos_num;
	initial_forks(philo);
	last_meal(philo);
	if (philo->data->philos_num == 1)
	{
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		statement(philo->data, philo->id, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->dead);
		philo->eat++;
		philo->data->all_eat++;
		if (philo->data->must_eat != -1 && philo->data->all_eat >= i)
			philo->data->all_ate = 1; 
		pthread_mutex_unlock(&philo->data->dead);
	}
	return (0);
}
