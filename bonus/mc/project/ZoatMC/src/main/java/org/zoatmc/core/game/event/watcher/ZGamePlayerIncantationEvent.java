package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGamePlayerIncantationEvent extends ZGameEvent {
    private final ZPlayer[] players;
    private final int level;
    private final int x;
    private final int y;

    public ZGamePlayerIncantationEvent(ZGame game, ZPlayer[] players, int x, int y, int level) {
        super(game);
        this.players = players;
        this.level = level;
        this.x = x;
        this.y = y;
    }

    public ZPlayer[] getPlayers() {
        return players;
    }

    public int getLevel() {
        return level;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
