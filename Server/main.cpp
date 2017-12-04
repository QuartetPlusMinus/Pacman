//
// Created by viewsharp on 28.11.17.
//

#include "service.grpc.pb.h"
#include "PlayerConnectionServer.h"

using grpc::Server;
using grpc::ServerBuilder;

int main() {

    std::string server_address("0.0.0.0:29563");
    PlayerConnectionImpl service("localhost:11211");

    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}