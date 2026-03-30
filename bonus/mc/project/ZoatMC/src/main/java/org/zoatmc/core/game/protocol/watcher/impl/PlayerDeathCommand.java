package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerDeathEvent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerDeathCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 1)
            return;

        int playerId = Integer.parseInt(args[0].substring(1));

        ZPlayer player = game.getPlayer(playerId);
        game.getEventBus().postEvent(new ZGamePlayerDeathEvent(game, player));
    }
}
