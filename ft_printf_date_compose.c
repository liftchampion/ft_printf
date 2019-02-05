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

//TODO use ft_S_printf
int		ft_printf_date_compose(t_arg_data *ad, void* arg, t_string **str) // TODO check wdth/prec
{
	t_date *dt;
	long int n;
	char buf[50];
	char use_year;

	ft_bzero(buf, 50);
	if (!(dt = (t_date*)malloc(sizeof(t_date))))
		return (0);
	n = *(long int*)arg;
	*dt = (t_date){1970, 0, 1, UTC, 0, 0};
	WHILE_TRUE(ft_upd_year(dt, &n));
	WHILE_TRUE(ft_upd_month(dt, &n));
	WHILE_TRUE(ft_upd_day(dt, &n));
	WHILE_TRUE(n >= 0 ? ft_add_hour(dt, &n) : ft_sub_hour(dt, &n));
	WHILE_TRUE(n >= 0 ? ft_add_minute(dt, &n) : ft_sub_minute(dt, &n));
	WHILE_TRUE(n >= 0 ? ft_add_second(dt, &n) : ft_sub_second(dt, &n));
	if (ad->alt && ((use_year = (FT_ABS(*(long*)arg - ad->prcsn) > HALF_YEAR)) + 1))
		ft_printf(ft_strcat(ft_strcat(buf, "%s %2d "), use_year ? "%5d" : "%02d:%02d"),
				months[dt->mth], dt->day, use_year ? dt->year : dt->hr, dt->min);
	/*ft_strcat(buf, )
	if (!ad->alt && ad->prcsn == 1)
		ft_printf("%d", dt->year);*/
	//ft_printf("%d.%d.%d %d:%d:%d\n", dt->year, dt->mth, dt->day, dt->hr, dt->min, dt->sec);
	return (1);
}