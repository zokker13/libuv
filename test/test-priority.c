/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "uv.h"
#include "task.h"

#ifndef _WIN32
#include <unistd.h>
#endif

TEST_IMPL(priority_get) {
  int32_t prio = 0;
  uv_pid_t this_pid = uv_os_getpid();
  int32_t result = uv_getpriority(this_pid, &prio);

  ASSERT(result == 0);

  return 0;
}

TEST_IMPL(priority_set) {
  int32_t result;
  uv_pid_t this_pid = uv_os_getpid();

  result = uv_setpriority(this_pid, 3);

  ASSERT(result == 0);

  return 0;
}

TEST_IMPL(priority_set_get) {
  int32_t old_prio = 0;
  int32_t new_prio = 0;
  uv_pid_t this_pid = uv_os_getpid();

  int32_t g_result = uv_getpriority(this_pid, &old_prio);
  int32_t s_result = uv_setpriority(this_pid, 3);
  int32_t g_result2 = uv_getpriority(this_pid, &new_prio);

  ASSERT(g_result == 0);
  ASSERT(g_result2 == 0);
  ASSERT(s_result == 0);
  ASSERT(old_prio != new_prio);

  return 0;
}
