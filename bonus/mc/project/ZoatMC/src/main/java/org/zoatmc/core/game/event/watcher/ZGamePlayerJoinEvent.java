package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerJoinEvent extends ZGamePlayerEvent {
    public ZGamePlayerJoinEvent(ZGame game, ZPlayer player) {
        super(game, player);
    }
}
