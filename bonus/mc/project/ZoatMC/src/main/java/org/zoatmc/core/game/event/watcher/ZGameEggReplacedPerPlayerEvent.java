package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZEgg;

public class ZGameEggReplacedPerPlayerEvent extends ZGameEggEvent {
    public ZGameEggReplacedPerPlayerEvent(ZGame game, ZEgg egg) {
        super(game, egg);
    }
}
