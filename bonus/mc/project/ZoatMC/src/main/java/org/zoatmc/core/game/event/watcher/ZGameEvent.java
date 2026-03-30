package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.ZEvent;

public class ZGameEvent implements ZEvent {

    private final ZGame game;

    public ZGameEvent(ZGame game) {
        this.game = game;
    }

    public ZGame getGame() {
        return game;
    }

}
