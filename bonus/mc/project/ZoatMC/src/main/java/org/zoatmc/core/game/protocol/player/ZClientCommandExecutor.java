package org.zoatmc.core.game.protocol.player;

import org.zoatmc.core.game.protocol.CommandState;

public interface ZClientCommandExecutor {
    CommandState onResponse(String response);
}
