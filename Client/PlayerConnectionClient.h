//
// Created by viewsharp on 01.12.17.
//

#ifndef ONENIGHTPACMAN_PLAYERCONNECTIONCLIENT_H
#define ONENIGHTPACMAN_PLAYERCONNECTIONCLIENT_H

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <cstdlib>
#include <list>
#include <chrono>
#include <string>

#include "service.grpc.pb.h"
#include "Pacman.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace pacman_service;
using namespace std;

class PlayerConnectionClient {
public:
    PlayerConnectionClient(std::shared_ptr <Channel> channel):
            stub_(PlayerConnection::NewStub(channel))
    {}

    ConnectReply *Connect(ConnectRequest &request);
    StartReply *Start(StartRequest &request, string hex);
    IterationReply *Iteration(IterationRequest &request, string hex);
    EndReply *End(EndRequest &request);

private:
    unique_ptr <PlayerConnection::Stub> stub_;
};

#endif //ONENIGHTPACMAN_PLAYERCONNECTIONCLIENT_H