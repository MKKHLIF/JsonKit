/**
 * @file json_internal.h
 * @brief Internal implementation details for JSON parsing library
 * @author JSON Parser Team
 * @version 1.0
 * @internal
 *
 * This header contains internal structures and functions used by the JSON parser.
 * These declarations should not be used directly by library users.
 */

#ifndef JSON_INTERNAL_H
#define JSON_INTERNAL_H

#include "json.h"

/**
 * @brief Default maximum nesting depth if not specified
 * @internal
 */
#define JSON_DEFAULT_MAX_DEPTH 32

/**
 * @brief Default maximum string length if not specified
 * @internal
 */
#define JSON_DEFAULT_MAX_STRING 1048576

/**
 * @brief Default maximum number length if not specified
 * @internal
 */
#define JSON_DEFAULT_MAX_NUMBER 32

/**
 * @brief Internal token types used by the lexer
 * @internal
 */
typedef enum {
    TOKEN_EOF,          /**< End of input */
    TOKEN_NULL,         /**< null literal */
    TOKEN_TRUE,         /**< true literal */
    TOKEN_FALSE,        /**< false literal */
    TOKEN_NUMBER,       /**< Numeric literal */
    TOKEN_STRING,       /**< String literal */
    TOKEN_ARRAY_START,  /**< [ character */
    TOKEN_ARRAY_END,    /**< ] character */
    TOKEN_OBJECT_START, /**< { character */
    TOKEN_OBJECT_END,   /**< } character */
    TOKEN_COMMA,        /**< , character */
    TOKEN_COLON,        /**< : character */
    TOKEN_ERROR         /**< Invalid token */
} token_type_t;

/**
 * @brief Structure representing a lexical token
 * @internal
 */
typedef struct {
    token_type_t type;  /**< Type of token */
    char* value;        /**< Token value string */
    size_t length;      /**< Length of value string */
    size_t line;        /**< Line number in input */
    size_t column;      /**< Column number in input */
} token_t;

/**
 * @brief Internal parser state
 * @internal
 */
struct json_parser {
    const char* input;           /**< Input string being parsed */
    size_t position;            /**< Current position in input */
    size_t line;               /**< Current line number */
    size_t column;             /**< Current column number */
    token_t current_token;     /**< Current token being processed */
    json_config_t config;      /**< Parser configuration */
    json_error_t last_error;   /**< Last error encountered */
    char error_message[256];   /**< Detailed error message */
};

/**
 * @brief Internal representation of JSON values
 * @internal
 */
struct json_value {
    json_type_t type;  /**< Type of value */
    union {
        bool boolean;              /**< Boolean value */
        double number;             /**< Number value */
        struct {
            char* data;            /**< String data */
            size_t length;         /**< String length */
        } string;
        struct {
            json_value_t** elements; /**< Array elements */
            size_t length;           /**< Number of elements */
            size_t capacity;         /**< Allocated capacity */
        } array;
        struct {
            char** keys;            /**< Object keys */
            json_value_t** values;  /**< Object values */
            size_t length;          /**< Number of pairs */
            size_t capacity;        /**< Allocated capacity */
        } object;
    } data;
};

/**
 * @brief Initializes lexer with input string
 * @param parser Parser instance
 * @param input Input string to parse
 * @internal
 */
void lexer_init(json_parser_t* parser, const char* input);

/**
 * @brief Gets next token from input
 * @param parser Parser instance
 * @return Next token
 * @internal
 */
token_t lexer_next_token(json_parser_t* parser);

/**
 * @brief Frees resources used by a token
 * @param token Token to free
 * @internal
 */
void lexer_free_token(token_t* token);

/**
 * @brief Parses a JSON value
 * @param parser Parser instance
 * @return Parsed value or NULL on error
 * @internal
 */
json_value_t* parse_value(json_parser_t* parser);

/**
 * @brief Parses a JSON array
 * @param parser Parser instance
 * @return Parsed array or NULL on error
 * @internal
 */
json_value_t* parse_array(json_parser_t* parser);

/**
 * @brief Parses a JSON object
 * @param parser Parser instance
 * @return Parsed object or NULL on error
 * @internal
 */
json_value_t* parse_object(json_parser_t* parser);

/**
 * @brief Parses a JSON string
 * @param parser Parser instance
 * @return Parsed string or NULL on error
 * @internal
 */
json_value_t* parse_string(json_parser_t* parser);

/**
 * @brief Parses a JSON number
 * @param parser Parser instance
 * @return Parsed number or NULL on error
 * @internal
 */
json_value_t* parse_number(json_parser_t* parser);

/**
 * @brief Validates a Unicode escape sequence
 * @param str String containing sequence
 * @param len Length of string
 * @return true if valid, false otherwise
 * @internal
 */
bool validate_unicode_sequence(const char* str, size_t len);

/**
 * @brief Validates a UTF-8 sequence
 * @param str String containing sequence
 * @param len Length of string
 * @return true if valid, false otherwise
 * @internal
 */
bool validate_utf8_sequence(const char* str, size_t len);

/**
 * @brief Internal memory allocation wrapper
 * @param size Number of bytes to allocate
 * @return Allocated memory or NULL on failure
 * @internal
 */
void* json_malloc(size_t size);

/**
 * @brief Internal memory reallocation wrapper
 * @param ptr Pointer to reallocate
 * @param size New size in bytes
 * @return Reallocated memory or NULL on failure
 * @internal
 */
void* json_realloc(void* ptr, size_t size);

/**
 * @brief Internal memory freeing wrapper
 * @param ptr Pointer to free
 * @internal
 */
void json_free_internal(void* ptr);

/**
 * @brief Internal string duplication
 * @param str String to duplicate
 * @return New string or NULL on failure
 * @internal
 */
char* json_strdup(const char* str);

/**
 * @brief Internal string length calculation
 * @param str String to measure
 * @return Length of string
 * @internal
 */
size_t json_strlen(const char* str);

/**
 * @brief Sets parser error state
 * @param parser Parser instance
 * @param error Error code
 * @param message Error message
 * @internal
 */
void set_error(json_parser_t* parser, json_error_t error, const char* message);

/**
 * @brief Clears parser error state
 * @param parser Parser instance
 * @internal
 */
void clear_error(json_parser_t* parser);

#endif /* JSON_INTERNAL_H */