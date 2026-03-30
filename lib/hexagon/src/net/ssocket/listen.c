/*
** EPITECH PROJECT, 2024
** libhexagon
** File description:
** The Hexagon library
*/

#include "hexagon/net/ssocket.h"
#include "hexagon/net/csocket.h"

#include "hexagon/util/c.h"
#include "hexagon/util/list.h"

#include <sys/socket.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <time.h>

struct setupfds {
    ssocket_t *self;
    int highest_fd;
};

struct checkfds {
    ssocket_t *self;
    void *context;
    ssocket_handlers_t *handlers;
};

static void ssocket_listen_setupfds_foreach(struct setupfds *context,
    csocket_t *socket)
{
    if (socket->fd > context->highest_fd)
        context->highest_fd = socket->fd;
    FD_SET(socket->fd, &context->self->read_client_fds);
}

static int ssocket_listen_setupfds(ssocket_t *self)
{
    struct setupfds context = { self, self->fd };

    FD_ZERO(&self->read_client_fds);
    FD_SET(self->fd, &self->read_client_fds);
    FD_ZERO(&self->write_client_fds);
    LIST_FOREACHC(self->clients, &context,
        &ssocket_listen_setupfds_foreach);
    return context.highest_fd + 1;
}

static void ssocket_listen_socket_flush(struct checkfds *context,
    csocket_t *socket)
{
    if (csocket_getout(socket) == 0)
        return;
    CALL_IFSET(context->handlers->when_writable)(context->context,
        context->self, socket);
    csocket_flush(socket);
}

static void ssocket_listen_checkfds_foreach(
    struct checkfds *context, csocket_t *socket)
{
    if (FD_ISSET(socket->fd, &context->self->write_client_fds))
        ssocket_listen_socket_flush(context, socket);
    if (!FD_ISSET(socket->fd, &context->self->read_client_fds))
        return;
    if (csocket_isalive(socket)) {
        csocket_sync(socket);
        CALL_IFSET(context->handlers->when_readable)(context->context,
            context->self, socket);
        ssocket_listen_socket_flush(context, socket);
    } else {
        CALL_IFSET(context->handlers->on_disconnect)(context->context,
            context->self, socket);
        ssocket_listen_socket_flush(context, socket);
        ssocket_close(context->self, socket);
    }
}

static bool ssocket_listen_doselect(ssocket_t *self,
    ssocket_handlers_t *handlers)
{
    int sstatus;
    struct timeval timeout_dup;
    bool timeout_set = self->select_timeout.tv_sec > 0 ||
        self->select_timeout.tv_usec > 0;

    if (timeout_set)
        memcpy(&timeout_dup, &self->select_timeout, sizeof(timeout_dup));
    sstatus = select(ssocket_listen_setupfds(self),
        &self->read_client_fds, &self->write_client_fds, NULL,
        timeout_set ? &timeout_dup : NULL);
    if (sstatus < 0 && errno == EINTR) {
        CALL_IFSET(handlers->on_signal)(self->context, self);
        CALL_IFSET(handlers->on_postprocess)(self->context, self);
        return true;
    }
    assert(sstatus >= 0);
    return false;
}

void ssocket_listen(ssocket_t *self, ssocket_handlers_t *handlers)
{
    struct checkfds foreach_context = { self, self->context, handlers };
    csocket_t *c_socket;

    assert(!self->listening);
    for (self->listening = true; self->listening;) {
        CALL_IFSET(handlers->on_preprocess)(self->context, self);
        if (ssocket_listen_doselect(self, handlers))
            continue;
        if (FD_ISSET(self->fd, &self->read_client_fds)) {
            c_socket = csocket_fromfd(accept(self->fd, NULL, 0), true);
            list_append(self->clients, c_socket);
            CALL_IFSET(handlers->on_connect)(self->context, self, c_socket);
            ssocket_listen_socket_flush(&foreach_context, c_socket);
        }
        LIST_FOREACHC(self->clients, &foreach_context,
            &ssocket_listen_checkfds_foreach);
        CALL_IFSET(handlers->on_postprocess)(self->context, self);
    }
    LIST_FOREACH(self->clients, FUNC &csocket_delete);
}
