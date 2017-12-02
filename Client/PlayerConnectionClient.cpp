//
// Created by viewsharp on 01.12.17.
//

#include "PlayerConnectionClient.h"

ConnectReply *PlayerConnectionClient::Connect(ConnectRequest &request) {
    ConnectReply *reply = new ConnectReply();
    ClientContext *context_ = new ClientContext();
    Status status = stub_->Connect(context_, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

StartReply *PlayerConnectionClient::Start(StartRequest &request, int id) {
    StartReply *reply = new StartReply();
    ClientContext *context_ = new ClientContext();
    context_->AddMetadata("id", to_string(id));
    Status status = stub_->Start(context_, request, reply);
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
    ClientContext *context_ = new ClientContext();
    Status status = stub_->Iteration(context_, request, reply);
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
    ClientContext *context_ = new ClientContext();
    Status status = stub_->End(context_, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}