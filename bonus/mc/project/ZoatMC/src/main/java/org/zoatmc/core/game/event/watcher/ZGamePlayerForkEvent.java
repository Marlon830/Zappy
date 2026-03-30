package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerForkEvent extends ZGamePlayerEvent {
    public ZGamePlayerForkEvent(ZGame game, ZPlayer player) {
        super(game, player);
    }
}
