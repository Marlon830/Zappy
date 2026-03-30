package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGamePlayerTakeResourceEvent;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class PlayerTakeResourceCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 2)
            return;

        int playerId = Integer.parseInt(args[0].substring(1));
        int resourceId = Integer.parseInt(args[1]);

        ZPlayer player = game.getPlayer(playerId);
        ZContent.ResourceType resourceType = ZContent.ResourceType.values()[resourceId];

        game.getEventBus().postEvent(new ZGamePlayerTakeResourceEvent(game, player, resourceType));
    }
}
