package org.zoatmc.core.game.protocol.player;

import org.bukkit.scheduler.BukkitRunnable;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.game.object.ZPlayerController;
import org.zoatmc.core.game.object.ZTeam;

import javax.net.SocketFactory;
import java.io.IOException;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

class ZPlayerClientTask extends BukkitRunnable {
    private final ZPlayerClient client;
    private final Socket socket;
    private final ZTeam team;

    public ZPlayerClientTask(ZPlayerClient client) {
        this.client = client;
        this.team = client.getPlayer().getTeam();
        this.socket = client.getHandler().getSocket();

        this.runTaskAsynchronously(ZoatPlugin.getInstance());
    }

    @Override
    public void run() {
        this.client.getHandler().connect(this.team);

        while (!socket.isClosed() && !this.isCancelled()) {
            this.client.getHandler().handleCommand();
        }
    }

    @Override
    public void cancel() {
        Logger logger = ZoatPlugin.getInstance().getLogger();

        logger.log(Level.FINE, "Cancelling player client task for game on socket %s.".formatted(this.socket.getRemoteSocketAddress()));

        try {
            this.socket.close();
        } catch (IOException e) {
            logger.log(Level.SEVERE,
                    "Failed to close player client socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                    e.fillInStackTrace());
        }

        super.cancel();
    }
}

public class ZPlayerClient implements AutoCloseable {
    private final ZClientCommandHandler handler;
    private final ZPlayerClientTask runnable;
    private final ZPlayerController player;
    private final Socket socket;

    public ZPlayerClient(String ip, int port, ZPlayerController player) throws IOException {
        this.player = player;

        this.socket = SocketFactory.getDefault().createSocket(ip, port);
        this.handler = new ZClientCommandHandler(this.socket, player);
        this.runnable = new ZPlayerClientTask(this);
    }

    public void close() {
        this.runnable.cancel();
    }

    public ZPlayerController getPlayer() {
        return player;
    }

    public ZClientCommandHandler getHandler() {
        return handler;
    }
}
