//
//  SoulSifterServer.cpp
//  soul-sifter
//
//  Created by Robby Neale on 7/16/14.
//
//

#include "SoulSifterServer.h"

#include <iostream>

#include <google/protobuf/stubs/common.h>
#include <rpcz/rpcz.hpp>

#include "soul_sifter_service.pb.h"
#include "soul_sifter_service.rpcz.h"

using namespace std;

namespace dogatech {
namespace soulsifter {

class SoulSifterServiceImpl : public SoulSifterService {
  
  virtual void GetSong(const GetSongRequest& request,
                       rpcz::reply<GetSongResponse> reply) {
    cout << "Got request for '" << request.id() << "'" << endl;
    GetSongResponse response;
    response.set_title("result1 for ");
    reply.send(response);
  }

};

}  // namespace soulsifter
}  // namespace dogatech

int main(int argc, const char* argv[]) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  
  rpcz::application application;
  rpcz::server server(application);
  dogatech::soulsifter::SoulSifterServiceImpl search_service;
  server.register_service(&search_service);
  cout << "Serving requests on port 5555." << endl;
  server.bind("tcp://*:5555");
  application.run();
}