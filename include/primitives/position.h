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
    Position(std::pair<T, T> xy_pair);
    Position<T> operator+=(const Position<T>& other);
    Position<T> operator*(const int other);
    T x;
    T y;
};

template <typename T>
Position<T>::Position() : x(), y()
{}

template <typename T>
Position<T>::Position(T x, T y) : x(x), y(y)
{}

template <typename T>
Position<T>::Position(std::pair<T, T> xy_pair) : x(xy_pair.first), y(xy_pair.second)
{}

template <typename T>
Position<T> Position<T>::operator+=(const Position<T>& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template <typename T>
Position<T> Position<T>::operator*(const int other)
{
    Position ret;
    ret.x = x * other;
    ret.y = y * other;
    return ret;
}

template <typename T>
Position<T> operator+(const Position<T>& p1, const Position<T>& p2)
{
    Position<T> ret;
    ret.x = p1.x + p2.x;
    ret.y = p1.y + p2.y;
    return ret;
}

}  // namespace commonlib

#endif  // PRIMITIVES_POSITION_H
