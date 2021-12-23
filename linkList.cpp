#include <iostream>
#include <exception>

using namespace std;

template <typename T>
class Node
{
public:
    T Data;
    Node<T> *next = NULL;
    Node<T> *prev = NULL;
    Node() {}
    Node(T data)
    {
        this->Data = data;
    }
    void print()
    {
        cout << "Data: " << Data << "  \t";
        cout << "name: " << this << "  \t";
        cout << "Next: " << next << "        \t";
        cout << "Prev: " << prev << "";
    }
};

template <typename T>
class LinkList
{
private:
    int _size = 0;
    Node<T> *_first = NULL;
    Node<T> *_last = NULL;
    bool _circular = false;

    Node<T> *findNodeByIndex(int index)
    {
        if (_size == 0)
            return NULL;
        if (index <= _size / 2)
        {
            int i = 0;
            Node<T> *node = _first;
            while (node != NULL)
            {
                if (i == index)
                    return node;
                node = node->next;
                i++;
            }
        }
        else
        {
            int i = _size - 1;
            Node<T> *node = _last;
            while (node != NULL)
            {
                if (i == index)
                    return node;
                node = node->prev;
                i--;
            }
        }
    }

public:
    LinkList() {}
    LinkList(initializer_list<T> _Ilist)
    {
        for (int i = 0; i < _Ilist.size(); i++)
            push_back(_Ilist.begin()[i]);
    }
    ~LinkList()
    {
        clear();
    }

    T first()
    {
        if (_size == 0)
            return NULL;
        if (_size == 0)
            return _first->Data;
    }
    T last()
    {
        if (_size == 0)
            return NULL;
        return _last->Data;
    }
    T at(int index)
    {
        if (_size == 0)
            throw std::logic_error("The list link is empty. But you tried to get some.");
        if (!_circular && (index < 0 || index > _size - 1))
            throw std::out_of_range("The index in the operator[] must be between 0 and (size-1).");
        if (_circular)
            index = index % _size;
        Node<T> *node = findNodeByIndex(index);
        return node->Data;
    }
    T &operator[](int index)
    {
        if (_size == 0)
            throw std::logic_error("The list link is empty. But you tried to get some.");
        if (!_circular && (index < 0 || index > _size - 1))
            throw std::out_of_range("The index in the operator[] must be between 0 and (size-1).");
        if (_circular)
            index = index % _size;
        Node<T> *node = findNodeByIndex(index);
        return (node->Data);
    }
    bool Set(int index, T element)
    {
        if (_size == 0)
            return false;
        if (!_circular && (index < 0 || index > _size - 1))
            return false;
        if (_circular)
            index = index % _size;
        Node<T> *node = findNodeByIndex(index);
        node.Data = element;
    }

    void push_first(T element)
    {
        Node<T> *temp = new Node<T>(element);
        if (_size == 0)
        {
            _first = temp;
            _last = temp;
        }
        else
        {
            temp->next = _first;
            _first->prev = temp;
            _first = temp;
        }
        _size++;
    }
    void push_back(T element)
    {
        Node<T> *temp = new Node<T>(element);
        if (_size == 0)
        {
            _first = temp;
            _last = temp;
        }
        else
        {
            temp->prev = _last;
            _last->next = temp;
            _last = temp;
        }
        _size++;
    }
    void push_index(int index, T element)
    {
        if (_size == 0)
        {
            Node<T> *temp = new Node<T>(element);
            _first = temp;
            _last = temp;
            _size++;
        }
        else if (index == 0)
            push_first(element);
        else if (index == _size)
            push_back(element);
        else if (index > 0 && index < _size)
        {
            Node<T> *temp = new Node<T>(element);
            int i = 0;
            Node<T> *node = _first;
            while (node != NULL)
            {
                if (i == index)
                {
                    temp->prev = node->prev;
                    node->prev->next = temp;
                    node->prev = temp;
                    temp->next = node;
                    _size++;
                    break;
                }
                node = node->next;
                i++;
            }
        }
        else if (_circular)
            push_index(index % _size, element);
    }

