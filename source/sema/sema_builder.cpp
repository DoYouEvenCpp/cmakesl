#include "sema/sema_builder.hpp"

namespace cmsl
{
    namespace sema
    {
        sema_builder::sema_builder(errors::errors_observer &errs)
            : m_errs{ errs }
        {}

        std::unique_ptr<sema_node> sema_builder::build(const ast::ast_node &ast_tree)
        {
            return std::unique_ptr<sema_node>();
        }
    }
}
