cmd_Release/test.node := ./gyp-mac-tool flock ./Release/linker.lock g++ -shared -Wl,-search_paths_first -mmacosx-version-min=10.5 -arch x86_64 -L./Release -install_name @rpath/test.node  -o Release/test.node Release/obj.target/test/src/test.o -undefined dynamic_lookup
