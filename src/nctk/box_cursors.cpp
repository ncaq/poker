#include "box_cursors.hpp"

namespace nctk
{
    std::ifstream arrow::ifs("arrow.txt");
    std::string   arrow::view_ = std::string(std::istreambuf_iterator<char>(arrow::ifs), std::istreambuf_iterator<char>());
}
