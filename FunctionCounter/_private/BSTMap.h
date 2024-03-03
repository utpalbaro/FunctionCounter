#ifndef BSTMAP_H
#define BSTMAP_H

#include <cstring>

namespace td
{

    template <typename T1, typename T2>
    struct Pair
    {
        T1 first;
        T2 second;
    };


    template <typename Container, typename Item>
    class iterator
    {
    private:
        // Container can change if you assign to some other thing
        Container* _container;
        // Item will keep changing for each value
        Item* _item;

    public:
        iterator(Container* container, Item* item);

        iterator& operator ++ ();
        iterator operator ++ (int);    // post increment
        Item& operator -> ();
        Item& operator * ();
        bool operator == (const iterator& other) const;
        bool operator != (const iterator& other) const;
    };


    template<typename Container, typename Item>
    inline iterator<Container, Item>::iterator(Container* container, Item* item) :
        _container(container), _item(item)
    {
    }

    template<typename Container, typename Item>
    inline iterator<Container, Item>& iterator<Container, Item>::operator++()
    {
        return _container->_next(*this);
    }

    template<typename Container, typename Item>
    inline iterator<Container, Item> iterator<Container, Item>::operator++(int)
    {
        // Post fix returns a temp iterator, similar to i++;
        iterator<Container, Item> temp = _container->_next(*this);
        return temp;
    }

    template<typename Container, typename Item>
    inline Item& iterator<Container, Item>::operator->()
    {
        return *_item;
    }

    template<typename Container, typename Item>
    inline Item& iterator<Container, Item>::operator*()
    {
        return *_item;
    }

    template<typename Container, typename Item>
    inline bool iterator<Container, Item>::operator==(const iterator& other) const
    {
        return _container == other._container && _item == other._item;
    }

    template<typename Container, typename Item>
    inline bool iterator<Container, Item>::operator!=(const iterator& other) const
    {
        return !(*this == other);
    }


    template <typename KEY, typename VALUE>
    class BSTMap
    {
    private:
        struct Node
        {
            KEY _key;
            VALUE _value;

            Node* _left;
            Node* _right;

        public:
            Node(const KEY& key, const VALUE& value) : _key(key), _value(value),
                _left(nullptr), _right(nullptr)
            { }
        };

    private:
        Node* _root;
        size_t _size;

    public:
        BSTMap();
        bool insert(const KEY& key, const VALUE& value);
        VALUE& operator []      (const KEY& key);
        void clear();

        bool find(const KEY& key) const;
        size_t size() const;
        void getData(void* data, const size_t count) const;

    private:
        Node* _create(const KEY& key, const VALUE& value);
        void _delete(Node*& node);
        bool _insert(Node*& node, const KEY& key, const VALUE& value);
        VALUE& _getOrCreate(Node*& node, const KEY& key);
        bool _find(Node* node, const KEY& key) const;
        void _getData(Node* node, char* buff, size_t& pos, const size_t buffSize) const;
    };

    template<typename KEY, typename VALUE>
    inline BSTMap<KEY, VALUE>::BSTMap() : _root(nullptr), _size(0)
    {
    }

    template<typename KEY, typename VALUE>
    inline bool BSTMap<KEY, VALUE>::insert(const KEY& key, const VALUE& value)
    {
        return _insert(_root, key, value);
    }

    template<typename KEY, typename VALUE>
    inline bool BSTMap<KEY, VALUE>::find(const KEY& key) const
    {
        // Tree is empty, return false
        return _find(_root, key);
    }

    template<typename KEY, typename VALUE>
    inline VALUE& BSTMap<KEY, VALUE>::operator[](const KEY& key)
    {
        return _getOrCreate(_root, key);
    }

    template<typename KEY, typename VALUE>
    inline void BSTMap<KEY, VALUE>::clear()
    {
        _delete(_root);
    }

    template<typename KEY, typename VALUE>
    inline size_t BSTMap<KEY, VALUE>::size() const
    {
        return _size;
    }

    template<typename KEY, typename VALUE>
    inline void BSTMap<KEY, VALUE>::getData(void* data, const size_t count) const
    {
        size_t pos = 0;
        auto buff = static_cast<char*>(data);
        const size_t buffSize = count * (sizeof(KEY) + sizeof(VALUE));

        _getData(_root, buff, pos, buffSize);
    }

    template<typename KEY, typename VALUE>
    inline bool BSTMap<KEY, VALUE>::_insert(Node*& node, const KEY& key, const VALUE& value)
    {
        bool success = false;
        if (!node)
        {
            node = _create(key, value);
            success = true;
        }
        else if (node->_key == key)
        {
            success = false;
        }
        else if (key < node->_key)
            success = _insert(node->_left, key, value);
        else
            success = _insert(node->_right, key, value);

        return success;
    }

    template<typename KEY, typename VALUE>
    inline bool BSTMap<KEY, VALUE>::_find(Node* node, const KEY& key) const
    {
        if (!node)
            return false;

        if (node->_key == key)
            return true;
        else if (key < node->_key)
            return _find(node->_left, key);
        else
            return _find(node->_right, key);
    }

    template<typename KEY, typename VALUE>
    inline void BSTMap<KEY, VALUE>::_getData(Node* node, char* buff, size_t& pos, const size_t buffSize) const
    {
        if (!node)
            return;

        if (pos >= buffSize)
            return;

        _getData(node->_left, buff, pos, buffSize);

        memcpy(buff + pos, &node->_key, sizeof(KEY));
        pos += sizeof(KEY);
        memcpy(buff + pos, &node->_value, sizeof(VALUE));
        pos += sizeof(VALUE);

        _getData(node->_right, buff, pos, buffSize);

    }

    template<typename KEY, typename VALUE>
    inline typename BSTMap<KEY, VALUE>::Node* BSTMap<KEY, VALUE>::_create(const KEY& key, const VALUE& value)
    {
        ++_size;
        return new Node(key, value);
    }

    template<typename KEY, typename VALUE>
    inline void BSTMap<KEY, VALUE>::_delete(Node*& node)
    {
        if (!node)
            return;

        _delete(node->_left);
        _delete(node->_right);

        delete node;
        node = nullptr;
        --_size;
    }

    template<typename KEY, typename VALUE>
    inline VALUE& BSTMap<KEY, VALUE>::_getOrCreate(Node*& node, const KEY& key)
    {
        if (!node)
        {
            node = _create(key, VALUE());
            return node->_value;
        }
        else if (node->_key == key)
            return node->_value;
        else if (key < node->_key)
            return _getOrCreate(node->_left, key);
        else
            return _getOrCreate(node->_right, key);
    }

}

#endif // !BSTMAP_H