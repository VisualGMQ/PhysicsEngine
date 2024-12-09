#pragma once

#include <array>
#include <cmath>
#include <iostream>
#include <type_traits>

// vectors

// operation fwd declare

template <typename T, size_t Len>
class SVector;

template <typename T, size_t Len>
auto operator+(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept;

template <typename T, size_t Len>
auto operator-(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept;

template <typename T, size_t Len>
auto operator*(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept;

template <typename T, size_t Len>
auto operator/(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept;

template <typename Derive, typename ElemType, size_t Len>
class SVectorBase {
public:
    constexpr size_t ElemCount() const noexcept { return Len; }

    ElemType operator[](size_t idx) const noexcept {
        assert(idx < Len);
        return Ptr()[idx];
    }

    ElemType& operator[](size_t idx) noexcept {
        assert(idx < Len);
        return Ptr()[idx];
    }

    ElemType* Ptr() noexcept { return (ElemType*)this; }

    const ElemType* Ptr() const noexcept {
        return (ElemType*)this;
    }

    Derive operator-() const noexcept {
        Derive result;
        for (size_t i = 0; i < Len; ++i) {
            result[i] = -(*this)[i];
        }
        return result;
    }

    Derive& operator+=(const SVectorBase& o) noexcept {
        for (size_t i = 0; i < Len; ++i) {
            (*this)[i] = o[i] + (*this)[i];
        }
        return (Derive&)(*this);
    }
    
    Derive& operator-=(const SVectorBase& o) noexcept {
        for (size_t i = 0; i < Len; ++i) {
            (*this)[i] = (*this)[i] - o[i];
        }
        return (Derive&)(*this);
    }

    template <typename T>
    Derive& operator*=(T value) noexcept {
        for (size_t i = 0; i < Len; ++i) {
            (*this)[i] *= value;
        }
        return (Derive&)(*this);
    }
    
    template <typename T>
    Derive& operator*=(const SVectorBase& o) noexcept {
        for (size_t i = 0; i < Len; ++i) {
            (*this)[i] = (*this)[i] * o[i];
        }
        return (Derive&)(*this);
    }

    template <typename T>
    Derive& operator/=(T value) noexcept {
        for (size_t i = 0; i < Len; ++i) {
            (*this)[i] /= value;
        }
        return (Derive&)(*this);
    }
};

template <typename T, size_t Len>
class SVector : public SVectorBase<SVector<T, Len>, T, Len> {
public:
    using ElemType = T;
    static constexpr size_t ElemCount = Len;

    SVector() { memset(datas_, 0, sizeof(ElemType) * ElemCount); }

    template <typename U>
    requires(std::convertible_to<U, ElemType>)
    explicit SVector(U elem) {
        auto value = static_cast<ElemType>(elem);
        memset(datas_, value, sizeof(ElemType) * ElemCount);
    }

    template <typename... Us>
    requires(std::convertible_to<Us, ElemType> && ...)
    explicit SVector(Us... elems) {
        auto datas[] = {static_cast<ElemType>(elems)...};
        memset(datas, 0, sizeof(ElemType) * ElemCount);
        memcpy(datas, &datas, sizeof(datas));
    }

private:
    ElemType datas_[ElemCount];
};

template <typename T>
class SVector<T, 2> : public SVectorBase<SVector<T, 2>, T, 2> {
public:
    using ElemType = T;
    static constexpr size_t ElemCount = 2;

    union {
        ElemType x, s, w;
    };
    
    union {
        ElemType y, r, h;
    };

    SVector(T x, T y) : x{x}, y{y} {}

    SVector() : x{ElemType{}}, y{ElemType{}} {}

    explicit SVector(T value) : x{value}, y{value} {}
};

template <typename T>
class SVector<T, 3> : public SVectorBase<SVector<T, 3>, T, 3> {
public:
    using ElemType = T;
    static constexpr size_t ElemCount = 3;

    union { ElemType x, s, w; };
    union { ElemType y, r, h; };
    union { ElemType z, t, l; };

    SVector(T x, T y, T z) : x{x}, y{y}, z{z} {}

    SVector() : x{0}, y {0}, z{0} {}

    explicit SVector(T value) : x{value}, y{value}, z{value} {}
};

template <typename T>
class SVector<T, 4> : public SVectorBase<SVector<T, 4>, T, 4> {
public:
    using ElemType = T;
    static constexpr size_t ElemCount = 4;

    union {
        ElemType x, r;
    };
    union {
        ElemType y, g;
    };
    union {
        ElemType z, b;
    };
    union {
        ElemType w, a;
    };

    SVector() : x{ElemType{}}, y{ElemType{}}, z{ElemType{}}, w{ElemType{}} {}

    SVector(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} {}

    explicit SVector(T value) : x{value}, y{value}, z{value}, w{value} {}
};

// operations

template <typename T, size_t Len>
auto operator+(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] + v2[i];
    }
    return v;
}

template <typename T, size_t Len>
auto operator-(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] - v2[i];
    }
    return v;
}

