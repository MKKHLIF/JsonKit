#pragma once

#include <map>
#include <memory>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace Json {
    /**
     * @brief Configuration options for encoding JSON values into strings.
     *
     * This struct provides settings to control how JSON values are serialized
     * into their string representations. Options include escaping non-ASCII
     * characters, forcing re-encoding, pretty printing with indentation,
     * and line wrapping thresholds.
     */
    struct EncodingOptions {
        /**
         * @brief If true, non-ASCII characters are escaped in the encoded string.
         *
         * This is useful for ensuring compatibility with systems that only
         * support ASCII characters. Defaults to false.
         */
        bool escapeNonAscii = false;

        /**
         * @brief If true, forces the JSON value to be re-encoded, bypassing
         * any cached encoding.
         *
         * This is useful when the internal state of the JSON value has changed
         * and a fresh encoding is required. Defaults to false.
         */
        bool reencode = false;

        /**
         * @brief If true, enables pretty printing, adding whitespace for
         * readability.
         *
         * Pretty printing adds indentation and line breaks to the encoded
         * string, making it easier to read. Defaults to false.
         */
        bool pretty = false;

        /**
         * @brief The number of spaces to indent nested structures when
         * pretty printing.
         *
         * This controls the level of indentation for each nested level in
         * arrays and objects. Defaults to 4.
         */
        size_t spacesPerIndentationLevel = 4;

        /**
         * @brief The maximum line length before wrapping elements in arrays
         * and objects when pretty printing.
         *
         * This helps to keep the encoded string within a manageable line
         * length. Defaults to 60.
         */
        size_t wrapThreshold = 60;

        /**
         * @brief The number of indentation levels to assume for the JSON
         * value.
         *
         * This is used to calculate the correct indentation level when
         * pretty printing nested structures. Defaults to 0.
         */
        size_t numIndentationLevels = 0;
    };


    /**
     * @brief Represents a JSON value, supporting various data types.
     *
     * This class encapsulates the data and operations for handling JSON values,
     * including null, boolean, string, integer, floating-point, array, and
     * object types. It provides methods for accessing, modifying, and
     * serializing JSON data.
     */
    class Value {
    public:
        /**
         * @brief Enumerates the different types of JSON values.
         */
        enum class Type {
            /** @brief An invalid JSON value. */
            Invalid,
            /** @brief A null JSON value. */
            Null,
            /** @brief A boolean JSON value (true or false). */
            Boolean,
            /** @brief A string JSON value. */
            String,
            /** @brief An integer JSON value. */
            Integer,
            /** @brief A floating-point JSON value. */
            FloatingPoint,
            /** @brief An array JSON value. */
            Array,
            /** @brief An object JSON value. */
            Object,
        };

        /**
         * @brief Iterator for traversing JSON arrays and objects.
         *
         * This class provides an iterator for navigating through the elements
         * of JSON arrays and objects. It supports incrementing, dereferencing,
         * and comparing iterators.
         */
        class Iterator {
        public:
            /**
             * @brief Constructs an iterator for a JSON array.
             *
             * @param container Pointer to the JSON array.
             * @param nextArrayEntry Iterator pointing to the initial position.
             */
            Iterator(
                const Value *container,
                std::vector<Value>::const_iterator &&nextArrayEntry
            );

            /**
             * @brief Constructs an iterator for a JSON object.
             *
             * @param container Pointer to the JSON object.
             * @param nextObjectEntry Iterator pointing to the initial position.
             */
            Iterator(
                const Json::Value *container,
                std::map<std::string, Value>::const_iterator &&nextObjectEntry
            );

            /**
             * @brief Advances the iterator to the next element.
             */
            void operator++();

            /**
             * @brief Checks if the iterator is not equal to another iterator.
             *
             * @param other The other iterator to compare with.
             * @return True if the iterators are not equal, false otherwise.
             */
            bool operator!=(const Iterator &other) const;

            /**
             * @brief Dereferences the iterator, returning a reference to itself.
             *
             * @return A reference to the iterator.
             */
            Iterator &operator*();

            /**
             * @brief Returns the key of the current element in a JSON object.
             *
             * @return The key of the current element.
             */
            [[nodiscard]] const std::string &key() const;

            /**
             * @brief Returns the value of the current element.
             *
             * @return The value of the current element.
             */
            [[nodiscard]] const Value &value() const;

        private:
            /** @brief Pointer to the JSON array or object being iterated. */
            const Value *container = nullptr;
            /** @brief Iterator for the current position in a JSON array. */
            std::vector<Value>::const_iterator nextArrayEntry;
            /** @brief Iterator for the current position in a JSON object. */
            std::map<std::string, Value>::const_iterator nextObjectEntry;
        };

        /** @brief Destructor. */
        ~Value() noexcept;

        /** @brief Copy constructor. */
        Value(const Value &);

        /** @brief Move constructor. */
        Value(Value &&) noexcept;

        /** @brief Copy assignment operator. */
        Value &operator=(const Value &);

        /** @brief Move assignment operator. */
        Value &operator=(Value &&) noexcept;

        /**
       * @brief Constructs a JSON value of the specified type.
       *
       * @param type The type of JSON value to create.
       */
        Value(Type type = Type::Invalid);

        /**
         * @brief Constructs a JSON null value.
         *
         * @param null The null value.
         */
        Value(std::nullptr_t);

        /**
         * @brief Constructs a JSON boolean value.
         *
         * @param value The boolean value.
         */
        Value(bool value);

        /**
         * @brief Constructs a JSON integer value.
         *
         * @param value The integer value.
         */
        Value(int value);

        /**
         * @brief Constructs a JSON maximum-sized integer value.
         *
         * @param value The maximum-sized integer value.
         */
        Value(intmax_t value);

        /**
         * @brief Constructs a JSON size value.
         *
         * @param value The size value.
         */
        Value(size_t value);

        /**
         * @brief Constructs a JSON floating-point value.
         *
         * @param value The floating-point value.
         */
        Value(double value);

        /**
         * @brief Constructs a JSON string value from a C-style string.
         *
         * @param value The C-style string value.
         */
        Value(const char *value);

        /**
         * @brief Constructs a JSON string value from a C++ string.
         *
         * @param value The C++ string value.
         */
        Value(const std::string &value);

        /**
         * @brief Checks if two JSON values are equal.
         *
         * @param other The other JSON value to compare with.
         * @return True if the values are equal, false otherwise.
         */
        bool operator==(const Value &other) const;

        /**
         * @brief Checks if two JSON values are not equal.
         *
         * @param other The other JSON value to compare with.
         * @return True if the values are not equal, false otherwise.
         */
        bool operator!=(const Value &other) const;

        /**
         * @brief Checks if a JSON value is less than another JSON value.
         *
         * @param other The other JSON value to compare with.
         * @return True if the value is less than the other value, false otherwise.
         */
        bool operator<(const Value &other) const;

        /**
        * @brief Typecast operator to boolean
        * @return The boolean equivalent of the JSON value.
        */
        operator bool() const;

        /**
   * @brief Typecast operator to C++ string.
   *
   * @return The C++ string equivalent of the JSON value.
   */
        operator std::string() const;

        /**
         * @brief Typecast operator to integer.
         *
         * @return The integer equivalent of the JSON value.
         */
        operator int() const;

        /**
         * @brief Typecast operator to maximum-sized integer.
         *
         * @return The maximum-sized integer equivalent of the JSON value.
         */
        operator intmax_t() const;

        /**
         * @brief Typecast operator to size.
         *
         * @return The size equivalent of the JSON value.
         */
        operator size_t() const;

        /**
         * @brief Typecast operator to floating-point.
         *
         * @return The floating-point equivalent of the JSON value.
         */
        operator double() const;

        /**
         * @brief Returns the type of the JSON value.
         *
         * @return The type of the JSON value.
         */
        [[nodiscard]] Type GetType() const;

        /**
         * @brief Returns the size of the JSON array.
         *
         * @return The size of the JSON array, or 0 if not an array.
         */
        [[nodiscard]] size_t GetSize() const;

        /**
         * @brief Checks if the JSON object has a key.
         *
         * @param key The key to check for.
         * @return True if the object has the key, false otherwise.
         */
        [[nodiscard]] bool Has(const std::string &key) const;

        /**
         * @brief Returns the keys of the JSON object.
         *
         * @return A vector of keys in the JSON object.
         */
        [[nodiscard]] std::vector<std::string> GetKeys() const;

        /**
         * @brief Returns a const reference to the element at the given index
         * in a JSON array.
         *
         * @param index The index of the element.
         * @return A const reference to the element, or a const reference to a
         * special null value if the index is out of range or the value is
         * not an array.
         */
        const Value &operator[](size_t index) const;

        /**
         * @brief Returns a const reference to the element at the given index
         * in a JSON array.
         *
         * @param index The index of the element.
         * @return A const reference to the element, or a const reference to a
         * special null value if the index is out of range or the value is
         * not an array.
         */
        const Value &operator[](int index) const;

        /**
         * @brief Returns a const reference to the element with the given key
         * in a JSON object.
         *
         * @param key The key of the element.
         * @return A const reference to the element, or a const reference to a
         * special null value if the key is not found or the value is not an
         * object.
         */
        const Value &operator[](const std::string &key) const;

        /**
         * @brief Returns a const reference to the element with the given key
         * in a JSON object.
         *
         * @param key The key of the element.
         * @return A const reference to the element, or a const reference to a
         * special null value if the key is not found or the value is not an
         * object.
         */
        const Value &operator[](const char *key) const;

        /**
         * @brief Returns a reference to the element at the given index in a
         * JSON array.
         *
         * @param index The index of the element.
         * @return A reference to the element, creating a null value if the
         * index is out of range.
         */
        Value &operator[](size_t index);

        /**
         * @brief Returns a reference to the element at the given index in a
         * JSON array.
         *
         * @param index The index of the element.
         * @return A reference to the element, creating a null value if the
         * index is out of range or negative.
         */
        Value &operator[](int index);

        /**
         * @brief Returns a reference to the element with the given key in a
         * JSON object.
         *
         * @param key The key of the element.
         * @return A reference to the element, creating a null value if the
         * key is not found.
         */
        Value &operator[](const std::string &key);

        /**
         * @brief Returns a reference to the element with the given key in a
         * JSON object.
         *
         * @param key The key of the element.
         * @return A reference to the element, creating a null value if the
         * key is not found or null.
         */
        Value &operator[](const char *key);

        /**
         * @brief Adds a copy of the given value to the end of the JSON array.
         *
         * @param value The value to add.
         * @return A reference to the added value.
         */
        Value &Add(const Value &value);

        /**
         * @brief Adds a move of the given value to the end of the JSON array.
         *
         * @param value The value to add.
         * @return A reference to the added value.
         */
        Value &Add(Value &&value);

        /**
         * @brief Inserts a copy of the given value at the given index in a
         * JSON array.
         *
         * @param value The value to insert.
         * @param index The index to insert at.
         * @return A reference to the inserted value.
         */
        Value &Insert(const Value &value, size_t index);

        /**
         * @brief Inserts a move of the given value at the given index in a
         * JSON array.
         *
         * @param value The value to insert.
         * @param index The index to insert at.
         * @return A reference to the inserted value.
         */
        Value &Insert(Value &&value, size_t index);

        /**
         * @brief Sets a copy of the given value with the given key in a
         * JSON object.
         *
         * @param key The key to set the value with.
         * @param value The value to set.
         * @return A reference to the set value.
         */
        Value &Set(
            const std::string &key,
            const Value &value
        );

        /**
         * @brief Removes the element at the given index in a JSON array.
         *
         * @param index The index of the element to remove.
         */
        void Remove(size_t index);

        /**
         * @brief Removes the element with the given key in a JSON object.
         *
         * @param key The key of the element to remove.
         */
        void Remove(const std::string &key);

        /**
         * @brief Returns an iterator to the beginning of the JSON array or object.
         *
         * @return An iterator to the beginning.
         */
        [[nodiscard]] Iterator begin() const;

        /**
         * @brief Returns an iterator to the end of the JSON array or object.
         *
         * @return An iterator to the end.
         */
        [[nodiscard]] Iterator end() const;

        /**
         * @brief Encodes the JSON value to a string.
         *
         * @param options Encoding options.
         * @return The encoded JSON string.
         */
        [[nodiscard]] std::string ToEncoding(const EncodingOptions &options = EncodingOptions()) const;

        /**
         * @brief Decodes a JSON value from a vector of uint32_t.
         *
         * @param encodingBeforeTrim The encoded JSON value.
         * @return The decoded JSON value.
         */
        static Value FromEncoding(const std::vector<uint32_t> &encodingBeforeTrim);

        /**
         * @brief Decodes a JSON value from a string.
         *
         * @param encodingBeforeTrim The encoded JSON value.
         * @return The decoded JSON value.
         */
        static Value FromEncoding(const std::string &encodingBeforeTrim);

    private:
        /**
        * @brief Private implementation details.
        */
        struct Impl;
        /**
         * @brief Unique pointer to the private implementation.
         */
        std::unique_ptr<Impl> impl_;
    };

    /**
     * This constructs a JSON array containing copies of the
     * elements in the given initializer list.
     *
     * @param[in] args
     *     These are the values to copy into the new array.
     *
     * @return
     *     The newly constructed JSON array is returned.
     */
    Value Array(std::initializer_list<const Value> args);

    /**
     * This constructs a JSON object containing copies of the
     * elements in the given initializer list.
     *
     * @param[in] args
     *     These are the values to copy into the new object.
     *
     * @return
     *     The newly constructed JSON object is returned.
     */
    Value Object(std::initializer_list<std::pair<const std::string, const Value> > args);

    /**
     * This is a support function for Google Test to print out
     * a Json::Type value.
     *
     * @param[in] type
     *     This is the Json::Type value to print.
     *
     * @param[in] os
     *     This points to the stream to which to print the
     *     Json::Type value.
     */
    void PrintTo(
        Value::Type type,
        std::ostream *os
    );

    /**
     * This is a support function for Google Test to print out
     * a Json value.
     *
     * @param[in] json
     *     This is the JSON value to print.
     *
     * @param[in] os
     *     This points to the stream to which to print the
     *     Json value.
     */
    void PrintTo(
        const Value &json,
        std::ostream *os
    );
}
