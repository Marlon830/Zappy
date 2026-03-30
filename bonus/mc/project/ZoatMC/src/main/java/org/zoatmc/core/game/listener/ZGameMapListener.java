package org.zoatmc.core.game.listener;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.ZEventHandler;
import org.zoatmc.core.game.event.ZEventListener;
import org.zoatmc.core.game.event.watcher.ZGameMapResizeEvent;
import org.zoatmc.core.game.event.watcher.ZGameTileUpdateEvent;
import org.zoatmc.core.game.object.ZMap;
import org.zoatmc.core.game.object.ZTile;

import java.util.Arrays;

public class ZGameMapListener implements ZEventListener {

    @ZEventHandler
    public void onMapResize(ZGameMapResizeEvent event) {
        ZGame game = event.getGame();
        ZMap map = game.getMap();

        if (map != null)
            map.clear();

        game.setMap(new ZMap(game, event.getNewSize()));
    }

    @ZEventHandler
    public void onTileUpdate(ZGameTileUpdateEvent event) {
        ZGame game = event.getGame();
        ZMap map = game.getMap();

        if (map == null)
            return;

        ZTile tile = map.getTile(event.getPos().x, event.getPos().y);
        if (tile == null)
            return;

        if (Arrays.compare(tile.getResourcesQuantities(), event.getContent().getResourcesQuantities()) == 0)
            return;

        tile.setResourcesQuantities(event.getContent().getResourcesQuantities());
        tile.updateDisplays();
    }

}
