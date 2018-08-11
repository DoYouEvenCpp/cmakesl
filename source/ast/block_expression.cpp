#include "ast/block_expression.hpp"

#include <algorithm>
#include <iterator>

namespace cmsl
{
    namespace ast
    {
        block_expression::block_expression(std::vector<std::unique_ptr<ast_node>> expressions)
            : ast_node{ expression_type::block }
            , m_expressions{ std::move(expressions) }
        {}

        std::vector<ast_node*> block_expression::get_expressions()
        {
            std::vector<ast_node*> result;

            std::transform(std::begin(m_expressions), std::end(m_expressions),
                           std::back_inserter(result),
                           [](auto& expr)
                           {
                               return expr.get();
                           });

            return result;
        }
    }
}
