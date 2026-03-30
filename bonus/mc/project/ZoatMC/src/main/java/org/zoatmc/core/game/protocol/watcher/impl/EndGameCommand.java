package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameEndEvent;
import org.zoatmc.core.game.object.ZTeam;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class EndGameCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 1)
            return;

        String team = args[0];

        ZTeam winner = game.getTeam(team);
        game.getEventBus().postEvent(new ZGameEndEvent(game, winner));
    }
}
