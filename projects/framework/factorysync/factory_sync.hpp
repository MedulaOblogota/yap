#ifndef RD70_FACTORYSYNC
#define RD70_FACTORYSYNC

#include "factory.hpp"
#include "shared_ptr.hpp"
#include "command.hpp"

SharedPtr<Command> Increment(void *do_nothing);

SharedPtr<Command> Decrement(void *do_nothing);

SharedPtr<Command> Exit(void *do_nothing);

void AcceptInput();

#endif //RD70_FACTORYSYNC
