// Generated by the protocol buffer compiler.  DO NOT EDIT!

#include "soul_sifter.rpcz.h"
#include "soul_sifter.pb.h"
#include <google/protobuf/descriptor.h>
#include <google/protobuf/stubs/once.h>
#include <rpcz/rpcz.hpp>
namespace {
}  // anonymouse namespace

namespace dogatech {
namespace soulsifter {
namespace proto {

void rpcz_protobuf_AssignDesc_soul_5fsifter_2eproto() {
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "soul_sifter.proto");
  GOOGLE_CHECK(file != NULL);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &rpcz_protobuf_AssignDesc_soul_5fsifter_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void rpcz_protobuf_ShutdownFile_soul_5fsifter_2eproto() {
}

void rpcz_protobuf_AddDesc_soul_5fsifter_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021soul_sifter.proto\022\031dogatech.soulsifter"
    ".proto\"\304\001\n\005Album\022\n\n\002id\030\001 \001(\005\022\014\n\004name\030\002 \001"
    "(\t\022\016\n\006artist\030\003 \001(\t\022\025\n\rcoverFilepath\030\004 \001("
    "\t\022\r\n\005mixed\030\005 \001(\010\022\r\n\005label\030\006 \001(\t\022\021\n\tcatal"
    "ogId\030\007 \001(\t\022\027\n\017releaseDateYear\030\010 \001(\005\022\030\n\020r"
    "eleaseDateMonth\030\t \001(\005\022\026\n\016releaseDateDay\030"
    "\n \001(\005\"R\n\005Genre\022\n\n\002id\030\001 \001(\005\022\014\n\004name\030\002 \001(\t"
    "\022/\n\005child\030\003 \003(\0132 .dogatech.soulsifter.pr"
    "oto.Genre\"\256\003\n\004Song\022\n\n\002id\030\001 \001(\005\022\016\n\006artist"
    "\030\002 \001(\t\022\r\n\005track\030\003 \001(\t\022\r\n\005title\030\004 \001(\t\022\017\n\007"
    "remixer\030\005 \001(\t\022\021\n\tfeaturing\030\020 \001(\t\022\020\n\010file"
    "Path\030\006 \001(\t\022\020\n\010reSongId\030\021 \001(\t\022\017\n\007albumId\030"
    "\007 \001(\005\022\016\n\006rating\030\010 \001(\005\022\021\n\tdateAdded\030\t \001(\t"
    "\022\020\n\010comments\030\n \001(\t\022\017\n\007trashed\030\013 \001(\010\022\023\n\013a"
    "lbumPartId\030\014 \001(\005\022\013\n\003bpm\030\r \001(\t\0225\n\010tonicKe"
    "y\030\016 \003(\0162#.dogatech.soulsifter.proto.Toni"
    "cKey\022\022\n\nlowQuality\030\017 \001(\010\022/\n\005album\030\022 \001(\0132"
    " .dogatech.soulsifter.proto.Album\022/\n\005gen"
    "re\030\023 \003(\0132 .dogatech.soulsifter.proto.Gen"
    "re*\310\001\n\010TonicKey\022\005\n\001C\020\000\022\005\n\001G\020\001\022\005\n\001D\020\002\022\005\n\001"
    "A\020\003\022\005\n\001E\020\004\022\005\n\001B\020\005\022\006\n\002Fs\020\006\022\006\n\002Db\020\007\022\006\n\002Ab\020"
    "\010\022\006\n\002Eb\020\t\022\006\n\002Bb\020\n\022\005\n\001F\020\013\022\006\n\002Am\020\014\022\006\n\002Em\020\r"
    "\022\006\n\002Bm\020\016\022\007\n\003Fsm\020\017\022\007\n\003Csm\020\020\022\007\n\003Gsm\020\021\022\007\n\003E"
    "bm\020\022\022\007\n\003Bbm\020\023\022\006\n\002Fm\020\024\022\006\n\002Cm\020\025\022\006\n\002Gm\020\026\022\006\n"
    "\002Dm\020\027", 965);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "soul_sifter.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&rpcz_protobuf_ShutdownFile_soul_5fsifter_2eproto);
}

}  // namespace proto
}  // namespace soulsifter
}  // namespace dogatech