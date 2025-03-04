// ---------------------------------------------------------------------------
// Copyright (C) 2021, Bela contributors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Includes work from abseil-cpp (https://github.com/abseil/abseil-cpp)
// with modifications.
//
// Copyright 2019 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ---------------------------------------------------------------------------
#ifndef BELA_SUBSITUTE_NARROW_HPP
#define BELA_SUBSITUTE_NARROW_HPP
#pragma once
#include "ascii.hpp"
#include "str_cat_narrow.hpp" //AlphaNum

namespace bela::narrow {

namespace substitute_internal {
void SubstituteAndAppendArray(std::string *output, std::string_view format, const std::string_view *args_array,
                              size_t num_args);
}
inline void SubstituteAndAppend(std::string *output, std::string_view format) {
  substitute_internal::SubstituteAndAppendArray(output, format, nullptr, 0);
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0) {
  const std::string_view args[] = {a0.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0,
                                const AlphaNum &a1) {
  const std::string_view args[] = {a0.Piece(), a1.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(), a4.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4, const AlphaNum &a5) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(), a4.Piece(), a5.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4, const AlphaNum &a5,
                                const AlphaNum &a6) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(), a4.Piece(), a5.Piece(), a6.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4, const AlphaNum &a5,
                                const AlphaNum &a6, const AlphaNum &a7) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(),
                                    a4.Piece(), a5.Piece(), a6.Piece(), a7.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4, const AlphaNum &a5,
                                const AlphaNum &a6, const AlphaNum &a7, const AlphaNum &a8) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(), a4.Piece(),
                                    a5.Piece(), a6.Piece(), a7.Piece(), a8.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

inline void SubstituteAndAppend(std::string *output, std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4, const AlphaNum &a5,
                                const AlphaNum &a6, const AlphaNum &a7, const AlphaNum &a8, const AlphaNum &a9) {
  const std::string_view args[] = {a0.Piece(), a1.Piece(), a2.Piece(), a3.Piece(), a4.Piece(),
                                    a5.Piece(), a6.Piece(), a7.Piece(), a8.Piece(), a9.Piece()};
  substitute_internal::SubstituteAndAppendArray(output, format, args, std::size(args));
}

[[nodiscard]] inline std::string Substitute(std::string_view format) {
  std::string result;
  SubstituteAndAppend(&result, format);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0) {
  std::string result;
  SubstituteAndAppend(&result, format, a0);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4,
                                             const AlphaNum &a5) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4, a5);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4,
                                             const AlphaNum &a5, const AlphaNum &a6) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4, a5, a6);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4,
                                             const AlphaNum &a5, const AlphaNum &a6, const AlphaNum &a7) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4, a5, a6, a7);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4,
                                             const AlphaNum &a5, const AlphaNum &a6, const AlphaNum &a7,
                                             const AlphaNum &a8) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4, a5, a6, a7, a8);
  return result;
}

[[nodiscard]] inline std::string Substitute(std::string_view format, const AlphaNum &a0, const AlphaNum &a1,
                                             const AlphaNum &a2, const AlphaNum &a3, const AlphaNum &a4,
                                             const AlphaNum &a5, const AlphaNum &a6, const AlphaNum &a7,
                                             const AlphaNum &a8, const AlphaNum &a9) {
  std::string result;
  SubstituteAndAppend(&result, format, a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
  return result;
}
} // namespace bela::narrow

#endif
