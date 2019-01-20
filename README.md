# Final Project for Systems
### By Rubin P. and Taaseen A.

The "Chatroom" (unnoficially called CoderzConnect) is a program meant to allow people to communicate with each other. Users can conect to the server and login or create an account to use the service. This program is less of 'chatroom' and more of a messaging service as conversations persist after logging of. 

Users have the ability to create accounts and add friends by username. In order to add a friend, a user must send a friend request and wait for the recepient to accept the request. Once the request is accepted, both users can message each other. Conversations are automatically saved and can be viewed later. 

All of the necessary commands needed are outlined as prompts to the user when the program is run. No additional libraries are needed either.

### Running CoderzConnect
In order to start socializing through **CoderzConnect** the "back page of the internet," simply start the server side program first, followed by running the clients.
To start the server you must follow normal C bulding procedures. Run the following code:

```
make
./server
```
Running the above will start the server on port 9949. Should this port need to be changed, the only current way to do so would be to change the `PORTNUM` value in chatroom.h to a free port.

To start up a client run:
```
./client server_addr
```
where `server_addr` is the ip address of the machine which is running the server program. The rest of the program can be navigated by reading through the prompts.

### Upcoming Features
Promised Features which will hopefully make an appearance in V2:
(aka. stretch goals we didn't meet)
1. allowing for group chats
2. allowing for users to see when their friends were last online/offline
3. the ablilty to delete user accounts from the program itself/administrative controls.

### Other Notes
-The only way to remove users currently is to delete the file named USERS. Doing so will permaanently delete everything associated with all users in the system
-A file named sub.log may show up in the directory when running the client side code. This was implemented to facilitate debugging and will delete itself after the client exits. 
