#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <QString>

/*
 * Structures and definitions
 */

#define FRAME_PAYLOAD_SIZE 128

#define CONNECTION_INIT_ATTEMPT 4
#define CONNECTION_SEND_ATTEMPT 3
#define CONNECTION_AWAIT_ATTEMPT 3
#define CONNECTION_FINAL_ATTEMP 8
#define CONNECTION_LISTEN_ATTEMPT 1

#define type_t char

#define ADDITIONAL_OVERHEAD 4
#define TOTAL_PAYLOAD_SIZE (FRAME_PAYLOAD_SIZE + ADDITIONAL_OVERHEAD)

/*
 * PTU types
 */

#define CHUNK '0'
#define META '1'
#define INIT '2'
#define ACK '3'
#define P_ACK '4'
#define LAST_CHUNK '5'

typedef struct
{
    type_t  type;
}Type;

typedef struct
{
    Type    type; // Allocates 1 bytes for type identification
    ushort  src; // Allocates 2 bytes for source adress
    ushort  dst; // Allocates 2 bytes for destination adress
    uint    total_size; // Allocates 4 bytes for total chunk size
    char    protocol; // Allocates 1 byte for protocol identification
    unsigned int magic_key; // Allocates 4 byres for unique identification

}Header;

typedef struct
{
    Type    type; // Allocates 1 byte
    char    data[FRAME_PAYLOAD_SIZE]; // 128 bytes allocated
    uint    chunk_size; // Allocates 4 bytes
}Chunk; // At least 5 bytes allocation


typedef union
{
    char    raw[FRAME_PAYLOAD_SIZE + ADDITIONAL_OVERHEAD];

    Header  header;
    Chunk    chunk;
}Packet;

struct Formatted_Packet
{
    QString src_adrs;
    QString dst_adrs;
    QString data;
    QString type;
    QString descr;
    QString protocol;
};
typedef struct
{
    ushort src; // 2 bytes allocated
    ushort dst; // 2 bytes allocated
#if defined __LINUX__ && __GNUC
    u_int8_t lenght; // 1 bytes allocated
    u_int8_t protocol; // 1 bytes allocated
#elif defined __WIN32 || __WIN64
    quint8 lenght; // 1 bytes allocated
    quint8 protocol; // 1 bytes allocated
#endif
}Frame_Header; // 6 bytes total allocated for this structure

typedef struct
{
    char            preAmble[10]; // 10 bytes allocated
    uint            unique_adress; // 4 bytes allocated
    Frame_Header    header; // 6 bytes allocated
    char            payload[128]; // 128 bytes allocated
    ushort          checksum; // 2 bytes allocated

}Frame; // 10 + 4 + 6 + 128 + 2 = 150 bytes total allocated for this structure

typedef union
{
    char    raw[150];
    Frame   frame; // 150 bytes allocated

}Frame_PTU;


#endif // STRUCTURES_H
