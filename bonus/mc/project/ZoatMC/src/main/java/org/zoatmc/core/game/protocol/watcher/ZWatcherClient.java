package org.zoatmc.core.game.protocol.watcher;

import org.bukkit.Bukkit;
import org.bukkit.scheduler.BukkitRunnable;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.game.protocol.ZCommandHandler;

import javax.net.SocketFactory;
import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

class ZWatcherClientTask extends BukkitRunnable {
    private final ZGame game;
    private Socket socket;

    public ZWatcherClientTask(ZGame game, Socket socket) {
        this.game = game;
        this.socket = socket;

        this.runTaskAsynchronously(ZoatPlugin.getInstance());
    }

    public Socket getSocket() {
        return this.socket;
    }

    public ZGame getGame() {
        return this.game;
    }

    @Override
    public void run() {
        BufferedReader socketReader;
        BufferedWriter socketWriter;

        Logger logger = ZoatPlugin.getInstance().getLogger();

        try {
            socketReader = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
            socketWriter = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));

            socketWriter.write("GRAPHIC\n");
            socketWriter.flush();
        } catch (IOException e) {
            logger.log(Level.SEVERE,
                "Failed to initiate a watcher client from socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                e.fillInStackTrace());

            return;
        }

        while (!socket.isClosed()) {
            try {
                String rawCommand = socketReader.readLine();

                if (rawCommand == null) {
                    logger.info("Socket %s has been closed by the remote host.".formatted(this.socket.getRemoteSocketAddress()));
                    Bukkit.getScheduler().runTask(ZoatPlugin.getInstance(), () -> {
                        try {
                            ZGameManager.removeGame(this.game);
                        } catch (IOException e) {
                            logger.log(Level.WARNING,
                                "Failed to terminate associated game from watcher client on socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                                e.fillInStackTrace());
                        }
                    });
                    break;
                }

                logger.fine("Socket %s sent command '%s'.".formatted(this.socket.getRemoteSocketAddress(), rawCommand));

                ZCommandHandler.handleCommand(this.game, rawCommand);
            } catch (IOException e) {
                if (!socket.isClosed())
                    logger.log(Level.SEVERE,
                        "Failed to read a line from socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                        e.fillInStackTrace());
            }
        }
    }

    @Override
    public void cancel() {
        Logger logger = ZoatPlugin.getInstance().getLogger();

        logger.log(Level.FINE, "Cancelling watcher client task for game on socket %s.".formatted(this.socket.getRemoteSocketAddress()));

        try {
            this.socket.close();
        } catch (IOException e) {
            logger.log(Level.SEVERE,
                           "Failed to close watcher client socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                           e.fillInStackTrace());
        }

        super.cancel();
    }
}

public class ZWatcherClient {
    private final ZGame game;
    private final ZWatcherClientTask clientTask;

    public ZWatcherClient(ZGame game, String host, int port) throws IOException {
        this.game = game;
        this.clientTask = new ZWatcherClientTask(this.game, SocketFactory.getDefault().createSocket(host, port));
    }

    public void close() {
        Socket socket = this.clientTask.getSocket();

        try {
            socket.close();
        } catch (IOException e) {
            ZoatPlugin.getInstance()
                      .getLogger()
                      .log(Level.SEVERE,
                           "Failed to close watcher client socket %s.".formatted(socket.getRemoteSocketAddress()),
                           e.fillInStackTrace());
        }

        if (!this.clientTask.isCancelled())
            this.clientTask.cancel();
    }

    public ZGame getGame() {
        return this.game;
    }

    public InetSocketAddress getAddress() {
        return (InetSocketAddress) this.clientTask.getSocket().getRemoteSocketAddress();
    }
}
