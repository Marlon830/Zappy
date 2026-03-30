package org.zoatmc.core.game.protocol.player.impl;

import org.zoatmc.core.game.protocol.CommandState;

public class OkCommand implements org.zoatmc.core.game.protocol.player.ZClientCommandExecutor {
    @Override
    public CommandState onResponse(String response) {
        if (response.equals("ok"))
            return CommandState.SUCCESS;
        if (response.equals("ko"))
            return CommandState.FAILED;
        return CommandState.UNKNOWN;
    }
}
