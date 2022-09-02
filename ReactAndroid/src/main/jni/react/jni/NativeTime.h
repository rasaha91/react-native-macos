/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace facebook {
namespace react {

#ifndef RN_EXPORT
#define RN_EXPORT __attribute__((visibility("default")))
#endif

RN_EXPORT double reactAndroidNativePerformanceNowHook();

} // namespace react
} // namespace facebook
