//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2020
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/net/DcId.h"
#include "td/telegram/net/NetQuery.h"
#include "td/telegram/UniqueId.h"

#include "td/utils/buffer.h"
#include "td/utils/ObjectPool.h"
#include "td/utils/StorerBase.h"

namespace td {

class NetQueryCreator {
 public:
  using Ptr = NetQueryPtr;
  using Ref = NetQueryRef;

  NetQueryCreator() {
    object_pool_.set_check_empty(true);
  }

  void stop_check() {
    object_pool_.set_check_empty(false);
  }

  Ptr create_update(BufferSlice &&buffer) {
    return object_pool_.create(NetQuery::State::OK, 0, BufferSlice(), std::move(buffer), DcId::main(),
                               NetQuery::Type::Common, NetQuery::AuthFlag::On, NetQuery::GzipFlag::Off, 0);
  }

  Ptr create(const Storer &storer, DcId dc_id = DcId::main(), NetQuery::Type type = NetQuery::Type::Common,
             NetQuery::AuthFlag auth_flag = NetQuery::AuthFlag::On) {
    return create(UniqueId::next(), storer, dc_id, type, auth_flag);
  }
  Ptr create(uint64 id, const Storer &storer, DcId dc_id = DcId::main(), NetQuery::Type type = NetQuery::Type::Common,
             NetQuery::AuthFlag auth_flag = NetQuery::AuthFlag::On);

 private:
  ObjectPool<NetQuery> object_pool_;
};

}  // namespace td
