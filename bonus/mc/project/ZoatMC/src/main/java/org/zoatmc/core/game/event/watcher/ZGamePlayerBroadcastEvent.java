package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerBroadcastEvent extends ZGamePlayerEvent {
    private final String message;

    public ZGamePlayerBroadcastEvent(ZGame game, ZPlayer player, String message) {
        super(game, player);
        this.message = message;
    }

    public String getMessage() {
        return message;
    }
}
