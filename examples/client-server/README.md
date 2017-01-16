#Client Server example

On this example many programs can comunicate with one server program.

#Client side

This starts the comunication open a socket with the server.
Transparently are redirected to a new port.
Send a message to the server side.

#Server side

Listen on specific port, waiting for a connection.
Transparantly redirect the client to a particular socket on a new port range.
When receive the client message they can respond, asyncronously.
The server sends a message to all clients connected say that he had a new client connected.
