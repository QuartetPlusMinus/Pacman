//
// Created by viewsharp on 28.11.17.
//

#include "PlayerConnectionServer.h"

using namespace std;
using chrono::high_resolution_clock;

#include "BaseBeing.cpp"

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

const int GHOST_COUNT = 4;

Status PlayerConnectionImpl::Connect(ServerContext *context, const ConnectRequest *request,
               ConnectReply *reply) {
    reply->set_id(players.size());
    players.push_back(Player(request->name()));
    return Status::OK;
}

Status PlayerConnectionImpl::Start(ServerContext *context, const StartRequest *request,
             StartReply *reply) {
    if (players.size() < 2) {
        reply->set_time(1000000);
        time = Time::now();
    } else {
        if (start) {
            reply->set_time(0);
        } else {
            auto pause = time - high_resolution_clock::now();
            reply->set_time(pause.count());
            start = true;
        }
        int i = 0;
        for (auto player: players) {
            player.init(i, 80 * i, 0);
            BeingInit *data = reply->add_being();
            data->set_allocated_data(player.getBeing());
            i++;
        }
        for (int i = 0; i < GHOST_COUNT; i++) {
            Ghost *ghost = new Ghost(i + players.size(), 400 + 80 * i, 400);
            ghosts.push_back(*ghost);
            BeingInit *data = reply->add_being();
            data->set_allocated_data(ghost->getBeing());

        }
    }
    return Status::OK;
}

Status PlayerConnectionImpl::Iteration(ServerContext *context, const IterationRequest *request,
                 IterationReply *reply) {

    for (auto player: players) {
        player.step();
        player.getBeing(reply->add_being());
    }
    for (auto ghost: ghosts) {
        ghost.step();
        ghost.getBeing(reply->add_being());
    }
    return Status::OK;
}

Status PlayerConnectionImpl::End(ServerContext *context, const EndRequest *request,
           EndReply *reply) {
    return Status::OK;
}