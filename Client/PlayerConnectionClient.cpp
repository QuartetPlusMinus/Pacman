//
// Created by viewsharp on 28.11.17.
//

#include "PlayerConnectionClient.h"

GetCoordsReply PlayerConnectionClient::GetCoords() {
    GetCoordsRequest request;
    GetCoordsReply reply;
    ClientContext context;
    Status status = stub_->GetCoords(&context, request, &reply);
    if (status.ok()) {
        return reply;
    } else {
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
        throw 404; //нужно нормальное исключение
    }

}