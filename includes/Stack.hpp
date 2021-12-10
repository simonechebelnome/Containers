#ifndef STACK_HPP
# define STACK_HPP

# include "Utils.hpp"
# include "Vector.hpp"

//? Stack è un container adapter (ovvero, per funzionare ha bisogno di ereditare da un altro container, in questo caso Vector)
//? Emula un sistema LIFO (last-in, first-out), ovvero il primo elemento che viene inserito è quello che verrà processato per  ultimo

namespace ft {
    template <typename T, typename Container = ft::vector<T> >
    class stack {
    public:
        typedef T           value_type;
        typedef Container   container_type;
        typedef size_t      size_type;

    protected:
        typedef value_type&				reference;
        typedef const value_type&		const_reference;
        typedef value_type*				pointer;
        typedef const value_type*		const_pointer;

        container_type	c; //* Avremo bisogno di chiamare i metodi del nostro container, quindi ne creaiamo un'istanza

        stack(const stack &src) : c(src.c) {};
        stack	&operator=(stack const &rhs) { this->c = rhs.c; };
    
    //* ##### Funzioni Membro #####
    public:

        explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {};
        virtual ~stack(void) {};

        //? Banalmente, utilizziamo i metodi di Vector

        size_type	size(void) const { return c.size(); };
        bool		empty(void) const { return c.empty(); };

        reference			top(void) { return c.back(); };
        const_reference		top(void) const { return c.back(); };
        void				push(const value_type &val) { c.push_back(val); };
        void 				pop(void) { c.pop_back(); };

        friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c == rhs.c);
        }

        friend bool operator< (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c < rhs.c);
        }
    };

    //* ##### Non-member overloads #####

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator> (const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (rhs < lhs);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return !(lhs < rhs);
    }
}
#endif