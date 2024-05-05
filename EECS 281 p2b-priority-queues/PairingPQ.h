// Project identifier: 43DE0E0C4C76BFAA6D8C2F5AEAE0518A9C42CF4E

#ifndef PAIRINGPQ_H
#define PAIRINGPQ_H

#include "Eecs281PQ.h"
#include <deque>
#include <utility>

// A specialized version of the priority queue ADT implemented as a pairing
// heap.
template <typename TYPE, typename COMP_FUNCTOR = std::less<TYPE>>
class PairingPQ : public Eecs281PQ<TYPE, COMP_FUNCTOR>
{
    // This is a way to refer to the base class object.
    using BaseClass = Eecs281PQ<TYPE, COMP_FUNCTOR>;

public:
    // Each node within the pairing heap
    class Node
    {
    public:
        // TODO: After you add add one extra pointer (see below), be sure
        // to initialize it here.
        explicit Node(const TYPE &val)
            : elt{val}, child{nullptr}, sibling{nullptr}, parent{nullptr}
        {
        }

        // Description: Allows access to the element at that Node's
        // position.  There are two versions, getElt() and a dereference
        // operator, use whichever one seems more natural to you.
        // Runtime: O(1) - this has been provided for you.
        const TYPE &getElt() const { return elt; }
        const TYPE &operator*() const { return elt; }

        // The following line allows you to access any private data
        // members of this Node class from within the PairingPQ class.
        // (ie: myNode.elt is a legal statement in PairingPQ's add_node()
        // function).
        friend PairingPQ;

    private:
        TYPE elt;
        Node *child;
        Node *sibling;
        Node *parent;
    }; // Node

    // Description: Construct an empty pairing heap with an optional
    //              comparison functor.
    // Runtime: O(1)
    explicit PairingPQ(COMP_FUNCTOR comp = COMP_FUNCTOR()) : BaseClass{comp}, root{nullptr}, numNodes{0}
    {

    } // PairingPQ()

    // Description: Construct a pairing heap out of an iterator range with an
    //              optional comparison functor.
    // Runtime: O(n) where n is number of elements in range.
    template <typename InputIterator>
    PairingPQ(InputIterator start, InputIterator end, COMP_FUNCTOR comp = COMP_FUNCTOR()) : BaseClass{comp}
    {
        numNodes = 0;
        root = nullptr;
        // while loop that starts at "start",
        while (start != end)
        {
            TYPE valToBeInsert = *start;
            push((valToBeInsert));
            start++;
        }

    } // PairingPQ()

    // Description: Copy constructor.
    // Runtime: O(n)
    PairingPQ(const PairingPQ &other) : BaseClass{other.compare}
    {
        // TODO: Implement this function.
        // NOTE: The structure does not have to be identical to the original,
        //       but it must still be a valid pairing heap.
        std::deque<Node *> nodeAdd;
        nodeAdd.push_back(other.root);
        // need to make sure this doesnt break something
        root = nullptr;
        numNodes = 0;
        while (!nodeAdd.empty())
        {
            // add sibling/child to list of nodes
            if ((nodeAdd[0])->sibling != nullptr)
            {
                nodeAdd.push_back((nodeAdd[0])->sibling);
            }
            if ((nodeAdd[0])->child != nullptr)
            {
                nodeAdd.push_back((nodeAdd[0])->child);
            }
            push(nodeAdd[0]->elt);
            nodeAdd.pop_front();
        }

    } // PairingPQ()

    // Description: Copy assignment operator.
    // Runtime: O(n)
    PairingPQ &operator=(const PairingPQ &rhs)
    {

        // notes
        // lecture 6 copy-swap, best copying
        //  TODO: Implement this function.
        //  HINT: Use the copy-swap method from the "Arrays and Containers"
        //  lecture.
        PairingPQ temp(rhs);
        //does this work ??
        std::swap(numNodes,temp.numNodes);
        std::swap(root,temp.root);
        return *this;
    } // operator=()

    // Description: Destructor
    // Runtime: O(n)
    ~PairingPQ()
    {
        // TODO: Implement this function.
        // note for copy constructor, destructor and update priorities:

        // proj 1 approach
        // make container deque
        // add starting location to it
        // while it's not empty
        //  get the next node from deque
        //  add things nearby to the deque, child and sibling in this instance
        // gotta do something with the current one, depends on which

        // destructor deletes the current one

        // copy constructor, must do deep copy, start is the other pairing heap's root
        // call push with each member to populate the empty one
        // so essentially populate deque
        // call push on the front
        //  pop front
        //  until deque is empty

        std::deque<Node *> nodeDelete;
            if(root != nullptr){  
            nodeDelete.push_back(root);
             }
        // need to make sure this doesnt break something
        while (!nodeDelete.empty())
        {

            // add sibling/child to list of nodes
            if ((nodeDelete[0])->sibling != nullptr)
            {
                nodeDelete.push_back((nodeDelete[0])->sibling);
            }
            if ((nodeDelete[0])->child != nullptr)
            {
                nodeDelete.push_back((nodeDelete[0])->child);
            }
            // sever ties that each node has
            nodeDelete[0]->sibling = nullptr;
            nodeDelete[0]->parent = nullptr;
            nodeDelete[0]->child = nullptr;

            // not sure if this would be alright ??????
            delete nodeDelete.front();
            nodeDelete.front() = nullptr;
            nodeDelete.pop_front();
        }

    } // ~PairingPQ()

