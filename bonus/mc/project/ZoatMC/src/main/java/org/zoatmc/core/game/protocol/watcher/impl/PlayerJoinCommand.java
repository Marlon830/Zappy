package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerJoinEvent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerJoinCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 6)
            return;

        int playerId = Integer.parseInt(args[0].substring(1));
        int x = Integer.parseInt(args[1]);
        int y = Integer.parseInt(args[2]);
        int orientation = Integer.parseInt(args[3]);
        int level = Integer.parseInt(args[4]);
        String team = args[5];

        ZPlayer player = new ZPlayer(game, playerId, x, y, orientation, level, team);
        game.getEventBus().postEvent(new ZGamePlayerJoinEvent(game, player));
    }
}
