package org.zoatmc.core.game.protocol.watcher.impl;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.watcher.ZGameEggReplacedPerPlayerEvent;
import org.zoatmc.core.game.object.ZEgg;
import org.zoatmc.core.game.protocol.ZCommandExecutor;

public class EggReplacedPerPlayerCommand implements ZCommandExecutor {
    @Override
    public void onCommand(ZGame game, String command, String[] args) {
        if (args.length != 1)
            return;

        int eggId = Integer.parseInt(args[0].substring(1));
        ZEgg egg = game.getEgg(eggId);

        game.getEventBus().postEvent(new ZGameEggReplacedPerPlayerEvent(game, egg));
    }
}
