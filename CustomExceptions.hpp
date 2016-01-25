//
//  Exception_MissingCard.hpp
//  Five Animals
//

#ifndef CustomExceptions_hpp
#define CustomExceptions_hpp

#include <string>
#include <exception>

class CustomExceptions : public std::exception {
protected:
    std::string error_message;
    
public:
    // Constructor (C strings)
    explicit CustomExceptions(const char* message) : error_message(message) {}
    
    // Constructor (C++ STL strings)
    explicit CustomExceptions(const std::string& message) : error_message(message) {}
    
    // Virtual to allow for subclassing.
    virtual ~CustomExceptions() throw () {}
    
    // Returns a pointer to the (constant) error description
    virtual const char* what() const throw () {
        return error_message.c_str();
    }
};

#endif /* CustomExceptions_hpp */
