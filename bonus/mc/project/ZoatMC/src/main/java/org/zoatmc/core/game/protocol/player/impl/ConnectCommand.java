package org.zoatmc.core.game.protocol.player.impl;

import org.bukkit.Bukkit;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.manager.ZControllerManager;
import org.zoatmc.core.game.object.ZPlayerController;
import org.zoatmc.core.game.protocol.CommandState;
import org.zoatmc.core.game.protocol.player.ZClientCommandExecutor;

public class ConnectCommand implements ZClientCommandExecutor {
    private final ZPlayerController player;
    private int line = 0;

    public ConnectCommand(ZPlayerController player) {
        this.player = player;
    }

    @Override
    public CommandState onResponse(String response) {
        if (response.equals("ko")) {
            this.player.getPlayer().spigot().sendMessage(ZoatFormatter.error("Failed to connect to the server because the team is full."));
            return CommandState.FAILED;
        }

        if (line == 0) {
            line++;
            return CommandState.CONTINUE;
        }

        this.player.setConnected(true);
        ZControllerManager.addController(this.player);
        Bukkit.getScheduler().runTask(ZoatPlugin.getInstance(), this.player::onConnect);
        return CommandState.SUCCESS;
    }
}
