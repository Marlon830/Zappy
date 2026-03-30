package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZTeam;

public class ZGameEndEvent extends ZGameEvent {
    private final ZTeam winner;

    public ZGameEndEvent(ZGame game, ZTeam winner) {
        super(game);
        this.winner = winner;
    }

    public ZTeam getWinner() {
        return winner;
    }
}
