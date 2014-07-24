// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: soul_sifter_service.proto

#ifndef PROTOBUF_soul_5fsifter_5fservice_2eproto__INCLUDED
#define PROTOBUF_soul_5fsifter_5fservice_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
#include "soul_sifter.pb.h"
// @@protoc_insertion_point(includes)

namespace dogatech {
namespace soulsifter {
namespace proto {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_soul_5fsifter_5fservice_2eproto();
void protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
void protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

class GetSongRequest;
class GetSongResponse;
class FindSongsRequest;
class FindSongsResponse;

// ===================================================================

class GetSongRequest : public ::google::protobuf::Message {
 public:
  GetSongRequest();
  virtual ~GetSongRequest();

  GetSongRequest(const GetSongRequest& from);

  inline GetSongRequest& operator=(const GetSongRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSongRequest& default_instance();

  void Swap(GetSongRequest* other);

  // implements Message ----------------------------------------------

  GetSongRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetSongRequest& from);
  void MergeFrom(const GetSongRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:dogatech.soulsifter.proto.GetSongRequest)
 private:
  inline void set_has_id();
  inline void clear_has_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

  void InitAsDefaultInstance();
  static GetSongRequest* default_instance_;
};
// -------------------------------------------------------------------

class GetSongResponse : public ::google::protobuf::Message {
 public:
  GetSongResponse();
  virtual ~GetSongResponse();

  GetSongResponse(const GetSongResponse& from);

  inline GetSongResponse& operator=(const GetSongResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const GetSongResponse& default_instance();

  void Swap(GetSongResponse* other);

  // implements Message ----------------------------------------------

  GetSongResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const GetSongResponse& from);
  void MergeFrom(const GetSongResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string title = 1;
  inline bool has_title() const;
  inline void clear_title();
  static const int kTitleFieldNumber = 1;
  inline const ::std::string& title() const;
  inline void set_title(const ::std::string& value);
  inline void set_title(const char* value);
  inline void set_title(const char* value, size_t size);
  inline ::std::string* mutable_title();
  inline ::std::string* release_title();
  inline void set_allocated_title(::std::string* title);

  // @@protoc_insertion_point(class_scope:dogatech.soulsifter.proto.GetSongResponse)
 private:
  inline void set_has_title();
  inline void clear_has_title();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* title_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

  void InitAsDefaultInstance();
  static GetSongResponse* default_instance_;
};
// -------------------------------------------------------------------

class FindSongsRequest : public ::google::protobuf::Message {
 public:
  FindSongsRequest();
  virtual ~FindSongsRequest();

  FindSongsRequest(const FindSongsRequest& from);

  inline FindSongsRequest& operator=(const FindSongsRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FindSongsRequest& default_instance();

  void Swap(FindSongsRequest* other);

  // implements Message ----------------------------------------------

  FindSongsRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FindSongsRequest& from);
  void MergeFrom(const FindSongsRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional string query = 1;
  inline bool has_query() const;
  inline void clear_query();
  static const int kQueryFieldNumber = 1;
  inline const ::std::string& query() const;
  inline void set_query(const ::std::string& value);
  inline void set_query(const char* value);
  inline void set_query(const char* value, size_t size);
  inline ::std::string* mutable_query();
  inline ::std::string* release_query();
  inline void set_allocated_query(::std::string* query);

  // optional .dogatech.soulsifter.proto.TonicKey key_to_match = 2;
  inline bool has_key_to_match() const;
  inline void clear_key_to_match();
  static const int kKeyToMatchFieldNumber = 2;
  inline ::dogatech::soulsifter::proto::TonicKey key_to_match() const;
  inline void set_key_to_match(::dogatech::soulsifter::proto::TonicKey value);

  // optional bool key_lock = 3 [default = true];
  inline bool has_key_lock() const;
  inline void clear_key_lock();
  static const int kKeyLockFieldNumber = 3;
  inline bool key_lock() const;
  inline void set_key_lock(bool value);

  // optional int32 max_bpm = 4;
  inline bool has_max_bpm() const;
  inline void clear_max_bpm();
  static const int kMaxBpmFieldNumber = 4;
  inline ::google::protobuf::int32 max_bpm() const;
  inline void set_max_bpm(::google::protobuf::int32 value);

  // optional int32 min_bpm = 5;
  inline bool has_min_bpm() const;
  inline void clear_min_bpm();
  static const int kMinBpmFieldNumber = 5;
  inline ::google::protobuf::int32 min_bpm() const;
  inline void set_min_bpm(::google::protobuf::int32 value);

  // repeated .dogatech.soulsifter.proto.Genre genre = 6;
  inline int genre_size() const;
  inline void clear_genre();
  static const int kGenreFieldNumber = 6;
  inline const ::dogatech::soulsifter::proto::Genre& genre(int index) const;
  inline ::dogatech::soulsifter::proto::Genre* mutable_genre(int index);
  inline ::dogatech::soulsifter::proto::Genre* add_genre();
  inline const ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Genre >&
      genre() const;
  inline ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Genre >*
      mutable_genre();

  // @@protoc_insertion_point(class_scope:dogatech.soulsifter.proto.FindSongsRequest)
 private:
  inline void set_has_query();
  inline void clear_has_query();
  inline void set_has_key_to_match();
  inline void clear_has_key_to_match();
  inline void set_has_key_lock();
  inline void clear_has_key_lock();
  inline void set_has_max_bpm();
  inline void clear_has_max_bpm();
  inline void set_has_min_bpm();
  inline void clear_has_min_bpm();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* query_;
  int key_to_match_;
  bool key_lock_;
  ::google::protobuf::int32 max_bpm_;
  ::google::protobuf::int32 min_bpm_;
  ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Genre > genre_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(6 + 31) / 32];

