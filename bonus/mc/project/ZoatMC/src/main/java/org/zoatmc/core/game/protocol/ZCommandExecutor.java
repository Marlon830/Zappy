package org.zoatmc.core.game.protocol;

import org.zoatmc.core.game.ZGame;

public interface ZCommandExecutor {
    void onCommand(ZGame game, String command, String[] args);
}
