cmake_minimum_required(VERSION 3.1...3.23)

project(
  Exchange_Client
  VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(deriv_client 
    main.cpp
    source/client/RequestFactory.cpp
    source/client/ExchangeClient.cpp
    source/feeddelayer/FeedDelayer.cpp
    source/comm/CommWebSocket.cpp
    source/comm/websocket/WebSocketBoost.cpp
)

target_link_libraries(deriv_client PRIVATE boost_system ssl crypto)