// user.h

#ifndef _USER_H_
#define _USER_H_
#include "user.h"
#include <string>

class User {
    public:
        virtual getName() const = 0;
        virtual getType() const = 0;
        virtual getMove() const = 0;
}


