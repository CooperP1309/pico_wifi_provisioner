This is not a read me! As stated in README however, this is an educational project for learning the ropes of embedded C. SO PLEASE DON'T USE THIS FOR SOMETHING OTHER THAN A HOBBY PROJECT! 

With that said, this file is purely used to log my design choices and lessons learnt as I go. The logs in this file only go as far back as the implementation of enum error types.

27-11-2025:

    Reviewing my progress from main made me realise I needed to do more to leave behind the
    object orientated paradigm I've been using for so long. Where main looked like this:

        pico_prov_init()

        if (pico_prov_has_credentials() || pico_prov_btn_pressed())

            ...

    I realised this is a terrible way to do things as it forces not only a gpio button
    implementation on the programmer, but an unnecessary function for checking data that
    the programmer can't even access.

    Hence, to adhere to the true nature of C, I'm refactoring the code to pass a credentials
    struct by reference, and assigning values to the struct within the init func.

    By doing this, the programmer will have full access/say of the data extracted from the 
    flash file system. From here, the programmer can choose to use other methods for provisioning
    and so on...

1-12-20256:

    It's now time to set up the captive server. To do this, I refer to the example tcp
    server in the pico sdk. 
    
    Find this in the pico sdk:
        
        /pico-examples/pico_w/wifi/tcp_server/picow_tcp_server.c
    
    Follwing this example code outlined the following tasks:

        1. Init a server state struct containing a client and server pcb struct:

            In network programming, a pcb is a "Protocol Control Block".
            This pcb struct holds the relevant data for a socket connection.
            I.e. data like IP address, port number and protocol (TCP or UDP)
            are all held in the struct for packet sending and recieving. 
            Thus, the server will contain a pointer pcb for a client and the server.
            This will allow us to declare a pcb instace at any scope in the program 
            and simply assign the server state pointers as needed.

        2. Start the server with a new declared pcb instance:

            Once the server struct is initialized, we declare a new pcb with
            IPADDR_TYPE_ANY for listening on the available address of our pico
            WIC. We bind our desired port to this pcb instance (port 80 for http).
            Once this pcb is setup, we beging listening on this pcb and assign the result
            of the listening connection to our server pcb.

        3. Handling connection:

            To handle conntections, the example uses a callback function. 
            This is done by setting the args of the callback function (which is the \
            server_pcb/pcb instance that points to the tcp connection). 
            Setting of the args:

                tcp_arg(server_t->server_pcb, server_t)

            Finally, we invoke tcp_accept to reference the function we will use as a 
            callback function:

                tcp_accept(server_t->server_pcb, server_accept_function)

        4. Handling accepted connection:
        


    

    