template <typename T, size_t Len>
auto operator*(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] * v2[i];
    }
    return v;
}

template <typename T, typename U, size_t Len>
auto operator*(const SVector<T, Len>& v1, U value) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] * value;
    }
    return v;
}

template <typename T, typename U, size_t Len>
auto operator*(U value, const SVector<T, Len>& v) noexcept {
    return v * value;
}

template <typename T, size_t Len>
auto operator/(const SVector<T, Len>& v1, const SVector<T, Len>& v2) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] / v2[i];
    }
    return v;
}

template <typename T, typename U, size_t Len>
auto operator/(const SVector<T, Len>& v1, U value) noexcept {
    SVector<T, Len> v;
    for (int i = 0; i < Len; i++) {
        v[i] = v1[i] / value;
    }
    return v;
}

template <typename T, size_t Len>
std::ostream& operator<<(std::ostream& o, const SVector<T, Len>& view) {
    o << "[" << std::endl;
    for (int i = 0; i < Len; i++) {
        o << view[i] << std::endl;
    }
    o << "]";
    return o;
}

// matrix

template <typename T, size_t Col, size_t Row>
class SMatrix {
public:
    using ElemType = T;

    static SMatrix Zeros() { return {}; }

    static SMatrix Identity() {
        SMatrix m;
        m.Diagonal(1);
        return m;
    }

    static SMatrix Ones() {
        SMatrix m;
        m.Fill(1);
        return m;
    }

    template <typename U>
    requires std::convertible_to<U, ElemType>
    static SMatrix Fill(U elem) {
        SMatrix m;
        m.Fill(elem);
        return m;
    }

    template <typename... Ts>
    static SMatrix FromRow(Ts... elems) {
        SMatrix m;
        m.SetValuesFromRow(elems...);
        return m;
    }

    template <typename... Ts>
    static SMatrix FromCol(Ts... elems) {
        SMatrix m;
        m.SetValuesFromCol(elems...);
        return m;
    }

    template <typename... Ts>
    requires(std::convertible_to<Ts, ElemType> && ...)
    static SMatrix Diag(Ts... elems) {
        SMatrix m;
        m.Diagonal(elems...);
        return m;
    }

    SMatrix() = default;

    SMatrix(const SMatrix& o) : data_{o.data_} {}

    SMatrix(SMatrix&& o) : data_{o.data_} {}

    SMatrix& operator=(SMatrix&& o) {
        if (&o != this) {
            data_ = std::move(o.data_);
        }
        return *this;
    }

    SMatrix& operator=(const SMatrix& o) {
        if (&o != this) {
            data_ = o.data_;
        }
        return *this;
    }

    template <typename... Ts>
    requires((std::convertible_to<Ts, ElemType> && ...) && sizeof...(Ts) >= 1)
    void SetValuesFromRow(Ts... elems) {
        ElemType datas[] = {static_cast<ElemType>(elems)...};
        for (int i = 0; i < std::min(sizeof...(elems), ElemCount()); i++) {
            size_t row = i / Col;
            size_t col = i % Col;
            operator[](col)[row] = datas[i];
        }
    }

    template <typename... Ts>
    requires((std::convertible_to<Ts, ElemType> && ...) && sizeof...(Ts) >= 1)
    void SetValuesFromCol(Ts... elems) {
        ElemType datas[] = {static_cast<ElemType>(elems)...};
        auto ptr = Ptr();
        memcpy(ptr, datas, sizeof(datas));
    }

