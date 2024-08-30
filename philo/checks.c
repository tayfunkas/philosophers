/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 16:25:51 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/30 16:27:22 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*health_check(void *arg)
{
	t_data		*data;
	int			i;
	int			should_continue;

	data = (t_data *)arg;
	should_continue = 1;
	while (should_continue)
	{
		i = 0;
		while (i < data->philos_num && should_continue)
		{
			if (check_death(data, i))
			{
				pthread_mutex_unlock(&data->eat);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat);
			i++;
		}
		usleep(300); 
		pthread_mutex_lock(&data->dead);
		should_continue = !data->is_dead;
		pthread_mutex_unlock(&data->dead);
	}
	return (NULL);
}

int	check_death(t_data *data, int i)
{
	long long	current_time; 

	pthread_mutex_lock(&data->eat);
	current_time = ft_timestamp();
	if (current_time - data->philo[i].last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->dead);
		if ((!data->is_dead && (data->philo[i].eat < data->must_eat || 
					data->must_eat == -1)) || data->philos_num == 1)
		{
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead);
			pthread_mutex_lock(&data->output);
			if (data->must_eat != 0)
			{
				printf("%lld ", ft_timestamp() - data->creation);
				printf("%d %s\n", data->philo[i].id, "died.");
			}
			pthread_mutex_unlock(&data->output);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	return (0);
}

int	check_end_conditions(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(&philo->data->dead);
	end = philo->data->is_dead || philo->data->all_ate 
		|| (philo->data->must_eat != -1 && philo->eat >= philo->data->must_eat);
	pthread_mutex_unlock(&philo->data->dead);
	return (end);
}

bool	check_args(char **arg)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ft_atoi(arg[1]) < 1)
		return (0);
	while (arg[i])
	{
		j = 0;
		while (arg [i][j])
		{
			if ((arg[i][j] != '+') && (!ft_isdigit(arg[i][j])))
				return (0);
			if (arg[i][j] == '+' && (!ft_isdigit(arg[i][j + 1])))
				return (0);
			if (arg[i][j] == '-')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
