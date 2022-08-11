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
    Executable

		${sources}
)

set(headers
    include/eigercodetask/main.h
    include/eigercodetask/mybaseclass.h
    include/eigercodetask/myfactory.h
    include/eigercodetask/spencoding.h
    include/eigercodetask/sync.h
    include/eigercodetask/fileio.h
    include/eigercodetask/adler32.h
    include/eigercodetask/sha1.h
    include/eigercodetask/signature.h
)

set(test_sources
  src/main_test.cpp
  src/fileio_test.cpp
  src/signature_test.cpp
  src/sync_test.cpp
  src/adler32_test.cpp
)
