/*Sockets

Son un camino para hablar con otros programas empleando FILE DESCRIPTORS estándar de UNIX

Cuando el SO Unix realiza operaciones I/O, lo hacen a mediante la lectura/escritura de descriptores de archivos. Un FILE DESCRIPTOR es un entero asociado a un archivo abierto.

Internet sockets 
Stream sockets (TCP)
	-> SOCK_STREAM
	-> Aplications
		Telnet
		HTTP
	-> Use Transmision Control Protocol (TCP)
	-> Use Internet Protocol (IP) for routing
Datagram sockets (UDP)
	-> SOCK-DGRAM 
	-> Aplications
		tftp
		dhcp
		streaming audio,video
	-> Conectionless
		You dont have to maintain an open conection
	-> Use User Datagram Protocol (UDP)
	-> Use Internet Protocol (IP) for routing
-Raw sockets

IP

network portion - host portion
class A 1-3 byte of network part
class B
class C 3 byte of network part

La porcion de red de la direccion IP es descrita por la netmask, para la cual se realiza la operaion AND con la direccion IP para conseguir el número de la red

netmask 255.255.255.000
	and
	 ip 192.000.002.012
	    192.000.002.000

192.0.2.12/30


IP address - street address of a hotel
port number - room number

Port number under 1024 are often considered special

BIG ENDIAN - NETWORK BYTE ORDER - más significativo primero B34F
LITTLE ENDIAN - HOST BYTE ORDER - menos significativo primero 4FB3


Your computer stores numbers in Host Byte Order. If it is and intel
x8086


htons() 	host to network short
htonl() 	host to network long
ntohs() 	network to host short
ntohl() 	network to host long

*/
struct addrinfo {
    int              ai_flags;     // AI_PASSIVE, AI_CANONNAME, etc.
    int              ai_family;    // AF_INET, AF_INET6, AF_UNSPEC
    int              ai_socktype;  // SOCK_STREAM, SOCK_DGRAM
    int              ai_protocol;  // use 0 for "any"
    size_t           ai_addrlen;   // size of ai_addr in bytes
    struct sockaddr *ai_addr;      // struct sockaddr_in or _in6
    char            *ai_canonname; // full canonical hostname
    
    struct addrinfo *ai_next;      // linked list, next node
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx AF_INET IPv4
    char              sa_data[14];  // 14 bytes of protocol address
}; 

//A pointer to a struct sockaddr_in can be cast to a pointer to
//a struct sockaddr* and vice-versa.

// (IPv4 only--see struct sockaddr_in6 for IPv6)
    
struct sockaddr_in {
    short int          sin_family;// sa_family // Address family, AF_INET 
    unsigned short int sin_port;    // Port number //In network byte order htons
    struct in_addr     sin_addr;    // Internet address 
    unsigned char      sin_zero[8]; // Same size as struct sockaddr
};

// IPv4 only  
// Internet address (a structure for historical reasons)
struct in_addr {
    uint32_t s_addr; // that's a 32-bit int (4 bytes)
};

//if you have declared ina to be of type struct sockaddr_in
//ina.sin_addr.s_addr references the 4-byte IP address

//inet_pton(), converts an IP address in numbers-and-dots
// notation into either a struct in_addr or a struct 
//in6_addr depending on whether you specify AF_INET or AF_INET6. 

struct sockaddr_in sa; // IPv4
    
inet_pton(AF_INET,"10.12.110.57", &(sa.sin_addr)); 
/*
Two computers cant share the same IP address

Private network numbers
10.x.x.x
192.168.x.x 0<=x<=255
172.y.x.x 16<=y<=31
*/


//https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/

//setsockopt reuse doc
// https://stackoverflow.com/questions/24194961/how-do-i-use-setsockoptso-reuseaddr

// sendto doc
//https://linux.die.net/man/2/sendto 

//recvfrom doc
// https://man7.org/linux/man-pages/man2/recvfrom.2.html