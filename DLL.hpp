#ifndef DLL_hpp
#define DLL_hpp

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <stdexcept>

// ----------------------------------------------------------------------------

/// LL is a container that supports constant time insertion and removal of
/// elements from anywhere in the container. Fast random access is not
/// supported. The class is implemented as a doubly-linked list. This container
/// provides bidirectional iteration capability.
///
/// Adding, removing, and moving the elements within the list or across several
/// lists does not invalidate the iterators or references. An iterator is
/// invalidated only when the corresponding element is deleted.
///
/// @note Mimics behavior of std::list.
/// @see https://en.cppreference.com/w/cpp/container/list

template <class T>
class LL {
private:
  /// @brief Template struct representing a Node in a doubly linked list.
  ///
  /// The Node struct contains data of type T, a pointer to the previous Node,
  /// and a pointer to the next Node. It is typically used as a building block
  /// for implementing a doubly linked list.

  struct Node {
      T     data;  ///< The data stored in the Node.
      Node* prev;  ///< A pointer to the previous Node.
      Node* next;  ///< A pointer to the next Node.
  };

  // ------------------------------------------------------------------------

  /// @brief Template class representing an iterator for a container.
  ///
  /// The Iterator class provides bidirectional iterator functionality and is
  /// typically used to iterate over elements in a container. It supports
  /// dereferencing, prefix increment, prefix decrement, and comparison ops.

  class Iterator {
  public:
      // Member Types
      using iterator_category = std::bidirectional_iterator_tag;  ///< The iterator category.
      using difference_type   = std::ptrdiff_t;                   ///< The difference type.
      using value_type        = T;                                ///< The value type.
      using pointer           = Node*;                            ///< The pointer type.
      using reference         = value_type&;                      ///< The reference type.

      /// @brief Constructs an Iterator object.
      /// @param ptr A pointer to the value the iterator points to.
      explicit Iterator(pointer ptr = nullptr) : m_ptr(ptr) {}

      /// @brief Dereferences the iterator.
      /// @return A reference to the value the iterator points to.
      reference operator*() const { return m_ptr->data; }

      /// @brief Returns a pointer to the node the iterator points to.
      /// @return A pointer to the node the iterator points to.
      /// @note This is a non-standard implementation.
      //lint -e1535 Suppress warning for inline function
      pointer operator->() { return m_ptr; }

      /// @brief Advances the iterator to the next element.
      /// @return A reference to the updated iterator.
      Iterator& operator++() { m_ptr = m_ptr->next; return *this; }

      /// @brief Moves the iterator to the previous element.
      /// @return A reference to the updated iterator.
      Iterator& operator--() { m_ptr = m_ptr->prev; return *this; }

      /// @brief Compares two iterators for equality.
      /// @param a The first iterator.
      /// @param b The second iterator.
      /// @return true if the iterators are equal, false otherwise.
      //lint -e9435
      friend bool operator==(const Iterator& a, const Iterator& b) {
          return a.m_ptr == b.m_ptr;
      }

      /// @brief Compares two iterators for inequality.
      /// @param a The first iterator
      //lint -e9435
      friend bool operator!=(const Iterator& a, const Iterator& b) {
          return a.m_ptr != b.m_ptr;
      }

  private:
      pointer m_ptr;  ///< A pointer to the value the iterator points to.
  };

  public:
    // member types
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = Iterator;
    using const_iterator  = const iterator;
    
    /// ----------------------------------------------------------------------
    /// @name LL
    /// @note Default constructor. Constructs a Linked List with count copies of
    /// the default value of value_type, e.g., the default value for an
    /// int is 0.
    /// ----------------------------------------------------------------------
    LL() : count(0), head(nullptr), tail(nullptr) {}
    
    /// ----------------------------------------------------------------------
    /// @name LL
    /// @param ilist   used to initialize the elements of the contianer
    /// @note Constructs the container with a copy of the contents of source.
    /// ----------------------------------------------------------------------
    LL(const std::initializer_list<T>& ilist);
    
    /// ----------------------------------------------------------------------
    /// @name LL
    /// @param other    holds a reference to other LL
    /// @note Copy-Constructor. Makes a deep copy of another Doubly Linked List.
    /// ----------------------------------------------------------------------
    LL(const LL& other);
    
    /// ----------------------------------------------------------------------
    /// @name LL
    /// @param other    holds the other List
    /// @note Mover-Constructor. Constructs container with the contents of other
    /// using move semantics. After the move, other is guaranteed to be empty()
    /// ----------------------------------------------------------------------
    LL(LL&& other);
  
    /// ----------------------------------------------------------------------
    /// @name ~LL
    /// @note Destructor.
    /// ----------------------------------------------------------------------
    //lint -e1540
    ~LL() noexcept;
  
    // Copy Assignment
    // -----------------------------------------------------------------------
    
    /// ----------------------------------------------------------------------
    /// @name operator=
    /// @param rhs    holds contents of other container
    /// @note COPY-assignment operator. Replaces the contents of the container
    ///       with a copy of the contents of rhs.
    /// @return *this
    /// ----------------------------------------------------------------------
    LL& operator=(const LL& rhs);
    
    //  Moving Assignment
    // -----------------------------------------------------------------------
    
    /// ----------------------------------------------------------------------
    /// @name operator=
    /// @param rhs    holds contents of other container
    /// @note MOVE-assignment operator. Replaces the contents with those of
    /// other using move semantics (i.e. the data in other is moved from other
    /// into this container). After the move, other is guaranteed to be empty()
    /// @return *this
    /// ----------------------------------------------------------------------
    LL& operator=(LL&& rhs);
  
    // Element access functions
    // -----------------------------------------------------------------------

    // @name: front() & const front()
    // @param: none
    // @return: Returns a reference to the first element in the container
    // @note: begin() function checks if the container is empty.
    reference front();
    const_reference front() const;

    reference back();
    const_reference back() const;
  
    // Iterators
    // -----------------------------------------------------------------------
    
    iterator begin();
    const_iterator begin() const;
    
    // @name: end() & const end()
    // @param: none
    // @return: Returns an iterator to the end of the container
    iterator end() { return iterator(nullptr); }
    const_iterator end() const { return iterator(nullptr);}
  
    // Capacity
    // -----------------------------------------------------------------------
    
    // @name: empty()
    // @param: none
    // @return: Returns true if size of container is equal to 0, false if not
    bool empty() const { return size() == 0; }
    
    // @name: size()
    // @param: none
    // @return: Returns the size of the container
    size_type size() const {return count;}
    
    // Modifiers
    // -----------------------------------------------------------------------
    
    void clear();
    iterator insert(iterator pos, const value_type& value);
    iterator erase(iterator pos);
    void push_back(const value_type& value);
    void pop_back();
    void push_front(const value_type& value);
    void pop_front();
    void swap(LL& other);
  
private:
  size_type count;
  Node*     head;
  Node*     tail;
};

#endif /* DLL_hpp */
