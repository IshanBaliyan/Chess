
// invalidmoveexception.h

#ifndef _INVALIDMOVEEXCEPTION_H_
#define _INVALIDMOVEEXCEPTION_H_

#include <string>

class InvalidMoveException {
    std::string varExcept;
    public:
        InvalidMoveException(std::string varExcept);
        InvalidMoveException();
        std::string getVarExcept() const;
        ~InvalidMoveException();
};

#endif


