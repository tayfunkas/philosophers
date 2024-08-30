/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:18:41 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/30 16:29:00 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_cycle(void *arg)
{
	t_philo	*philo;
	int		delay;

	delay = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0 && philo->data->philos_num != 1)
	{
		delay = (philo->data->time_to_eat * 100) / philo->data->philos_num;
		usleep(delay);
	}
	while (!check_end_conditions(philo))
	{
		if (philo_eat(philo) || check_end_conditions(philo))
			return (NULL);
		if (philo_sleep(philo) || check_end_conditions(philo))
			return (NULL);
		if (philo_think(philo) || check_end_conditions(philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		*data;
	pthread_t	health_thread;

	if (argc != 5 && argc != 6)
	{
		printf("Argument count is incorrect.\n");
		return (1);
	}
	if (!check_args(argv))
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		printf("Data allocation is not OK.\n");
		return (1);
	}
	data->argv = argv;
	init_data(data);
	health_thread = init_philos(data);
	if (!init_threads(data))
		return (1);
	pthread_join(health_thread, NULL);
	cleanup_threads(data);
	return (0);
}
