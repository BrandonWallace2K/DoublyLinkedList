/// @author - Brandon Wallace
/// @file - stack.hpp
/// @brief - Stack Adapter

#ifndef Stack_h
#define Stack_h

// Stack Adapter
template <class T>
class Stack : protected List<T>
{
    
// Member Types
public:
  using value_type      = typename List<T>::value_type; ///< The value type
  using reference       = typename List<T>::reference;  ///< The reference type
  using size_type       = typename List<T>::size_type;  ///< The size type

public:
    /// ----------------------------------------------------------------------
    /// @name Stack()
    /// @note Stack constructor user member initiailization to initialize the
    /// elements within the container
    /// ----------------------------------------------------------------------
    Stack() : List<T>() {}
    
    /// ----------------------------------------------------------------------
    /// @name empty()
    /// @note checks if the stack is empty
    /// @return returns true if the stack is empty, false if not empty
    /// ----------------------------------------------------------------------
    bool empty() const { return empty(); }

    /// ----------------------------------------------------------------------
    /// @name top()
    /// @note calls the back() function to return the top element of the stack
    /// @return returns the top element of the stack
    /// ----------------------------------------------------------------------
    reference top() { return back(); }
    
    /// ----------------------------------------------------------------------
    /// @name push()
    /// @param value holds the value to be inserted into the stack
    /// @note inserts an element (value) onto the top of the stack
    /// ----------------------------------------------------------------------
    void push(const value_type& value) { push_back(value); }
    
    /// ----------------------------------------------------------------------
    /// @name pop()
    /// @note pops off the top element of the stack
    /// ----------------------------------------------------------------------
    void pop() { pop_back(); }
    
};  // class Stack

#endif /* Stack_h */
