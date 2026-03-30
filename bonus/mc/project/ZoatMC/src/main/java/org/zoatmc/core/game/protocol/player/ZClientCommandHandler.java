package org.zoatmc.core.game.protocol.player;

import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayerController;
import org.zoatmc.core.game.object.ZTeam;
import org.zoatmc.core.game.protocol.CommandState;
import org.zoatmc.core.game.protocol.player.impl.ConnectCommand;
import org.zoatmc.core.game.protocol.player.impl.IncantationCommand;
import org.zoatmc.core.game.protocol.player.impl.OkCommand;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;

public class ZClientCommandHandler {
    private final List<ZClientCommandExecutor> pendingCommands = new ArrayList<>();

    private final Logger logger;
    private final Socket socket;
    private final ZPlayerController player;
    private final BufferedReader inputStream;
    private final BufferedWriter outputStream;

    public ZClientCommandHandler(Socket socket, ZPlayerController player) throws IOException {
        this.socket = socket;
        this.player = player;

        this.logger = ZoatPlugin.getInstance().getLogger();
        this.inputStream = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
        this.outputStream = new BufferedWriter(new OutputStreamWriter(this.socket.getOutputStream()));

        if (!this.inputStream.readLine().equals("WELCOME")) {
            this.logger.log(Level.SEVERE,
                    "Failed to establish a connection with the client %s.".formatted(socket.getRemoteSocketAddress()));
            throw new IOException("Failed to establish a connection with the client.");
        }
    }

    public Socket getSocket() {
        return socket;
    }

    private void sendCommand(String command) {
        try {
            this.outputStream.write(command + "\n");
            this.outputStream.flush();
        } catch (IOException e) {
            this.logger.log(Level.SEVERE,
                    "Failed to write into socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                    e.fillInStackTrace());
        }
    }

    private String receiveCommand() {
        try {
            return this.inputStream.readLine();
        } catch (IOException e) {
            this.logger.log(Level.SEVERE,
                    "Failed to read from socket %s.".formatted(this.socket.getRemoteSocketAddress()),
                    e.fillInStackTrace());
        }

        return null;
    }

    private boolean canExecuteCommand() {
        return this.pendingCommands.size() < 10;
    }

    private boolean checkAndLog() {
        if (!this.canExecuteCommand()) {
            this.logger.log(Level.WARNING, "Too many pending actions in the queue.");
            this.player.getPlayer().spigot().sendMessage(ZoatFormatter.error("Too many pending actions in the queue."));
            return false;
        }
        return true;
    }

    public void handleCommand() {
        String response = this.receiveCommand();

        if (response == null)
            return;

        if (this.pendingCommands.isEmpty()) {
            this.logger.log(Level.WARNING, "Received a response without any pending commands.");
            return;
        }

        ZClientCommandExecutor executor = this.pendingCommands.getFirst();
        CommandState state = executor.onResponse(response);

        if (state == CommandState.UNKNOWN) {
            // TODO: Handle unknown command
            return;
        }
        if (state == CommandState.CONTINUE)
            return;
        pendingCommands.removeFirst();
    }

    public void connect(ZTeam team) {
        if (!this.checkAndLog())
            return;

        this.sendCommand(team.getName());
        this.pendingCommands.add(new ConnectCommand(player));
    }

    public void forward() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Forward");
        this.pendingCommands.add(new OkCommand());
    }

    public void left() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Left");
        this.pendingCommands.add(new OkCommand());
    }

    public void right() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Right");
        this.pendingCommands.add(new OkCommand());
    }

    public void broadcast(String message) {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Broadcast " + message);
        this.pendingCommands.add(new OkCommand());
    }

    public void fork() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Fork");
        this.pendingCommands.add(new OkCommand());
    }

    public void eject() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Eject");
        this.pendingCommands.add(new OkCommand());
    }

    public void take(ZContent.ResourceType type) {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Take " + type.name().toLowerCase());
        this.pendingCommands.add(new OkCommand());
    }

    public void set(ZContent.ResourceType type) {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Set " + type.name().toLowerCase());
        this.pendingCommands.add(new OkCommand());
    }

    public void incantation() {
        if (!this.checkAndLog())
            return;

        this.sendCommand("Incantation");
        this.pendingCommands.add(new IncantationCommand());
    }
}
