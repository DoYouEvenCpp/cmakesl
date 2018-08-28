#pragma once

#include "ast/parameter_declaration.hpp"
#include "lexer/token/token.hpp"

#include <boost/optional.hpp>

#include <memory>

namespace cmsl
{
    namespace errors
    {
        class errors_observer;
    }

    namespace ast
    {
        class ast_context;
        class ast_node;
        class type;
        class function_node;
        class block_node;
        class return_node;
        class infix_node;
        class declaration_node;
        class class_node;
        class member_declaration;

        class parser
        {
        public:
            using token_container_t = lexer::token::token_container_t;
            using token_it = token_container_t::const_iterator;
            using token_type_t = lexer::token::token_type;

            parser(errors::errors_observer& err_observer, const token_container_t& tokens);

            const type* get_type(ast_context& ctx);
            boost::optional<std::vector<parameter_declaration>> get_parameters_declaration(ast_context& ctx);
            std::unique_ptr<infix_node> get_infix();
            std::unique_ptr<block_node> get_block(ast_context& ctx);
            std::unique_ptr<function_node> get_function(ast_context& ctx);
            std::unique_ptr<return_node> get_return_node();
            std::unique_ptr<declaration_node> get_declaration(ast_context& ctx);
            std::unique_ptr<class_node> get_class(ast_context& ctx);
            boost::optional<member_declaration> get_class_member_declaration(ast_context& ctx);

            std::unique_ptr<class_node> try_get_class_node(ast_context& ctx);

            bool is_at_end() const;

        private:
            bool eat(boost::optional<token_type_t> type = {});
            bool eat_type();

            bool expect_not_at_end();
            bool expect_token(token_type_t type);
            bool expect_token_other_than(token_type_t type);

            bool is_builtin_type(token_type_t token_type) const;
            bool current_is_infix_token() const;
            bool current_is_type(ast_context& ctx) const;
            bool current_is(token_type_t token_type) const;

            token_type_t peek(size_t n) const;
            bool declaration_starts(ast_context& ctx) const;
            bool class_function_starts() const;

            void raise_error();

            boost::optional<parameter_declaration> get_parameter_declaration(ast_context& ctx);
            // Returns true on success, false otherwise
            bool prepare_for_next_parameter_declaration();

            boost::optional<lexer::token::token> get_identifier();

        private:
            errors::errors_observer& m_err_observer;
            token_it m_token;
            token_it m_end;
        };
    }
}
