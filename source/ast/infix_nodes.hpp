#pragma once

#include "ast/ast_node.hpp"
#include "lexer/token/token.hpp"

#include <memory>

namespace cmsl::ast
{
        class binary_operator_node : public ast_node
        {
        public:
            explicit binary_operator_node(std::unique_ptr<ast_node> lhs, lexer::token::token op,  std::unique_ptr<ast_node> rhs)
                : m_lhs{ std::move(lhs)}
                , m_operator{ op }
                , m_rhs{ std::move(rhs)}
            {}

            const ast_node& get_lhs() const
            {
                return *m_lhs;
            }

            lexer::token::token get_operator() const
            {
                return m_operator;
            }

            const ast_node& get_rhs() const
            {
                return *m_rhs;
            }

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }

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

            const ast_node& get_lhs() const
            {
                return *m_lhs;
            }

            lexer::token::token get_member_name() const
            {
                return m_member_name;
            }

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }

        private:
            std::unique_ptr<ast_node> m_lhs;
            lexer::token::token m_member_name;
        };

        class call_node : public ast_node
        {
        public:
            using params_t = std::vector<std::unique_ptr<ast_node>>;

            explicit call_node(lexer::token::token name, params_t parameter_nodes)
                : m_name{ std::move(name) }
                , m_parameter_nodes{ std::move(parameter_nodes) }
            {}

            lexer::token::token get_name() const
            {
                return m_name;
            }

            const params_t& get_param_nodes() const
            {
                return m_parameter_nodes;
            }

        private:
            lexer::token::token m_name;
            params_t m_parameter_nodes;
        };

        class function_call_node : public call_node
        {
        public:
            explicit function_call_node(lexer::token::token name, params_t params)
                : call_node{ name, std::move(params) }
            {}

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }
        };

        class member_function_call_node : public call_node
        {
        public:
            explicit member_function_call_node(std::unique_ptr<ast_node> lhs, lexer::token::token name, params_t params)
                : call_node{ name, std::move(params) }
                , m_lhs{ std::move(lhs) }
            {}

            const ast_node& get_lhs() const
            {
                return *m_lhs;
            }

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }

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

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }
        };

        class int_value_node : public fundamental_value_node
        {
        public:
            explicit int_value_node(lexer::token::token token)
                    : fundamental_value_node{token}
            {}

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }
        };

        class double_value_node : public fundamental_value_node
        {
        public:
            explicit double_value_node(lexer::token::token token)
                : fundamental_value_node{token}
            {}

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }
        };

        class string_value_node : public fundamental_value_node
        {
        public:
            explicit string_value_node(lexer::token::token token)
                : fundamental_value_node{token}
            {}

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }
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

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }

        private:
            lexer::token::token m_identifer;
        };

        class initializer_list_node : public ast_node
        {
        private:
            using token_t = lexer::token::token;

        public:
            explicit initializer_list_node(token_t begin_token,
                                           token_t end_token,
                                           std::vector<std::unique_ptr<ast_node>> values)
                    : m_begin_token{ begin_token }
                    , m_end_token{ end_token }
                    , m_values{ std::move(values) }
            {}

            const std::vector<std::unique_ptr<ast_node>>& values() const
            {
                return m_values;
            }

            std::pair<token_t, token_t> begin_end() const
            {
                return { m_begin_token, m_end_token };
            }

            void visit(ast_node_visitor &visitor) const override
            {
                visitor.visit(*this);
            }

        private:
            token_t m_begin_token;
            token_t m_end_token;
            std::vector<std::unique_ptr<ast_node>> m_values;
        };
}
