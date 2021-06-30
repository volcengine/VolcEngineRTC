## Install

### Without CMake
1. Use `git clone --recurse-submodules https://github.com/socketio/socket.io-client-cpp.git` to clone your local repo.
2. Add `./lib/asio/asio/include`, `./lib/websocketpp` and `./lib/rapidjson/include` to headers search path.
3. Include all files under `./src` in your project, add `sio_client.cpp`,`sio_socket.cpp`,`internal/sio_client_impl.cpp`, `internal/sio_packet.cpp` to source list.
4. Include `sio_client.h` in your client code where you want to use it.
