package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerEvent extends ZGameEvent {
    private final ZPlayer player;

    public ZGamePlayerEvent(ZGame game, ZPlayer player) {
        super(game);
        this.player = player;
    }

    public ZPlayer getPlayer() {
        return player;
    }
}
