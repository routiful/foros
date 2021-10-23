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

#ifndef AKIT_FAILSAFE_FSROS_COMMON_OBSERVABLE_HPP_
#define AKIT_FAILSAFE_FSROS_COMMON_OBSERVABLE_HPP_

#include <list>

#include "common/observer.hpp"

namespace akit {
namespace failsafe {
namespace fsros {

template <typename T>
class Observable {
 public:
  void AddObserver(Observer<T> *observer) { observers_.push_back(observer); }
  void RemoveObserver(Observer<T> *observer) { observers_.remove(observer); }
  void Notify(const T &event) {
    for (auto observer : observers_) {
      observer->Update(event);
    }
  }

 private:
  std::list<Observer<T> *> observers_;
};

}  // namespace fsros
}  // namespace failsafe
}  // namespace akit

#endif  // AKIT_FAILSAFE_FSROS_COMMON_OBSERVABLE_HPP_