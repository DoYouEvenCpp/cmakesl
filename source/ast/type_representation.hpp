#pragma once

#include "lexer/token/token.hpp"

namespace cmsl
{
    namespace ast
    {
        class type_representation
        {
        private:

        public:
            explicit type_representation(lexer::token::token primary_name,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ { primary_name } }
                    , m_nested_types{ std::move(nested_types) }
            {}
            explicit type_representation(lexer::token::token_container_t tokens,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ std::move(tokens) }
                    , m_nested_types{ std::move(nested_types) }
            {}

            lexer::token::token primary_name() const
            {
                return m_tokens.front();
            }

            const std::vector<type_representation>& nested_types() const
            {
                return m_nested_types;
            }

            const lexer::token::token_container_t& tokens() const
            {
                return m_tokens;
            }

            std::string to_string() const
            {
                // Todo: create string once, store it somewhere (some strings container) and return string_view.
                std::string result;

                for(const auto& token : m_tokens)
                {
                    result += token.str().to_string();
                }

                return result;
            }

            bool operator==(const type_representation& rhs) const
            {
                return this == &rhs || (to_string() == rhs.to_string() && m_nested_types == rhs.m_nested_types);
            }

            bool operator!=(const type_representation& rhs) const
            {
                return !(*this == rhs);
            }

            bool is_generic() const
            {
                return !m_nested_types.empty();
            }

        private:
            lexer::token::token_container_t m_tokens;

            // 'template parameters' of generic types.
            std::vector<type_representation> m_nested_types;
        };
    }
}
