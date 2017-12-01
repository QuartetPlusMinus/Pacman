//
// Created by viewsharp on 01.12.17.
//

#include "PlayerConnectionClient.h"

ConnectReply *PlayerConnectionClient::Connect(ConnectRequest &request) {
    ConnectReply *reply = new ConnectReply();
    ClientContext context;
    Status status = stub_->Connect(&context, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

StartReply *PlayerConnectionClient::Start(StartRequest &request) {
    StartReply *reply = new StartReply();
    ClientContext context;
    Status status = stub_->Start(&context, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

IterationReply *PlayerConnectionClient::Iteration(IterationRequest &request) {
    IterationReply *reply = new IterationReply();
    ClientContext context;
    Status status = stub_->Iteration(&context, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

EndReply *PlayerConnectionClient::End(EndRequest &request) {
    EndReply *reply = new EndReply();
    ClientContext context;
    Status status = stub_->End(&context, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}