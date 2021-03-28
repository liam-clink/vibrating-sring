#include "../include/Spring.hpp"

Spring& Spring::operator=(const Spring& rhs)
{
    if (this == &rhs) return *this;
    else
    {
        m_springConstant = rhs.m_springConstant;
        m_equiLength = rhs.m_equiLength;
        return *this;
    } 
}

std::ostream& operator<<(std::ostream& out, const Spring& sp)
{
    out << "k = " << sp.k() << '\n' << "L0 = " << sp.L0() << '\n';
    return out;
}