// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: soul_sifter_service.proto

#ifndef RPCZ_soul_5fsifter_5fservice_2eproto__INCLUDED
#define RPCZ_soul_5fsifter_5fservice_2eproto__INCLUDED

#include <string>
#include <rpcz/service.hpp>

namespace google {
namespace protobuf {
class ServiceDescriptor;
class MethodDescriptor;
}  // namespace protobuf
}  // namespace google
namespace rpcz {
class rpc;
class closure;
class rpc_channel;
}  //namesacpe rpcz
#include "soul_sifter_service.pb.h"

namespace dogatech {
namespace soulsifter {
void rpcz_protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
void rpcz_protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

class SoulSifterService_Stub;

class SoulSifterService : public rpcz::service {
 protected:
  // This class should be treated as an abstract interface.
  inline SoulSifterService() {};
 public:
  virtual ~SoulSifterService();

  typedef SoulSifterService_Stub Stub;

  static const ::google::protobuf::ServiceDescriptor* descriptor();

  virtual void GetSong(const ::dogatech::soulsifter::GetSongRequest& request,
                       ::rpcz::reply< ::dogatech::soulsifter::GetSongResponse> response);

  // implements Service ----------------------------------------------

  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void call_method(const ::google::protobuf::MethodDescriptor* method,
                  const ::google::protobuf::Message& request,
                  ::rpcz::server_channel* channel);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(SoulSifterService);
};

class SoulSifterService_Stub {
 public:
  SoulSifterService_Stub(::rpcz::rpc_channel* channel, 
                   bool owns_channel=false);
  SoulSifterService_Stub(::rpcz::rpc_channel* channel, 
                   const ::std::string& service_name,
                   bool owns_channel=false);
  ~SoulSifterService_Stub();

  inline ::rpcz::rpc_channel* channel() { return channel_; }


  void GetSong(const ::dogatech::soulsifter::GetSongRequest& request,
                       ::dogatech::soulsifter::GetSongResponse* response,
                       ::rpcz::rpc* rpc,                     ::rpcz::closure* done);
  void GetSong(const ::dogatech::soulsifter::GetSongRequest& request,
                       ::dogatech::soulsifter::GetSongResponse* response,
                       long deadline_ms = -1);
 private:
  ::rpcz::rpc_channel* channel_;
  ::std::string service_name_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(SoulSifterService_Stub);
};


}  // namespace soulsifter
}  // namespace dogatech
#endif  // RPCZ_soul_5fsifter_5fservice_2eproto__INCLUDED