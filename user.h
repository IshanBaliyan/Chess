// user.h

#ifndef _USER_H_
#define _USER_H_
#include "user.h"
#include <string>

class User {
    public:
        virtual std::string getType() const = 0;
        virtual std::string getMove() = 0;
        virtual std::string getColour() const = 0;
};

#endif
