/// @author - Brandon Wallace
/// @file - dll.cpp
/// @brief - Doubly Linked List Container

#include "dll.hpp"

// =======================================================================
//                      D E F I N I T I O N S
// =======================================================================

// Non Member Equality Overload
// -----------------------------------------------------------------------

template <class T>
bool operator==(const LL<T>& lhs, const LL<T>& rhs)
{
  bool flag = true;

  if (lhs.size() != rhs.size())
  {
    return false;
  }
  
  if (lhs.size() == rhs.size())
  {
    auto rhs_itr = rhs.begin();
    
    for (auto lhs_itr = lhs.begin(); lhs_itr != lhs.end(); ++lhs_itr)
    {
      if (*lhs_itr != *rhs_itr)
      {
        flag = false;
        break;
      }
      ++rhs_itr;
    }
    return flag;
  }
   else
     return false;
}

// Non Member Non-Equality Overload
// -----------------------------------------------------------------------

template <class T> bool operator!=(const LL<T>& lhs, const LL<T>& rhs)
{
  return !(lhs == rhs);
}

// Deconstructor
// -----------------------------------------------------------------------

template <class T>
LL<T>::~LL() noexcept
{
    clear( );
    delete head;
    delete tail;
}

// Initailizer List Constructor
// -----------------------------------------------------------------------

template <class T>
LL<T>::LL(const std::initializer_list<T>& ilist)
: LL<T>() {
  for (const auto& element : ilist)
  {
    push_back(element);
  }
}

// Copy Constructor
// -----------------------------------------------------------------------

template <class T>
LL<T>::LL(const LL& other)
: LL<T>() {
    for (const auto& element : other)
    {
        push_back(element);
    }
}

// Move Constructor
// -----------------------------------------------------------------------

template <class T>
LL<T>::LL(LL&& other)
: count(std::exchange(other.count, 0)),
  head(std::exchange(other.head, nullptr)),
  tail(std::exchange(other.tail, nullptr))
{}

// Copy Assignment
// -----------------------------------------------------------------------

template <class T>
LL<T>& LL<T>::operator=(const LL& rhs)
{
    // Checks for self-assignment
    if (this != &rhs) {
        
        // Creates a temporary copy of rhs
        LL<T> cpy = rhs;

        // Swaps the contents of *this with the copy
        std::swap(count, cpy.count);
        std::swap(head, cpy.head);
        std::swap(tail, cpy.tail);
    }

    // Return *this to allow for chained assignments
    return *this;
}

// Move Assignment
// -----------------------------------------------------------------------

template <class T>
LL<T>& LL<T>::operator=(LL&& rhs)
{
    // Checks For Self-Assignment
    if (this != &rhs) {
        clear();

        count = std::exchange(rhs.count, 0);
        head  = std::exchange(rhs.head, nullptr);
        tail  = std::exchange(rhs.tail, nullptr);
    }

    return *this;
}

// Element access functions
// -----------------------------------------------------------------------


template <class T>
typename LL<T>::reference LL<T>::front() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    return head->data;
}

template <class T>
typename LL<T>::const_reference LL<T>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    return head->data;
}

template <class T>
typename LL<T>::reference LL<T>::back()
{
    // Checks if the container is empty
    if (tail == nullptr) {
        throw std::out_of_range("List is empty");
    }
    
    // Returns the back of the container
    return tail->data;
    
}

template <class T>
typename LL<T>::const_reference LL<T>::back() const
{
    // Checks if the container is empty
    if (tail == nullptr) {
        throw std::out_of_range("List is empty");
    }
    
    // Returns the back of the container
    return tail->data;
}


// Iterators
// -----------------------------------------------------------------------

template <class T>
typename LL<T>::iterator LL<T>::begin()
{
    // Checks if the container is empty
    if (empty())
    {
        return iterator(nullptr);
    }
      
    return iterator(head);
}

template <class T>
typename LL<T>::const_iterator LL<T>::begin() const
{
    // Checks if the container is empty
    if (empty())
    {
        return iterator(nullptr);
    }
  
    return iterator(head);
}

// Modifiers
// -----------------------------------------------------------------------

template <class T>
void LL<T>::clear()
{
    // Declares a pointer
    Node* tmp;
    
    // Checks if the container is empty
    while (head != nullptr)
    {
        tmp = head;

        head = head->next;

        delete tmp;
    }

    tail = nullptr;
  
    count = 0;
}// clear

// -----------------------------------------------------------------------

