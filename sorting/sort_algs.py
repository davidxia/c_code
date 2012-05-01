#!/usr/bin/env python

A = [3, 7, 4, 9, 5, 2, 6, 1]

def insertionSort( A ):
    '''Insertion sort'''

    for i in range( 1, len( A ) ):
        # The sequence A[ 0, ... , i - 1 ] is already sorted.
        # We're now sorting A[ i ]. Pull A[ i ] out and save into item.
        # Create a hole in the array where A[ i ] used to be.
        item = A[ i ]
        iHole = i

        # If the hole is before the beginning of the array and the item
        # before the hole is bigger than the item, move the bigger item up.
        while iHole > 0 and A[ iHole - 1 ] > item:
            A[ iHole ] = A[ iHole - 1 ]
            iHole -= 1

        A[ iHole ] = item

    return A


def selectionSort( A ):
    '''Selection sort'''

    for iPos in range( len( A ) ):
        iMin = iPos

        for i in range( iPos + 1, len( A ) ):
            if A[ i ] < A[ iMin ]: iMin = i

        if iMin != iPos:
            a = A[ iMin ]
            A[ iMin ] = A[ iPos ]
            A[ iPos ] = a

    return A


def bubbleSort( A ):
    '''Bubble sort'''

    swapped = True
    while swapped:
        swapped = False
        for i in range( 1, len( A ) ):
            if A[ i ] < A[ i - 1 ]:
                a = A[ i ]
                A[ i ] = A[ i - 1 ]
                A[ i - 1 ] = a
                swapped = True

    return A


def bubbleSortOpt1( A ):
    '''Optimized bubble sort'''

    swapped = True
    n = len( A )

    while swapped:
        swapped = False
        for i in range( 1, n ):
            if A[ i ] < A[ i - 1 ]:
                a = A[ i ]
                A[ i ] = A[ i - 1 ]
                A[ i - 1 ] = a
                swapped = True

        n -= 1

    return A


def bubbleSortOpt2( A ):
    '''
    Optimized bubble sort
    After every pass, all elements after the last swap are sorted,
    and do not need to be checked again.
    '''

    n = len( A )

    while n != 0:
        newn = 0
        for i in range( 1, n ):
            if A[ i ] < A[ i - 1 ]:
                a = A[ i ]
                A[ i ] = A[ i - 1 ]
                A[ i - 1 ] = a
                newn = i

        n = newn

    return A


def quicksort( A ):
    '''Quicksort'''

    if not A: return A
    else:
        pivot = A[ 0 ]
        lesser = quicksort( [x for x in A[ 1: ] if x <= pivot] )
        greater = quicksort( [x for x in A[ 1: ] if x > pivot] )
        return lesser + [pivot] + greater


def quicksortInPlace( A ):
    '''Quicksort in place variation'''

    def partition( theList, iLeft, iRight, iPivot ):
        """Moves all elements less than pivot before it, and those greater than
        pivot after."""

        # Move pivot to the end of the list.
        pivotVal = theList[ iPivot ]
        theList[ iPivot ] = theList[ iRight ]
        theList[ iRight ] = pivotVal

        iStore = iLeft

        for i in range( iLeft, iRight ):
            if theList[ i ] < pivotVal:
                a = theList[ i ]
                theList[ i ] = theList[ iStore ]
                theList[ iStore ] = a
                iStore += 1

            a = theList[ iStore ]
            theList[ iStore ] = theList[ iRight]
            theList[ iRight ] = a

        return iStore

    def qsort( theList, iLeft, iRight ):

        if iLeft < iRight:
            iPivot = (iLeft + iRight) / 2
            iNewPivot = partition( theList, iLeft, iRight, iPivot )
            qsort( theList, iLeft, iNewPivot )
            qsort( theList, iNewPivot, iRight )

    return qsort( A, 0, len( A ) - 1 )


def mergeSort( A ):

    def merge( left, right ):

        result = []
        while left or right:
            if left and right:
                if left[ 0 ] <= right[ 0 ]:
                    result.append( left[ 0 ] )
                    left = left[ 1: ]
                else:
                    result.append( right[ 0 ] )
                    right = right[ 1: ]
            elif left:
                result += left
                left = []
            elif right:
                result += right
                right = []

        return result

    # If list size is 1, consider it sorted and return it
    if len( A ) <= 1: return A
    iMiddle = len( A ) / 2 - 1
    left = [x for i, x in enumerate( A ) if i <= iMiddle]
    right = [x for i, x in enumerate( A ) if i > iMiddle]

    left = mergeSort( left )
    right = mergeSort( right )
    return merge( left, right )


if __name__ == '__main__':
    # insertionSort()
    # selectionSort()
    print bubbleSort( A )
    print '==================================='
    print bubbleSortOpt1( A )
    print '==================================='
    print bubbleSortOpt2( A )
    print '==================================='
    print quicksort( A )
    print '==================================='
    print mergeSort( A )