    // Description: Assumes that all elements inside the pairing heap are out
    //              of order and 'rebuilds' the pairing heap by fixing the
    //              pairing heap invariant.  You CANNOT delete 'old' nodes
    //              and create new ones!
    // Runtime: O(n)
    virtual void updatePriorities()
    {
        // TODO: Implement this function.

        // update priorities
        // underlying data has changed, but not given as to how
        // need to fix it
        //  follow the above
        // something that is done with current, remove the references it has, all ptrs = null
        // delete root aka after putting it in the deque, set root to nullptr/delete
        // count should not change
        // meld for each value, first value ever gotten should be the root to start but sever all ties still
        // current val -> holds front of deque, use it to add more to the deque if possible, then sever ties, then meld
        // meld with root each time

        std::deque<Node *> nodeFixList;
        nodeFixList.push_back(root);
        // need to make sure this doesnt break anything
        root = nullptr;
        while (!nodeFixList.empty())
        {
            // add sibling/child to list of nodes
            if ((nodeFixList[0])->sibling != nullptr)
            {
                // idk if these -> actually do what they are supposed to with the ptrs in the deque
                nodeFixList.push_back((nodeFixList[0])->sibling);
            }
            if ((nodeFixList[0])->child != nullptr)
            {
                nodeFixList.push_back((nodeFixList[0])->child);
            }
            // sever ties that each node has
            nodeFixList[0]->sibling = nullptr;
            nodeFixList[0]->parent = nullptr;
            nodeFixList[0]->child = nullptr;
            // must run meld everytime
            if (root == nullptr)
            {
                root = nodeFixList.front();
            }
            else
            {
                meld(root, nodeFixList[0]);
            }
            nodeFixList.pop_front();
        }

    } // updatePriorities()

    // Description: Add a new element to the pairing heap. This is already
    //              done. You should implement push functionality entirely
    //              in the addNode() function, and this function calls
    //              addNode().
    // Runtime: O(1)
    virtual void push(const TYPE &val)
    {
        addNode(val);
    } // push()

    // Description: Remove the most extreme (defined by 'compare') element
    //              from the pairing heap.
    // Note: We will not run tests on your code that would require it to pop
    // an element when the pairing heap is empty. Though you are welcome to
    // if you are familiar with them, you do not need to use exceptions in
    // this project.
    // Runtime: Amortized O(log(n))
    virtual void pop()
    {
        // create new priorities/relationships
        // meld each pair
        // merge basically

        // multipass or double pass

        // two pass
        // essentially meld each pair and put it in a new container
        // left to right putting them in so push back/push front with a deque
        //  then right to left taking them out/melding them

        // repeat until container is size 1
        // meld takes care of the root and everything else, it is only the iteration over the container that may
        // prove difficult

        // multipass
        // take 2 things from front,meld together, push the result to the back
        //  do this until size = 1

        // TODO: Implement this function.
        // first grab the original root's child
        Node *originalChild = root->child;
        Node *tempSibling;
        // delete root/parent,
        // idk if this is how I am supposed to do it ??
        //originally had delete root here 
        delete root;
        numNodes--;
        if (originalChild != nullptr)
        {
            root = originalChild;
            tempSibling = originalChild->sibling;
            // put all node ptrs into a deque
            std::deque<Node *> containNodes;
             containNodes.push_back(originalChild);
            // populate deque
            while (tempSibling != nullptr)
            {
                // need to see if this breaks
                containNodes.push_back(tempSibling);
                tempSibling = tempSibling->sibling;
            }

            while (containNodes.size() != 1)
            {
                // grab the two things you want to meld
                // meld and push back result
                // have to break the relationships before we meld
                // no parent/prev, no sibling
                // idk if this works??
                containNodes[0]->sibling = nullptr;
                containNodes[0]->parent = nullptr;
                containNodes[1]->sibling = nullptr;
                containNodes[1]->parent = nullptr;
                containNodes.push_back(meld(containNodes[0], containNodes[1]));
                // popfront twice
                containNodes.pop_front();
                containNodes.pop_front();
            }
        }
        else
        {
            root = nullptr;
        }

    } // pop()

    // Description: Return the most extreme (defined by 'compare') element of
    //              the pairing heap. This should be a reference for speed.
    //              It MUST be const because we cannot allow it to be
    //              modified, as that might make it no longer be the most
    //              extreme element.
    // Runtime: O(1)
    virtual const TYPE &top() const
    {
        /// should just be the root's value
        return root->elt;
    } // top()

    // Description: Get the number of elements in the pairing heap.
    // Runtime: O(1)
    virtual std::size_t size() const
    {
        // TODO: Implement this function
        return numNodes;
    } // size()

