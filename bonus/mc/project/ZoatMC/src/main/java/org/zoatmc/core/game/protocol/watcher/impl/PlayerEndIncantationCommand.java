package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerEndIncantationEvent;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerEndIncantationCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 3)
            return;

        int x = Integer.parseInt(args[0]);
        int y = Integer.parseInt(args[1]);
        boolean success = Integer.parseInt(args[2]) == 1;

        game.getEventBus().postEvent(new ZGamePlayerEndIncantationEvent(game, x, y, success));
    }
}
