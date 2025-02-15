#ifndef ITERATOR_H
#define ITERATOR_H
#include <map>
#include <string>
#include <value.h>
#include <vector>


class Iterator {
public:
    Iterator(
        const Value *container,
        std::vector<Value>::const_iterator &&nextArrayEntry
    );


    Iterator(
        const Value *container,
        std::map<std::string, Value>::const_iterator &&nextObjectEntry
    );

    void operator++();

    bool operator!=(const Iterator &other) const;

    Iterator &operator*();

    [[nodiscard]] const std::string &key() const;

    [[nodiscard]] const Value &value() const;

private:
    const Value *container;
    std::vector<Value>::const_iterator nextArrayEntry;
    std::map<std::string, Value>::const_iterator nextObjectEntry;
};


#endif //ITERATOR_H
