#ifndef IPROMPT_H
#define IPROMPT_H


#include <string>
#include <iomanip>

class IPrompt
{

public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~IPrompt() {}
    
    // Pure virutal to print query
    virtual void printQuery() const = 0;
};



#endif //! IPROMPT_H