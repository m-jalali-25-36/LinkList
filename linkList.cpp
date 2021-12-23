#include <iostream>

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
    bool _circular = true;

public:
    LinkList() {}
    ~LinkList()
    {
        while (_size != 0)
            pop_first();
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
            return NULL;
        if (!_circular && (index < 0 || index > _size - 1))
            return NULL;
        if (_circular)
            index = index % _size;
        int i = 0;
        Node<T> *node = _first;
        while (node != NULL)
        {
            if (i == index)
                return node->Data;
            node = node->next;
            i++;
        }
    }
    T operator[](int index)
    {
        return at(index);
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
        }
        else if (index == 0)
        {
            Push_first(element);
            return;
        }
        else if (index == _size)
        {
            Push_back(element);
            return;
        }
        else if (index > 0 && index < _size)
        {
            Node<T> *temp = new Node<T>(element);
            int i = 0;
            Node<T> *node = _first;
            while (node != NULL)
            {
                if (i == index)
                {
                    temp->prev = node->prev->next;
                    node->prev->next = temp;
                    node->prev = temp;
                    temp->next = node;
                    break;
                }
                node = node->next;
                i++;
            }
        }
        _size++;
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
        else
        {
        }
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
        while (_size > 0)
            pop_first();
    }

    void print()
    {
        int i = 0;
        Node<T> *node = _first;
        while (node != NULL)
        {
            cout << "index: " << i << "   ";
            cout << "name: " << node << "  \t";
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
    LinkList<int> list;

    list.push_first(5);
    list.push_first(10);
    list.push_first(20);
    list.push_first(8);
    list.print();
    list.rotate_left();
    list.print();
    list.rotate_right();
    list.print();
    list.rotate_right();
    list.print();
    list.rotate_right();
    list.print();

    cout << "\nEnd" << endl;
    return 0;
}