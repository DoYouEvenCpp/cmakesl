#pragma once

#include "ast/ast_node_visitor.hpp"
#include "sema/sema_context.hpp"
#include "sema/sema_node.hpp"
#include "sema/type_member_info.hpp"

#include <optional>

#include <memory>
#include <vector>

namespace cmsl {
namespace ast {
class ast_node;
class type_representation;
}

namespace errors {
class errors_observer;
}

namespace lexer {
class token;
}

namespace sema {
class add_subdirectory_handler;
class builtin_token_provider;
class expression_node;
class variable_declaration_node;
class sema_type;
class identifiers_context;
class sema_type_factory;
class sema_function_factory;
class sema_context_factory;
class user_sema_function;
class sema_context_impl;
struct function_signature;

class sema_builder_ast_visitor : public ast::ast_node_visitor
{
private:
  using param_expressions_t = std::vector<std::unique_ptr<expression_node>>;

public:
  explicit sema_builder_ast_visitor(
    sema_context& generic_types_context, sema_context& ctx,
    errors::errors_observer& errs, identifiers_context& ids_context,
    sema_type_factory& type_factory, sema_function_factory& function_factory,
    sema_context_factory& context_factory,
    add_subdirectory_handler& add_subdirectory_handler,
    const builtin_token_provider& builtin_token_provider,
    sema_function* currently_parsing_function =
      nullptr); // Todo: Create private ctor that takes
                // currently_parsing_function

  void visit(const ast::block_node& node) override;
  void visit(const ast::class_node& node) override;
  void visit(const ast::conditional_node& node) override;
  void visit(const ast::if_else_node& node) override;
  void visit(const ast::binary_operator_node& node) override;
  void visit(const ast::class_member_access_node& node) override;
  void visit(const ast::function_call_node& node) override;
  void visit(const ast::member_function_call_node& node) override;
  void visit(const ast::bool_value_node& node) override;
  void visit(const ast::int_value_node& node) override;
  void visit(const ast::double_value_node& node) override;
  void visit(const ast::string_value_node& node) override;
  void visit(const ast::id_node& node) override;
  void visit(const ast::return_node& node) override;
  void visit(const ast::translation_unit_node& node) override;
  void visit(const ast::user_function_node& node) override;
  void visit(const ast::variable_declaration_node& node) override;
  void visit(const ast::while_node& node) override;
  void visit(const ast::initializer_list_node& node) override;

private:
  const sema_type* try_get_or_create_generic_type(
    const sema_context& search_context, const ast::type_representation& name);

  std::unique_ptr<expression_node> build_function_call(
    const ast::function_call_node& node);
  std::unique_ptr<expression_node> build_add_subdirectory_call(
    const ast::function_call_node& node);

  template <typename T>
  std::unique_ptr<T> to_node(std::unique_ptr<sema_node> node) const;
  std::unique_ptr<expression_node> to_expression(
    std::unique_ptr<sema_node> node) const;

  void raise_error(const lexer::token token, const std::string& message);

  sema_builder_ast_visitor clone() const;
  sema_builder_ast_visitor clone(sema_context& ctx_to_visit) const;

  template <typename T>
  std::unique_ptr<T> visit_child_node(const ast::ast_node& node);

  template <typename T>
  std::unique_ptr<T> visit_child_node(const ast::ast_node& node,
                                      sema_context& ctx_to_visit);
  std::unique_ptr<sema_node> visit_child(const ast::ast_node& node);
  std::unique_ptr<sema_node> visit_child(const ast::ast_node& node,
                                         sema_context& ctx_to_visit);
  std::unique_ptr<expression_node> visit_child_expr(const ast::ast_node& node);

  std::optional<param_expressions_t> get_function_call_params(
    const std::vector<std::unique_ptr<ast::ast_node>>& passed_params);

  struct ids_ctx_guard
  {
    explicit ids_ctx_guard(identifiers_context& ids_context);

    ~ids_ctx_guard();

    identifiers_context& m_ids_ctx;
  };

  ids_ctx_guard ids_guard();

  struct function_declaration
  {
    const ast::user_function_node& ast_function_node;
    user_sema_function* fun{ nullptr };
    const ast::block_node& body_to_visit;
  };

  struct class_members
  {
    std::vector<member_info> info;
    std::vector<std::unique_ptr<variable_declaration_node>> declarations;
    std::vector<function_declaration> functions;
  };

  std::optional<function_declaration> get_function_declaration_and_add_to_ctx(
    const ast::user_function_node& node, sema_context_impl& ctx);
  std::optional<class_members> collect_class_members_and_add_functions_to_ctx(
    const ast::class_node& node, sema_context_impl& class_context);

  template <unsigned N>
  lexer::token make_token(lexer::token_type token_type, const char (&tok)[N]);

  param_expressions_t convert_params_to_cast_nodes_if_need(
    const function_signature& signature, param_expressions_t params);
  std::unique_ptr<expression_node> convert_to_cast_return_node_if_need(
    std::unique_ptr<expression_node> expression);
  std::unique_ptr<expression_node> convert_to_cast_node_if_need(
    const sema_type& expected_result_type,
    std::unique_ptr<expression_node> expression);

public:
  std::unique_ptr<sema_node> m_result_node;

private:
  sema_context& m_generic_types_context;
  sema_context& m_ctx;
  errors::errors_observer& m_errors_observer;
  identifiers_context& m_ids_context;
  sema_type_factory& m_type_factory;
  sema_function_factory& m_function_factory;
  sema_context_factory& m_context_factory;
  add_subdirectory_handler& m_add_subdirectory_handler;
  const builtin_token_provider& m_builtin_token_provider;
  sema_function* m_currently_parsed_function{ nullptr };
};
}
}