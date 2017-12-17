//
// Created by viewsharp on 28.11.17.
//

#include "PlayerConnectionServer.h"

template< typename T >
std::string PlayerConnectionImpl::hex( T i )
{
    std::stringstream stream;
    stream << std::hex << i;
    return stream.str();
}

LocClient &PlayerConnectionImpl::clientFromContext(ServerContext *context) {
    auto str_ref = context->client_metadata().find("hex")->second;

    if (str_ref.data() == nullptr)
        throw "pasha-1";

    string hex = str_ref.data();

    hex = hex.substr(0, str_ref.length()); // lenght != size

    auto result = clientMap.find(hex)->second;

    if (str_ref.data() == nullptr)
        throw "pasha-2";

    return *result;
}

Status PlayerConnectionImpl::Connect(ServerContext *context, const ConnectRequest *request,
               ConnectReply *reply) {

    auto client = new LocClient(request->name());
    string hexStr = hex<LocClient *>(client);

    clients.push(client);
    clientMap.insert(pair<string,Client<GHOST_COUNT> *>(hexStr, client) );
    reply->set_hex(hexStr);

    cout << request->name() <<": connect to Server" << endl;

    return Status::OK;
}

Status PlayerConnectionImpl::Start(ServerContext *context, const StartRequest *request,
             StartReply *reply) {

    LocClient client;
    try {
        client = clientFromContext(context);
    } catch(...) {
        return Status::CANCELLED;
    }

    if (client.room != nullptr) {

        reply->set_id(client.getId());
        reply->set_time(0);

        MapManager::getMap(reply);

        client.room->getStartReply(reply);
    } else {
        if (clients.size() < PLAYER_COUNT) {
            reply->set_time(1000000);
            time = steady_clock::now();
        } else {
            reply->set_time((google::protobuf::uint64)duration_cast<chrono::milliseconds>(steady_clock::now() - time).count());

            startGame();
        }
    }
    return Status::OK;
}

Status PlayerConnectionImpl::Iteration(ServerContext *context, const IterationRequest *request,
                 IterationReply *reply) {
    LocClient client;

    try {
        client = clientFromContext(context);
    } catch (...) {
        return Status::CANCELLED;
    }

    client.setEvent(request->direction());
    client.room->step();
    client.room->getIterationReply(reply);
    return Status::OK;
}

Status PlayerConnectionImpl::End(ServerContext *context, const EndRequest *request,
           EndReply *reply) {
    return Status::OK;
}

void PlayerConnectionImpl::startGame() {

    auto gameRoom = new GameRoom<GHOST_COUNT>();

    for (int i = 0; i < PLAYER_COUNT; i++) {
        LocClient* client = clients.front();

        gameRoom->addPlayer(client->name);
        client->setRoom(gameRoom);
        clients.pop();
    }

    gameRoom->start();
}
