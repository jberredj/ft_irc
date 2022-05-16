/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nullptr_t.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 14:22:19 by jberredj          #+#    #+#             */
/*   Updated: 2022/05/16 01:59:26 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPTR_T_HPP
# define NULLPTR_T_HPP
namespace ft
{
	class Nullptr
	{
	public:
		Nullptr(void);
		Nullptr(const Nullptr &src);
		~Nullptr(void);
		Nullptr	operator=(const Nullptr &rhs);

		template<class T>
		operator T*() const { return 0; }

		template<class C, class T>
		operator T C::*() const { return 0; } 

	private:
	   void operator&() const;
	};
	extern const Nullptr null_ptr;
}
#endif