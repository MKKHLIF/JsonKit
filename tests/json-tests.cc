#include <gtest/gtest.h>
#include <value.h>

TEST(JsonTests, FromNull) {
     const Value json(nullptr);
    ASSERT_EQ("null", json.ToEncoding());
}