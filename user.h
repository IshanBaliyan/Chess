// user.h

#ifndef _USER_H_
#define _USER_H_
#include "user.h"
#include <string>

class User {
    public:
        virtual string getName() const = 0;
        virtual string getType() const = 0;
        virtual string getMove() const = 0;
};

#endif
