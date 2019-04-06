#pragma once

#include "lexer/token/token.hpp"

namespace cmsl
{
    namespace ast
    {
        class type_representation
        {
        public:
            struct is_reference_tag{};

            explicit type_representation(lexer::token::token primary_name,
                                         lexer::token::token reference_token,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ { primary_name } }
                    , m_nested_types{ std::move(nested_types) }
                    , m_reference_token{ reference_token }
            {}
            explicit type_representation(lexer::token::token_container_t tokens,
                                         lexer::token::token reference_token,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ std::move(tokens) }
                    , m_nested_types{ std::move(nested_types) }
                    , m_reference_token{ reference_token }
            {}

            explicit type_representation(lexer::token::token primary_name,
                                         is_reference_tag,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ { primary_name } }
                    , m_nested_types{ std::move(nested_types) }
                    , m_is_reference{ true }
            {}
            explicit type_representation(lexer::token::token_container_t tokens,
                                         is_reference_tag,
                                         std::vector<type_representation> nested_types  = {})
                    : m_tokens{ std::move(tokens) }
                    , m_nested_types{ std::move(nested_types) }
                    , m_is_reference{ true }
            {}
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
                auto str = to_string_without_reference();
                if(!is_reference())
                {
                    return str;
                }

                str += '&';
                return str;
            }

            std::string to_string_without_reference() const
            {
                // Todo: create string once, store it somewhere (some strings container) and return string_view.
                std::string result;

                for(const auto& token : m_tokens)
                {
                    result += token.str();
                }

                return result;
            }

            bool operator==(const type_representation& rhs) const
            {
                // Todo: Do we need to compare nested types? Full name is already compared with to_string_without_reference() comparison
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

            bool is_reference() const
            {
                return m_reference_token.has_value() || m_is_reference;
            }

        private:
            lexer::token::token_container_t m_tokens;
            std::optional<lexer::token::token> m_reference_token;
            bool m_is_reference{ false };

            // 'template parameters' of generic types.
            std::vector<type_representation> m_nested_types;
        };
    }
}
