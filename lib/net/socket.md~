	
# Java / C++ socket class

If you need to do socket communication between a Java and/or C++ programs, you've come to the right place. I've developed a fairly basic class that can be used to communicate between Java applications and C++ programs via a socket connection. There are client and server classes for both Java and C++, so you could use these classes for communication between the same language or between languages.

The classes below have been tested and seem to work.  You must of course balance your sends and receives otherwise it will stall.  You will have to determine whether the byte order needs to be reversed between your client and server.

Efficiency isn't the best. I worked some time to get the classes to perform as well as they do. Sending and receiving of bytes is fairly fast, but other types require the Java side to convert the data array to an array of bytes. This was necessary in order to get the data to be sent in bigger, more efficient blocks. I suspect the conversion could be done faster than my stream technique, but I have not pursued it.

The fastest method I found to send data was using the datagram methods.  Be careful, since this is not a guaranteed delivery form of communication, packets can and do get lost in transit. You'll need to do some sort of communication via the normal send and receive routines to provide resending of missing packets.

For more details about the implementation, see section 7 in my master's thesis. You can use this code for whatever you like.

A lot of the C code for the socket routines I lifted from the excellent tutorial: Beej's Guide to Network Programming. For a starting point on the Java code, I used the book: Java: How to Program, Deitel & Deitel.

Update: I updated the original classes in October 2009. This was to make it compile with current versions of GCC and Visual Studio. There is now a Visual Studio solution for compiling on Windows. I moved the reuseable buffers to the heap. I also cleaned the code up a bit. The datagram methods (at least in C++) didn't seem to work, so I removed the method bodies until the next version (around 2019 or so).


##Files and links:

'socket.zip'	__New and improved version__


* Src:
- https://www.keithv.com/software/socket/
- https://www.keithv.com/pub/ms/parallel_sph_simulation.pdf
- https://www.bogotobogo.com/cplusplus/sockets_server_client.php
- https://www.bogotobogo.com/cplusplus/sockets_server_client_2.php
- etc...


