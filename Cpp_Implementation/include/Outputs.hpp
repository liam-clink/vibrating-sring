/*
 *  This file is for defining the output methods so we don't have
 *  to worry too much about having a bunch of cout and << statements in the code
 */

#pragma once
template<typename... Args>
void Print(std::ostream& out, Args&&... args)
{
    // Uses C++17 Folding Expressions
    ((out << std::forward<Args>(args) << '\t'), ...);
    out << '\n';
}