#include <iostream>
#include <vector>
#include <unistd.h>
#include "tinysp.hh"

// The Arduno max buff is 64 that includes control bytes, not only payload
#define DATA_SIZE 5 

unsigned char payload[DATA_SIZE];
int tries = 3;

int main(int argc, char* argv[])
{
    TinySP tinysp("/dev/ttyACM0", B9600);

    // Connect
    tinysp.start_connection();

    if(tinysp.get_connection_status()){
        std::cout << "NOT connected!" << std::endl;
        return 0;
    }else
    {
        std::cout << "Connected!" << std::endl;
    }

    // Dummy payload 0xFF 0xCA 0xFE 0xCA 0xFE ......
    for(int i = 0; i < DATA_SIZE; i++)
    {
        if(i == 0){
            payload[i] = 0xFF; // The id of the payload
        }else
        {
            if(i % 2 == 0)
            {
                payload[i] = 0xCA;
            }else
                payload[i] = 0xFE;
        }
    }

    // Try a PING-PONG communication
    for(int j = 0; j < tries; j++)
    {
    
        // Construct the packet
        Packet packet_s = Packet(payload, DATA_SIZE);

        try{
            // Send the packet
            tinysp.send_packet(packet_s);

            // Print out the sent packet
            unsigned int a;
            std::cout << "Sent: " << std::hex << " 0x" << (int)packet_s.id;
            for (a = 0; a < packet_s.len; a++)
                std::cout << " 0x" << std::hex << (int)packet_s.buf[a];
            std::cout << std::endl;

        }
        catch(PckIOError& e){
            std::cout << "I cannot send anything" <<
                std::endl;
        }

        sleep(1);

        try{
            // Read packet 
            Packet packet(tinysp.read_packet());

            // Print out the received packet
            unsigned int a;
            std::cout << "Received: " << std::hex << " 0x" << (int)packet.id;
            for(a = 0; a < packet.len; a++)
                std::cout << std::hex << " 0x" << (int)packet.buf[a];
            std::cout << std::endl;

        }
        catch(PckNoPacketsReady& e){
            std::cout << "I have not received anything" <<
                std::endl;
        }
    }

    tinysp.close_connection();
    return 0;
}
