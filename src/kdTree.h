// A C++ program to demonstrate operations of KD tree
// Adapted from:
// https://www.geeksforgeeks.org/search-and-insertion-in-k-dimensional-tree/
#ifndef KDTREE_H
#define KDTREE_H

#include <bits/stdc++.h>

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

// A structure to represent node of kd tree
template <class T> class Elem
{
public:
    Elem( LVector3f point, T value )
        : point( point )
        , left( NULL )
        , right( NULL )
        , value( value )
        {};
    ~Elem()
    {
        if( this->left != NULL )
        {
            delete this->left;
        }
        if( this->right != NULL )
        {
            delete this->right;
        }
    };

    T get_value() { return this->value; }

    template<class U> friend class KDTree;
private:
    LVector3f point; // To store k dimensional point
    Elem *left, *right;
    T value;
};

template <class T> class KDTree {

public:
    KDTree()
        : root( NULL ) {};
    ~KDTree()
    {
        if( this->root )
            delete this->root;
    }

    Elem<T>* insert( LVector3f point, T value )
    {
        Elem<T>* n = this->insert_rec(this->root, point, 0, value);
        if( this->root == NULL )
            this->root = n;
        return n;
    }

    T search( LVector3f point )
    {
        // Pass current depth as 0
        Elem<T>* closest = search_rec(this->root, point, 0);
        return closest->value;
    }

private:
    Elem<T>* insert_rec( Elem<T>* root, LVector3f point, unsigned depth, T value )
    {
        // Tree is empty?
        if (root == NULL)
            return new Elem<T>( point, value );
     
        // Calculate current dimension (cd) of comparison
        unsigned cd = depth % 3;
     
        // Compare the new point with root on current dimension 'cd'
        // and decide the left or right subtree
        if (point[cd] < (root->point[cd]))
            root->left = insert_rec(root->left, point, depth + 1, value);
        else
            root->right = insert_rec(root->right, point, depth + 1, value);
     
        return root;
    }

    Elem<T>* search_rec( Elem<T>* root, LVector3f point, unsigned depth )
    {
        std::cout << "search_rec" << root << " " << point << " " << depth << std::endl;
        // Base cases
        if (root == NULL)
            return NULL;
        if (root->point == point)
            return root;
     
        // Current dimension is computed using current depth and total
        // dimensions (k)
        unsigned cd = depth % 3;
     
        // Compare point with root with respect to cd (Current dimension)
        if (point[cd] < root->point[cd])
            return this->search_rec(root->left, point, depth + 1);
     
        return this->search_rec(root->right, point, depth + 1);
    }
    
    Elem<T>* root;
};

#endif
