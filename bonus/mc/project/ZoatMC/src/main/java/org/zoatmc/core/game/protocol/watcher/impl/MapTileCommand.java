package org.zoatmc.core.game.protocol.watcher.impl;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameTileUpdateEvent;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class MapTileCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 9)
            return;

        int x = Integer.parseInt(args[0]);
        int y = Integer.parseInt(args[1]);
        int[] resources = new int[7];
        for (int i = 0; i < 7; i++)
            resources[i] = Integer.parseInt(args[i + 2]);

        game.getEventBus().postEvent(new ZGameTileUpdateEvent(game, new Vector2i(x, y), new ZContent(resources)));
    }
}
