#ifndef ELEMENT_EXCEPTION_H
#define ELEMENT_EXCEPTION_H

#include <stdexcept>
#include <string>

class ElementException : public std::exception {
public:
    enum ErrorType {
        SYNTAX_ERROR,
        EMPTY_NAME,
        DUPLICATE_ELEMENT,
        SAME_NODES,
        INVALID_PHYSICAL_VALUE,
        NONPOSITIVE_VALUE,
        INVALID_MODEL // مخصوص دیود
    };

    ElementException(ErrorType type, const std::string& elementType, const std::string& detail = "");

    const char* what() const noexcept override;

private:
    std::string message;
};

#endif
