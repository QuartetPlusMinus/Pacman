//
// Created by viewsharp on 28.11.17.
//

#include "PlayerConnectionServer.h"
#include "MapManager.h"

template< typename T >
std::string PlayerConnectionImpl::hex( T i )
{
    std::stringstream stream;
    stream << std::hex << i;
    return stream.str();
}

LocClient *PlayerConnectionImpl::clientFromContext(ServerContext *context) {
    auto hex_str = context->client_metadata().find("hex")->second;
    auto hex_chars = new char[hex_str.length() + 1];
    strncpy(hex_chars, hex_str.data(), hex_str.length());
    hex_chars[hex_str.length()] = '\0';
    return  clientMap.find(hex_chars)->second;
}

Status PlayerConnectionImpl::Connect(ServerContext *context, const ConnectRequest *request,
               ConnectReply *reply) {

    auto client = new LocClient(request->name());
    string hexStr = hex<LocClient *>(client);

    clients.push(client);
    cout << "pair: " <<hexStr << " , "<< client<< endl;
    clientMap.insert(pair<string,Client<PLAYER_COUNT, GHOST_COUNT> *>(hexStr, client) );
    reply->set_hex(hexStr);

    cout << request->name() <<": connect to Server" << endl;

    return Status::OK;
}

Status PlayerConnectionImpl::Start(ServerContext *context, const StartRequest *request,
             StartReply *reply) {
    if (start) {
        LocClient *client = clientFromContext(context);

        reply->set_id(client->getId());
        reply->set_time(0);

        MapManager::getMap(reply);

        client->room->getStartReply(reply);
    } else {
        if (clients.size() < PLAYER_COUNT) {
            reply->set_time(1000000);
            time = steady_clock::now();
        } else {
            reply->set_time(duration_cast<chrono::milliseconds>(steady_clock::now() - time).count());

            startGame();

            start = true;
        }
    }
    return Status::OK;
}

Status PlayerConnectionImpl::Iteration(ServerContext *context, const IterationRequest *request,
                 IterationReply *reply) {
    LocClient *client = clientFromContext(context);

    client->setEvent(request->direction());
    client->room->getIterationReply(reply);
    client->room->step();
    return Status::OK;
}

Status PlayerConnectionImpl::End(ServerContext *context, const EndRequest *request,
           EndReply *reply) {
    return Status::OK;
}

void PlayerConnectionImpl::startGame() {


    auto gameRoom = new GameRoom<PLAYER_COUNT, GHOST_COUNT>();

    for (int i = 0; i < PLAYER_COUNT; i++) {
        LocClient* client = clients.front();
        clients.pop();
        client->setRoom(gameRoom);
    }
}