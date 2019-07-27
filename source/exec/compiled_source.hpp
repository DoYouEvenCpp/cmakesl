#pragma once

#include "common/source_view.hpp"

#include <memory>

namespace cmsl {
namespace ast {
class ast_node;
}

namespace sema {
class builtin_token_provider;
class sema_node;
class sema_function;
class sema_context;
}

namespace exec {
class compiled_source
{
public:
  explicit compiled_source(
    std::unique_ptr<ast::ast_node> ast_tree,
    std::unique_ptr<sema::sema_context> builtin_context,
    const sema::sema_context& global_context,
    std::unique_ptr<sema::sema_node> sema_tree, source_view source,
    std::unique_ptr<sema::builtin_token_provider> builtin_token_provider);
  ~compiled_source();

  const sema::sema_function* get_main() const;
  const sema::sema_context& get_global_context() const;

  const sema::sema_node& sema_tree() const;

private:
  std::unique_ptr<ast::ast_node> m_ast_tree;
  std::unique_ptr<sema::sema_context> m_builtin_context;
  const sema::sema_context& m_global_context;
  std::unique_ptr<sema::sema_node> m_sema_tree;
  source_view m_source;
  std::unique_ptr<sema::builtin_token_provider> m_builtin_token_provider;
};
}
}