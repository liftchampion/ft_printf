/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehugh-be <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 22:40:21 by ehugh-be          #+#    #+#             */
/*   Updated: 2019/01/27 04:20:43 by ehugh-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_parser.h"
#include "ft_printf.h"

#define DAY 86400
#define UTC 3
#define HALF_YEAR (31556926 / 2)

#define WHILE_TRUE(a) while(a)

typedef struct	s_date
{
	int	year; /// 1970 ?
	char		mth; /// 0 ?
	char		day; ///1
	char 		hr; /// 0 ?
	char 		min; /// 0 ?
	char 		sec; /// 0 ?
}				t_date;

// TODO move to header

static char mts[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
							 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

int ft_upd_year(t_date *dt, long int *n)
{
	if ((*n < (IS_LEAP_YEAR(dt->year) + 365) * DAY && *n >= 0) ||
			(*n > -1 * (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= (IS_LEAP_YEAR(dt->year) + 365) * DAY;
		++dt->year;
		return (1);
	}
	*n += (IS_LEAP_YEAR(dt->year - 1) + 365) * DAY;
	--dt->year;
	return (1);
}

int ft_upd_month(t_date *dt, long int *n)
{
	if ((*n < (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n >= 0) || (*n > -1 *
			(mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY
			&& *n < 0))
		return (0);
	if (*n > 0)
	{
		if (*n < (mts[dt->mth] + (dt->mth==1 && IS_LEAP_YEAR(dt->year))) * DAY)
			return (0);
		*n -= (mts[dt->mth] + (dt->mth==1 && IS_LEAP_YEAR(dt->year))) * DAY;
		if (dt->mth == 11 && !(dt->mth = 0))
			++dt->year;
		else
			++dt->mth;
		return (1);
	}
	if (*n < (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY)
		return (0);
	*n -= (mts[dt->mth] + (dt->mth == 1 && IS_LEAP_YEAR(dt->year))) * DAY;
	if (dt->mth == 0 && (dt->mth = 11))
		--dt->year;
	else
		--dt->mth;
	return (1);
}

int ft_upd_day(t_date *dt, long int *n)
{
	if ((*n < DAY && *n >= 0) || (*n > -1 * DAY && *n < 0))
		return (0);
	if (*n > 0)
	{
		*n -= DAY;
		if (dt->day == mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))
				&& (dt->day = 1))
			if (dt->mth == 11 && !(dt->mth = 0))
				++dt->year;
			else
				++dt->mth;
		else
			++dt->day;
		return (1);
	}
	*n += DAY;
	if (dt->day == 1 && (dt->day = mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
		if (dt->mth == 0 && (dt->mth = 11))
			--dt->year;
		else
			--dt->mth;
	else
		--dt->day;
	return (1);
}

int ft_add_hour(t_date *dt, long int *n)
{
	if (*n < 3600)
		return (0);
	*n -= 3600;
	if (dt->hr == 23 && !(dt->hr = 0))
		if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
									IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
			if (dt->mth == 11 && !(dt->mth = 0))
				++dt->year;
			else
				++dt->mth;
		else
			++dt->day;
	else
		++dt->hr;
	return (1);
}

int ft_sub_hour(t_date *dt, long int *n)
{
	if (*n > -3600)
		return (0);
	*n += 3600;
	if (dt->hr == 0 && (dt->hr = 23))
		if (dt->day == 1 && (dt->day = mts[dt->mth] +
				(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
			if (dt->mth == 0 && (dt->mth = 11))
				--dt->year;
			else
				--dt->mth;
		else
			--dt->day;
	else
		--dt->hr;
	return (1);
}

int ft_add_minute(t_date *dt, long int *n)
{
	if (*n < 60)
		return (0);
	*n -= 60;
	if (dt->min == 59 && !(dt->min = 0))
		if (dt->hr == 23 && !(dt->hr = 0))
			if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
									IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
				if (dt->mth == 11 && !(dt->mth = 0))
					++dt->year;
				else
					++dt->mth;
			else
				++dt->day;
		else
			++dt->hr;
	else
		++dt->min;
	return (1);
}

int ft_sub_minute(t_date *dt, long int *n)
{
	if (*n > -60)
		return (0);
	*n += 60;
	if (dt->min == 00 && (dt->min = 59))
		if (dt->hr == 00 && (dt->hr = 23))
			if (dt->day == 1 && (dt->day = mts[dt->mth] +
					(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
				if (dt->mth == 0 && (dt->mth = 11))
					--dt->year;
				else
					--dt->mth;
			else
				--dt->day;
		else
			--dt->hr;
	else
		--dt->min;
	return (1);
}

int ft_add_second(t_date *dt, long int *n)
{
	if (*n < 1)
		return (0);
	*n -= 1;
	if (dt->sec == 59 && !(dt->sec = 0))
		if (dt->min == 59 && !(dt->min = 0))
			if (dt->hr == 23 && !(dt->hr = 0))
				if (dt->day == mts[dt->mth] + (dt->mth == 1 &&
						IS_LEAP_YEAR(dt->year)) && (dt->day = 1))
					if (dt->mth == 11 && !(dt->mth = 0))
						++dt->year;
					else
						++dt->mth;
				else
					++dt->day;
			else
				++dt->hr;
		else
			++dt->min;
	else
		++dt->sec;
	return (1);
}

int ft_sub_second(t_date *dt, long int *n)
{
	if (*n > -1)
		return (0);
	*n += 1;
	if (dt->sec == 0 && (dt->sec = 59))
		if (dt->min == 0 && (dt->min = 59))
			if (dt->hr == 0 && (dt->hr = 23))
				if (dt->day == 1 && (dt->day = mts[dt->mth] +
									(dt->mth == 1 && IS_LEAP_YEAR(dt->year))))
					if (dt->mth == 0 && (dt->mth = 11))
						--dt->year;
					else
						--dt->mth;
				else
					--dt->day;
			else
				--dt->hr;
		else
			--dt->min;
	else
		--dt->sec;
	return (1);
}

t_date *ft_unix_time_to_date(long int ut)
{
	t_date *dt;

	if (!(dt = (t_date*)malloc(sizeof(t_date))))
		return (0);
	*dt = (t_date){1970, 0, 1, UTC, 0, 0};
	WHILE_TRUE(ft_upd_year(dt, &ut));
	WHILE_TRUE(ft_upd_month(dt, &ut));
	WHILE_TRUE(ft_upd_day(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_hour(dt, &ut) : ft_sub_hour(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_minute(dt, &ut) : ft_sub_minute(dt, &ut));
	WHILE_TRUE(ut >= 0 ? ft_add_second(dt, &ut) : ft_sub_second(dt, &ut));
	return (dt);
}

#include <stdio.h> // TODO delete it

//TODO use ft_S_printf

char *ft_printf_date_compose_get_str(t_date *dt, void *arg, t_arg_data *ad)
{
	char *res;
	char buf[50];
	char use_year;

	ft_bzero(buf, 50);
	res = ft_memalloc(1000); // TODO just temporary for sprintf
	if (ad->alt &&
		((use_year = (FT_ABS(*(long*)arg - ad->prcsn) > HALF_YEAR)) + 1)) 			// TODO use ft_sprintf
		sprintf(res, ft_strcat(ft_strcat(buf, "%s %2d "), use_year ? "%5d" :
		"%02d:%02d"), months[dt->mth], dt->day, use_year ? dt->year : dt->hr,
				dt->min);
	else if (ad->size == DEFAULT || ad->size == LONG)
	{
		ad->size == DEFAULT ? sprintf(res, "%4d-%02d-%02d %02d:%02d", dt->year,
				dt->mth, dt->day, dt->hr, dt->min) :
				sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", dt->year,
				dt->mth, dt->day, dt->hr, dt->min, dt->sec);
	}
	else if (ad->size == SHORT || ad->size == CHAR)
	{
		ad->size == SHORT ? sprintf(res, "%4d-%02d-%02d", dt->year, dt->mth,
				dt->day) : sprintf(res, "%4d-%02d", dt->year, dt->mth);
	}
	return (res);
}

int		ft_printf_date_compose(t_arg_data *ad, void* arg, t_string **str)
{
	t_date *dt;
	char *res;

	dt = ft_unix_time_to_date(*(long int*)arg);
	res = ft_printf_date_compose_get_str(dt, arg, ad);
	if (!ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ft_strlen(res), ad->ac);
	ft_string_push_back_s(str, res);
	if (ad->l_a)
		ft_string_push_back_n_c(str, ad->wdth - ft_strlen(res), ad->ac);
	return (1);
}