## Design
The objective of this application is to design a feed delayer, i.e., the feed must be delayed by a certain amount of time before being reported to the client.
### Solving the core problem
The problem statement looks very simple on surface, however, it has lots of quirks that need to be considered to solve this problem correctly.

The key issue to be considered here is that we can't rely on the flow rate of the incoming data and can't consider it as a reference for duration calculation. Hence, we need to timestamp our data. Hence, when the data is being stored, it will be time stamped with the time that it was received. Next, key issue to be considered is that we can't let our feed delayer thread to run continously, hence, we will have to make it sleep. However, as we have a requirement to send the data after "x" seconds, we need to consider a maximum error that we are willing to tolerate in sending the data. The thread can't be allowed to sleep for more than this duration.

Once, we have taken into account these two issues, the problem is relatively simple. The thread sleep for the maxium tolerance delay time error and when it wakes up it will check if the check if the delay duration has elapsed for the next data packet. If that is the case, it will be forwarded, otherwise the thread will sleep again.

This scheme will be able to handle the situations when the stream is steady, unsteady, has uneven delay, interruption etc., because it time stamps every data packet and forwards it only after the required duration has passed.

For the delay of 60 secs and maximum tolerable error in delay of 1 sec (i.e, forward at the most after 61 secs), the observed average delay is 60.690596 secs and an average error of 0.690596 secs and with an standard deviation of 0.061902895.


The thread sleep cycle can also be optimized further. The relavent discussion can be found in the "Extensions" section.
### Application Design

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
### Feed Delayer Thread Sleep Schedule
The feed delayer thread uses a very simple sleeping schedule, i.e., it sleeps for at the most maximum tolerable error threshold in the time delay for forwarding the data. However, this may not be optimal in case the feed is slower and data packets are received infrequently (with longer duration between them). 

This can be improved further by letting the thread check the time stamp of the next packet to be send and calculate the time remaining for it to be sent. Accordingly, it can sleep for this calculated duration. It would be optimal in the sense that the thread will only wakeup when it needs to send the data and the spurious wakeups will be eliminated. It can even handle the case when the stream has interrupted for some reason and there is no data incoming. In this case, it can make itself sleep for the maxium delay duration and check if there is any new data available to be sent.

I have deliberately avoided implementation of this algorithm to keep the sample applicatoin simple. However, in production environement, this or similar scheme would be required to save resources and avoid unnecessary computations.
### Multiple listens for the delayed feed
Currently, we only have a single exchange feed listener and a delayed feed listener. These are provided through dependency injection in the constructors. This is however is easy to extend. We can very easily extend it as follows:
* Remove dependency injection from constructor
* Provide a seperate method to register listerned that adds the listener to the list of the listeners
* When sending an update to the listener, loop over all the listeners and send the update

### Multi Feed from remote exchange
Currently, we have only one websocket instance that can listenen to a single attribute, e.g., R_25 ticket. It is possible to extend to multiple websockets that can be used to listen to various attributes in parallel. Accordingly, the clients will also have to be extended to be able to listener to the updates. This however will be a rather substantial change.

### Better buffer Handling
The feed delayer maintains a buffer storing as much data as needed. However, in real life situations that may not be a correct assumption. There are various strategies that we could follow, including 
i.	Drop the new packets
ii.	Behave like a ring buffer
iii. Perform some aggregation operation on the new data, instead of dropping it, e.g., storing the average.

### Improved Exception Handling
Exception handling infrastructure is already in place, but currently it doesn't do anything other than printing the error message. This can easily be extended for better error handling, e.g., retries etc.
### Automated Testing
Currently, we do not have any unit/integration testing in place. This can definitely be improved with automated unit and integration testing.
## Requirements
Deriv client has the following requirements

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
***** Realtime Data received *****

**** Delayed Tick **** 

{"echo_req":{"ticks":"R_10"},"msg_type":"tick","subscription":{"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62"},"tick":{"ask":6845.784,"bid":6845.584,"epoch":1653573230,"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62","pip_size":3,"quote":6845.684,"symbol":"R_10"}}

***** Realtime Data received *****

**** Delayed Tick **** 

{"echo_req":{"ticks":"R_10"},"msg_type":"tick","subscription":{"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62"},"tick":{"ask":6845.575,"bid":6845.375,"epoch":1653573232,"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62","pip_size":3,"quote":6845.475,"symbol":"R_10"}}

***** Realtime Data received *****

**** Delayed Tick **** 

{"echo_req":{"ticks":"R_10"},"msg_type":"tick","subscription":{"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62"},"tick":{"ask":6845.686,"bid":6845.486,"epoch":1653573234,"id":"caeb78f5-6f21-e5c0-f7c6-b8aba8855e62","pip_size":3,"quote":6845.586,"symbol":"R_10"}}

***** Realtime Data received *****
```
The "Readtime Data received" is the message that is printed when the actual realtime data is receieved from the online exchange. In this case, the original message is not printed to avoid cluttering the output. Initially, we will only see this message, as the delayed data still needs to wait.

The message "Delayed Tick" followed by the original tick message is the delayed tick that has been delayed by a certain fixed time length.