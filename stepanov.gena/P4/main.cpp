#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error in command line argument\n";
    return 1;
  }

  int typeMatrix = 0;
  char* endOfParsing = nullptr;

  try
  {
    typeMatrix = std::strtoll(argv[1], std::addressof(endOfParsing), 10);
  }
  catch (const std::out_of_range&)
  {
    std::cerr << "Value of first CLA is too large\n";
    return 1;
  }
  catch (const std::invalid_argument&)
  {
    std::cerr << "Cannot parse a value\n";
    return 1;
  }

  if (*endOfParsing != '\0')
  {
    std::cerr << "Wrong first argument\n";
    return 1;
  }

  using namespace stepanov;

  size_t rows = 0, cols = 0;
  size_t count = 0, strnum = 0;

  std::ifstream input(argv[2]);
  input >> rows >> cols;
  if (!input)
  {
    std::cerr << "Cannot read a number\n";
    return 2;
  }

  int array[10000] = {};
  int* matrix = nullptr;

  if (typeMatrix == 1)
  {
    matrix = array;
  }
  else if (typeMatrix == 2)
  {
    try
    {
      matrix = new int [rows * cols];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Not enough memory\n";
      return 3;
    }
  }
  else
  {
    std::cerr << "The first number is neither 1 nor 2\n";
    return 1;
  }
}
