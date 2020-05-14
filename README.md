## Usage (BASH, typical):

    % ./server_pull &                            <== Start ZMQ_PULL server
    [1] 19000                                    <== Server PID
    % ./client_push                              <== Client pushing ~10kmessages
    % D: 20-05-14 18:54:23 Received = 10240      <== Response from server; none lost

    % ./client_push  1024000                     <== Client pusing 1Mmessages
    % D: 20-05-14 18:54:37 Received = 1024000    <== Response from server; none lost

    % kill -USR1 19000                           <== Interrupt server via signal
    % 
    [1]+  Done ./server_pull                     <== Server exit message


### client_push.c 
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

### server_pull.c
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

### Prerequisites (ubuntu; typical; ca. 2020-May)

* libzmq3-dev
* libczmq-dev
