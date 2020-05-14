////////////////////////////////////////////////////////////////////////
// Minimal server using ZMQ_PULL socket
//
// Cf. https://lists.zeromq.org/pipermail/zeromq-dev/2020-May/033360.html
//
// Build:  cc server_pull.c -lczmq -lzmq -o server_pull
//
// Usage:  ./server_pull
//
// N.B. paired with client pushing N messsages as fast as possible
////////////////////////////////////////////////////////////////////////
#include <zmq.h>
#include <czmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

typedef zsock_t* pZS;

int main(void) {
int received = 0;

void *context = zmq_ctx_new();                        // Setup context, ...
void *server_pull = zmq_socket(context, ZMQ_PULL);    // ... socket, ...
int rc = zmq_bind(server_pull, "tcp://*:5555");       // ... bind socket, ...
  assert(rc==0);
  zpoller_t* poller = zpoller_new(server_pull,NULL);  // ... create poller
  assert(poller);

  zsys_set_logstream(stdout);                         // Setup logging

  while(!zsys_interrupted) {                          // Loop until signaled

    pZS which = (pZS) zpoller_wait(poller, 2000);     // Poll with 2s timeout

    if (which) {                                      // If no timeout, ...
    char *message = zstr_recv(which);                 // ... then receive ...
      {                 
      char lead[20];
      int request_nbr;
      char trail[20];
        if (3==sscanf(message,"%19[{\"id:]%d%2[}]",lead,&request_nbr,trail)) {
          if (!strcmp(lead,"{\"id\":") && !strcmp(trail,"}")) {
            ++received;                                // ... and parse data
          }
        }
        //handle_json(message);                        // Handler is disabled
      }
      zstr_free(&message);                             // Cleanup message

    } else {                                           // On assumed timeout (!which) ...
      if (received) {
        zsys_debug("Received = %d",received);          // ... show received count
        received = 0;
      }
    } 
  }
  return 0;
}
