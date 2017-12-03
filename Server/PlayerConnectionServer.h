//
// Created by viewsharp on 28.11.17.
//

#ifndef PLAYERCONNECTIONSERVER_H
#define PLAYERCONNECTIONSERVER_H

//#include "GameRoom.cpp"
//#include "Client.cpp" // оооочень плохо

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

#include "service.grpc.pb.h"
#include "Client.h"
#include "GameRoom.h"

using grpc::ServerContext;
using grpc::Status;
using namespace pacman_service;
using namespace std;

const int GHOST_COUNT = 4;
const int PLAYER_COUNT = 2;

typedef std::chrono::high_resolution_clock Time;
typedef Client<PLAYER_COUNT, GHOST_COUNT> LocClient;

class PlayerConnectionImpl: public PlayerConnection::Service {

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

    void startGame();

private:

    template< typename T >
    std::string hex( T i );
    queue<LocClient *> clients;
    chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1l, 1000000000l> > > time;
    bool start;
    map<string, LocClient *> clientMap;
    LocClient *clientFromContext(ServerContext *context);
};

#endif //PACMAN_GAMEROOM_H