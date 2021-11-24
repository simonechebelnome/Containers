#ifndef VECTOR_INTERFACE_HPP
# define VECTOR_INTERFACE_HPP

# include "Iterator.hpp"
# include "Rev_iterator.hpp"
# include "Utils.hpp"

namespace ft {
    template<typename T, typename Allocator = std::allocator<T>>
    class vector {
    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;   
        typedef typename allocator_type::reference			reference;
        typedef typename allocator_type::const_reference	const_reference;
        typedef typename allocator_type::pointer			pointer;
        typedef typename allocator_type::const_pointer		const_pointer;

        typedef ptrdiff_t									difference_type;
        typedef size_t										size_type;

    };
}
#endif