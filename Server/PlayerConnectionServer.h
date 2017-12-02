/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <list>
#include <map>
#include <chrono>

#include "service.grpc.pb.h"
#include "Player.h"
#include "Ghost.h"
#include "BaseBeing.h"

using grpc::ServerContext;
using grpc::Status;
using namespace pacman_service;
using namespace std;

typedef std::chrono::high_resolution_clock Time;

class PlayerConnectionImpl final : public PlayerConnection::Service {

public:

    PlayerConnectionImpl() : PlayerConnection::Service(), start(false) {
    }

    Status Connect(ServerContext *context, const ConnectRequest *request,
                   ConnectReply *reply) override;

    Status Start(ServerContext *context, const StartRequest *request,
                 StartReply *reply) override;

    Status Iteration(ServerContext *context, const IterationRequest *request,
                     IterationReply *reply) override;

    Status End(ServerContext *context, const EndRequest *request,
               EndReply *reply) override;

private:

    list <Player> players;
    chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> > > time;
    bool start;
    list <Ghost> ghosts;

};
