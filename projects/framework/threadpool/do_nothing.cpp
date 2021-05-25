#include "do_nothing.hpp"

DoNothing::DoNothing(int priority_)
    : Task(priority_)
{}

void DoNothing::Execute()
{
}