    // Description: Return true if the pairing heap is empty.
    // Runtime: O(1)
    virtual bool empty() const
    {
        return numNodes == 0;

    } // empty()

    // Description: Updates the priority of an element already in the pairing
    //              heap by replacing the element refered to by the Node with
    //              new_value.  Must maintain pairing heap invariants.
    //
    // PRECONDITION: The new priority, given by 'new_value' must be more
    //              extreme (as defined by comp) than the old priority.
    //
    // Runtime: As discussed in reading material.
    // need to ensure to use parent/previouse here, essentially they want this
    // element that is being assigned a new priority to now be the new extreme
    void updateElt(Node *node, const TYPE &new_value)
    {

        //  uses a ptr to a node in the PQ, to change the value
        //  now need to make a valid PQ again
        //  set sibling and parent to nullptr
        // meld afterwards

        //  need to make some changes, ie. reassign siblings though, no changes to parent ptr
        // need to grab the location of the node ptr due to this, start with node *'s parent's child
        //  if that = node * then, node is the left most, b/c we chose parent ptr then we dont need to worry about sibling assignment
        // if not left most then need to do sibling reassign

        //  need to make some changes, ie. reassign siblings though, no changes to parent ptr
        // need to grab the location of the node ptr due to this, start with node *'s parent's child
        //  if that = node * then, node is the left most, b/c we chose parent ptr then we dont need to worry about sibling assignment
        // if not left most then need to do sibling reassign

        // I dont think it works this way... maybe use the elts instead?? nut what if 2 vals in a row that have the same elts ??
        // maybe it would be in the same location in memory so could stilll do it this way ??
        // dont need to alter any siblings if left most node,they all would still point to
        node->elt = new_value;
        Node *parentStart = node->parent;
        Node *childSiblingBefore = nullptr;

        // case if the root is not the node being altered
        if (parentStart != nullptr)
            childSiblingBefore = parentStart->child;

        // note use compare here, childSiblingBefore should have higher priority
        if (childSiblingBefore != nullptr && this->compare(node->elt, childSiblingBefore->sibling->elt))
        {
            /// possible cases
            // right most node   //sandwiched between 2 nodes
            // then the previous node needs their sibling to be set to nullptr/if the node that is altered has a sibling then connect that one
            /// 1 -> 2 -> 3, 2 altered, then connect 1 to 3, 3 altered then set 2's sibling to 3's sibling(nullptr)
            // is eltPA < eltPB
            // second should be root if true
            // if (this->compare(pa->elt, pb->elt))
            // {

            // keep iterating until reach node before the node we changed
            // note use compare here, childSiblingBefore should have higher priority
            while (this->compare(node->elt, childSiblingBefore->sibling->elt))
            {
                childSiblingBefore = childSiblingBefore->sibling;
            }
            // next set it's sibling to the node we changed's sibling
            // break
            childSiblingBefore->sibling = node->sibling;
            // then reorg the nodes
            node->sibling = nullptr;
            node->parent = nullptr;
            meld(root, node);
        }

    } // updateElt()

    // Description: Add a new element to the pairing heap. Returns a Node*
    //              corresponding to the newly added element.
    // Runtime: O(1)
    // NOTE: Whenever you create a node, and thus return a Node *, you must
    //       be sure to never move or copy/delete that node in the future,
    //       until it is eliminated by the user calling pop(). Remember this
    //       when you implement updateElt() and updatePriorities().
    Node *addNode(const TYPE &val)
    {
        Node *nodeToBeAdded = new Node(val);
        //nodeToBeAdded->elt = val;
        // requires meld apparently according to video
        if (root == nullptr)
        {
            root = nodeToBeAdded;
            numNodes++;
            return root;
        }

        numNodes++;
        // otherwise run meld
        return meld(root, nodeToBeAdded);
        // pointer is for updateElt()

    } // addNode()

private:
    // TODO: We recommend creating a 'meld' function (see the Pairing Heap
    // papers).
    Node *meld(Node *pa, Node *pb)
    {
        // puts together 2 pairing heaps
        // roots of both pairing heaps
        // compare the values, highest value is most extreme
        // is eltPA < eltPB
        // second should be root if true
        if (this->compare(pa->elt, pb->elt))
        {
            // might work??
            // essetially if pb has a child, best thing to do is add new node to the left,
            //  new node -> sibling, current root's child, then assign parent child as needed
            pa->sibling = pb->child;
            pb->child = pa;
            pa->parent = pb;
            root = pb;
            return pb;
        }
        // first one should be root
        pb->sibling = pa->child;
        pa->child = pb;
        pb->parent = pa;
        root = pa;
        return pb;
    }

    // default, should have null for children, parent and sibling
    //  only children pointer should change/should only add children
    Node *root;
    uint32_t numNodes;

    // NOTE: For member variables, you are only allowed to add a "root
    //       pointer" and a "count" of the number of nodes. Anything else
    //       (such as a deque) should be declared inside of member functions
    //       as needed.
};

#endif // PAIRINGPQ_H
