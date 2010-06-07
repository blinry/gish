# Copyright (c) 2009, Whispersoft s.r.l.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# * Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following disclaimer
# in the documentation and/or other materials provided with the
# distribution.
# * Neither the name of Whispersoft s.r.l. nor the names of its
# contributors may be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Finds Vorbis library
#
#  Vorbis_INCLUDE_DIR - where to find vorbisenc.h, etc.
#  Vorbis_LIBRARIES   - List of libraries when using Vorbis.
#  Vorbis_FOUND       - True if Vorbis found.
#

if (Vorbis_INCLUDE_DIR)
  # Already in cache, be silent
  set(Vorbis_FIND_QUIETLY TRUE)
endif (Vorbis_INCLUDE_DIR)

find_path(Vorbis_INCLUDE_DIR vorbis/vorbisenc.h
  /opt/local/include
  /usr/local/include
  /usr/include
  /mingw/include
)

set(Vorbis_NAMES vorbis)
find_library(Vorbis_LIBRARY
  NAMES ${Vorbis_NAMES}
  PATHS /usr/lib /usr/local/lib /opt/local/lib /mingw/lib
)

set(VorbisFile_NAMES vorbisfile)
find_library(VorbisFile_LIBRARY
  NAMES ${VorbisFile_NAMES}
  PATHS /usr/lib /usr/local/lib /opt/local/lib /mingw/lib
)
set(Vorbis_LIBRARIES ${Vorbis_LIBRARY} ${VorbisFile_LIBRARY})

if (Vorbis_INCLUDE_DIR AND Vorbis_LIBRARIES)
   set(Vorbis_FOUND TRUE)
   set( Vorbis_LIBRARIES ${Vorbis_LIBRARIES} )
else (Vorbis_INCLUDE_DIR AND Vorbis_LIBRARIES)
   set(Vorbis_FOUND FALSE)
   set(Vorbis_LIBRARIES)
endif (Vorbis_INCLUDE_DIR AND Vorbis_LIBRARIES)

if (Vorbis_FOUND)
   if (NOT Vorbis_FIND_QUIETLY)
      message(STATUS "Found Vorbis: ${Vorbis_LIBRARIES}")
   endif (NOT Vorbis_FIND_QUIETLY)
else (Vorbis_FOUND)
   if (Vorbis_FIND_REQUIRED)
      message(STATUS "Looked for Vorbis libraries named ${Vorbis_NAMES}.")
      message(STATUS "Include file detected: [${Vorbis_INCLUDE_DIR}].")
      message(STATUS "Lib file detected: [${Vorbis_LIBRARIES}].")
      message(FATAL_ERROR "=========> Could NOT find Vorbis library")
   endif (Vorbis_FIND_REQUIRED)
endif (Vorbis_FOUND)

mark_as_advanced(
  Vorbis_LIBRARIES
  Vorbis_INCLUDE_DIR
  )
