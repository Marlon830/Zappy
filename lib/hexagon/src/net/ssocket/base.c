/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"
#include "hexagon/net/csocket.h"

#include "hexagon/util/mem.h"

#include <sys/socket.h>
#include <arpa/inet.h>

#include <assert.h>
#include <unistd.h>

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

static ssocket_t *ssocket_setup(int fd)
{
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(addr);

    STRUCT_NEWIN(ssocket, self);
    *self = (ssocket_t){
        .fd = fd,
        .listening = false,
        .clients = list_new()
    };
    assert(getsockname(self->fd, (struct sockaddr *) &addr, &addr_size) == 0);
    inet_ntop(AF_INET, &addr.sin_addr, self->ip_addr, INET_ADDRSTRLEN);
    self->port = ntohs(addr.sin_port);
    memset(&self->select_timeout, 0, sizeof(struct timeval));
    return self;
}

ssocket_t *ssocket_new(const char *ip, uint16_t port)
{
    int fd;
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { .s_addr = inet_addr(ip) }
    };

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0 ||
        setsockopt(fd, SOL_SOCKET, SO_LINGER,
            &(struct linger) { 1, 1 }, sizeof(struct linger)) != 0 ||
        bind(fd, (struct sockaddr *) &addr, sizeof(addr)) != 0 ||
        listen(fd, SSOCKET_BACKLOG) != 0)
        return NULL;
    return ssocket_setup(fd);
}

void ssocket_delete(ssocket_t *self)
{
    assert(!ssocket_islistening(self));
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);
    list_delete(self->clients);
    mem_free(self);
}
