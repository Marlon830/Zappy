package org.zoatmc.core.game.runnable;

import org.bukkit.scheduler.BukkitRunnable;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.game.ZGame;

public class ZGameRunnable extends BukkitRunnable {
    private final ZGame game;

    public ZGameRunnable(ZGame game) {
        this.game = game;

        this.runTaskTimer(ZoatPlugin.getInstance(), 0, 5);
    }

    @Override
    public void run() {
        this.game.getEventBus().processEvents();
    }
}
