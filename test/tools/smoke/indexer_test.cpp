#include <gmock/gmock.h>

#include "tools/lib/cmsl_index.hpp"
#include "tools/lib/cmsl_parsed_source.hpp"

namespace
{
    const char* entry_type_to_string(enum cmsl_index_entry_type entry_type)
    {
        switch (entry_type) {

            case type:
                return "type";
            case identifier:
                return "identifier";
            case parameter_declaration_identifier:
                return "parameter declaration identifier";
            case class_member_identifier:
                return "class member identifier";
            case operator_function:
                return "operator function";
            case function_call_name:
                return "function call name";
            default:
                return "unknown";
        }
    }
}

namespace cmsl::tools::test
{
    using ::testing::NotNull;
    using ::testing::Eq;

    class IndexerSmokeTest : public ::testing::Test
    {
    protected:
        std::pair<cmsl_parsed_source*,cmsl_index_entries*>  index_source(const char* source)
        {
            cmsl_parsed_source* parsed_source =
                    cmsl_parse_source(source, nullptr);
            if(parsed_source == nullptr)
            {
                return {};
            }

            cmsl_index_entries* index_entries = cmsl_index(parsed_source);
            if(index_entries == nullptr)
            {
                return {};
            }

            return std::make_pair(parsed_source, index_entries);
        }

        void cleanup(cmsl_parsed_source* parsed_source, cmsl_index_entries* index_entries)
        {
            cmsl_destroy_index_entries(index_entries);
            cmsl_destroy_parsed_source(parsed_source);
        }

        void print(cmsl_index_entries* index_entries)
        {
            int i;
            for (i = 0; i < index_entries->num_entries; ++i) {
                struct cmsl_index_entry* entry = &index_entries->entries[i];
                printf("source begin: %d, source end: %d, destination position: %d, entry "
                       "type: %s, destination path: %s\n",
                       entry->begin_pos, entry->end_pos, entry->position,
                       entry_type_to_string(entry->type), entry->source_path);
            }
        }
    };


    TEST_F(IndexerSmokeTest,            UnaryOperator)
    {
        const auto source = "auto foo = -42;";
        auto [parsed_source, index_entries] = index_source(source);
        ASSERT_THAT(parsed_source, NotNull());
        ASSERT_THAT(index_entries, NotNull());

        print(index_entries);

        EXPECT_THAT(index_entries->num_entries, Eq(2u));

        cleanup(parsed_source, index_entries);
    }

    TEST_F(IndexerSmokeTest,            ForLoopIteration)
    {
        const auto source =
                "void foo()"
                "{"
                "    for(int i;;) {}"
                "}";
        auto [parsed_source, index_entries] = index_source(source);
        ASSERT_THAT(parsed_source, NotNull());
        ASSERT_THAT(index_entries, NotNull());

        // void and int types.
        EXPECT_THAT(index_entries->num_entries, Eq(2u));

        cleanup(parsed_source, index_entries);
    }
}
