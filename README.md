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
