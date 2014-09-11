#pragma once

#include <cstddef>

namespace lib
{

/** Collection of types. */
template<typename THead, typename ... TTail>
struct TypeList
{
    /** Head of collections. */
    typedef THead head_t;

    /** Collection without head. */
    typedef TypeList<TTail...> tail_t;

    /** Applies to every type in list from head to end. */
    static void apply()
    {
        head_t::apply();
        tail_t::apply();
    }
};

/** Specialization of TypeList for recursion end. */
template<>
struct TypeList<std::nullptr_t>
{
    /** Head is nullptr. */
    typedef std::nullptr_t head_t;

    /** Tail is nullptr. */
    typedef std::nullptr_t tail_t;

    /** Does nothing. */
    static void apply() { }
};

/** Apply method for type list like structures. */
template<template<typename ... T> class TList, typename ... TTypes>
void apply()
{
    TList<TTypes...>::apply();
}

} // namespace lib
