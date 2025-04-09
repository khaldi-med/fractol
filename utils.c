/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhald <mohkhald@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:05:10 by mohkhald          #+#    #+#             */
/*   Updated: 2025/04/08 20:05:10 by mohkhald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
 * @brief Change the color scheme
 * 
 * Cycles through available color schemes (1-3)
 * 
 * @param fractol Pointer to the main fractol structure
 */
void	change_color_scheme(t_fractol *fractol)
{
	fractol->color_scheme = (fractol->color_scheme % 3) + 1;
	render_fractol(fractol);
}


/**
 * @brief Change iterations
 * 
 * Increases or decreases max iterations within reasonable bounds
 * 
 * @param fractol Pointer to the main fractol structure
 * @param increase 1 to increase, 0 to decrease
 */
void	change_iterations(t_fractol *fractol, int increase)
{
	if (increase && fractol->max_iterations < 1000)
		fractol->max_iterations += 10;
	else if (!increase && fractol->max_iterations > 10)
		fractol->max_iterations -= 10;
	render_fractol(fractol);
}

/**
 * @brief Check if a character is a whitespace
 * 
 * @param c The character to check
 * @return int 1 if whitespace, 0 otherwise
 */
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

/**
 * @brief Calculate power for float conversion
 * 
 * @param base The base number
 * @param power The power/exponent
 * @return double The result of base^power
 */
double	ft_pow(double base, int power)
{
	double	result;

	if (power == 0)
		return (1);
	if (power < 0)
		return (1.0 / ft_pow(base, -power));
	
	result = 1.0;
	while (power--)
		result *= base;
	
	return (result);
}

/**
 * @brief Validate if a string has valid float format
 * 
 * Checks that the string contains only digits, an optional
 * decimal point, and an optional leading sign.
 * 
 * @param str The string to check
 * @return int 1 if valid format, 0 otherwise
 */
int	check_float_format(const char *str)
{
	int	i;
	int	has_digits;
	int	decimal_count;

	i = 0;
	has_digits = 0;
	decimal_count = 0;
	
	// Skip whitespace and handle sign
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	
	// Process digits and decimal point
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			has_digits = 1;
		else if (str[i] == '.')
			decimal_count++;
		else
			return (0);
		i++;
	}
	
	// Check final validity conditions
	return (has_digits && decimal_count <= 1);
}

/**
 * @brief Handle the fractional part of a float conversion
 * 
 * @param str The string starting at the decimal point
 * @param value Pointer to the current value to update
 * @return int 0 on success, -1 on failure
 */
static int	handle_fraction(const char *str, double *value)
{
	int		i;
	double	fraction;
	int		decimal_place;

	i = 1;  // Skip the decimal point
	fraction = 0.0;
	decimal_place = 1;
	
	while (str[i] && ft_isdigit(str[i]))
	{
		fraction = fraction * 10 + (str[i] - '0');
		decimal_place *= 10;
		i++;
	}
	
	*value += fraction / decimal_place;
	
	// If we didn't stop at the end of the string, the format is invalid
	if (str[i] != '\0')
		return (-1);
	
	return (0);
}

/**
 * @brief Convert string to double (custom atof)
 * 
 * Handles signs, integers, and decimal fractions.
 * Returns 0.0 for invalid inputs.
 * 
 * @param str The string to convert
 * @return double The converted value
 */
double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	value;

	i = 0;
	sign = 1;
	value = 0.0;
	
	// Skip whitespace
	while (ft_isspace(str[i]))
		i++;
	
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	
	// Parse integer part
	while (str[i] && ft_isdigit(str[i]))
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	
	// Parse fractional part if present
	if (str[i] == '.')
	{
		if (handle_fraction(&str[i], &value) < 0)
			return (0.0);
	}
	else if (str[i] != '\0')
	{
		// Invalid character in the string
		return (0.0);
	}
	
	return (sign * value);
}

/**
 * @brief Check if a string represents a valid parameter
 * 
 * Validates that the string can be converted to a valid float value.
 * 
 * @param str The string to validate
 * @return int 1 if valid, 0 otherwise
 */
int	is_valid_param(char *str)
{
	if (!str)
		return (0);
	
	// Check basic format first
	if (!check_float_format(str))
		return (0);
	
	// Additional checks can be added here if needed
	
	return (1);
}

