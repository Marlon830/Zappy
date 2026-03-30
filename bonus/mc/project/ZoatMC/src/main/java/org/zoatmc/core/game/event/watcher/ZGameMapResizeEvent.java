package org.zoatmc.core.game.event.watcher;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;

public class ZGameMapResizeEvent extends ZGameEvent {
    private final Vector2i newSize;

    public ZGameMapResizeEvent(ZGame game, Vector2i newSize) {
        super(game);
        this.newSize = newSize;
    }

    public Vector2i getNewSize() {
        return newSize;
    }
}
