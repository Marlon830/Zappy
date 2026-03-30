package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZEgg;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGameEggSpawnEvent extends ZGameEggEvent {

    private final ZPlayer player;

    public ZGameEggSpawnEvent(ZGame game, ZEgg egg, ZPlayer player) {
        super(game, egg);
        this.player = player;
    }

    public ZPlayer getPlayer() {
        return player;
    }
}
