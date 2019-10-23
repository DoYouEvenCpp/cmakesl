#include <gmock/gmock.h>

#include "tools/lib/cmsl_index.hpp"
#include "tools/lib/cmsl_parsed_source.hpp"

namespace cmsl::tools::test
{
    using ::testing::NotNull;
    using ::testing::Eq;

    TEST(IndexerSmokeTest,            UnaryOperator)
    {
        const auto source = "auto foo = -42;";

        cmsl_parsed_source* parsed_source =
                cmsl_parse_source(source, nullptr);
        ASSERT_THAT(parsed_source, NotNull());

        cmsl_index_entries* index_entries = cmsl_index(parsed_source);
        ASSERT_THAT(index_entries, NotNull());

        EXPECT_THAT(index_entries->num_entries, Eq(2u));

        cmsl_destroy_index_entries(index_entries);
        cmsl_destroy_parsed_source(parsed_source);
    } 
}
