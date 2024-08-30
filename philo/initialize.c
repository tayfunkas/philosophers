/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:36:42 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/28 15:30:24 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data)
{
	int	i;

	i = -1;
	data->philos_num = ft_atoi(data->argv[1]);
	data->time_to_die = ft_atoi(data->argv[2]);
	data->time_to_eat = ft_atoi(data->argv[3]);
	data->time_to_sleep = ft_atoi(data->argv[4]);
	if (data->argv[5])
		data->must_eat = ft_atoi(data->argv[5]);
	else
		data->must_eat = -1;
	data->all_eat = 0;
	data->is_dead = 0;
	data->all_ate = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philos_num);
	if (!data->fork)
		return (0);
	while (++i < data->philos_num)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (0);
	}
	if (data->philos_num < 1)
		return (0);
	return (1);
}

pthread_t	init_philos(t_data *data)
{
	pthread_t	health_thread;
	int			i;

	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->philos_num);
	if (!data->philo)
		printf("data->philo allocation is not OK\n");
	i = 0;
	while (i < data->philos_num)
	{
		data->philo[i].eat = 0;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].right_fork = &data->fork[i];
		if (i == (data->philos_num -1))
			data->philo[i].left_fork = &data->fork[0];
		else
			data->philo[i].left_fork = &data->fork[i + 1];
		data->philo[i].last_meal = ft_timestamp();
		i++;
	}
	if (pthread_create(&health_thread, NULL, health_check, (void *)data) != 0)
		printf("health_thread not created");
	return (health_thread);
}

void	cleanup_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
		pthread_join(data->philo[i].threads, NULL);
	i = -1;
	while (++i < data->philos_num)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->dead);
	free(data->fork);
	free(data->philo);
	free(data);
}

int	init_threads(t_data *data)
{
	int			i;

	i = -1;
	data->creation = ft_timestamp();
	pthread_mutex_init(&data->output, NULL);
	pthread_mutex_init(&data->eat, NULL);
	pthread_mutex_init(&data->dead, NULL);
	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_create(&data->philo[i].threads, NULL, philo_cycle, 
				&data->philo[i]) != 0)
		{
			printf("Failed to create thread");
			return (0);
		}
	}
	return (1);
}
