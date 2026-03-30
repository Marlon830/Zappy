package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerIncantationEvent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerIncantationCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length < 3)
            return;

        int x = Integer.parseInt(args[0]);
        int y = Integer.parseInt(args[1]);
        int level = Integer.parseInt(args[2]);

        ZPlayer[] players = new ZPlayer[args.length - 3];
        for (int i = 3; i < args.length; i++) {
            int playerId = Integer.parseInt(args[i].substring(1));
            players[i - 3] = game.getPlayer(playerId);
        }

        game.getEventBus().postEvent(new ZGamePlayerIncantationEvent(game, players, x, y, level));
    }
}
