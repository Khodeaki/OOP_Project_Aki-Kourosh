#include "ElementException.h"

ElementException::ElementException(ErrorType type, const std::string& elementType, const std::string& detail) {
    switch (type) {
        case SYNTAX_ERROR:
            message = "Syntax error while adding " + elementType + ".";
            break;
        case EMPTY_NAME:
            message = elementType + " name cannot be empty.";
            break;
        case DUPLICATE_ELEMENT:
            message = elementType + " '" + detail + "' already exists in the circuit.";
            break;
        case SAME_NODES:
            message = elementType + " cannot be connected to the same node on both ends.";
            break;
        case INVALID_PHYSICAL_VALUE:
            message = "Invalid physical value format for " + elementType + ".";
            break;
        case NONPOSITIVE_VALUE:
            message = elementType + " value must be positive and non-zero.";
            break;
        case INVALID_MODEL:
            message = "Model '" + detail + "' is invalid for " + elementType + ".";
            break;
    }
}

const char* ElementException::what() const noexcept {
    return message.c_str();
}
