#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "Utils.hpp"

//? Std::list funziona utilizzando le "Doubly linked list". Cosa sono? Sono liste linkate che utilizzano DUE NODI.
//? Nelle SINGLE LINKED LIST, ogni nodo contiene due parti, ovvero i DATI ed un PUNTATORE AL PROSSIMO NODO
//? Tuttavia, la std::list è BIDIREZIONALE, pertanto, avremo bisogno di DUE NODI, uno che punta al nodo SUCCESSIVO ed uno che punta al nodo PRECEDENTE!

namespace ft {

    template <typename Spe, typename node_type>
    class lstIte {
        protected:
            //* Al nodo possono accedere solo le classi che ereditano
            node_type						*_node;
            lstIte(node_type *src);

        public:
            typedef Spe						value_type;
            typedef ptrdiff_t				difference_type;
            typedef value_type&				reference;
            typedef value_type*				pointer;

            lstIte(void);
            lstIte(const lstIte &src);
            virtual ~lstIte(void);
            lstIte	&operator=(lstIte const &rhs);

            template <class U> bool	operator==(const lstIte<U, node_type> &rhs) const;
            template <class U> bool	operator!=(const lstIte<U, node_type> &rhs) const;

            lstIte		&operator++(void);
            lstIte		operator++(int);
            lstIte		&operator--(void);
            lstIte		operator--(int);

            reference	operator*(void) const;
            pointer		operator->(void) const;

            //? Questa roba proprio non sono riuscito a capire cosa cazzo faccia :/
            //? Pare sia un getter per il value di node, ma non capisco se sia un overload...
            operator lstIte<const Spe, node_type>(void) const {
                return lstIte<const Spe, node_type>(this->_node);
            }

            //* La classe list che andremo a creare deve accedere ai NODI!
            template <class, class>
            friend class list;

            template <class, class>
            friend class lstIte;

    };

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type>::lstIte(void) : _node(NULL) { return ; }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type>::lstIte(node_type *src) {
        this->_node = src;
    }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type>::lstIte(const lstIte &src) { *this = src; }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type>::~lstIte(void) { return ; }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type> &lstIte<Spe, node_type>::operator=(const lstIte &rhs) {
        if (this == &rhs)
            return (*this);
        this->_node = rhs._node;
        return (*this);
    }

    template <typename Spe, typename node_type> template <class U>
    bool	lstIte<Spe, node_type>::operator==(const lstIte<U, node_type> &rhs) const {
        return (this->_node == rhs._node);
    }

    template <typename Spe, typename node_type> template <class U>
    bool	lstIte<Spe, node_type>::operator!=(const lstIte<U, node_type> &rhs) const {
        return (this->_node != rhs._node);
    }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type> &lstIte<Spe, node_type>::operator++(void) {
        this->_node = this->_node->next;
        return (*this);
    }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type> lstIte<Spe, node_type>::operator++(int) {
        lstIte<Spe, node_type>	tmp(*this);
        ++(*this);
        return (tmp);
    }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type>& lstIte<Spe, node_type>::operator--(void) {
        this->_node = this->_node->prev;
        return (*this);
    }

    template <typename Spe, typename node_type>
    lstIte<Spe, node_type> lstIte<Spe, node_type>::operator--(int) {
        lstIte<Spe, node_type>	tmp(*this);
        --(*this);
        return (tmp);
    }

    template <typename Spe, typename node_type>
    typename lstIte<Spe, node_type>::reference lstIte<Spe, node_type>::operator*(void) const {
        return (this->_node->data);
    }

    template <typename Spe, typename node_type>
    typename lstIte<Spe, node_type>::pointer lstIte<Spe, node_type>::operator->(void) const {
        return &this->operator*();
    }

}
#endif