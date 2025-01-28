
# Test Cases:

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
