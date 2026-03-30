/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/csocket.h"
#include "hexagon/net/csocket_block.h"

#include "hexagon/util/c.h"
#include "hexagon/util/mem.h"

#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>
#include <assert.h>
#include <stddef.h>

csocket_t *csocket_new(const char *ip, uint16_t port)
{
    int fd;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = {
            .s_addr = inet_addr(ip)
        }
    };

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0 ||
        connect(fd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
        return NULL;
    return csocket_fromfd(fd, false);
}

static void csocket_fromfd_configfd(csocket_t *self)
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);

    assert(getpeername(self->fd, (struct sockaddr *) &addr, &addr_size) == 0);
    inet_ntop(AF_INET, &addr.sin_addr, self->ip_addr, INET_ADDRSTRLEN);
    self->port = ntohs(addr.sin_port);
    assert(setsockopt(self->fd, SOL_SOCKET, SO_KEEPALIVE,
        &(int){ 1 }, sizeof(int)) == 0);
    assert(setsockopt(self->fd, SOL_SOCKET,
        SO_LINGER, &(struct linger) { 1, 1 }, sizeof(struct linger)) == 0);
}

csocket_t *csocket_fromfd(int fd, bool async)
{
    assert(fd >= 0);
    STRUCT_NEWIN(csocket, self);
    *self = (csocket_t) {
        .fd = fd,
        .context = NULL,
        .async = async,
        .in_buff_ptr = self->in_buff,
        .in_buff_ceil = self->in_buff,
        .out_buff_ptr = self->out_buff,
        .out_block_queue = async ? list_new() : NULL,
    };
    csocket_fromfd_configfd(self);
    return self;
}

void csocket_delete(csocket_t *self)
{
    CALL_IFSET(self->context_deleter)(self->context);
    shutdown(self->fd, SHUT_RD);
    csocket_flush(self);
    shutdown(self->fd, SHUT_WR);
    close(self->fd);
    if (self->out_block_queue) {
        list_foreach(self->out_block_queue, FUNC &csocket_block_delete);
        list_delete(self->out_block_queue);
    }
    mem_free(self);
}
