General Rules:

    Whitespace (ws):
        Allowed before or after structural characters: [, ], {, }, :, ,.
        Can be any combination of: Space (0x20), Horizontal tab (0x09), Line feed (0x0A), Carriage return (0x0D).

    JSON Text Structure:
        A JSON text is a sequence of tokens: ws value ws.

Structural Characters:

    Begin Array: [, represented by %x5B.
    End Array: ], represented by %x5D.
    Begin Object: {, represented by %x7B.
    End Object: }, represented by %x7D.
    Name Separator: :, represented by %x3A.
    Value Separator: ,, represented by %x2C.

JSON Values:

    Valid JSON Values:
        Object, Array, String, Number, true, false, null.
        Literal names (true, false, null) MUST be lowercase.
        No other literal names allowed.

    Value Definition:
        value = false / null / true / object / array / number / string.

Objects:

    Object Structure:
        Represented by { and } with zero or more name/value pairs (member).
        Member Structure: member = string name-separator value.
        Uniqueness: Object names SHOULD be unique (behavior with duplicates may vary).

    Object Parsing:
        object = begin-object [ member *( value-separator member ) ] end-object.

Arrays:

    Array Structure:
        Represented by [ and ] with zero or more values.
        Elements separated by commas.
        No Type Restriction: Elements in an array do not need to be of the same type.
        array = begin-array [ value *( value-separator value ) ] end-array.

Numbers:

    Number Representation:
        Base 10, with optional sign (+/-), integer part, fraction part (.), and exponent part (e/E).
        No leading zeros allowed (except for 0 itself).
        Valid numeric characters and structure are defined by:
            number = [ minus ] int [ frac ] [ exp ].
        frac is a decimal point followed by digits.
        exp uses e or E followed by an optional sign and digits.

    Invalid Numbers:
        Values like Infinity and NaN are not permitted.

Strings:

    String Representation:
        Strings are surrounded by quotation marks ("), and can contain Unicode characters (except certain escape sequences).
        Must escape: " (quotation mark), \ (reverse solidus), and control characters (U+0000 through U+001F).
        Escape Sequences:
            For basic characters: \", \\, \/, \b, \f, \n, \r, \t.
            For Unicode: \uXXXX (for characters in the Basic Multilingual Plane), \uD834\uDD1E for surrogate pairs.
        String Parsing:
            string = quotation-mark *char quotation-mark.
            char is either an unescaped character or an escape sequence.

Character Encoding:

    JSON Encoding:
        JSON MUST be encoded in UTF-8, UTF-16, or UTF-32.
        The default encoding is UTF-8. JSON texts in UTF-8 are most interoperable.
        Implementations MUST NOT add a byte order mark (BOM) to the JSON text.
        Implementations MAY ignore a BOM if present.

Unicode Characters:

    Unicode Compliance:
        JSON text SHOULD represent strings entirely with valid Unicode characters (whether escaped or not).
        Unpaired UTF-16 surrogates (e.g., \uDEAD) or invalid encodings are not allowed, as they can cause unpredictable behavior in parsers.

String Comparison:

    String Equality:
        Implementations MUST compare string member names by comparing the sequences of Unicode code units.
        Implementations comparing strings with escaped characters must treat equivalent escapes as equal, e.g., "a\\b" and "a\u005Cb" should be considered equal.

Parsers:

    JSON Parser Requirements:
        A JSON parser MUST accept any JSON text conforming to the JSON grammar.
        Parsers MAY impose limits on:
            Size of text.
            Depth of nesting.
            Range and precision of numbers.
            Length and content of strings.

Generators:

    JSON Generator Requirements:
        A JSON generator MUST produce text strictly conforming to the JSON grammar.

Security Considerations:

    Security Risks:
        Avoid using eval() or similar functions for parsing JSON text, as they pose security risks when the JSON text might contain executable code.

Test Cases:


| Test Case                    | Input                        | Expected Output                                | Object After Parsing (Success/Failure)  |
|------------------------------|------------------------------|-----------------------------------------------|-----------------------------------------|
| **Whitespace Handling**      | `" { "key": "value" } "`     | Parsed JSON with whitespace around object     | `{"key": "value"}`                      |
| **Basic JSON Structures**    | `"{}"`                       | Empty object                                  | `{}`                                    |
|                              | `"[]"`                       | Empty array                                   | `[]`                                    |
|                              | `{"key": "value"}`           | Single key-value pair                         | `{"key": "value"}`                      |
|                              | `[1, "two", true, null]`     | Array with mixed elements                     | `[1, "two", true, null]`                |
| **Numbers**                  | `"42"`                       | Integer value                                 | `42`                                    |
|                              | `"-42"`                      | Negative integer value                        | `-42`                                   |
|                              | `"3.14"`                     | Floating point number                         | `3.14`                                  |
|                              | `"1e3"`                      | Exponent notation                             | `1000`                                  |
|                              | `"012"`                      | Invalid number (leading zeros)                | Parse Failure                           |
|                              | `"Infinity"`                 | Invalid number                                | Parse Failure                           |
| **Strings**                  | `"\"hello\""`                | Simple string                                 | `"hello"`                               |
|                              | `"\"a\\b\""`                 | String with escape sequences                  | `"a\\b"`                                |
|                              | `"\"a\u005Cb\""`             | String with escaped Unicode                   | `"a\\b"`                                |
|                              | `"\"Hello\nWorld\""`         | String with newline escape                    | `"Hello\nWorld"`                        |
|                              | `"\"🌍\""`                   | String with Unicode character                 | `"🌍"`                                  |
|                              | `"\"\\uD834\\uDD1E\""`       | String with UTF-16 surrogate pair             | `"𝄞"`                                   |
|                              | `"\"\\uDEAD\""`              | String with unpaired surrogate                | Parse Failure                           |
| **Objects**                  | `{"a": 1, "b": 2}`           | Object with multiple key-value pairs          | `{"a": 1, "b": 2}`                      |
|                              | `{"a": {"b": 2}}`            | Nested object                                 | `{"a": {"b": 2}}`                       |
|                              | `{"key": 1, "key": 2}`       | Object with duplicate keys                    | Parse Failure                           |
|                              | `{"key": }`                  | Object with missing value                     | Parse Failure                           |
| **Arrays**                   | `[1, "two", true, null]`     | Array with mixed types                        | `[1, "two", true, null]`                |
|                              | `[]`                         | Empty array                                   | `[]`                                    |
|                              | `[1, 1, 1]`                  | Array with duplicate values                   | `[1, 1, 1]`                             |
| **Encoding & BOM**           | `"\uFEFF{}"`                 | JSON with BOM                                 | `{"}`                                   |
| **Security Tests**           | `"{\"key\": \"function() {...}\"}"` | JSON with executable code                | Parse Failure                           |
| **Parsing Edge Cases**       | `"{\"key\": {\"key\": {\"key\": {\"key\": {}}}}}"` | Deeply nested JSON            | Success (Parsed object with depth)       |
|                              | `"{}"`                       | Large JSON text                               | Success (Parsed object)                 |
|                              | `"{key": value}"`            | Invalid JSON structure                        | Parse Failure                           |
| **MIME Type**                | `"{\"key\": \"value\"}"`     | application/json as MIME type                 | Success (Proper MIME type)              |