  friend void  protobuf_AddDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

  void InitAsDefaultInstance();
  static FindSongsRequest* default_instance_;
};
// -------------------------------------------------------------------

class FindSongsResponse : public ::google::protobuf::Message {
 public:
  FindSongsResponse();
  virtual ~FindSongsResponse();

  FindSongsResponse(const FindSongsResponse& from);

  inline FindSongsResponse& operator=(const FindSongsResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FindSongsResponse& default_instance();

  void Swap(FindSongsResponse* other);

  // implements Message ----------------------------------------------

  FindSongsResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FindSongsResponse& from);
  void MergeFrom(const FindSongsResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .dogatech.soulsifter.proto.Song song = 1;
  inline int song_size() const;
  inline void clear_song();
  static const int kSongFieldNumber = 1;
  inline const ::dogatech::soulsifter::proto::Song& song(int index) const;
  inline ::dogatech::soulsifter::proto::Song* mutable_song(int index);
  inline ::dogatech::soulsifter::proto::Song* add_song();
  inline const ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Song >&
      song() const;
  inline ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Song >*
      mutable_song();

  // @@protoc_insertion_point(class_scope:dogatech.soulsifter.proto.FindSongsResponse)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Song > song_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_AssignDesc_soul_5fsifter_5fservice_2eproto();
  friend void protobuf_ShutdownFile_soul_5fsifter_5fservice_2eproto();

  void InitAsDefaultInstance();
  static FindSongsResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// GetSongRequest

// optional int32 id = 1;
inline bool GetSongRequest::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetSongRequest::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetSongRequest::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetSongRequest::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 GetSongRequest::id() const {
  return id_;
}
inline void GetSongRequest::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// -------------------------------------------------------------------

// GetSongResponse

// optional string title = 1;
inline bool GetSongResponse::has_title() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void GetSongResponse::set_has_title() {
  _has_bits_[0] |= 0x00000001u;
}
inline void GetSongResponse::clear_has_title() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void GetSongResponse::clear_title() {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    title_->clear();
  }
  clear_has_title();
}
inline const ::std::string& GetSongResponse::title() const {
  return *title_;
}
inline void GetSongResponse::set_title(const ::std::string& value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void GetSongResponse::set_title(const char* value) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(value);
}
inline void GetSongResponse::set_title(const char* value, size_t size) {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  title_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* GetSongResponse::mutable_title() {
  set_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    title_ = new ::std::string;
  }
  return title_;
}
inline ::std::string* GetSongResponse::release_title() {
  clear_has_title();
  if (title_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = title_;
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void GetSongResponse::set_allocated_title(::std::string* title) {
  if (title_ != &::google::protobuf::internal::kEmptyString) {
    delete title_;
  }
  if (title) {
    set_has_title();
    title_ = title;
  } else {
    clear_has_title();
    title_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// FindSongsRequest

// optional string query = 1;
inline bool FindSongsRequest::has_query() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FindSongsRequest::set_has_query() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FindSongsRequest::clear_has_query() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FindSongsRequest::clear_query() {
  if (query_ != &::google::protobuf::internal::kEmptyString) {
    query_->clear();
  }
  clear_has_query();
}
inline const ::std::string& FindSongsRequest::query() const {
  return *query_;
}
inline void FindSongsRequest::set_query(const ::std::string& value) {
  set_has_query();
  if (query_ == &::google::protobuf::internal::kEmptyString) {
    query_ = new ::std::string;
  }
  query_->assign(value);
}
inline void FindSongsRequest::set_query(const char* value) {
  set_has_query();
  if (query_ == &::google::protobuf::internal::kEmptyString) {
    query_ = new ::std::string;
  }
  query_->assign(value);
}
inline void FindSongsRequest::set_query(const char* value, size_t size) {
  set_has_query();
  if (query_ == &::google::protobuf::internal::kEmptyString) {
    query_ = new ::std::string;
  }
  query_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* FindSongsRequest::mutable_query() {
  set_has_query();
  if (query_ == &::google::protobuf::internal::kEmptyString) {
    query_ = new ::std::string;
  }
  return query_;
}
inline ::std::string* FindSongsRequest::release_query() {
  clear_has_query();
  if (query_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = query_;
    query_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void FindSongsRequest::set_allocated_query(::std::string* query) {
  if (query_ != &::google::protobuf::internal::kEmptyString) {
    delete query_;
  }
  if (query) {
    set_has_query();
    query_ = query;
  } else {
    clear_has_query();
    query_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// optional .dogatech.soulsifter.proto.TonicKey key_to_match = 2;
inline bool FindSongsRequest::has_key_to_match() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FindSongsRequest::set_has_key_to_match() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FindSongsRequest::clear_has_key_to_match() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FindSongsRequest::clear_key_to_match() {
  key_to_match_ = 0;
  clear_has_key_to_match();
}
inline ::dogatech::soulsifter::proto::TonicKey FindSongsRequest::key_to_match() const {
  return static_cast< ::dogatech::soulsifter::proto::TonicKey >(key_to_match_);
}
inline void FindSongsRequest::set_key_to_match(::dogatech::soulsifter::proto::TonicKey value) {
  assert(::dogatech::soulsifter::proto::TonicKey_IsValid(value));
  set_has_key_to_match();
  key_to_match_ = value;
}

// optional bool key_lock = 3 [default = true];
inline bool FindSongsRequest::has_key_lock() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FindSongsRequest::set_has_key_lock() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FindSongsRequest::clear_has_key_lock() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FindSongsRequest::clear_key_lock() {
  key_lock_ = true;
  clear_has_key_lock();
}
inline bool FindSongsRequest::key_lock() const {
  return key_lock_;
}
inline void FindSongsRequest::set_key_lock(bool value) {
  set_has_key_lock();
  key_lock_ = value;
}

// optional int32 max_bpm = 4;
inline bool FindSongsRequest::has_max_bpm() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void FindSongsRequest::set_has_max_bpm() {
  _has_bits_[0] |= 0x00000008u;
}
inline void FindSongsRequest::clear_has_max_bpm() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void FindSongsRequest::clear_max_bpm() {
  max_bpm_ = 0;
  clear_has_max_bpm();
}
inline ::google::protobuf::int32 FindSongsRequest::max_bpm() const {
  return max_bpm_;
}
inline void FindSongsRequest::set_max_bpm(::google::protobuf::int32 value) {
  set_has_max_bpm();
  max_bpm_ = value;
}

// optional int32 min_bpm = 5;
inline bool FindSongsRequest::has_min_bpm() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void FindSongsRequest::set_has_min_bpm() {
  _has_bits_[0] |= 0x00000010u;
}
inline void FindSongsRequest::clear_has_min_bpm() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void FindSongsRequest::clear_min_bpm() {
  min_bpm_ = 0;
  clear_has_min_bpm();
}
inline ::google::protobuf::int32 FindSongsRequest::min_bpm() const {
  return min_bpm_;
}
inline void FindSongsRequest::set_min_bpm(::google::protobuf::int32 value) {
  set_has_min_bpm();
  min_bpm_ = value;
}

// repeated .dogatech.soulsifter.proto.Genre genre = 6;
inline int FindSongsRequest::genre_size() const {
  return genre_.size();
}
inline void FindSongsRequest::clear_genre() {
  genre_.Clear();
}
inline const ::dogatech::soulsifter::proto::Genre& FindSongsRequest::genre(int index) const {
  return genre_.Get(index);
}
inline ::dogatech::soulsifter::proto::Genre* FindSongsRequest::mutable_genre(int index) {
  return genre_.Mutable(index);
}
inline ::dogatech::soulsifter::proto::Genre* FindSongsRequest::add_genre() {
  return genre_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Genre >&
FindSongsRequest::genre() const {
  return genre_;
}
inline ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Genre >*
FindSongsRequest::mutable_genre() {
  return &genre_;
}

// -------------------------------------------------------------------

// FindSongsResponse

// repeated .dogatech.soulsifter.proto.Song song = 1;
inline int FindSongsResponse::song_size() const {
  return song_.size();
}
inline void FindSongsResponse::clear_song() {
  song_.Clear();
}
inline const ::dogatech::soulsifter::proto::Song& FindSongsResponse::song(int index) const {
  return song_.Get(index);
}
inline ::dogatech::soulsifter::proto::Song* FindSongsResponse::mutable_song(int index) {
  return song_.Mutable(index);
}
inline ::dogatech::soulsifter::proto::Song* FindSongsResponse::add_song() {
  return song_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Song >&
FindSongsResponse::song() const {
  return song_;
}
inline ::google::protobuf::RepeatedPtrField< ::dogatech::soulsifter::proto::Song >*
FindSongsResponse::mutable_song() {
  return &song_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace soulsifter
}  // namespace dogatech

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_soul_5fsifter_5fservice_2eproto__INCLUDED
