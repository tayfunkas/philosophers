/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:36:29 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/29 14:46:15 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	statement(t_data *data, int id, char *str)
{
	int	should_print;

	pthread_mutex_lock(&data->dead);
	should_print = !data->is_dead;
	pthread_mutex_unlock(&data->dead);
	if (should_print)
	{
		pthread_mutex_lock(&data->output);
		printf("%lld ", ft_timestamp() - data->creation);
		printf("%d %s\n", id, str);
		pthread_mutex_unlock(&data->output);
	}
}

void	last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat);
	philo->last_meal = ft_timestamp();
	pthread_mutex_unlock(&philo->data->eat);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		if (str[i + 1] == '+' || str [i + 1] == '-')
			return (0);
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((result == 214748364) && (str[i] == '8') && (sign % 2 == 1))
			return (-2147483648);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long long	ft_timestamp(void)
{
	struct timeval	te;
	long long		miliseconds;

	gettimeofday(&te, NULL);
	miliseconds = ((te.tv_sec * 1000) + te.tv_usec / 1000);
	return (miliseconds);
}
