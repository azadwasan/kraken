## Requirements

Deriv client requires the following

* **C++11:** Robust support for most language features.
* **Boost:** Boost.Asio and some other parts of Boost used to communicate with Deriv websocket API.
* **OpenSSL:** Required for using TLS/Secure sockets

## Building

Please build as follows
In the root source directory, execute the following commands

```
mkdir build
cd build
cmake ..
build
```
It generates an executable binary. Please execute the binary as follows

```
./deriv_client
```