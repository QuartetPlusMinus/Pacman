//
// Created by viewsharp on 28.11.17.
//

#include "PlayerConnectionServer.h"

using namespace std;
using chrono::high_resolution_clock;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

const int GHOST_COUNT = 4;

Status PlayerConnectionImpl::Connect(ServerContext *context, const ConnectRequest *request,
               ConnectReply *reply) {
    reply->set_id(rand());
    players.push_back(Player(request->name()));
    cout << request->name() <<": connect to Server" << endl;
    return Status::OK;
}

Status PlayerConnectionImpl::Start(ServerContext *context, const StartRequest *request,
             StartReply *reply) {
    auto context_map = context->client_metadata();
    cout << "\nmyMultimap contains:\n";
    for (auto it = context_map.begin(); it != context_map.end(); ++it)
    {
        cout << it->first << " : " << it->second << endl;
    }
    if (players.size() < 2) {
        reply->set_time(1000000);
        time = Time::now();
        cout << "please wait second player..." << endl;
    } else {
        if (start) {
            cout << "time 0" <<endl;
            reply->set_time(0);

            int i = 0;
            for (auto pIter = players.begin(); pIter != players.end(); ++pIter) {
                pIter->init(i, 80 * i, 0);
                BeingInit *data = reply->add_being();
                data->set_name(pIter->name);
                //cout << pIter->name << endl;
                data->set_allocated_data(pIter->getBeing());
                data->set_type(PACMAN);
                i++;
            }
            for (int i = 0; i < 2; i++) {
                cout << reply->being(i).name() << endl;
            }
            for (int i = 0; i < GHOST_COUNT; i++) {
                Ghost *ghost = new Ghost(i + players.size(), 400 + 80 * i, 400);
                ghosts.push_back(*ghost);
                BeingInit *data = reply->add_being();
                data->set_allocated_data(ghost->getBeing());
                data->set_type(GHOST);
            }
        } else {
            cout << "time not 0" <<endl;
            auto pause = Time::now() - time;
            reply->set_time(int(pause.count()/1000));
            start = true;
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
    reply->set_health(10);
    return Status::OK;
}

Status PlayerConnectionImpl::End(ServerContext *context, const EndRequest *request,
           EndReply *reply) {
    return Status::OK;
}