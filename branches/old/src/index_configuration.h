// Copyright (c) 2010, Roman Khmelichek
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//  3. Neither the name of Roman Khmelichek nor the names of its contributors
//     may be used to endorse or promote products derived from this software
//     without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//==============================================================================================================================================================
// Author(s): Roman Khmelichek
//
// Each index has a meta file that describes the standard properties it was indexed with. This class provides access to those values. It is built on top of the
// KeyValueStore.
//==============================================================================================================================================================

#ifndef INDEX_CONFIGURATION_H_
#define INDEX_CONFIGURATION_H_

#include "key_value_store.h"

#include <string>

#include "globals.h"
#include "logger.h"

class IndexConfiguration : public KeyValueStore {
public:
  IndexConfiguration(const char* filename);

  template<typename ValueT>
    static ValueT GetResultValue(const KeyValueStore::KeyValueResult<ValueT>& key_value_result, bool exit_on_error);

private:
  std::string filename_;
};

template<typename ValueT>
  ValueT IndexConfiguration::GetResultValue(const KeyValueStore::KeyValueResult<ValueT>& key_value_result, bool exit_on_error) {
    if (key_value_result.error()) {
      GetErrorLogger().Log(std::string("Problem in index meta file '" + key_value_result.filename() + "' (") + key_value_result.GetErrorMessage() + ")", exit_on_error);
    }

    return key_value_result.value_t();
  }

#endif /* INDEX_CONFIGURATION_H_ */