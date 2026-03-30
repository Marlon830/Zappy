package org.zoatmc.core.game.event.watcher;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerPositionEvent extends ZGamePlayerEvent {
    private final Vector2i position;
    private final int direction;

    public ZGamePlayerPositionEvent(ZGame game, ZPlayer player, Vector2i position, int direction) {
        super(game, player);
        this.position = position;
        this.direction = direction;
    }

    public Vector2i getPosition() {
        return position;
    }

    public int getDirection() {
        return direction;
    }
}
