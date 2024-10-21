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

    bool remove(const T& value)
    {
        /* From https://stackoverflow.com/a/36711682/1936575 */
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
        return true;
    }

    void resort()
    {
       std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
};

#endif
