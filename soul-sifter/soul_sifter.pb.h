// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: soul_sifter.proto

#ifndef PROTOBUF_soul_5fsifter_2eproto__INCLUDED
#define PROTOBUF_soul_5fsifter_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_soul_5fsifter_2eproto();
void protobuf_AssignDesc_soul_5fsifter_2eproto();
void protobuf_ShutdownFile_soul_5fsifter_2eproto();

class Genre;

// ===================================================================

class Genre : public ::google::protobuf::Message {
 public:
  Genre();
  virtual ~Genre();

  Genre(const Genre& from);

  inline Genre& operator=(const Genre& from) {
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
  static const Genre& default_instance();

  void Swap(Genre* other);

  // implements Message ----------------------------------------------

  Genre* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Genre& from);
  void MergeFrom(const Genre& from);
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

  // optional string name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // repeated .Genre child = 3;
  inline int child_size() const;
  inline void clear_child();
  static const int kChildFieldNumber = 3;
  inline const ::Genre& child(int index) const;
  inline ::Genre* mutable_child(int index);
  inline ::Genre* add_child();
  inline const ::google::protobuf::RepeatedPtrField< ::Genre >&
      child() const;
  inline ::google::protobuf::RepeatedPtrField< ::Genre >*
      mutable_child();

  // @@protoc_insertion_point(class_scope:Genre)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* name_;
  ::google::protobuf::RepeatedPtrField< ::Genre > child_;
  ::google::protobuf::int32 id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_soul_5fsifter_2eproto();
  friend void protobuf_AssignDesc_soul_5fsifter_2eproto();
  friend void protobuf_ShutdownFile_soul_5fsifter_2eproto();

  void InitAsDefaultInstance();
  static Genre* default_instance_;
};
// ===================================================================


// ===================================================================

// Genre

// optional int32 id = 1;
inline bool Genre::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Genre::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Genre::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Genre::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 Genre::id() const {
  return id_;
}
inline void Genre::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
}

// optional string name = 2;
inline bool Genre::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Genre::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Genre::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Genre::clear_name() {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& Genre::name() const {
  return *name_;
}
inline void Genre::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Genre::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(value);
}
inline void Genre::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* Genre::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    name_ = new ::std::string;
  }
  return name_;
}
inline ::std::string* Genre::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void Genre::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::kEmptyString) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// repeated .Genre child = 3;
inline int Genre::child_size() const {
  return child_.size();
}
inline void Genre::clear_child() {
  child_.Clear();
}
inline const ::Genre& Genre::child(int index) const {
  return child_.Get(index);
}
inline ::Genre* Genre::mutable_child(int index) {
  return child_.Mutable(index);
}
inline ::Genre* Genre::add_child() {
  return child_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::Genre >&
Genre::child() const {
  return child_;
}
inline ::google::protobuf::RepeatedPtrField< ::Genre >*
Genre::mutable_child() {
  return &child_;
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_soul_5fsifter_2eproto__INCLUDED
