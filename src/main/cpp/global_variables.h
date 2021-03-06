// Copyright 2016 The Bazel Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// global_variables.h: The global state in the blaze.cc Blaze client.
//

#ifndef BAZEL_SRC_MAIN_CPP_GLOBAL_VARIABLES_H_
#define BAZEL_SRC_MAIN_CPP_GLOBAL_VARIABLES_H_

#include <sys/types.h>
#include <string>
#include <vector>

#include "src/main/cpp/util/port.h"  // pid_t on Windows/MSVC

namespace blaze {

class StartupOptions;

// The reason for a blaze server restart.
// Keep in sync with logging.proto.
enum RestartReason {
  NO_RESTART = 0,
  NO_DAEMON,
  NEW_VERSION,
  NEW_OPTIONS,
  PID_FILE_BUT_NO_SERVER,
  SERVER_VANISHED,
  SERVER_UNRESPONSIVE
};

struct GlobalVariables {
  GlobalVariables();

  // Whrere to write the server's JVM's output. Default value is
  // <output_base>/server/jvm.out.
  std::string jvm_log_file;

  // Whether or not the jvm_log_file should be opened with O_APPEND.
  bool jvm_log_file_append;

  // The nearest enclosing workspace directory, starting from cwd.
  // If not under a workspace directory, this is equal to cwd.
  std::string workspace;

  // TODO(laszlocsomor) 2016-11-28: move pid_t usage out of here and wherever
  // else it appears. Find some way to not have to declare a pid_t here, either
  // by making PID handling platform-independent or some other idea.
  pid_t server_pid;

  // The reason for the server restart.
  RestartReason restart_reason;

  // The absolute path of the blaze binary.
  std::string binary_path;
};

}  // namespace blaze

#endif  // BAZEL_SRC_MAIN_CPP_GLOBAL_VARIABLES_H_
