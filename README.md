## Design
The objective of this application is to design a feed delayer, i.e., the feed must be delayed by a certain amount of time before being reported to the client.
Though, the core problem in itself is very simple but we needed a complete infrastructre around it to make it extensible 

The application is divided in the following parts

* Feed delayer
This is the core problem implementation. It is implemented as a thread that run infinitely (It does provide an interface to exit the thread loop but it is not called from anywhere in the code right now). It also is a listener to the realtime data feed from the communication layer. That is how it gathers the data and stores it as a string in a queue.

Feed delayer sleeps for a prespecified time and once it wakes up, it retrieves the top most data in the queue and sends it to its listener, which effectively delays the data by a certain time duration.

* comm (communication)
This is the communication layer used to fetch data from the online exchange. ```CommWebSocket``` is websocket implementation as offered by Boost Beast library. ```CommWebSocket``` provides the abstraction over Boost library.

* Client

```ExchangeClient``` acts like a controller. This is where the flow for the operations related to websocket sequence and sending requests to online exchange is controlled. Currently, flow of steps has been hardcoed consisting of the following steps:
1. establishing connection to the online exchange 
2. sending the tick subscription request
3. Indefinitely listening to the updates of the subscription

The exchage client also has an additional role of a listener to the events of the feed delayer. Hence, instead of having another class that implements the feed delayer listerner inerface, I chose to make the exchange client to listen to the feed delayer updates and print them. This keeps the code for this sampel application simpler. It serves to proves the point that any client could implement the feed delayer listener interface and get the updates.

## Assumptions and Limitations
### Single Threaded Architecture
The current architecture is single threaded in the sense that the web socket has a single instance to get a single stream of data. Similarly, the feed delayer is a seperate thread but it is a single thread feed delayer server.
### Simple Buffer
The delayed data will need to be buffered. The buffer size will be affected by two parameters, a) The amount of delay b) Tick frequency. I have taken a simple assumption that the delay and tick frequency are not going to result in very high memory consumption and it would be safe to keep buffering when needed.

## Extensions
### Multiple listens for the delayed feed
Currently, we only have a single exchange feed listener and a delayed feed listener. These are provided through dependency injection in the constructors. This is however is easy to extend. We can very easily extend it as follows:
* Remove dependency injection from constructor
* Provide a seperate method to register listerned that adds the listener to the list of the listeners
* When sending an update to the listener, loop over all the listeners and send the update

### Multi-attribute listening
Currently, we have only one websocket instance that can listenen to a single attribute, e.g., R_25 ticket. It is possible to extend to multiple websockets that can be used to listen to various attributes in parallel. Accordingly, the clients will also have to be extended to be able to listener to the updates. This however will be a rather substantial change.

The feed delayer maintains a buffer storing as much data as needed. However, in real life situations that may not be a correct assumption. There are various strategies that we could follow, including 
i.	Drop the new packets
ii.	Behave like a ring buffer
iii. Perform some aggregation operation on the new data, instead of dropping it, e.g., storing the average.

Exception handling infrastructure is already in place, but currently it doesn't do anything other than printing the error message. This can easily be extended for better error handling, e.g., retries etc.
## Requirements

Deriv client is a requires the following

* **CMake 3.1:** or above. It has been tested with CMake version 3.18.4.
* **C++17:** or above
* **Boost:** Boost.Asio and some other parts of Boost used to communicate with Deriv websocket API.
* **OpenSSL:** Required for using TLS/Secure sockets

## Building and Running
### Configuration
Before building, we can configure the application and tune different parameters using the configuration file /include/common/config.h. It is a header file, hence requires recompiling the binary. This can be easily fixed by providing an external json config file.

### Building
Please build as follows
In the root source directory, execute the following commands

```
mkdir build
cd build
cmake ..
build
```
It generates an executable binary.

### Running
Please execute the binary as follows

```
./deriv_client
```
The typical output looks as follows:

```
***** Realtime Data received *****
***** Realtime Data received *****

**** Delayed Tick **** 

{"echo_req":{"ticks":"R_10"},"msg_type":"tick","subscription":{"id":"26475207-c429-85da-24ea-8c00fb82e602"},"tick":{"ask":6849.787,"bid":6849.587,"epoch":1653568986,"id":"26475207-c429-85da-24ea-8c00fb82e602","pip_size":3,"quote":6849.687,"symbol":"R_10"}}

***** Realtime Data received *****
***** Realtime Data received *****
```
The "Readtime Data received" is the message that is printed when the actual realtime data is receieved from the online exchange. In this case, the original message is not printed to avoid cluttering the output.

The message "Delayed Tick" followed by the original tick message is the delayed tick that has been delayed by a certain fixed time length.