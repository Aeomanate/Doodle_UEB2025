// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "ECollisions.h"

#include "CCollisions.h"

ECollisions::ECollisions()
: Entity("Collisions")
{
    Claim<CCollisions>();
}
