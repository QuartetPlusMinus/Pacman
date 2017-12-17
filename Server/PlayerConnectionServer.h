//
// Created by viewsharp on 28.11.17.
//

#ifndef PLAYERCONNECTIONSERVER_H
#define PLAYERCONNECTIONSERVER_H

#include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>
#include <queue>
#include <list>
#include <map>
#include <chrono>
#include <sstream>
#include <iomanip>
//#include <libmemcached/memcached.hpp>

#include "generated/service.grpc.pb.h"
#include "Client.h"
#include "GameRoom.h"

using namespace pacman_service;
using namespace std;

using grpc::ServerContext;
using grpc::Status;
using chrono::steady_clock;

const int GHOST_COUNT = 4;
const int PLAYER_COUNT = 2;

typedef Client<GHOST_COUNT> LocClient;

class PlayerConnectionImpl : public PlayerConnection::Service {

public:

    explicit PlayerConnectionImpl(const string &memcachedHost) :
            PlayerConnection::Service()
            /*mcClient(memcachedHost)*/ {}

    Status Connect(ServerContext *context, const ConnectRequest *request,
                   ConnectReply *reply) override;

    Status Start(ServerContext *context, const StartRequest *request,
                 StartReply *reply) override;

    Status Iteration(ServerContext *context, const IterationRequest *request,
                     IterationReply *reply) override;

    Status End(ServerContext *context, const EndRequest *request,
               EndReply *reply) override;

    void startGame();

private:

    template<typename T>
    std::string hex(T i);

    queue<LocClient *> clients;
    chrono::steady_clock::time_point time;
    map<string, LocClient *> clientMap;

    LocClient &clientFromContext(ServerContext *context);

    //memcache::Memcache mcClient;

};

#endif //PACMAN_GAMEROOM_H