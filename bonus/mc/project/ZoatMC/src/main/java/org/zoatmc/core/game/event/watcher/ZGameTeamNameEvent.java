package org.zoatmc.core.game.event.watcher;

import org.zoatmc.core.game.ZGame;

public class ZGameTeamNameEvent extends ZGameEvent {
    private final String teamName;

    public ZGameTeamNameEvent(ZGame game, String teamName) {
        super(game);
        this.teamName = teamName;
    }

    public String getTeamName() {
        return teamName;
    }
}
