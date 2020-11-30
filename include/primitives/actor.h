/// @file actor.h
/// @author Alberto Santagostino

#ifndef PRIMITIVES_ACTOR_H
#define PRIMITIVES_ACTOR_H

namespace commonlib
{
/// @class Actor
/// @brief Generic movable object represented by a character that can be placed on a Grid
class Actor
{
  public:
    Actor();
    Actor(const std::size_t id);
    Actor(const std::size_t id, unsigned char character);

    inline const unsigned char GetCharacter() { return m_character; }
    inline void SetCharacter(char character) { m_character = character; }

    inline const std::size_t Id() { return m_id; }

    Actor& operator=(const Actor& other);

  private:
    char m_character;
    std::size_t m_id;
    std::size_t m_x;
    std::size_t m_y;
};

Actor::Actor()
{}

Actor::Actor(std::size_t id) : m_id(id)
{}

Actor::Actor(std::size_t id, unsigned char character) : m_id(id), m_character(character)
{}

Actor& Actor::operator=(const Actor& other)
{
    m_id = other.m_id;
    m_character = other.m_character;
    return *this;
}

}  // namespace commonlib

#endif  // PRIMITIVES_ACTOR_H
