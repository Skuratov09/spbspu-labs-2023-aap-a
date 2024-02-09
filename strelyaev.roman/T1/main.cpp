#include <iostream>
#include <iomanip>
#include "base-types.hpp"
#include "shape.hpp"
#include <cstring>
#include "rectangle.hpp"
#include "triangle.hpp"
#include "parallelogram.hpp"
#include "inputShapes.hpp"
#include "stringProc.hpp"

using namespace strelyaev;

int main ()
{
  const size_t maxshapes = 1000;
  char * string = nullptr;
  size_t current_index = 0;
  Shape * list[maxshapes] = {nullptr};
  bool errors = false;

  std::cin >> std::noskipws;
  while (std::cin.good())
  {
    if (!std::cin.good())
    {
      std::cerr << "Something went wrong with the input\n";
      for (size_t i = 0; i < current_index; i++)
      {
        delete list[i];
      }
      return 1;
    }
    string = nullptr;
    try
    {
      string = inputString(std::cin);
    }
    catch (const std::logic_error& e)
    {
      std::cerr << e.what() << "\n";
      delete [] string;
      for (size_t i = 0; i < current_index; i++)
      {
        delete list[i];
      }
      return 2;
    }
    if (strncmp("SCALE", string, 5) == 0)
    {
      size_t pos = 0;
      const char * argument_string = string + 6;
      double arguments[3]{};
      for (size_t i = 0; i < 3; ++i)
      {
        arguments[i] = std::stod(argument_string, std::addressof(pos));
        argument_string += pos;
      }
      try
      {
        scaleShapes(list, current_index, arguments, std::cout);
        delete [] string;
        break;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        delete [] string;
        for (size_t i = 0; i < current_index; i++)
        {
          delete list[i];
        }
        return 2;
      }
    }
    Shape * new_shape = nullptr;
    try
    {
      new_shape = getShape(string);
      if (new_shape != nullptr)
      {
        list[current_index++] = new_shape;
      }
    }
    catch(const std::invalid_argument & e)
    {
      delete new_shape;
      errors = true;
    }
    delete [] string;
  }
  std::cin >> std::skipws;
  if (errors)
  {
    std::cerr << "Some shapes are incorrect!\n";
  }
  for (size_t i = 0; i < current_index; i++)
  {
    delete list[i];
  }
}
