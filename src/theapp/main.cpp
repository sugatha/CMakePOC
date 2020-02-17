#include <iostream>
#include "mylibshared.h"

int main()
{
   std::cout << "Hey! - a shout from a terra-firmian :) " << std::endl;

   UseMyClass myclass_obj;
#ifdef _OOPS_
   std::cout << "Hey! - a shout from a sugathan :) " << std::endl;
#endif


   myclass_obj.PrintUseMyClassHello();
   return 0;
}