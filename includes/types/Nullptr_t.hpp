/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nullptr_t.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:22:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 17:22:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPTR_T_HPP
# define NULLPTR_T_HPP
namespace ft
{
	class Nullptr
	{
	public:
		// Constructors dans destructor
				Nullptr(void);
				Nullptr(const Nullptr& src);
				~Nullptr(void);
		// Operators
		Nullptr	operator=(const Nullptr& rhs);
		template<class T>
				operator T*() const { return 0; }

		template<class C, class T>
				operator T C::*() const { return 0; } 

	private:
		// Operators
	   void	operator&() const;
	};
	
	// null_ptr is a global object working kinda c++11 nullptr
	// an only be used by precising namespace ft, in order to prevent conflict
	// with any kind of null_ptr that could exists
	extern const Nullptr null_ptr;
}

#endif