// File is a simple class that stores values for a specific spring
#pragma once
#include <iostream>

class Spring
{
public:
    Spring() = default;
    Spring(double springConstant, double equiLength) :
        m_springConstant(springConstant),
        m_equiLength(equiLength) {};
    Spring(const Spring& sp) :
        m_springConstant(sp.m_springConstant),
        m_equiLength(sp.m_equiLength) {};

    // assignment operator overloading to use with copy constructors
    // no move assignment necessary since we are not heap-allocating
    Spring& operator=(const Spring& rhs)
    {
        if (this == &rhs) return *this;
        else
        {
            m_springConstant = rhs.m_springConstant;
            m_equiLength = rhs.m_equiLength;
            return *this;
        } 
    }

    inline double k(void) const { return m_springConstant; }
    inline double L0(void) const { return m_equiLength; }

    friend std::ostream& operator<<(std::ostream& out, const Spring& sp)
    {
        out << "k = " << sp.k() << '\n' << "L0 = " << sp.L0() << '\n';
        return out;
    }

private:
    double m_springConstant;
    double m_equiLength;
};