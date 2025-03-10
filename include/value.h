
#ifndef VALUE_H
#define VALUE_H
#include <map>
#include <memory>
#include <vector>

class Iterator;

struct EncodingOptions {
    bool escapeNonAscii = false;

    bool reencode = false;

    bool pretty = false;

    size_t spacesPerIndentationLevel = 4;

    size_t wrapThreshold = 60;

    size_t numIndentationLevels = 0;
};

class Value {
public:
    enum class Type {
        Invalid,
        Null,
        Boolean,
        String,
        Integer,
        FloatingPoint,
        Array,
        Object,
    };

    ~Value() noexcept;

    Value(const Value &);

    Value(Value &&) noexcept;

    Value &operator=(const Value &);

    Value &operator=(Value &&) noexcept;

    explicit Value(Type type = Type::Invalid);

    explicit Value(std::nullptr_t);

    explicit Value(bool value);

    explicit Value(int value);

    explicit Value(intmax_t value);

    explicit Value(size_t value);

    explicit Value(double value);

    explicit Value(const char *value);

    explicit Value(const std::string &value);

    bool operator==(const Value &other) const;

    bool operator!=(const Value &other) const;

    bool operator<(const Value &other) const;

    explicit operator bool() const;

    explicit operator std::string() const;

    explicit operator int() const;

    explicit operator intmax_t() const;

    explicit operator size_t() const;

    explicit operator double() const;

    [[nodiscard]] Type GetType() const;

    [[nodiscard]] size_t GetSize() const;

    [[nodiscard]] bool Has(const std::string &key) const;

    [[nodiscard]] std::vector<std::string> GetKeys() const;

    const Value &operator[](size_t index) const;

    const Value &operator[](int index) const;

    const Value &operator[](const std::string &key) const;

    const Value &operator[](const char *key) const;

    Value &operator[](size_t index);

    Value &operator[](int index);

    Value &operator[](const std::string &key);

    Value &operator[](const char *key);

    Value &Add(const Value &value);

    Value &Add(Value &&value);

    Value &Insert(const Value &value, size_t index);

    Value &Insert(Value &&value, size_t index);

    Value &Set(const std::string &key, const Value &value);

    void Remove(size_t index);

    void Remove(const std::string &key);

    [[nodiscard]] Iterator begin() const;

    [[nodiscard]] Iterator end() const;

    [[nodiscard]] std::string ToEncoding(const EncodingOptions &options = EncodingOptions()) const;


    //     static Value FromEncoding(const std::vector<Utf8::UnicodeCodePoint> &encodingBeforeTrim);

    static Value FromEncoding(const std::string &encodingBeforeTrim);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};


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


#endif //VALUE_H




