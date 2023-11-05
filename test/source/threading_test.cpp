#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "threading" ? 0 : 1;
}
