#pragma once

#include "math/matrix.hpp"
#include "math/smatrix.hpp"

template <typename MatrixType, bool IsConst = true>
class MatrixView {
public:
    using ElemType = typename MatrixType::T;

    template <bool OtherIsConst>
    MatrixView(const MatrixView<MatrixType, OtherIsConst>& o)
    requires(IsConst)
        : matrix_{&o},
          colBeg_{o.colBeg_},
          colLen_{o.colLen_},
          rowBeg_{o.rowBeg_},
          rowLen_{o.rowLen_},
          col_{o.col_},
          row_{o.row_} {}

    MatrixView(const MatrixView<MatrixType, false>& o)
    requires(!IsConst)
        : matrix_{&o},
          colBeg_{o.colBeg_},
          colLen_{o.colLen_},
          rowBeg_{o.rowBeg_},
          rowLen_{o.rowLen_},
          col_{o.col_},
          row_{o.row_} {}

    MatrixView(const MatrixType& m)
    requires(IsConst)
        : matrix_{&m},
          colBeg_{0},
          colLen_{m.ColNum()},
          rowBeg_{0},
          rowLen_{m.RowNum()},
          col_{m.ColNum()},
          row_{m.RowNum()} {}

    MatrixView(MatrixType& m)
    requires(!IsConst)
        : matrix_{&m},
          colBeg_{0},
          colLen_{m.ColNum()},
          rowBeg_{0},
          rowLen_{m.RowNum()},
          col_{m.ColNum()},
          row_{m.RowNum()} {}

    MatrixView(const MatrixType& m, size_t colBeg, size_t colLen, size_t rowBeg,
               size_t rowLen)
    requires(IsConst)
        : matrix_{&m},
          colBeg_{colBeg},
          colLen_{colLen},
          rowBeg_{rowBeg},
          rowLen_{rowLen},
          col_{m.ColNum()},
          row_{m.RowNum()} {
        assert(colBeg + colLen <= m.ColNum() && rowBeg + rowLen <= m.RowNum());
    }

    MatrixView(MatrixType& m, size_t colBeg, size_t colLen, size_t rowBeg,
               size_t rowLen)
    requires(!IsConst)
        : matrix_{&m},
          colBeg_{colBeg},
          colLen_{colLen},
          rowBeg_{rowBeg},
          rowLen_{rowLen},
          col_{m.ColNum()},
          row_{m.RowNum()} {
        assert(colBeg + colLen <= m.ColNum() && rowBeg + rowLen <= m.RowNum());
    }

    MatrixView(const MatrixView&) = default;
    MatrixView(MatrixView&&) = default;

    size_t ElemCount() const noexcept { return colLen_ * rowLen_; }

    size_t ColBegin() const noexcept { return colBeg_; }

    size_t RowBegin() const noexcept { return rowBeg_; }

    size_t ColNum() const noexcept { return colLen_; }

    size_t RowNum() const noexcept { return rowLen_; }

    size_t ColEnd() const noexcept { return colBeg_ + colLen_; }

    size_t RowEnd() const noexcept { return rowBeg_ + rowLen_; }

    bool IsSquare() const noexcept { return colLen_ == rowLen_; }

    auto operator[](size_t idx) const noexcept
    requires(IsConst)
    {
        assert(idx < colLen_);
        return Column<ElemType, IsConst>(*(matrix_->Ptr() + row_ * (idx + colBeg_) + rowBeg_),
                                  rowLen_);
    }

    auto operator[](size_t idx) noexcept
    requires(!IsConst)
    {
        assert(idx < colLen_);
        return Column<ElemType, IsConst>(*(matrix_->Ptr() + row_ * (idx + colBeg_) + rowBeg_),
                                  rowLen_);
    }

    MatrixType Clone() const {
        return *matrix_;
    }

private:
    std::conditional_t<IsConst, const MatrixType*, MatrixType*> matrix_ = nullptr;
    size_t colBeg_, colLen_, rowBeg_, rowLen_;
    size_t col_, row_;
};