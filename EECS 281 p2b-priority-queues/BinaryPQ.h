// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef BINARYPQ_H
#define BINARYPQ_H

#include <algorithm>
#include "Eecs281PQ.h"

// A specialized version of the priority queue ADT implemented as a binary heap.
template <typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class BinaryPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR>
{
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Description: Construct an empty PQ with an optional comparison functor.
    // Runtime: O(1)
    explicit BinaryPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) : BaseClass{comp}, data{}
    {
        data.push_back(TYPE());
    } // BinaryPQ

    // Description: Construct a PQ out of an iterator range with an optional
    //              comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template <typename InputIterator>
    BinaryPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) : BaseClass{comp}
    {
        // TODO: Implement this function
        data.push_back(TYPE());
        while (start != end)
        {
            data.push_back(*start);
            start++;
        }
        updatePriorities();
    } // BinaryPQ

    // Description: Destructor doesn't need any code, the data vector will
    //              be destroyed automatically.
    virtual ~BinaryPQ()
    {
    } // ~BinaryPQ()

    // Description: Assumes that all elements inside the heap are out of order and
    //              'rebuilds' the heap by fixing the heap invariant.
    // Runtime: O(n)
    virtual void updatePriorities()
    {
        // might need to use a loop starting at data.size()-2, data.size()-1 is most likely a leaf?
        for (size_t i = (data.size() - 1); i != SIZE_MAX; i--)
        {
            if (i == 0)
            {
                break;
            }
            FixDown(data, ((data.size() - 1)), (i));
        }
    } // updatePriorities()

    // Description: Add a new element to the PQ.
    // Runtime: O(log(n))
    virtual void push(const TYPE &val)
    {
        // TODO: Implement this function.
        data.push_back(val);
        // fix with fix up as per video for the project, need to see if this is the right k value or if loop needed
        FixUp(data, ((data.size() - 1)));

    } // push()

    // Description: Remove the most extreme (defined by 'compare') element
    //              from the PQ.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the PQ is empty. Though you are welcome to if you are
    // familiar with them, you do not need to use exceptions in this project.
    // Runtime: O(log(n))
    virtual void pop()
    {
        // TODO: Implement this function.
        // switch the extreme with the lowest priority element in the vector
        std::swap(data[1], data[data.size() - 1]);
        // get rid of the element at the end(now the extreme)
        data.pop_back();
        // need to double check if the second parameter is correct
        // use fix down since need top-> down approach with element decreasing in priority, says in video to do this
        // need to check if only need to do it with only the first element
        FixDown(data, ((data.size() - 1)), 1);

    } // pop()

    // Description: Return the most extreme (defined by 'compare') element of
    //              the PQ. This should be a reference for speed. It MUST
    //              be const because we cannot allow it to be modified, as
    //              that might make it no longer be the most extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const
    {
        // TODO: Implement this function.
        // committed to adding a garbage val in the 0 spot
        return data[1];
    } // top()

    // Description: Get the number of elements in the PQ.
    // Runtime: O(1)
    virtual std::size_t size() const
    {
        // should just use this. data will always have garbage in the front to make it start at one
        return data.size() - 1;

    } // size()

    // Description: Return true if the PQ is empty.
    // Runtime: O(1)
    virtual bool empty() const
    {
        if (data.size() - 1 == 0)
        {
            return true;
        }
        return false;
    } // empty()

private:
    // Note: This vector *must* be used for your PQ implementation.
    std::vector<TYPE> data;
    // NOTE: You are not allowed to add any member variables. You don't need
    //       a "heapSize", since you can call your own size() member
    //       function, or check data.size().

    // TODO: Add any additional member functions you require here.
    //       For instance, you might add fixUp() and fixDown().

    void FixDown(std::vector<TYPE> &heap, size_t heapsize, size_t k)
    {
        while (2 * k <= heapsize)
        {
            size_t j = 2 * k;
            if (j < heapsize && this->compare(heap[j], heap[j + 1]))
            {
                ++j;
            }

            if (!(this->compare(heap[k], heap[j])))
            {
                break;
            }
            std::swap(heap[k], heap[j]);
            k = j;
        }
    }

    // same here regarding compare comment
    void FixUp(std::vector<TYPE> &heap, size_t k)
    {
        while (k > 1 && this->compare(heap[k / 2], heap[k]))
        {
            std::swap(heap[k], heap[k / 2]);
            k /= 2;
        }
    }

}; // BinaryPQ

#endif // BINARYPQ_H
