/*
 * Copyright (c) 2021 42dot All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AKIT_FAILOVER_FOROS_RAFT_OTHER_NODE_HPP_
#define AKIT_FAILOVER_FOROS_RAFT_OTHER_NODE_HPP_

#include <foros_msgs/srv/append_entries.hpp>
#include <foros_msgs/srv/request_vote.hpp>
#include <rclcpp/client.hpp>
#include <rclcpp/node_interfaces/node_base_interface.hpp>
#include <rclcpp/node_interfaces/node_graph_interface.hpp>
#include <rclcpp/node_interfaces/node_services_interface.hpp>

#include <functional>
#include <memory>
#include <string>

#include "akit/failover/foros/data.hpp"

namespace akit {
namespace failover {
namespace foros {
namespace raft {

class OtherNode {
 public:
  OtherNode(
      rclcpp::node_interfaces::NodeBaseInterface::SharedPtr node_base,
      rclcpp::node_interfaces::NodeGraphInterface::SharedPtr node_graph,
      rclcpp::node_interfaces::NodeServicesInterface::SharedPtr node_services,
      const std::string& cluster_name, const uint32_t node_id);

  bool broadcast(uint64_t current_term, uint32_t node_id,
                 std::function<void(uint64_t, bool)> callback);

  bool commit(uint64_t current_term, uint32_t node_id, uint64_t prev_log_index,
              uint64_t prev_log_term, Data::SharedPtr data,
              std::function<void(uint64_t, bool)> callback);

  bool request_vote(uint64_t current_term, uint32_t node_id,
                    std::function<void(uint64_t, bool)> callback);

 private:
  void send_append_entreis(
      foros_msgs::srv::AppendEntries::Request::SharedPtr request,
      std::function<void(uint64_t, bool)> callback);

  // index of the next data entry to send to this node
  uint64_t next_index_;
  // index of highest data entry known to be replicated on this node
  uint64_t match_index_;
  rclcpp::Client<foros_msgs::srv::AppendEntries>::SharedPtr append_entries_;
  rclcpp::Client<foros_msgs::srv::RequestVote>::SharedPtr request_vote_;
};

}  // namespace raft
}  // namespace foros
}  // namespace failover
}  // namespace akit

#endif  // AKIT_FAILOVER_FOROS_RAFT_OTHER_NODE_HPP_
