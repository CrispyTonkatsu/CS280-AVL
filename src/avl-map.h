/**
 * @file avl-map.hpp
 * @author Edgar Jose Donoso Mansilla (e.donosomansilla)
 * @course CS280
 * @term Spring 2025
 *
 * @brief Implementation for a binary search tree
 */

#include <cmath>
#ifndef AVLMAP_H
  #define AVLMAP_H

  #include <iosfwd>
  #include <optional>

namespace CS280 {

  /**
   * @brief This class represents a binary search tree using key K and stores
   * values of type V. It has support for the following operations:
   * - Insert
   * - Find
   * - Erase
   *
   * @param K The type for the key to be used (Needs the < and > operator
   * overloads)
   * @param V The type for the values to be used (Needs to be copiable)
   */
  template<typename K, typename V>
  class AVLmap {

    // Forward declarations for the struct
    struct AVLmap_iterator;
    struct AVLmap_iterator_const;

  public:

    // standard names for iterator types
    typedef AVLmap_iterator iterator;
    typedef AVLmap_iterator_const const_iterator;

    /**
     * @brief This class represents a Node in the AVL. It mainly features
     * getters, setters and traversal methods.
     */
    class Node {
    public:

      /**
       * @brief Factory method for an empty unlinked node of key K.
       *
       * @param key The key to use.
       * @return Pointer to allocated node.
       */
      static auto CreateNode(K key) -> Node*;

      /**
       * @brief Constructor for a Node.
       *
       * @param k The key of this node.
       * @param v The value of this node.
       * @param h The node's height.
       * @param b The node's balance.
       * @param l The left child's pointer.
       * @param r The right child's pointer.
       */
      Node(K k, V val, Node* p, int h, int b, Node* l, Node* r);

      // Deleted copy constructor
      Node(const Node&) = delete;

      // Deleted copy assignment operator
      auto operator=(const Node&) -> Node& = delete;

      /**
       * @brief Getter of a reference to the key of this node.
       * @return Const reference to the key.
       */
      auto Key() const -> const K&; // return a const reference

      /**
       * @brief Getter of a reference to the value of this node.
       * @return Reference to the value.
       */
      auto Value() -> V&; // return a reference

      /**
       * @brief Getter of a reference to the value of this node.
       * @return Reference to the value.
       */
      auto Value() const -> const V&; // return a reference

      /**
       * @brief Function to get the node furthest left of a node.
       * @return Pointer to the node.
       */
      auto first() -> Node*; // minimum - follow left as far as possible

      /**
       * @brief Function to get the node furthest right of a node.
       * @return Pointer to the node.
       */
      auto last() -> Node*; // maximum - follow right as far as possible

      /**
       * @brief Will get the node's successor
       * @return Pointer to the node.
       */
      auto increment() -> Node*; // successor

      /**
       * @brief Will get the node's predecessor
       * @return Pointer to the node.
       */
      auto decrement() -> Node*; // predecessor

      /**
       * @brief Prints a node
       */
      auto print(std::ostream& os) const -> void;

    private:

      enum class Rotation {
        NONE,
        RIGHT,
        LEFT
      };

      /**
       * @brief Returns whether this node is the right child of a node.
       * @return Whether it is the right child.
       */
      auto is_right_child() const -> bool;

      /**
       * @brief Returns whether this node is the left child of a node.
       * @return Whether it is the left child.
       */
      auto is_left_child() const -> bool;

      /**
       * @brief Will add a child updating the links properly and setting it to
       * the correct side.
       */
      auto add_child(Node& node) -> void;

      /**
       * @brief Will remove a child.
       */
      auto unlink_child(Node& node) -> void;

      /**
       * @brief Will replace the child updating all necessary links
       *
       * @param to_replace The node to replace (nothing will happen if the node
       * is not a child)
       * @param replacement The node to replace it with
       */
      auto replace_child(Node* to_replace, Node* replacement) -> void;

      /**
       * @brief Returns whether the node has children or not.
       * @return Whether the node has children.
       */
      auto has_children() const -> bool;

      /**
       * @brief Gets the only child this node has.
       * @return Optional pointer to the node. If there are 2 children nodes it
       * returns nullopt.
       */
      auto get_only_child() -> std::optional<Node*>;

      /**
       * @brief This will try to fix the balance of the node. Otherwise it will
       * return false
       *
       * @return Whether a rotation occured
       */
      auto try_fix_balance(Node* previous, Node*& root) -> Rotation;

