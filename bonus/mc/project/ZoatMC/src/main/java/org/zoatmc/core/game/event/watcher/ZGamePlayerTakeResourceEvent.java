package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZContent;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerTakeResourceEvent extends ZGamePlayerEvent {
    private final ZContent.ResourceType resourceType;

    public ZGamePlayerTakeResourceEvent(ZGame game, ZPlayer player, ZContent.ResourceType resourceType) {
        super(game, player);
        this.resourceType = resourceType;
    }

    public ZContent.ResourceType getResourceType() {
        return resourceType;
    }
}
