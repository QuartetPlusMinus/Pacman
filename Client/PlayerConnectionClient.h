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
#include <generated/service.grpc.pb.h>

#include "Pacman.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using namespace std;
using namespace pacman_service;

class PlayerConnectionClient {
public:
    explicit PlayerConnectionClient(const string &host):
            stub_(PlayerConnection::NewStub(grpc::CreateChannel(
                    host + ":29563", grpc::InsecureChannelCredentials())))
    {}

    ConnectReply *Connect(ConnectRequest &request);
    StartReply *Start(StartRequest &request);
    IterationReply *Iteration(IterationRequest &request);
    EndReply *End(EndRequest &request);

    void setHex(const string  &value) {
        hex = value;
    }

private:

    string hex;
    unique_ptr <PlayerConnection::Stub> stub_;
};

#endif //ONENIGHTPACMAN_PLAYERCONNECTIONCLIENT_H