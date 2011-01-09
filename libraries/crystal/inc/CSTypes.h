#ifndef CSTYPES_H
#define CSTYPES_H
#include <string>
#include <stdint.h>

//nil is redefined here to improve readability.
//seeing NULL everywhere just looks very bad in code
#define nil NULL

//the self macro is defined to be used to get a
//reference to the current object
#define self (*this)

//this is also defined to improve readability, but
//to anyone who doesn't know the insides of this code
//it may look odd. It is meant to be used in the
//definition of abstract classes or abstract virtual
//functions in a class
#define abstract =0

//this is here to make changing the string type easier
//a preferred string type would be a full UCS-4 string
//but such a type does not seem to exist in a small
//library. 
typedef std::wstring CSString;
#endif
