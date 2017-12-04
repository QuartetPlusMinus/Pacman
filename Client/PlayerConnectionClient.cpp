//
// Created by viewsharp on 01.12.17.
//

#include "PlayerConnectionClient.h"

ConnectReply *PlayerConnectionClient::Connect(ConnectRequest &request) {
    auto *reply = new ConnectReply();
    auto *context_ = new ClientContext();
    Status status = stub_->Connect(context_, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

StartReply *PlayerConnectionClient::Start(StartRequest &request, string hex) {
    auto *reply = new StartReply();
    auto *context_ = new ClientContext();
    context_->AddMetadata("hex", hex);
    Status status = stub_->Start(context_, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}

IterationReply *PlayerConnectionClient::Iteration(IterationRequest &request, string hex) {
    auto *reply = new IterationReply();
    auto *context_ = new ClientContext();
    context_->AddMetadata("hex", hex);
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
    auto *reply = new EndReply();
    auto *context_ = new ClientContext();
    Status status = stub_->End(context_, request, reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_code();
    }
}