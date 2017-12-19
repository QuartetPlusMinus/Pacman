//
// Created by viewsharp on 01.12.17.
//

#include "PlayerConnectionClient.h"

ConnectReply *PlayerConnectionClient::Connect(ConnectRequest &request) {
    auto *reply = new ConnectReply();
    ClientContext context;
    Status status = stub_->Connect(&context, request, reply);
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
    return reply;
}

StartReply *PlayerConnectionClient::Start(StartRequest &request) {
    auto *reply = new StartReply();
    ClientContext context;
    context.AddMetadata("hex", hex);
    Status status = stub_->Start(&context, request, reply);
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
    return reply;
}

IterationReply *PlayerConnectionClient::Iteration(IterationRequest &request) {
    auto *reply = new IterationReply();
    ClientContext context;
    context.AddMetadata("hex", hex);
    Status status = stub_->Iteration(&context, request, reply);
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
    return reply;
}

EndReply *PlayerConnectionClient::End(EndRequest &request) {
    auto *reply = new EndReply();
    ClientContext context;
    cout << hex <<endl;
    context.AddMetadata("hex", hex);
    Status status = stub_->End(&context, request, reply);
    if (!status.ok()) {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
    return reply;
}