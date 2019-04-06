#pragma once

#include "common/string.hpp"

namespace cmsl::exec
{
        namespace inst
        {
            class instance;
        }

        class identifiers_context
        {
        public:
            virtual ~identifiers_context() = default;
            virtual inst::instance* lookup_identifier(cmsl::string_view identifier) = 0;
        };
}
