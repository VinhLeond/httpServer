# httpServer

## Feature
### TCP Server
* Asynchronous 
* Multithread

### RobotModifier
* Barebone openRAVE plugin
## Build
Run build srcript by using following command
```
./build.sh {cleanbuildArgument} // Using 1 to make clean build. 0 is otherwise
```
The build scrip include
* Building binary file
* Install binary file
* Run Unit test
## Docker
### Build
* Using Dockefile to build local image
* Pull built image from docker hub using this command
```
docker pull vinhqpn/http_server:latest
```
### Run
Run the server by using
```
docker run -dp {yourHostPort}:9000 -ti --name server http_server
```
Tested the server by using telnet
```
telnet localhost {yourHostPort}
```

## Future work
### Tcp Server
* Aggerate data send
* Connection manager to manage multiple connection session
* Connection manager to create interface with other object such as RobotModifier class
 
 ## Note
 Used OpenRave branch: 

https://github.com/VinhLeond/openrave/tree/feature/building_success