package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameTimeUnitEvent;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class TimeSetCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 1)
            return;

        int timeUnit = Integer.parseInt(args[0]);

        game.getEventBus().postEvent(new ZGameTimeUnitEvent(game, timeUnit));
    }
}
