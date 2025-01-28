/**
 * @file json.h
 * @brief Public API for JSON parsing and manipulation library
 * @author JSON Parser Team
 * @version 1.0
 *
 * This library provides functionality for parsing, manipulating, and generating JSON data
 * according to RFC 8259 (The JavaScript Object Notation (JSON) Data Interchange Format).
 */

#ifndef JSON_H
#define JSON_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Error codes returned by JSON operations
 */
typedef enum json_error {
    JSON_SUCCESS = 0,        /**< Operation completed successfully */
    JSON_ERROR_SYNTAX,       /**< Invalid JSON syntax */
    JSON_ERROR_INVALID_TYPE, /**< Attempted operation on wrong value type */
    JSON_ERROR_MEMORY,       /**< Memory allocation failure */
    JSON_ERROR_LIMIT,        /**< Parser limit exceeded */
    JSON_ERROR_ENCODING      /**< Invalid character encoding */
} json_error_t;

/**
 * @brief Available JSON value types
 */
typedef enum json_type {
    JSON_NULL,    /**< null value */
    JSON_BOOLEAN, /**< true or false */
    JSON_NUMBER,  /**< IEEE 754 double-precision number */
    JSON_STRING,  /**< UTF-8 encoded string */
    JSON_ARRAY,   /**< Array of JSON values */
    JSON_OBJECT   /**< Collection of key-value pairs */
} json_type_t;

/**
 * @brief Opaque type representing a JSON value
 */
typedef struct json_value json_value_t;

/**
 * @brief Opaque type representing a JSON parser
 */
typedef struct json_parser json_parser_t;

/**
 * @brief Configuration options for JSON parser
 */
typedef struct json_config {
    size_t max_nesting_depth;  /**< Maximum allowed nesting depth */
    size_t max_string_length;  /**< Maximum allowed string length */
    size_t max_number_length;  /**< Maximum allowed number length */
} json_config_t;

/**
 * @brief Creates a new JSON parser with specified configuration
 * @param config Parser configuration, NULL for default settings
 * @return Pointer to parser instance or NULL on failure
 */
json_parser_t* json_create_parser(const json_config_t* config);

/**
 * @brief Frees resources associated with a JSON parser
 * @param parser Parser instance to free
 */
void json_free_parser(json_parser_t* parser);

/**
 * @brief Parses a JSON string
 * @param parser Parser instance
 * @param input NULL-terminated string containing JSON data
 * @return Parsed JSON value or NULL on error
 */
json_value_t* json_parse_string(json_parser_t* parser, const char* input);

/**
 * @brief Parses JSON from a file
 * @param parser Parser instance
 * @param filename Path to file containing JSON data
 * @return Parsed JSON value or NULL on error
 */
json_value_t* json_parse_file(json_parser_t* parser, const char* filename);

/**
 * @brief Retrieves the last error from a parser
 * @param parser Parser instance
 * @return Error code indicating the last error
 */
json_error_t json_get_error(const json_parser_t* parser);

/**
 * @brief Converts an error code to a human-readable string
 * @param error Error code
 * @return String describing the error
 */
const char* json_get_error_string(json_error_t error);

/**
 * @brief Gets the type of a JSON value
 * @param value JSON value
 * @return Type of the value
 */
json_type_t json_get_type(const json_value_t* value);

/**
 * @brief Checks if a JSON value is null
 * @param value JSON value
 * @return true if value is null, false otherwise
 */
bool json_is_null(const json_value_t* value);

/**
 * @brief Gets the boolean value
 * @param value JSON value of type JSON_BOOLEAN
 * @return Boolean value
 */
bool json_get_boolean(const json_value_t* value);

/**
 * @brief Gets the number value
 * @param value JSON value of type JSON_NUMBER
 * @return Number value
 */
double json_get_number(const json_value_t* value);

/**
 * @brief Gets the string value
 * @param value JSON value of type JSON_STRING
 * @return NULL-terminated string or NULL on error
 */
const char* json_get_string(const json_value_t* value);

/**
 * @brief Gets the length of an array
 * @param array JSON value of type JSON_ARRAY
 * @return Number of elements in the array
 */
size_t json_array_length(const json_value_t* array);

/**
 * @brief Gets an element from an array
 * @param array JSON value of type JSON_ARRAY
 * @param index Index of the element to retrieve
 * @return Element at specified index or NULL if index is out of bounds
 */
json_value_t* json_array_get(json_value_t* array, size_t index);

/**
 * @brief Gets the number of members in an object
 * @param object JSON value of type JSON_OBJECT
 * @return Number of key-value pairs in the object
 */
size_t json_object_length(const json_value_t* object);

/**
 * @brief Gets all keys in an object
 * @param object JSON value of type JSON_OBJECT
 * @return NULL-terminated array of strings containing the keys
 */
const char** json_object_keys(const json_value_t* object);

/**
 * @brief Gets a value from an object by key
 * @param object JSON value of type JSON_OBJECT
 * @param key Key to look up
 * @return Value associated with key or NULL if not found
 */
json_value_t* json_object_get(json_value_t* object, const char* key);

/**
 * @brief Creates a deep copy of a JSON value
 * @param value JSON value to clone
 * @return New JSON value or NULL on error
 */
json_value_t* json_clone(const json_value_t* value);

/**
 * @brief Frees a JSON value and all its children
 * @param value JSON value to free
 */
void json_free(json_value_t* value);

/**
 * @brief Creates a new null JSON value
 * @return New JSON value or NULL on error
 */
json_value_t* json_null(void);

/**
 * @brief Creates a new boolean JSON value
 * @param value Boolean value
 * @return New JSON value or NULL on error
 */
json_value_t* json_boolean(bool value);

/**
 * @brief Creates a new number JSON value
 * @param value Number value
 * @return New JSON value or NULL on error
 */
json_value_t* json_number(double value);

/**
 * @brief Creates a new string JSON value
 * @param value NULL-terminated string
 * @return New JSON value or NULL on error
 */
json_value_t* json_string(const char* value);

/**
 * @brief Creates a new empty array
 * @return New JSON value or NULL on error
 */
json_value_t* json_array(void);

/**
 * @brief Creates a new empty object
 * @return New JSON value or NULL on error
 */
json_value_t* json_object(void);

/**
 * @brief Converts a JSON value to a string
 * @param value JSON value to convert
 * @return NULL-terminated string containing JSON representation or NULL on error
 */
char* json_stringify(const json_value_t* value);

/**
 * @brief Writes a JSON value to a file
 * @param value JSON value to write
 * @param filename Path to output file
 * @return true on success, false on error
 */
bool json_stringify_file(const json_value_t* value, const char* filename);

#endif /* JSON_H */