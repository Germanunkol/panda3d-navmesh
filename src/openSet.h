#ifndef OPEN_SET_H
#define OPEN_SET_H

#include <queue>

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
> class OpenSet : public std::priority_queue<T, Container, Compare>
{
    /* This defines a std::priority_queue with an additonal find */
public:
    typedef typename
        std::priority_queue<
        T,
        Container,
        Compare>::container_type::const_iterator const_iterator;

    ~OpenSet()
    {
        for( auto it = this->c.begin(); it != this->c.end(); it++ )
            (*it)->set_open( false );
    }

    void push( T&& value )
    {
        value->set_open( true );
        this->std::priority_queue<T, Container, Compare>::push( value );
    }
    void push( const T& value )
    {
        value->set_open( true );
        this->std::priority_queue<T, Container, Compare>::push( value );
    }
		
    void pop()
    {
        T t = this->top();
        t->set_open( false );
        this->std::priority_queue<T, Container, Compare>::pop();
    }

    const_iterator find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return first;
            ++first;
        }
        return last;
    }

    /* Warning: May be slow!! */
    bool contains(const T&val)
    {
       return std::find(this->c.begin(), this->c.end(), val) != this->c.end();
    }


    /*bool remove(const T& value)
    {
        // From https://stackoverflow.com/a/36711682/1936575
        auto it = std::find(this->c.begin(), this->c.end(), value);

        if (it == this->c.end()) {
            return false;
        }
        if (it == this->c.begin()) {
            // deque the top element
            this->pop();
        }    
        else {
            // remove element and re-heap
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
        }

        value->set_open( false );
        return true;
    }*/

    void resort()
    {
       std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
};

#endif
