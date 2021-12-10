#ifndef MAP_HPP
# define MAP_HPP

# include "Map_interface.hpp"

namespace ft {
    template <class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::map(const key_compare &comp, const allocator_type &alloc) : \
            _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        return ;
    }

    template <class Key, class T, class Compare, class Alloc> template <class Ite>
    map<Key, T, Compare, Alloc>::map(
        typename ft::enable_if<!std::numeric_limits<Ite>::is_integer, Ite>::type first,
        Ite last, const key_compare &comp, const allocator_type &alloc) : \
            _data(), _key_cmp(comp), _alloc(alloc), _size(0) {
        this->_data = new node_type;
        this->_create_data_it(first, last);
    }

    template<class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::map(map const &src) : \
            _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0) {
        this->_data = new node_type;
        *this = src;
    }

    template<class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>::~map(void) {
        this->clear();
        delete this->_data;
    }

    template<class Key, class T, class Compare, class Alloc>
    map<Key, T, Compare, Alloc>&
    map<Key, T, Compare, Alloc>::operator=(map const &rhs) {
        if (this == &rhs)
            return (*this);
        this->clear();
        this->_create_data_it(rhs.begin(), rhs.end());
        return (*this);
    }

    //* ######################## Iteratori ########################

    //? Gli iteratori sono veramente semplici, il valore alla fine è sempre quello del nodo più a destra (che è il più grande)
    //? Viceverse, il primo sarà quello più a sinistra
    
    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::begin(void) {
        return iterator(farLeft(this->_data));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator
    map<Key, T, Compare, Alloc>::begin(void) const {
        return const_iterator(farLeft(this->_data));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::end(void) {
        return iterator(farRight(this->_data));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator
    map<Key, T, Compare, Alloc>::end(void) const {
        return const_iterator(farRight(this->_data));
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator
    map<Key, T, Compare, Alloc>::rbegin(void) {
        return reverse_iterator(this->end());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator
    map<Key, T, Compare, Alloc>::rbegin(void) const {
        return const_reverse_iterator(this->end());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator
    map<Key, T, Compare, Alloc>::rend(void) {
        return reverse_iterator(this->begin());
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator
    map<Key, T, Compare, Alloc>::rend(void) const {
        return const_reverse_iterator(this->begin());
    }

    //* ######################## Capacità ########################

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type
    map<Key, T, Compare, Alloc>::size(void) const {
        return (this->_size);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type
    map<Key, T, Compare, Alloc>::max_size(void) const {
        return (this->_max_size);
    }

    template<class Key, class T, class Compare, class Alloc>
    bool	map<Key, T, Compare, Alloc>::empty(void) const {
        return (this->_size == 0 ? true : false);
    }

    //* ######################## Accesso Elementi ########################

    //? Inserts value_type(key, T()) if the key does not exist. 
    //? This function is equivalent to return insert(std::make_pair(key, T())).first->second;

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type&
    map<Key, T, Compare, Alloc>::operator[](const key_type &k) {
        return (this->insert(value_type(k, mapped_type()))).first->second;
    }

    //* ######################## Modificatori ########################

    template<class Key, class T, class Compare, class Alloc>
    ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
    map<Key, T, Compare, Alloc>::insert(const value_type &val) {
        ft::pair<iterator, bool> res;

        //? Se esiste già non lo aggiunge, semplicemente returna quello già presente
        //? Per altro, dato che count returna praticamente solo 1 o 0 possiamo usarlo come flag ed è molto adorabile
        res.second = !this->count(val.first);
        if (res.second == true)
            this->_btree_add(new node_type(val));
        res.first = this->find(val.first);
        return (res);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::insert(iterator position, const value_type &val) {
        //! Qui castiamo a void di fatto sopprimendo position, non ci serve.
        //? btree_add contiene già l'algoritmo per inserire l'elemento nella posizione giusta
        static_cast<void>(position); 
        return this->insert(val).first;
    }

    template<class Key, class T, class Compare, class Alloc> template <class Ite>
    void	map<Key, T, Compare, Alloc>::insert(Ite first, Ite last) {
        while (first != last)
            this->insert(*first++);
    }

    //? Possiamo eliminare un nodo passando una posizione, una chiave o un range

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::erase(iterator position) {
        this->erase(position++, position);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type
    map<Key, T, Compare, Alloc>::erase(const key_type &k) {
        iterator element = this->find(k);

        if (element == this->end())
            return (0);
        this->_btree_rm(element._node);
        return (1);
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last) {
        while (first != last)
            this->_btree_rm((first++)._node);
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::swap(map &x) {
        map tmp;

        tmp._cpy_content(x);
        x._cpy_content(*this);
        this->_cpy_content(tmp);
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::clear(void) {
        node_ptr ghost = this->end()._node;

        if (this->_size == 0)
            return ;
        ghost->parent->right = NULL;
        this->_btree_clear(this->_data);
        this->_data = ghost;
        this->_size = 0;
    }

    //* ######################## Osservatori ########################

    //? Returna la funziona che compara le chiavi, semplicemente
    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::key_compare
    map<Key, T, Compare, Alloc>::key_comp(void) const {
        return (key_compare());
    }

    //! Questo value_compare è un FUNCTOR (o Funtore), sono OGGETTI che possono essere trattati come FUNZIONI
    //? Il funtore non è altro che una classe che esegue un overload sull'operatore (), di fatto rendendo quell'oggetto a tutti gli effetti una funzione
    //? Questa è una delle tante figate del generic programming, in quanto almeno in teoria come programmatori siamo in grado di ASTRARRE qualsiasi cosa
    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::value_compare
    map<Key, T, Compare, Alloc>::value_comp(void) const {
        return (value_compare(key_compare()));
    }

    //* ######################## Operazioni ########################

    //? Trova un elemento che abbia la key == k, ne abbiamo una versione const ed una non const

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::find(const key_type &k) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (this->_key_eq(it->first, k))
                break ;
            ++it;
        }
        return (it);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator
    map<Key, T, Compare, Alloc>::find(const key_type &k) const {
        const_iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (this->_key_eq(it->first, k))
                break ;
            ++it;
        }
        return (it);
    }

    //? Count returna il numero di elementi che matchano con una chiave specifica

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::size_type
    map<Key, T, Compare, Alloc>::count(const key_type &k) const {
        const_iterator	it = this->begin(), ite = this->end();
        size_type		res = 0;

        while (it != ite)
        {
            if (this->_key_eq((it++)->first, k))
            {
                ++res;
                break ; //! Qui in realtà bisogna breakare, perchè Map non può avere la stessa chiave più di una volta
            }
        }
        return (res);
    }

    //? Lower Bound returna il primo elemento che sia >= alla key passata come parametro

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (!this->_key_cmp(it->first, k))
                break;
            ++it;
        }
        return (it);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator
    map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) const {
        const_iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (!this->_key_cmp(it->first, k))
                break;
            ++it;
        }
        return (it);
    }

    //? UPPER BOUND FA PRATICAMENTE LA STESSA IDENTICA COSA CIOE' COS

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::iterator
    map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) {
        iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (this->_key_cmp(k, it->first))
                break;
            ++it;
        }
        return (it);
    }

    template<class Key, class T, class Compare, class Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator
    map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) const {
        const_iterator it = this->begin(), ite = this->end();

        while (it != ite)
        {
            if (this->_key_cmp(k, it->first))
                break;
            ++it;
        }
        return (it);
    }

    //? Allora, in teoria equal range returna il range di elementi che hanno LA STESSA CHIAVE
    //! Il problema è che, trattandosi di una mappa, questo range conterrà al massimo un elemento...
    //! E allora dico io perchè cazzo creare una funzione del genere, vabbè

    template<class Key, class T, class Compare, class Alloc>
    ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator>
    map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const {
        pair<const_iterator, const_iterator> res;

        res.first = this->lower_bound(k);
        res.second = this->upper_bound(k);
        return (res);
    }

    template<class Key, class T, class Compare, class Alloc>
    ft::pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator>
    map<Key, T, Compare, Alloc>::equal_range(const key_type &k) {
        pair<iterator, iterator> res;

        res.first = this->lower_bound(k);
        res.second = this->upper_bound(k);
        return (res);
    }

    //* ######################## Metodi Privati ########################

    template<class Key, class T, class Compare, class Alloc> template <class Ite>
    void	map<Key, T, Compare, Alloc>::_create_data_it(Ite first, Ite last) {
        this->insert(first, last);
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::_create_data(size_type size, const value_type &val) {
        (void)size; (void)val;
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::_cpy_content(map &src) {
        this->clear();
        node_ptr tmp = this->_data;

        this->_data = src._data;
        this->_key_cmp = src._key_cmp;
        this->_alloc = src._alloc;
        this->_size = src._size;
        src._data = tmp; src._size = 0;
        tmp = NULL;
    }

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::_btree_clear(node_ptr node) {
        if (node == NULL)
            return ;
        this->_btree_clear(node->left);
        this->_btree_clear(node->right);
        delete node;
    }

    //? I prossimi due metodi sono importanti, in quanto vanno a modificare il binary tree ed hanno bisogno di algoritmi particolari
    //? I nodi aggiunti vanno SEMPRE SULLA LEAF (quindi nel punto più basso dell'albero) e prima di aggiungerli bisogna confrontarli
    //? Con tutti gli altri nodi partendo dalla ROOT, decidendo quindi se spostarsi a destra o sinistra.

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::_btree_add(node_ptr newNode) {
        node_ptr	*parent = &this->_data;
        node_ptr	*node = &this->_data;
        node_ptr	ghost = farRight(this->_data);
        bool		side_left = -1;

        ++this->_size;
        while (*node && *node != ghost)
        {
            parent = node;
            side_left = this->_key_cmp(newNode->data.first, (*node)->data.first);
            node = (side_left ? &(*node)->left : &(*node)->right);
        }
        if (*node == NULL)
        {
            newNode->parent = (*parent);
            *node = newNode;
        }
        else
        {
            *node = newNode;
            newNode->parent = ghost->parent;
            ghost->parent = farRight(newNode);
            farRight(newNode)->right = ghost;
        }
    }

    //? Per il delete invece c'è bisogno di effettuare un REPLACE, bisogna prendere il NODO PIU' IN BASSO E PIU' A DESTRA
    //? E sostituirlo con il nodo che si desidera eliminare, dopodichè possiamo eliminarlo tranquillamente.

    template<class Key, class T, class Compare, class Alloc>
    void	map<Key, T, Compare, Alloc>::_btree_rm(node_ptr rmNode) {
        node_ptr	replaceNode = NULL;
        node_ptr	*rmPlace = &this->_data;

        --this->_size;
        if (rmNode->parent)
            rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
        if (rmNode->left == NULL && rmNode->right == NULL)
            ;
        else if (rmNode->left == NULL)
            replaceNode = rmNode->right;
        else
        {
            replaceNode = farRight(rmNode->left);
            if (replaceNode != rmNode->left)
                if ((replaceNode->parent->right = replaceNode->left))
                    replaceNode->left->parent = replaceNode->parent;
        }
        if (replaceNode)
        {
            replaceNode->parent = rmNode->parent;
            if (rmNode->left && rmNode->left != replaceNode)
            {
                replaceNode->left = rmNode->left;
                replaceNode->left->parent = replaceNode;
            }
            if (rmNode->right && rmNode->right != replaceNode)
            {
                replaceNode->right = rmNode->right;
                replaceNode->right->parent = replaceNode;
            }
        }
        *rmPlace = replaceNode;
        delete rmNode;
    }

    //? Reminder che _key_cmp è la funzione che sorta le chiavi
    template<class Key, class T, class Compare, class Alloc>
    bool
    map<Key, T, Compare, Alloc>::_key_eq(const key_type &k1, const key_type &k2) const {
        return (!this->_key_cmp(k1, k2) && !this->_key_cmp(k2, k1));
    }

    template <class Key, class T, class Compare, class Alloc>
    const typename map<Key, T, Compare, Alloc>::size_type
    map<Key, T, Compare, Alloc>::_max_size =
        std::numeric_limits<difference_type>::max() / (sizeof(node_type) / 2 ?: 1);

    //* ######################## Non-Member Overloads ########################

    template <class Key, class T, class Compare, class Alloc>
    bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator< (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator> (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
        x.swap(y);
    }

    //* ######################## Other ########################

    //? Definiamo il FUNTORE per value_compare
    template <class Key, class T, class Compare, class Alloc>
    class	map<Key, T, Compare, Alloc>::value_compare {
    public:
        Compare comp;
        value_compare(Compare c) : comp(c) { };
        
        bool	operator()(const value_type &x, const value_type &y) const {
            return comp(x.first, y.first);
        }
    };
    
}
#endif