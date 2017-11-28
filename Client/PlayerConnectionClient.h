//
// Created by viewsharp on 28.11.17.
//

#ifndef CLIENT_GETCOORDS_H
#define CLIENT_GETCOORDS_H

#include <grpc++/grpc++.h>
#include "service.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using pacman_service::PlayerConnection;
using pacman_service::GetCoordsRequest;
using pacman_service::GetCoordsReply;
using pacman_service::SinglePlayer;

class PlayerConnectionClient {
public:
    explicit PlayerConnectionClient(std::shared_ptr<Channel> channel)
    : stub_(PlayerConnection::NewStub(channel)) {}

    GetCoordsReply GetCoords();

private:
    std::unique_ptr<PlayerConnection::Stub> stub_;

};

#endif //CLIENT_GETCOORDS_H
