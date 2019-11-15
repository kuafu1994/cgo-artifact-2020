/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*!
 *  Copyright (c) 2018 by Contributors.
 *
 * \file tvm/relay/pass/pass_util.h
 * \brief Utilities for writing
 */
#ifndef TVM_RELAY_PASS_PASS_UTIL_H_
#define TVM_RELAY_PASS_PASS_UTIL_H_

#include <tvm/relay/op.h>
#include <tvm/relay/expr.h>
#include <tvm/relay/attrs/transform.h>
#include <unordered_map>

namespace tvm {
namespace relay {

/*!
 * \brief Get reference counter of each internal ExprNode in body.
 * \param body The body expression.
 * \return The reference count mapping.
 */
std::unordered_map<const Node*, size_t>
GetExprRefCount(const Expr& body);

/*!
 * \brief Check if expr is positive constant.
 * \param expr The expression to be checked.
 * \return Whether all elements of expr is positive constant.
 */
bool IsAllPositiveConstant(const Expr& expr);

/*!
 * \brief Substitute var with subst.
 * \param type The type to be substituted.
 * \param tvar The type variable to be substituted.
 * \param subst The target of substitution.
 * \return The substituted result.
 */
Type TypeSubst(const Type& type, const TypeVar& tvar, const Type& subst);

/*!
 * \brief Substitute var with subst.
 * \param expr The expr to be substituted.
 * \param tvar The type variable to be substituted.
 * \param subst The target of substitution.
 * \return The substituted result.
 */
Expr TypeSubst(const Expr& expr, const TypeVar& tvar, const Type& subst);

/*!
 * \brief Substitute type vars in type.
 * \param type The type to be substituted.
 * \param subst_map The map of substitution.
 * \return The substituted result.
 */
Type TypeSubst(const Type& type, const tvm::Map<TypeVar, Type>& subst_map);

/*!
 * \brief Substitute type vars in type.
 * \param expr The expr to be substituted.
 * \param subst_map The map of substitution.
 * \return The substituted result.
 */
Expr TypeSubst(const Expr& expr, const tvm::Map<TypeVar, Type>& subst_map);

/*!
 * \brief Make arbitrary transformation preserve the out most function.
 * \param func The transformation.
 * \param e The expression
 * \return the transformed expression. If e is a function the return is also a function.
 */
inline Expr TransformF(const std::function<Expr(const Expr&)>& func, const Expr& e) {
  if (const FunctionNode* f = e.as<FunctionNode>()) {
    return FunctionNode::make(f->params, func(f->body), f->ret_type, f->type_params, f->attrs);
  } else {
    return func(e);
  }
}

}  // namespace relay
}  // namespace tvm
#endif  // TVM_RELAY_PASS_PASS_UTIL_H_