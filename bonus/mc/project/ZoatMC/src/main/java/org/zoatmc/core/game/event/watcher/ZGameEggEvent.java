package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZEgg;

public class ZGameEggEvent extends ZGameEvent {
    private final ZEgg egg;

    public ZGameEggEvent(ZGame game, ZEgg egg) {
        super(game);
        this.egg = egg;
    }

    public ZEgg getEgg() {
        return egg;
    }
}