    T pop_first()
    {
        if (_size == 0)
            return NULL;
        T data;
        if (_size == 1)
        {
            data = _first->Data;
            delete _first;
            _first = NULL;
            _last = NULL;
        }
        else
        {
            Node<T> *temp = _first;
            data = _first->Data;
            _first = _first->next;
            _first->prev = NULL;
            delete temp;
        }
        _size--;
        return data;
    }
    T pop_back()
    {
        if (_size == 0)
            return NULL;
        T data;
        if (_size == 1)
        {
            data = _first->Data;
            delete _first;
            _first = NULL;
            _last = NULL;
        }
        else
        {
            Node<T> *temp = _last;
            data = _last->Data;
            _last = _last->prev;
            _last->next = NULL;
            delete temp;
        }
        _size--;
        return data;
    }
    T pop_index(int index)
    {
        if (_size == 0)
            return NULL;
        else if (index == 0)
            return pop_first();
        else if (index == _size - 1)
            return pop_back();
        else if (index > 0 && index < _size)
        {
            T data;
            int i = 0;
            Node<T> *node = _first;
            while (node != NULL)
            {
                if (i == index)
                {
                    data = node->Data;
                    node->prev->next = node->next;
                    node->next->prev = node->prev;
                    delete node;
                    break;
                }
                node = node->next;
                i++;
            }
            _size--;
            return data;
        }
        else if (_circular)
            return pop_index(index % _size);
        return NULL;
    }

    void rotate_left()
    {
        if (_size < 2)
            return;
        Node<T> *temp = _first;
        _first = _first->next;
        _first->prev = NULL;
        _last->next = temp;
        temp->prev = _last;
        temp->next = NULL;
        _last = temp;
    }
    void rotate_right()
    {
        if (_size < 2)
            return;
        Node<T> *temp = _last;
        _last = _last->prev;
        _last->next = NULL;
        _first->prev = temp;
        temp->next = _first;
        temp->prev = NULL;
        _first = temp;
    }

    bool swap(int oneIndex, int twoIndex)
    {
        if (_size == 0)
            return false;
        if (!_circular && (oneIndex < 0 || oneIndex > _size - 1) && (twoIndex < 0 || twoIndex > _size - 1))
            return false;
        if (_circular)
        {
            oneIndex = oneIndex % _size;
            twoIndex = twoIndex % _size;
        }
        Node<T> *nodeOne = findNodeByIndex(oneIndex);
        Node<T> *nodeTwo = findNodeByIndex(twoIndex);
        if (nodeOne->next != NULL)
            nodeOne->next->prev = nodeTwo;
        if (nodeOne->prev != NULL)
            nodeOne->prev->next = nodeTwo;
        if (nodeTwo->next != NULL)
            nodeTwo->next->prev = nodeOne;
        if (nodeTwo->prev != NULL)
            nodeTwo->prev->next = nodeOne;
        Node<T> *temp1 = nodeTwo->next;
        Node<T> *temp2 = nodeTwo->prev;
        nodeTwo->next = nodeOne->next;
        nodeTwo->prev = nodeOne->prev;
        nodeOne->next = temp1;
        nodeOne->prev = temp2;
        if (oneIndex == 0)
            _first = nodeTwo;
        else if (oneIndex == _size - 1)
            _last = nodeTwo;
        if (twoIndex == 0)
            _first = nodeOne;
        else if (twoIndex == _size - 1)
            _last = nodeOne;
        return true;
    }

    int size()
    {
        return _size;
    }
    bool isEmpty()
    {
        return _size == 0;
    }

    void setCircular(bool circular)
    {
        this->_circular = circular;
    }
    bool isCircular()
    {
        return this->_circular;
    }

    void clear()
    {
        Node<T> *node = _first;
        while (node != NULL)
        {
            _first = node->next;
            delete node;
            node = _first;
            _size--;
        }
    }

    LinkList<T> &operator=(initializer_list<T> _Ilist)
    {
        clear();
        for (int i = 0; i < _Ilist.size(); i++)
            push_back(_Ilist.begin()[i]);
        return *this;
    }
    LinkList<T> &operator+=(initializer_list<T> _Ilist)
    {
        for (int i = 0; i < _Ilist.size(); i++)
            push_back(_Ilist.begin()[i]);
        return *this;
    }

    void print()
    {
        int i = 0;
        Node<T> *node = _first;
        while (node != NULL)
        {
            cout << "index: " << i << "   ";
            node->print();
            cout << "\n";
            // cout << "--------------------------------" << endl;
            node = node->next;
            i++;
        }
        cout << "## Size: " << _size << endl;
    }
};

int main(int argc, char const *argv[])
{
    LinkList<int> list = {99, 77, 88};
    // list.setCircular(true);
    list.print();
    list = {1, 10, 8, 7, 15};
    list.print();
    list += {32, 36};
    list.print();

    cout << "\nEnd" << endl;
    return 0;
}