    template <typename FirstType, typename... OtherTypes>
    void Diagonal(FirstType elem, OtherTypes... elems) {
        auto minLen = std::min(Col, Row);
        constexpr size_t elemCount = sizeof...(elems);
        if constexpr (elemCount == 0) {
            for (int i = 0; i < minLen; i++) {
                (*this)[i][i] = elem;
            }
        } else {
            ElemType datas[] = {static_cast<ElemType>(elem),
                                static_cast<ElemType>(elems)...};
            for (int i = 0; i < std::min(minLen, elemCount); i++) {
                (*this)[i][i] = datas[i];
            }
        }
    }

    template <typename U>
    void Fill(U elem) {
        auto elemCount = ElemCount();
        memset(Ptr(), elem, sizeof(ElemType) * elemCount);
    }

    auto operator[](size_t i) const noexcept { return data_[i]; }

    auto& operator[](size_t i) noexcept { return data_[i]; }

    bool operator==(const SMatrix& o) const noexcept {
        for (int r = 0; r < Row; r++) {
            for (int c = 0; c < Col; c++) {
                if ((*this)[c][r] != (*this)[c][r]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const SMatrix& o) const noexcept { return !(*this == o); }

    constexpr size_t ElemCount() const noexcept { return Col * Row; }

    ElemType* Ptr() { return data_[0].Ptr(); }

    const ElemType* Ptr() const { return data_[0].Ptr(); }

    constexpr auto ColNum() const noexcept { return Col; }

    constexpr auto RowNum() const noexcept { return Row; }

private:
    std::array<SVector<ElemType, Row>, Col> data_;
};

// matrix operations

template <typename T, size_t Col, size_t Row>
SMatrix<T, Col, Row> operator+(const SMatrix<T, Col, Row>& m1,
                               const SMatrix<T, Col, Row>& m2) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] + m2[c][r];
        }
    }
    return m;
}

template <typename T, size_t Col, size_t Row>
SMatrix<T, Col, Row> operator-(const SMatrix<T, Col, Row>& m1,
                               const SMatrix<T, Col, Row>& m2) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] - m2[c][r];
        }
    }
    return m;
}

template <typename T, typename U, size_t Col, size_t Row>
SMatrix<T, Col, Row> operator*(const SMatrix<T, Col, Row>& m1, U value) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] * value;
        }
    }
    return m;
}

template <typename T, typename U, size_t Col, size_t Row>
SMatrix<T, Col, Row> operator*(U value, const SMatrix<T, Col, Row>& m1) {
    return m1 * value;
}

template <typename T, typename U, size_t Col, size_t Row>
SMatrix<T, Col, Row> operator/(const SMatrix<T, Col, Row>& m1, U value) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] / value;
        }
    }
    return m;
}

template <typename T, size_t Len, size_t Row, size_t Col>
SMatrix<T, Col, Row> operator*(const SMatrix<T, Len, Row>& m1,
                               const SMatrix<T, Col, Len>& m2) {
    SMatrix<T, Col, Row> mat;

    for (int m = 0; m < Row; m++) {
        for (int r = 0; r < Col; r++) {
            double sum = 0;
            for (int n = 0; n < Len; n++) {
                sum += m1[n][m] * m2[r][n];
            }
            mat[r][m] = sum;
        }
    }
    return mat;
}

template <typename T, size_t Col, size_t Row>
SMatrix<T, Col, Row> MulEach(const SMatrix<T, Col, Row>& m1,
                             const SMatrix<T, Col, Row>& m2) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] * m2[c][r];
        }
    }
    return m;
}

template <typename T, size_t Col, size_t Row>
SMatrix<T, Col, Row> DivEach(const SMatrix<T, Col, Row>& m1,
                             const SMatrix<T, Col, Row>& m2) {
    SMatrix<T, Col, Row> m;
    for (int c = 0; c < Col; c++) {
        for (int r = 0; r < Row; r++) {
            m[c][r] = m1[c][r] / m2[c][r];
        }
    }
    return m;
}

template <typename T, size_t Col, size_t Row>
SVector<T, Row> operator*(const SMatrix<T, Col, Row>& m,
                               const SVector<T, Col>& v) {
    SVector<T, Row> result;

    for (int r = 0; r < Row; r++) {
        result[r] = 0;
        for (int c = 0; c < Col; c++) {
            result[r] += m[c][r] * v[c];
        }
    }

    return result;
}