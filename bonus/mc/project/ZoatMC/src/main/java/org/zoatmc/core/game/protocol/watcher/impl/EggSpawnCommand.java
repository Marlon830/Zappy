package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameEggSpawnEvent;
import org.zoatmc.core.game.object.ZEgg;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class EggSpawnCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 4)
            return;

        int eggId = Integer.parseInt(args[0].substring(1));
        int playerId = Integer.parseInt(args[1].substring(1));
        int x = Integer.parseInt(args[2]);
        int y = Integer.parseInt(args[3]);

        ZEgg egg = new ZEgg(game, eggId, x, y);
        ZPlayer player = game.getPlayer(playerId);
        game.getEventBus().postEvent(new ZGameEggSpawnEvent(game, egg, player));
    }
}
