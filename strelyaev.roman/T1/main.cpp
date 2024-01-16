#include <iostream>
#include <iomanip>
#include "base-types.hpp"
#include "shape.hpp"
#include <cstring>
#include "rectangle.hpp"
#include "triangle.hpp"
#include "Parallelogram.hpp"
#include "inputShapes.hpp"
#include "stringProc.hpp"

using namespace strelyaev;

int main ()
{
  const size_t max_shapes = 1000;
  char * string = nullptr;
  size_t current_index = 0;
  Shape ** list = new Shape * [max_shapes]{nullptr};
  const char ** errors = new const char * [max_shapes]{nullptr};
  size_t errors_count = 0;

  std::cin >> std::noskipws;
  while (true)
  {
    if (!std::cin.good())
    {
      std::cout << "Something went wrong with input\n";
      return 1;
    }
    string = nullptr;
    try
    {
      string = inputString(std::cin);
    }
    catch (const std::logic_error & e)
    {
      std::cerr << e.what() << "\n";
      delete [] string;
      delete [] errors;
      for (size_t i = 0; i < current_index; i++)
      {
        delete list[i];
      }
      delete [] list;
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
        scaleShapes(list, current_index, arguments, max_shapes);
        delete [] string;
        break;
      }
      catch(const std::exception & e)
      {
        std::cerr << e.what() << '\n';
        delete [] string;
        for (size_t i = 0; i < current_index; i++)
        {
          delete list[i];
        }
        delete [] list;
        delete [] errors;
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
      errors[errors_count++] = e.what();
    }
    delete [] string;
  }
  std::cin >> std::skipws;

  printErrors(errors, max_shapes);
  for (size_t i = 0; i < current_index; i++)
  {
    delete list[i];
  }
  delete [] list;
  delete [] errors;
}
