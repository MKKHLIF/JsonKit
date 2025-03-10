#include "value.h"
#include "utf8.h"

std::vector<uint32_t> WHITESPACE_CHARACTERS{
    0x20, // ' '
    0x09, // '\t'
    0x0D, // '\r'
    0x0A, // '\n'
};

/**
 * This maps the escaped representations of special characters
 * back to the actual characters they represent.
 */
const std::map<uint32_t, uint32_t> SPECIAL_ESCAPE_DECODINGS{
    {0x22, 0x22}, // '"'
    {0x5C, 0x5C}, // '\\'
    {0x2F, 0x2F}, // '\\'
    {0x62, 0x08}, // '\b'
    {0x66, 0x0C}, // '\f'
    {0x6E, 0x0A}, // '\n'
    {0x72, 0x0D}, // '\r'
    {0x74, 0x09}, // '\t'
};

/**
 * This maps special characters to their escaped representations.
 */
const std::map<uint32_t, uint32_t> SPECIAL_ESCAPE_ENCODINGS{
    {0x22, 0x22}, // '"'
    {0x5C, 0x5C}, // '\\'
    {0x2F, 0x2F}, // '\\'
    {0x08, 0x62}, // '\b'
    {0x0C, 0x66}, // '\f'
    {0x0A, 0x6E}, // '\n'
    {0x0D, 0x72}, // '\r'
    {0x09, 0x74}, // '\t'
};


Iterator::Iterator(
    const Value *container,
    std::vector<Value>::const_iterator &&nextArrayEntry
): container(container), nextArrayEntry(std::move(nextArrayEntry)) {
}

Iterator::Iterator(
    const Value *container,
    std::map<std::string, Value>::const_iterator &&nextObjectEntry
) : container(container), nextObjectEntry(std::move(nextObjectEntry)) {
}

void Iterator::operator++() {
    container->GetType() == Value::Type::Array ? ++nextArrayEntry : ++nextObjectEntry;
}

bool Iterator::operator!=(const Iterator &other) const {
    return container->GetType() == Value::Type::Array
               ? nextArrayEntry != other.nextArrayEntry
               : nextObjectEntry != other.nextObjectEntry;
}


auto Iterator::operator*() -> Iterator & {
    return *this;
}

const std::string &Iterator::key() const {
    return nextObjectEntry->first;
}

const Value &Iterator::value() const {
    return container->GetType() == Value::Type::Array ? *nextArrayEntry : nextObjectEntry->second;
}
