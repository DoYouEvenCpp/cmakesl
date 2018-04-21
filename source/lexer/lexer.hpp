#pragma once

#include "common/source_location.hpp"
#include "common/string.hpp"
#include "lexer/token/token.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace cmsl
{
    namespace errors
    {
        class errors_observer;
    }

    namespace lexer
    {
        class lexer
        {
        private:
            using source_t = cmsl::string_view;
            using source_it_t = source_t::const_iterator;
            using token_t = token::token;

        public:
            using tokens_container_t = std::vector<token_t>;

            lexer(errors::errors_observer& err_observer, source_t source);

            tokens_container_t lex();

        private:
            struct aritmetical_token_definition
            {
                token_t::token_type_t single;
                token_t::token_type_t op_equal;
                token_t::token_type_t twice;

                bool has_twice() const
                {
                    return twice != token_t::token_type_t::undef;
                }
            };

            using aritmetical_token_definition_t = std::unordered_map<char, aritmetical_token_definition>;
            aritmetical_token_definition_t create_arithmetical_token_definitions() const;

            using one_char_tokens_t = std::unordered_map<char, token_t::token_type_t>;
            one_char_tokens_t create_one_char_tokens() const;

            token_t get_next_token();
            token_t::token_type_t get_next_token_type();
            token_t::token_type_t get_numeric_token_type();
            token_t::token_type_t get_identifier_token_type();
            token_t::token_type_t get_equal_token_type();
            token_t::token_type_t get_string_token_type();
            token_t::token_type_t get_arithmetical_token_type(char operator_char);
            token_t::token_type_t get_one_char_token_type(char c);

            void consume_integer();
            void consume_char();

            bool is_end() const;
            bool has_next() const;

            bool is_identifier_char(char c) const;
            bool is_arithmetical_operator(char c) const;
            bool is_one_char_token(char c) const;

            char current() const;
            char next() const;

        private:
            errors::errors_observer& m_err_observer;
            const source_t m_source;
            source_location m_source_loc;
            const aritmetical_token_definition_t m_aritmetical_token_definitions;
            const one_char_tokens_t m_one_char_tokens;
        };
    }
}
