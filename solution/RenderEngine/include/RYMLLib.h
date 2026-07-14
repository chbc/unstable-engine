#include "ryml.hpp"

#include <string>

namespace sre
{

namespace RYMLLib
{

c4::substr toC4Substr(std::string& buffer);
void readString(c4::yml::ConstNodeRef node, std::string& target);

} // namespace RYMLLib

} // namespace sre
