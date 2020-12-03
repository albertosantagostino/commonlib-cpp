/// @file actor.h
/// @author Alberto Santagostino

#ifndef PRIMITIVES_ACTOR_H
#define PRIMITIVES_ACTOR_H

#ifdef TEST_BUILD
#include <primitives/position.h>
#else
#include <commonlib/include/primitives/position.h>
#endif

namespace commonlib
{
/// @class Actor
/// @brief Generic movable object represented by a character that can be placed on a Grid
class Actor
{
  public:
    // Constructors
    Actor();
    Actor(const std::size_t id);
    Actor(const std::size_t id, unsigned char character);

    // Setters
    inline void SetCharacter(char character) { m_character = character; }

    // Getters
    inline const unsigned char GetCharacter() { return m_character; }
    inline const std::size_t Id() { return m_id; }

    // Operators
    Actor& operator=(const Actor& other);

  private:
    char m_character;
    std::size_t m_id;
    // TODO: Add Position
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