      /**
       * @brief Performs a right rotation about the calling node.
       */
      auto rotate_right() -> void;

      /**
       * @brief Performs a left rotation about the calling node.
       */
      auto rotate_left() -> void;

      /**
       * @brief Recursive function that will update the balance of the nodes in
       * the tree.
       */
      auto insert_balance(Node* previous, Node*& root) -> void;

      /**
       * @brief Propagates the height of this node downwards recursively.
       */
      auto propagate_height_down() -> void;

      /**
       * @brief The key of this node.
       */
      K key;

      /**
       * @brief The value that is being held by the node.
       */
      V value;

      /**
       * @brief The distance of the node relative to the leaves of the sub-tree
       */
      size_t height;

      /**
       * @brief The difference of height between the left and right children's
       * height
       */
      int balance;

      /**
       * @brief The parent of this node
       */
      Node* parent;

      /**
       * @brief The left child's pointer
       */
      Node* left;

      /**
       * @brief The right child's pointer
       */
      Node* right;

      // Friending the AVLmap class so the internals can be accessed.
      friend AVLmap;
    };

  private:

    /**
     * @brief This class is the non const iterator of the map
     */
    struct AVLmap_iterator {
    private:

      /**
       * @brief Pointer to the iterator's node.
       */
      Node* p_node;

    public:

      /**
       * @brief Constructor for the iterator
       * @param Pointer to the node
       */
      AVLmap_iterator(Node* p = nullptr);

      /**
       * @brief Copy constructor for the iterator
       */
      AVLmap_iterator(AVLmap_iterator& rhs);

      /**
       * @brief Conversion operator into const
       */
      operator AVLmap_iterator_const();

      /**
       * @brief Copy assignment operator
       */
      auto operator=(const AVLmap_iterator& rhs) -> AVLmap_iterator&;

      /**
       * @brief Pre-increment operator (successor)
       */
      auto operator++() -> AVLmap_iterator&;

      /**
       * @brief Post-increment operator (successor)
       */
      auto operator++(int) -> AVLmap_iterator;

      /**
       * @brief Pre-decrement operator (predecessor)
       */
      auto operator--() -> AVLmap_iterator&;

      /**
       * @brief Post-decrement operator (predecessor)
       */
      auto operator--(int) -> AVLmap_iterator;

      /**
       * @brief Dereferencing operator.
       * @return Reference to the node.
       */
      auto operator*() -> Node&;

      /**
       * @brief Arrow operator.
       * @return Pointer to the node.
       */
      auto operator->() -> Node*;

      /**
       * @brief Inequality operator.
       */
      auto operator!=(const AVLmap_iterator& rhs) -> bool;

      /**
       * @brief Equality operator.
       */
      auto operator==(const AVLmap_iterator& rhs) -> bool;

      friend AVLmap;
    };

    /**
     * @brief This class is the const iterator of the map
     */
    struct AVLmap_iterator_const {
    private:

      /**
       * @brief Pointer to the iterator's node.
       */
      Node* p_node;

    public:

      /**
       * @brief Constructor for the iterator
       * @param Pointer to the node
       */
      AVLmap_iterator_const(Node* p = nullptr);

      /**
       * @brief Copy constructor for the iterator
       */
      AVLmap_iterator_const(AVLmap_iterator_const& rhs);

      /**
       * @brief Copy assignment operator
       */
      auto operator=(const AVLmap_iterator_const& rhs)
        -> AVLmap_iterator_const&;

      /**
       * @brief Pre-increment operator (successor)
       */
      auto operator++() -> AVLmap_iterator_const&;

      /**
       * @brief Post-increment operator (successor)
       */
      auto operator++(int) -> AVLmap_iterator_const;

      /**
       * @brief Pre-decrement operator (predecessor)
       */
      auto operator--() -> AVLmap_iterator_const&;

      /**
       * @brief Post-decrement operator (predecessor)
       */
      auto operator--(int) -> AVLmap_iterator_const;

      /**
       * @brief Dereferencing operator.
       * @return Reference to the node.
       */
      auto operator*() -> const Node&;

      /**
       * @brief Arrow operator.
       * @return Pointer to the node.
       */
      auto operator->() -> const Node*;

      /**
       * @brief Inequality operator.
       */
      auto operator!=(const AVLmap_iterator_const& rhs) -> bool;

