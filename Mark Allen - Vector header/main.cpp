#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"

template <typename Object>
class Vector{
private:
    int theSize;
    int theCapacity;
    Object * objects;

public:
    explicit Vector( int initSize = 0 )
      : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
      { objects = new Object[ theCapacity ]; }

    Vector( const Vector & rhs )
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }

    Vector & operator= ( const Vector & rhs ){   /// 将rhs先复制一份， 为了防止对源数据的改动？
        /**
         it works by using the copy-constructor's functionality to create a local copy of the data,
         then takes the copied data with a swap function, swapping the old data with the new data. The
         temporary copy then destructs, taking the old data with it. We are left with a copy of the new data.
        */
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    ~Vector( )
      { delete [ ] objects; }

    Vector( Vector && rhs ) /// move-ctor
      : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector & operator= ( Vector && rhs ) /// move-ctor
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );

        return *this;
    }

    bool empty( ) const
      { return size( ) == 0; }
    int size( ) const
      { return theSize; }
    int capacity( ) const
      { return theCapacity; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
                                                     #endif
        return objects[ index ];
    }

    void resize( int newSize )
    {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }

    void reserve( int newCapacity )
    {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] ); /// move!!

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [ ] newArray;   /// old data were destructed with the newArray
    }

      // Stacky stuff
    void push_back( const Object & x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );  /// if size exceeds the capacity, call reserve() and expand the size doublely.
        objects[ theSize++ ] = x;
    }
      // Stacky stuff
    void push_back( Object && x )
    {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back( )
    {
        if( empty( ) )
            throw UnderflowException{ };
        --theSize;
    }

    const Object & back ( ) const
    {
        if( empty( ) )
            throw UnderflowException{ };
        return objects[ theSize - 1 ];
    }

      // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
      { return &objects[ 0 ]; }
    const_iterator begin( ) const
      { return &objects[ 0 ]; }
    iterator end( )
      { return &objects[ size( ) ]; }
    const_iterator end( ) const
      { return &objects[ size( ) ]; }

    static const int SPARE_CAPACITY = 2;

};

#endif
