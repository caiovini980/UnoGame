#include "PlayerBehaviour.h"

PlayerBehaviour::PlayerBehaviour(std::string&& name)
    : playerName(std::move(name))
{}

std::string* PlayerBehaviour::GetName()
{
    return &playerName;
}
