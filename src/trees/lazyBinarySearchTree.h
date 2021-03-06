#ifndef lazyBINARY_SEARCH_TREE_H
#define lazyBINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <vector>
using namespace std;       

// lazyBinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class lazyBinarySearchTree
{
  public:
    lazyBinarySearchTree( ) : root{ nullptr }
    {
        removeCounter=0;
        insertCounter=0;
        containsCounter=0;
        sucRemove=0;       
    }

    /**
     * Copy constructor
     */
    lazyBinarySearchTree( const lazyBinarySearchTree & rhs ) : root{ nullptr }
    {
        removeCounter=0;
        insertCounter=0;
        containsCounter=0;
        sucRemove=0;
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    lazyBinarySearchTree( lazyBinarySearchTree && rhs ) : root{ rhs.root }
    {
        removeCounter=0;
        insertCounter=0;
        containsCounter=0;
        sucRemove=0;
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~lazyBinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    lazyBinarySearchTree & operator=( const lazyBinarySearchTree & rhs )
    {
        lazyBinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    lazyBinarySearchTree & operator=( lazyBinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) 
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    /* code by andrew baumann*/
    int returnRC()
    {
        return removeCounter;
    }
    int returnCC()
    {
        return containsCounter;
    }
    int returnIC()
    {
        return insertCounter;
    }

    int getNum() const
    {
        getNum(root);
    }

    int height() const
    {
        height(root,0);
    }

    int path() const
    {
        path(root,0);
    }

    int returnRemove() const
    {
        return sucRemove;
    }

    void reset()
    {
        reset(root);
    }

    vector<string> returnSearch()
    {
    	return enzs;
    }
    /*end of code by andrew baumann*/


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

  private:
    int removeCounter;
    int containsCounter;
    int insertCounter;
    int sucRemove;
    vector<string> enzs;
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        bool deleted;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, bool b = 0 )
          : element{ theElement }, left{ lt }, right{ rt }, deleted{ b } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, bool b = 0 )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt }, deleted{ b } { }
    };

    BinaryNode *root;
    /*additional coding by andrew baumann*/
    int getNum(BinaryNode *t) const
    {
        if(t == nullptr)
            return 0;
        else
           return getNum(t->right) + getNum(t->left) + 1;
    }

    int height(BinaryNode *t, int lvl) const
    {
        if(t == nullptr)
            return 0;
        else if(t->right == nullptr && t->left == nullptr)
            return lvl;
        else 
            return heightMax(height(t->right,lvl+1), height(t->left,lvl+1));        
    }

    int heightMax(int x, int y) const
    {
        if(x>y)
            return x;
        else
            return y;
    }

    int path(BinaryNode *t, int lvl) const
    {
        if(t == nullptr)
            return 0;
        else
            return path(t->right,lvl+1)+path(t->left,lvl+1)+lvl;
    }

    void reset(BinaryNode *t)
    {
        removeCounter=0;
        containsCounter=0;
        insertCounter=0;
        sucRemove=0;
    }


    /* end of additional coding */

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        insertCounter++;
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else if ( t->element == x)//NEW CODE FOR DUPLICATE ENTRIES HERE (BY ANDREW BAUMANN)
        	t->element.merge(x);
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        insertCounter++;
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else if ( t->element == x)//NEW CODE FOR DUPLICATE ENTRIES HERE (BY ANDREW BAUMANN)
        	t->element.merge(x);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        removeCounter++;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if(t->deleted == true)
            return;
        else
        {   
            //new code by andrew baumann for lazy deletion
            sucRemove++;
            t->deleted = true;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) 
    {
        containsCounter++;
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else if(t->deleted == false)
        {
        	enzs = t->element.returnNames(); 
            return true;
        }
        else
            return false;   
        
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
