#pragma once

#include "ast/user_function_node.hpp"
#include "lexer/token/token.hpp"

namespace cmsl
{
    namespace ast
    {
        enum class type_kind;
        class ast_context;

        class type
        {
        public:
            using token_type_t = lexer::token::token_type;

            explicit type(lexer::token::token token);
            explicit type(cmsl::string_view name, type_kind kind, const ast_context* ast_ctx);

            type(const type&) = delete;
            type& operator=(const type&) = delete;

            virtual ~type() {}

            bool is_fundamental() const;

            cmsl::string_view get_name() const;

            const function* get_function(cmsl::string_view name) const;
            bool has_function(cmsl::string_view name) const;

            type_kind get_kind() const;

            bool operator==(const type& other) const;
            bool operator!=(const type& other) const;

        protected:
            void add_function();

        private:
            cmsl::string_view m_name;
            type_kind m_kind;
            const ast_context* m_ast_ctx;
        };
    }
}
