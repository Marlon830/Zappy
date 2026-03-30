package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;

public class ZGameTimeUnitEvent extends ZGameEvent {
    private final int timeUnit;

    public ZGameTimeUnitEvent(ZGame game, int timeUnit) {
        super(game);
        this.timeUnit = timeUnit;
    }

    public int getTimeUnit() {
        return timeUnit;
    }
}
