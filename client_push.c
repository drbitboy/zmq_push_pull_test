////////////////////////////////////////////////////////////////////////
// Minimal client using ZMQ_PUSH socket
//
// Cf. https://lists.zeromq.org/pipermail/zeromq-dev/2020-May/033360.html
//
// Build:  cc client_push.c -lczmq -lzmq -o client_push
//
// Usage:  ./client_push [10240]
//
// N.B. paired with server receiving pushed N messsages
////////////////////////////////////////////////////////////////////////
#include <zmq.h>
#include <czmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char** argv)
{
  int request_nbr = 10240;                            // Default:  ~10k messages

  void *context = zmq_ctx_new ();                     // Setup context, ...
  void *client_push = zmq_socket (context, ZMQ_PUSH); // ... PUSH socket, ...
  zmq_connect (client_push, "tcp://localhost:5555");  // ... connected to PULL socket

  if (argc > 1) sscanf(argv[1],"%d",&request_nbr);    // Usage:  ./client_push [N]

  while (0 < request_nbr--) {                         // Send messages in loop
  char json_string [256];
    sprintf(json_string,"{\"id\":%d}",request_nbr);   // JSON:  {"id":n}
    zstr_send (client_push, json_string);             // Send JSON string message
  }
  zmq_close (client_push);                            // Cleanup
  zmq_ctx_destroy (context);
  return 0;
}
