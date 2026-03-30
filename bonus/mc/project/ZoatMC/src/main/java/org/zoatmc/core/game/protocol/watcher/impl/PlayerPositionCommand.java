package org.zoatmc.core.game.protocol.watcher.impl;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerPositionEvent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerPositionCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 4)
            return;

        int playerId = Integer.parseInt(args[0].substring(1));
        int x = Integer.parseInt(args[1]);
        int y = Integer.parseInt(args[2]);
        int direction = Integer.parseInt(args[3]);

        ZPlayer player = game.getPlayer(playerId);
        game.getEventBus().postEvent(new ZGamePlayerPositionEvent(game, player, new Vector2i(x, y), direction));
    }
}
