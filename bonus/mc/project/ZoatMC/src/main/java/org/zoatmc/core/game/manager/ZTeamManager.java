package org.zoatmc.core.game.manager;

import org.bukkit.Color;
import org.zoatmc.core.game.object.ZTeam;

import java.util.HashMap;

public class ZTeamManager {
    private final HashMap<String, ZTeam> teams = new HashMap<>();
    private final Color[] colors = {Color.RED, Color.BLUE, Color.GREEN, Color.YELLOW, Color.PURPLE, Color.AQUA, Color.FUCHSIA, Color.OLIVE};
    private int colorIndex = 0;

    public ZTeam getTeam(String name) {
        return teams.get(name);
    }

    public void addTeam(String name) {
        if (this.teams.containsKey(name))
            return;
        this.teams.put(name, new ZTeam(name, colors[colorIndex++]));
    }

    public HashMap<String, ZTeam> getTeams() {
        return teams;
    }
}
