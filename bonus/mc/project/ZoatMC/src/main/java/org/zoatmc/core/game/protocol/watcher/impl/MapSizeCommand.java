package org.zoatmc.core.game.protocol.watcher.impl;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameMapResizeEvent;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class MapSizeCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 2)
            return;

        int width = Integer.parseInt(args[0]);
        int height = Integer.parseInt(args[1]);

        game.getEventBus().postEvent(new ZGameMapResizeEvent(game, new Vector2i(width, height)));
    }
}
