package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;

public class ZGamePlayerEndIncantationEvent extends ZGameEvent {
    private final int x;
    private final int y;
    private final boolean success;

    public ZGamePlayerEndIncantationEvent(ZGame game, int x, int y, boolean success) {
        super(game);
        this.x = x;
        this.y = y;
        this.success = success;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public boolean isSuccess() {
        return success;
    }
}
