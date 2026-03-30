package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerBroadcastEvent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerBroadcastCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 2)
            return;

        int playerId = Integer.parseInt(args[0].substring(1));
        String message = args[1];

        ZPlayer player = game.getPlayer(playerId);
        game.getEventBus().postEvent(new ZGamePlayerBroadcastEvent(game, player, message));
    }
}
