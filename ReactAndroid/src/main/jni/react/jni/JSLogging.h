/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <android/log.h>
#include <string>

namespace facebook {
namespace react {

#ifndef RN_EXPORT
#define RN_EXPORT __attribute__((visibility("default")))
#endif

RN_EXPORT void reactAndroidLoggingHook(
    const std::string &message,
    android_LogPriority logLevel);
RN_EXPORT void reactAndroidLoggingHook(const std::string &message, unsigned int logLevel);

} // namespace react
} // namespace facebook
