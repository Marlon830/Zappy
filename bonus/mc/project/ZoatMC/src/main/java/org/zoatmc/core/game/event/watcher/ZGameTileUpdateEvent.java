package org.zoatmc.core.game.event.watcher;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZContent;

public class ZGameTileUpdateEvent extends ZGameEvent {
    private final ZContent content;
    private final Vector2i pos;

    public ZGameTileUpdateEvent(ZGame game, Vector2i pos, ZContent content) {
        super(game);
        this.pos = pos;
        this.content = content;
    }

    public ZContent getContent() {
        return content;
    }

    public Vector2i getPos() {
        return pos;
    }
}
