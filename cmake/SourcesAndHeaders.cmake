set(sources
    src/main.cpp
    src/adler32/adler32.cpp
    src/fileio/fileio.cpp
    src/sync/sync.cpp
    src/fileio/signature.cpp
    src/mybaseclass.cpp
)

set(exe_sources
    src/main.cpp
    src/adler32/adler32.cpp
    src/fileio/fileio.cpp
    src/sync/sync.cpp
    src/fileio/signature.cpp
    src/mybaseclass.cpp

		${sources}
)

set(headers
    include/mybaseclass.h
    include/myfactory.h
    include/spencoding.h
    include/sync.h
    include/fileio.h
    include/adler32.h
    include/sha1.h
    include/signature.h
)

set(test_sources
  src/tests.cpp
  src/fileio_test.cpp
  src/signature_test.cpp
  src/sync_test.cpp
  src/adler32_test.cpp
)
