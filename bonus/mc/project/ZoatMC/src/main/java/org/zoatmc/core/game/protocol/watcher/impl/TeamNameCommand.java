package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameTeamNameEvent;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class TeamNameCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 1)
            return;

        String teamName = args[0];

        game.getEventBus().postEvent(new ZGameTeamNameEvent(game, teamName));
    }
}
