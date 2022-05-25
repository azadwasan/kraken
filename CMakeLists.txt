cmake_minimum_required(VERSION 3.1...3.23)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
  Exchange
  VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Adding something we can run - Output name matches target name
add_executable(kraken_client 
    main.cpp
#    source/client/kraken.cpp
    source/client/exchange.cpp
    source/comm/CommWebSocket.cpp
    source/comm/websocket/WebSocketBoost.cpp
)

# Make sure you link your targets with this command. It can also link libraries and
# even flags, so linking a target that does not exist will not give a configure-time error.
target_link_libraries(kraken_client PRIVATE boost_system ssl crypto)