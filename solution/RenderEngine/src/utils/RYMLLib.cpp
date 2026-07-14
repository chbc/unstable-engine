#include "RYMLLib.h"

namespace sre
{

namespace RYMLLib
{

c4::substr toC4Substr(std::string& buffer)
{
    return c4::substr(buffer.data(), buffer.size());
}

void readString(c4::yml::ConstNodeRef node, std::string& target)
{
    c4::substr val;
    node >> val;
    target.assign(val.str, val.len);
}

} // namespace RYMLLib

} // namespace sre