      /**
       * @brief Equality operator.
       */
      auto operator==(const AVLmap_iterator_const& rhs) -> bool;

      friend AVLmap;
    };

    // end iterators are same for all AVLmaps, thus static
    // make AVLmap_iterator a friend
    // to allow AVLmap_iterator to access end iterators
    static AVLmap_iterator end_it;
    static AVLmap_iterator_const const_end_it;

  public:

    // Rule of 5

    /**
     * @brief Constructor
     */
    AVLmap();

    /**
     * @brief Copy Constructor
     */
    AVLmap(const AVLmap& rhs);

    /**
     * @brief Copy Assignment Operator
     */
    auto operator=(const AVLmap& rhs) -> AVLmap&;

    /**
     * @brief Move Constructor
     */
    AVLmap(AVLmap&& rhs);

    /**
     * @brief Move Assignment Operator
     */
    AVLmap& operator=(AVLmap&& rhs);

    /**
     * @brief Virtual Destructor
     */
    virtual ~AVLmap();

    /**
     * @brief Getter for the size
     * @return The size of the tree
     */
    auto size() -> unsigned int;

    /**
     * @brief Getter for the depth of a node in the tree
     * @param node The node to get the depth of
     * @return The depth of the given node
     */
    auto getdepth(Node*& node) const -> unsigned int;

    /**
     * @brief Indexer for the map
     * @param key The key to search for (will create a node if there isn't one)
     * @return Reference to the value
     */
    auto operator[](const K& key) -> V&;

    // next method doesn't make sense
    // because operator[] inserts a non-existing element
    // which is not allowed on const maps
    // VALUE_TYPE operator[](int key) const;

    /**
     * @brief Returns an iterator to the first node of the tree
     */
    auto begin() -> iterator;

    /**
     * @brief Returns an iterator to the last node of the tree
     */
    auto end() -> iterator;

    /**
     * @brief Searches for a value using the key
     */
    auto find(const K& key) -> iterator;

    /**
     * @brief Searches for a value using the key and erases it
     */
    auto erase(iterator it) -> void;

    /**
     * @brief Returns an iterator to the first node of the tree
     */
    auto begin() const -> const_iterator;

    /**
     * @brief Returns an iterator to the last node of the tree
     */
    auto end() const -> const_iterator;

    /**
     * @brief Searches for a value using the key
     */
    auto find(const K& key) const -> const_iterator;

    // do not need this one (why) (because const functions should not be able to
    // edit the tree) AVLmap_iterator_const erase(AVLmap_iterator& it) const;

    /**
     * @brief Integrity for the check of the tree
     * @return Whether the tree is valid
     */
    auto sanityCheck() -> bool;

    /**
     * @brief Get the edge to display the tree for a given node
     * @return The character to use for rendering
     */
    auto get_edge_symbol(const Node* node) const -> char;

    /**
     * @brief Print method for the tree
     */
    auto print(std::ostream& os, bool print_value = false) const -> void;

    // inner class (AVLmap_iterator) doesn't have any special priveleges
    // in accessing private data/methods of the outer class (AVLmap)
    // so need friendship to allow AVLmap_iterator to access private
    // "AVLmap::end_it" BTW - same is true for outer class accessing inner class
    // private data
    friend struct AVLmap_iterator;
    friend struct AVLmap_iterator_const;

  private:

    /**
     * @brief Result of a node query
     */
    struct NodeSearch {
      Node& node;
      std::size_t depth;
    };

    /**
     * @brief Search for a given node with a key
     * @param key The key to search for
     * @return Optional to the found node
     */
    auto search_node(K key) const -> std::optional<NodeSearch>;

    /**
     * @brief Delete the whole tree
     */
    auto clear() -> void;

    /**
     * @brief The root of the AVL
     */
    Node* root{nullptr};

    /**
     * @brief The amount of elements in the AVL
     */
    unsigned int size_{0};
  };

  /**
   * @brief Left bitshift operator for printing
   * @param os The stream to print to
   * @param map The map to print
   * @return The stream that was used to print
   */
  template<typename KEY_TYPE, typename VALUE_TYPE>
  auto operator<<(std::ostream& os, const AVLmap<KEY_TYPE, VALUE_TYPE>& map)
    -> std::ostream&;
} // namespace CS280

  #ifndef AVL_CPP
    #include "avl-map.cpp"
  #endif

#endif
