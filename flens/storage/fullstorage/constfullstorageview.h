/*
 *   Copyright (c) 2007, Michael Lehn
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2) Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in
 *      the documentation and/or other materials provided with the
 *      distribution.
 *   3) Neither the name of the FLENS development group nor the names of
 *      its contributors may be used to endorse or promote products derived
 *      from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FLENS_STORAGE_FULLSTORAGE_CONSTFULLSTORAGEVIEW_H
#define FLENS_STORAGE_FULLSTORAGE_CONSTFULLSTORAGEVIEW_H 1

#include <cxxblas/typedefs.h>
#include <flens/typedefs.h>
#include <flens/storage/indexoptions.h>

namespace flens {

template <typename T, typename I, typename A>
    class Array;

template <typename T, typename I, typename A>
    class ArrayView;

template <typename T, typename I, typename A>
    class ConstArrayView;

template <typename T, StorageOrder Order, typename I, typename A>
    class FullStorage;

template <typename T, StorageOrder Order, typename I, typename A>
    class FullStorageView;

template <typename T,
          StorageOrder Order,
          typename I = IndexOptions<>,
          typename A = std::allocator<T> >
class ConstFullStorageView
{
    public:
        typedef T                                     ElementType;
        typedef typename I::IndexType                 IndexType;
        typedef A                                     Allocator;

        static const StorageOrder                     order = Order;
        static const IndexType                        defaultIndexBase
                                                          = I::defaultIndexBase;

        typedef ConstFullStorageView                  ConstView;
        typedef FullStorageView<T, Order, I, A>       View;
        typedef FullStorage<T, Order, I, A>           NoView;

        typedef flens::ConstArrayView<T, I, A>        ConstArrayView;
        typedef flens::ArrayView<T, I, A>             ArrayView;
        typedef flens::Array<T, I, A>                 Array;

        ConstFullStorageView(IndexType numRows, IndexType numCols,
                             const ElementType *data,
                             IndexType leadingDimension,
                             IndexType firstRow = I::defaultIndexBase,
                             IndexType firstCol = I::defaultIndexBase,
                             const Allocator &allocator = Allocator());

        template <typename ARRAY>
            ConstFullStorageView(IndexType numRows, IndexType numCols,
                                 ARRAY &array,
                                 IndexType leadingDimension,
                                 IndexType firstRow = I::defaultIndexBase,
                                 IndexType firstCol = I::defaultIndexBase,
                                 const Allocator &allocator = Allocator());

        ConstFullStorageView(const ConstFullStorageView &rhs);

        template <typename RHS>
            ConstFullStorageView(const RHS &rhs);

        ~ConstFullStorageView();

        //-- operators ---------------------------------------------------------

        const ElementType &
        operator()(IndexType row, IndexType col) const;

        //-- methods -----------------------------------------------------------

        IndexType
        firstRow() const;

        IndexType
        lastRow() const;

        IndexType
        firstCol() const;

        IndexType
        lastCol() const;

        IndexType
        numRows() const;

        IndexType
        numCols() const;

        IndexType
        leadingDimension() const;

        IndexType
        strideRow() const;

        IndexType
        strideCol() const;

        const ElementType *
        data() const;

        const Allocator &
        allocator() const;

        void
        changeIndexBase(IndexType firstRow, IndexType firstCol);

        // view of fullstorage scheme as an array
        const ConstArrayView
        arrayView(IndexType firstViewIndex = I::defaultIndexBase) const;

        // view of rectangular part
        const ConstView
        view(IndexType fromRow, IndexType fromCol,
             IndexType toRow, IndexType toCol,
             IndexType strideRow = IndexType(1),
             IndexType strideCol = IndexType(1),
             IndexType firstViewRow = I::defaultIndexBase,
             IndexType firstViewCol = I::defaultIndexBase) const;

        // view of single row
        const ConstArrayView
        viewRow(IndexType row,
                IndexType firstViewIndex = I::defaultIndexBase) const;

        const ConstArrayView
        viewRow(IndexType row,
                IndexType firstCol, IndexType lastCol,
                IndexType stride,
                IndexType firstViewIndex = I::defaultIndexBase) const;

        // view of single column
        const ConstArrayView
        viewCol(IndexType col,
                IndexType firstViewIndex = I::defaultIndexBase) const;

        const ConstArrayView
        viewCol(IndexType firstRow, IndexType lastRow,
                IndexType stride, IndexType col,
                IndexType firstViewIndex = I::defaultIndexBase) const;

        // view of d-th diagonal
        const ConstArrayView
        viewDiag(IndexType d,
                 IndexType firstViewIndex = I::defaultIndexBase) const;

        // view of d-th anti-diagonal
        const ConstArrayView
        viewAntiDiag(IndexType d,
                     IndexType firstViewIndex = I::defaultIndexBase) const;

    private:
        const ElementType    *data_;
        Allocator            allocator_;
        IndexType            numRows_, numCols_;
        IndexType            leadingDimension_;
        IndexType            firstRow_, firstCol_;
};

} // namespace flens

#endif // FLENS_STORAGE_FULLSTORAGE_CONSTFULLSTORAGEVIEW_H
