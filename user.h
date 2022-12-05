// user.h

#ifndef _USER_H_
#define _USER_H_
#include "user.h"
#include <string>

class User {
    public:
        virtual string getType() const = 0;
        virtual string getMove() = 0;
};

#endif
