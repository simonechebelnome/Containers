#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

namespace ft {

    //* L'implementazione è identica a quella di list_iterator
    template <typename T, typename node_type>
    class mapIte {
        protected:
            node_type						*_node;
            mapIte(node_type *src);

        public:
            typedef T						value_type;
            typedef ptrdiff_t				difference_type;
            typedef value_type&				reference;
            typedef value_type*				pointer;

            mapIte(void);
            mapIte(const mapIte &src);
            virtual ~mapIte(void);
            mapIte	&operator=(mapIte const &rhs);

            template <class U> bool	operator==(const mapIte<U, node_type> &rhs) const;
            template <class U> bool	operator!=(const mapIte<U, node_type> &rhs) const;

            mapIte		&operator++(void);
            mapIte		operator++(int);
            mapIte		&operator--(void);
            mapIte		operator--(int);

            reference	operator*(void) const;
            pointer		operator->(void) const;

            operator mapIte<const T, node_type>(void) const {
                return mapIte<const T, node_type>(this->_node);
            }

            template <class, class, class, class>
            friend class map;

            template <class, class>
            friend class mapIte;

    };
}

#endif 