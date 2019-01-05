#pragma once

#include "lexer/token/token.hpp"

#include "sema/sema_node.hpp"
#include "sema/sema_node_visitor.hpp"

namespace cmsl
{
    namespace ast
    {
        class type;
    }

    namespace sema
    {
        class variable_declaration_node : public sema_node
        {
        public:
            explicit variable_declaration_node(const ast::type& type, const lexer::token::token name, std::unique_ptr<sema_node> initialization)
                : m_type{ type }
                , m_name{ name }
                , m_initialization{ std::move(initialization) }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }

            const ast::type& type() const
            {
                return m_type;
            }

            lexer::token::token name() const
            {
                return m_name;
            }

            const sema_node* initialization() const
            {
                return m_initialization.get();
            }

        private:
            const ast::type& m_type;
            const lexer::token::token m_name;
            std::unique_ptr<sema_node> m_initialization;
        };

        class expression_node : public sema_node
        {
        public:
            virtual const ast::type& type() const = 0;
        };

        template <typename T>
        class value_node : public expression_node
        {
        public:
            explicit value_node(const ast::type& t, T val)
                : m_type{ t }
                , m_value{ val }
            {}

            T value() const
            {
                return m_value;
            }

            const ast::type& type() const override
            {
                return m_type;
            }

        private:
            const ast::type& m_type;
            T m_value;
        };

        class bool_value_node : public value_node<bool>
        {
        public:
            explicit bool_value_node(const ast::type& t, bool val)
                : value_node{ t, val }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }
        };

        // Todo: move int alias to a common file
        class int_value_node : public value_node<std::int64_t>
        {
        public:
            explicit int_value_node(const ast::type& t, std::int64_t val)
                    : value_node{ t, val }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }
        };

        class double_value_node : public value_node<double>
        {
        public:
            explicit double_value_node(const ast::type& t, double val)
                    : value_node{ t, val }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }
        };

        class string_value_node : public value_node<cmsl::string_view>
        {
        public:
            explicit string_value_node(const ast::type& t, cmsl::string_view val)
                    : value_node{ t, val }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }
        };

        class id_node : public expression_node
        {
        public:
            explicit id_node(const ast::type& t, lexer::token::token id)
                : m_type{ t }
                , m_id{ id }
            {}

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }

            const ast::type& type() const override
            {
                return m_type;
            }

            // Todo: consider renaming getters to get_*
            lexer::token::token id() const
            {
                return m_id;
            }

        private:
            const ast::type& m_type;
            lexer::token::token m_id;
        };

        class return_node : public expression_node
        {
        public:
            explicit return_node(std::unique_ptr<expression_node> expr)
                : m_expr{ std::move(expr) }
            {}

            const ast::type& type() const override
            {
                return m_expr->type();
            }

            const expression_node& expression() const
            {
                return *m_expr;
            }

            void visit(sema_node_visitor& visitor) override
            {
                visitor.visit(*this);
            }

        private:
            std::unique_ptr<expression_node> m_expr;
        };
    }
}

