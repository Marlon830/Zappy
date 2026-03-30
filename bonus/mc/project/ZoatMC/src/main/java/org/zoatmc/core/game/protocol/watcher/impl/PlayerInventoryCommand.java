package org.zoatmc.core.game.protocol.watcher.impl;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerInventoryEvent;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerInventoryCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 10)
            return;

        int id = Integer.parseInt(args[0].substring(1));
        int x = Integer.parseInt(args[1]);
        int y = Integer.parseInt(args[2]);
        int[] resources = new int[7];
        for (int i = 0; i < 7; i++)
            resources[i] = Integer.parseInt(args[3 + i]);

        ZContent inventory = new ZContent(resources);
        ZPlayer player = game.getPlayer(id);
        if (player == null)
            return;

        game.getEventBus().postEvent(new ZGamePlayerInventoryEvent(game, player, new Vector2i(x, y), inventory));
    }
}