template <class T>
typename LL<T>::iterator LL<T>::erase(iterator pos)
{
    // Iterator points to end(), nothing to erase
    if (pos == end()) {
        return pos;
    }
    
    // Declares a raw pointer to the position node
    Node* current = pos.operator->();
    
    // Returns an iterator to the new head (node following the one being deleted)
    if (current == head) {
        
        head = head->next;
        
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        
        delete current;
        
        // Decrements the count in the container
        count--;
        
        return iterator(head);
    }
    // Returns end() iterator as there is no node following the last node
    else if (current == tail)
    {
        tail = tail->prev;
        
        tail->next = nullptr;
        
        delete current;
        
        // Decrements the count in the container
        count--;
        
        return end();
    }
    // Returns an iterator to the node following the one being deleted
    else
    {
        current->prev->next = current->next;
        
        current->next->prev = current->prev;
        
        auto nextNode = current->next;
        
        delete current;
        
        // Decrements the count in the container
        count--;
        
        return iterator(nextNode);
    }
}// erase

// -----------------------------------------------------------------------

template <class T>
typename LL<T>::iterator LL<T>::insert(iterator pos, const value_type& value)
{
    // Declares a raw pointer to the position node
    Node* current = pos.operator->();
    
    // Creates a new node with the given value
    Node* newNode = new Node{value};
    newNode->next = nullptr;
    newNode->prev = nullptr;
    
    // Checks if the container is empty
    if (empty())
    {
        // Sets the head and tail to the new node
        head = newNode;
        tail = newNode;
        
        // Increments the count of the container
        count++;
        
        // Returns an iterator to the new node
        return iterator(newNode);
    }
    
    // Checks if the position is a nullptr
    if (current == nullptr)
    {
        // Inserts the node at the end of the list
        tail->next = newNode;
        
        newNode->prev = tail;
        
        tail = newNode;
    }
    // Checks if the position is pointing to the head
    else if (current == head)
    {
        // Inserts the node at the beginning of the list
        head->prev = newNode;
        
        newNode->next = head;
        
        head = newNode;
    }
    // Inserts the node in the middle of two nodes
    else
    {
        Node* q = current->prev;
        
        newNode->prev = q;
        
        newNode->next = current;
        
        q->next = newNode;
        
        current->prev = newNode;
    }
    
    // Increments the count of the container
    count++;
    
    // Returns an iterator to the node following the new node
    return iterator(newNode);
}
// -----------------------------------------------------------------------

template <class T>
void LL<T>::push_back(const value_type& value)
{
    // Creates a new node with the given value
    Node* newNode = new Node{value};
    
    newNode->next = nullptr;
    
    newNode->prev = nullptr;
    
    // Checks if the list is empty
    // Sets head and tail to the new node
    if (empty())
    {
        head = newNode;
        
        tail = newNode;
    }
    // Links the new node to the current tail of the list
    else
    {
        tail->next = newNode;
        
        newNode->prev = tail;
        
        tail = newNode;
    }
    
    // Increments the count of the container
    count++;
}

// -----------------------------------------------------------------------
template <class T>
void LL<T>::pop_back()
{
    // Checks if the list is empty
    if (empty())
    {
        std::cerr << "List is empty! Can not execute pop_back()." << std::endl;
        return;
    }
    
    // Handles the case when there is only one node in the list
    if (head == tail && count == 1)
    {
        delete head;
        
        head = nullptr;
        
        tail = nullptr;
    }
    else
    {
        // Sets the tail pointer to the previous node
        // and removes the current tail
        Node* p = tail->prev;
        
        p->next = nullptr;
        
        delete tail;
        
        tail = p;
    }
    
    // Decrements the count in the container
    count--;
}

// -----------------------------------------------------------------------

template <class T>
void LL<T>::push_front(const value_type& value)
{
    // Create a new node with the given value
    Node* new_node = new Node();
    new_node->data = value;

    // Assigns the previous pointer to nullptr
    new_node->prev = nullptr;

    // Assigns the next pointer to the current head node
    new_node->next = head;
  
    // If the list is not empty
    if(head != nullptr)
    {
        // Set the current head's previous pointer to new node
        head->prev = new_node;
    }
  
    // Point the head to the new node
    head = new_node;
    
    // Increments the count of the container
    count++;
    
    // return
    return;
}

// -----------------------------------------------------------------------

template <class T>
void LL<T>::pop_front()
{
    // Checks if the list is empty and returns
    if (head == nullptr)
    {
        std::cerr << "Cannot perform pop_front(). The list is empty." << std::endl;
        return;
    }
    
    // Assigns head to a pointer
    Node* p = head;
    
    // Moves the head pointer to the next node
    head = head->next;
  
    // Updates the previous pointer of the new head to nullptr
    if (head != nullptr)
    {
        head->prev = nullptr;
    }
    else
    {
        // If the list becomes empty, updates the tail pointer
        tail = nullptr;
    }
    
    // Deletes the old head node
    delete p;
    
    // Decrements the count in the list
    count--;
}

// -----------------------------------------------------------------------

template <class T>
void LL<T>::swap(LL& other)
{
    // Swaps the private data members of the two containers
    std::swap(count, other.count);
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}
