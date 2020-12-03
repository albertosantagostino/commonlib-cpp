/// @file matrix.h
/// @author Alberto Santagostino

#ifndef PRIMITIVES_POSITION_H
#define PRIMITIVES_POSITION_H

namespace commonlib
{
/// @class Position
/// @brief 2D generic matrix template
/// @tparam T Type of data stored
template <typename T>
class Position
{
  public:
    Position();
    Position(T x, T y);
    Position<T> operator+=(const Position<T>& other);
    T x;
    T y;
};

template <typename T>
Position<T>::Position(T x, T y) : x(x), y(y)
{}

template <typename T>
Position<T> Position<T>::operator+=(const Position<T>& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
Position<T> operator+(const Position<T>& p1, const Position<T>& p2)
{
    T x{p1.x + p2.x};
    T y{p1.y + p2.y};
    Position<T> ret;
    ret.x = x;
    ret.y = y;
    return ret;
}

}  // namespace commonlib

#endif  // PRIMITIVES_POSITION_H
