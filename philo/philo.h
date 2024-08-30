/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasapog <tkasapog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:31:48 by tkasapog          #+#    #+#             */
/*   Updated: 2024/08/30 16:28:49 by tkasapog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	int					eat;
	long long			last_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_t			threads;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	char				**argv;
	int					philos_num;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					is_dead;
	int					all_eat;
	int					all_ate;
	long long			creation;
	t_philo				*philo;
	pthread_mutex_t		eat;
	pthread_mutex_t		*fork;
	pthread_mutex_t		output;
	pthread_mutex_t		dead;
}	t_data;

//main.c
void		*philo_cycle(void *arg);
//acitivities.c
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
int			philo_eat(t_philo *philo);
void		initial_forks(t_philo *philo);
//initialize.c
int			init_data(t_data *data);
pthread_t	init_philos(t_data *data);
int			init_threads(t_data *data);
void		cleanup_threads(t_data *data);
//helpers.c
void		statement(t_data *data, int id, char *str);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
long long	ft_timestamp(void);
void		last_meal(t_philo *philo);
//checks.c
void		*health_check(void *arg);
int			check_death(t_data *data, int i);
bool		check_args(char **arg);
int			check_end_conditions(t_philo *philo);

#endif
