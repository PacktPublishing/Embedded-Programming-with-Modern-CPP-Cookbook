// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_MESSAGE_H_
#define FLATBUFFERS_GENERATED_MESSAGE_H_

#include "flatbuffers/flatbuffers.h"

struct Message;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Message FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t x_;
  int32_t y_;

 public:
  Message() {
    memset(static_cast<void *>(this), 0, sizeof(Message));
  }
  Message(int32_t _x, int32_t _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  int32_t x() const {
    return flatbuffers::EndianScalar(x_);
  }
  int32_t y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Message, 8);

#endif  // FLATBUFFERS_GENERATED_MESSAGE_H_
