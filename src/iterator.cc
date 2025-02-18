#include "iterator.h"

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
