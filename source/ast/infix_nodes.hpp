#pragma once

#include "ast/ast_node.hpp"
#include "lexer/token/token.hpp"

#include <memory>

namespace cmsl
{
    namespace ast
    {
        class binary_operator_node : public ast_node
        {
        public:
            explicit binary_operator_node(std::unique_ptr<ast_node> lhs, lexer::token::token op,  std::unique_ptr<ast_node> rhs)
                : m_lhs{ std::move(lhs)}
                , m_operator{ op }
                , m_rhs{ std::move(rhs)}
            {}

        private:
            std::unique_ptr<ast_node> m_lhs;
            lexer::token::token m_operator;
            std::unique_ptr<ast_node> m_rhs;
        };

        class class_member_access_node : public ast_node
        {
        public:
            explicit class_member_access_node(std::unique_ptr<ast_node> lhs, lexer::token::token member_name)
                : m_lhs{ std::move(lhs) }
                , m_member_name{ member_name }
            {}

        private:
            std::unique_ptr<ast_node> m_lhs;
            lexer::token::token m_member_name;
        };

        class call_node : public ast_node
        {
        public:
            using params_t = std::vector<std::unique_ptr<ast_node>>;

            explicit call_node(lexer::token::token name, params_t parameter_expressions)
                : m_name{ name }
                , m_parameter_expressions{ std::move(parameter_expressions) }
            {}

        private:
            lexer::token::token m_name;
            params_t m_parameter_expressions;
        };

        class function_call_node : public call_node
        {
        public:
            explicit function_call_node(lexer::token::token name, params_t params)
                : call_node{ name, std::move(params) }
            {}
        };

        class member_function_call_node : public call_node
        {
        public:
            explicit member_function_call_node(std::unique_ptr<ast_node> lhs, lexer::token::token name, params_t params)
                : call_node{ name, std::move(params) }
                , m_lhs{ std::move(lhs) }
            {}

        private:
            std::unique_ptr<ast_node> m_lhs;
        };

        class fundamental_value_node : public ast_node
        {
        public:
            explicit fundamental_value_node(lexer::token::token token)
                : m_token{ token }
            {}

            lexer::token::token get_token() const
            {
                return m_token;
            }

        protected:
            const lexer::token::token m_token;
        };

        class bool_value_node : public fundamental_value_node
        {
        public:
            explicit bool_value_node(lexer::token::token token)
                : fundamental_value_node{token}
            {}
        };

        class int_value_node : public fundamental_value_node
        {
        public:
            explicit int_value_node(lexer::token::token token)
                    : fundamental_value_node{token}
            {}
        };

        class double_value_node : public fundamental_value_node
        {
        public:
            explicit double_value_node(lexer::token::token token)
                : fundamental_value_node{token}
            {}
        };

        class string_value_node : public fundamental_value_node
        {
        public:
            explicit string_value_node(lexer::token::token token)
                : fundamental_value_node{token}
            {}
        };

        class id_node : public ast_node
        {
        public:
            explicit id_node(lexer::token::token identifer)
                : m_identifer{ identifer }
            {}

            lexer::token::token get_identifier() const
            {
                return m_identifer;
            }

        private:
            lexer::token::token m_identifer;
        };
    }
}
