package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerLevelEvent extends ZGamePlayerEvent {
    private final int level;

    public ZGamePlayerLevelEvent(ZGame game, ZPlayer player, int level) {
        super(game, player);
        this.level = level;
    }

    public int getLevel() {
        return level;
    }
}
