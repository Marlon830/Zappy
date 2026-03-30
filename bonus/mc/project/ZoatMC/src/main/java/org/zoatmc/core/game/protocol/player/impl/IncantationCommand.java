package org.zoatmc.core.game.protocol.player.impl;

import org.zoatmc.core.game.protocol.CommandState;

public class IncantationCommand implements org.zoatmc.core.game.protocol.player.ZClientCommandExecutor {
    private boolean first;

    public IncantationCommand(boolean first) {
        this.first = first;
    }

    public IncantationCommand() {
        this.first = true;
    }

    @Override
    public CommandState onResponse(String response) {
        if (response.equals("ko"))
            return CommandState.FAILED;

        if (this.first) {
            this.first = false;
            return CommandState.CONTINUE;
        }

        return CommandState.SUCCESS;
    }
}
