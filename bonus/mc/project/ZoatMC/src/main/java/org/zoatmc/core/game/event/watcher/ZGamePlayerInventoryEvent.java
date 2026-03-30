package org.zoatmc.core.game.event.watcher;

import org.joml.Vector2i;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerInventoryEvent extends ZGamePlayerEvent {

    private final ZContent inventory;
    private final Vector2i position;

    public ZGamePlayerInventoryEvent(ZGame game, ZPlayer player, Vector2i position, ZContent inventory) {
        super(game, player);
        this.position = position;
        this.inventory = inventory;
    }

    public Vector2i getPosition() {
        return position;
    }

    public ZContent getInventory() {
        return inventory;
    }
}
