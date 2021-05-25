#include <iostream>
#include <new>
#include <cassert>
#include <cstdio>

#include "templated_stack.hpp"
#include "tests.h"

int main()
{
  Stack<double> double_stack;
  Stack<std::string> string_stack;

  double_stack.Push(3.2);
  string_stack.Push("whassup");
  std::cout << "value is " << double_stack.Top() << std::endl;
	// Stack<int> stack;
	// Stack<int> new_stack;
  //
	// stack.Push(5);
	// stack.Push(7);
	// stack.Push(3);
  //
	// WrapperCompareInt("Top", (int)stack.Top() == 3, 1);
  //
	// stack.Pop();
  //
	// WrapperCompareInt("Top", (int)stack.Top() == 7, 1);
  //
	// WrapperCompareSizet("Count", stack.Count() == 2, 1);
  //
	// stack.Push(2);
	// WrapperCompareInt("Top", (int)stack.Top() == 2, 1);
	// WrapperCompareSizet("Count", stack.Count() == 3, 1);
  //
	// stack.Pop();
	// stack.Pop();
	// WrapperCompareInt("IsEmpty", stack.IsEmpty() == 0, 1);
	// stack.Pop();
	// WrapperCompareSizet("Count", stack.Count() == 0, 1);
	// WrapperCompareInt("IsEmpty", stack.IsEmpty() == 1, 1);
  //
	// stack.Push(1);
	// stack.Push(2);
	// stack.Push(3);
	// new_stack.Push(4);
	// new_stack.Push(5);
	// new_stack.Push(6);
	// stack = new_stack;
  //
	// Stack<int> new_new_stack(stack);
}
