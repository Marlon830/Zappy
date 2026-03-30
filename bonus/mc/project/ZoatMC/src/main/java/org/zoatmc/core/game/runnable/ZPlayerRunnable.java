package org.zoatmc.core.game.runnable;

import net.citizensnpcs.util.NMS;
import org.bukkit.Location;
import org.bukkit.scheduler.BukkitRunnable;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.object.ZPlayer;

public class ZPlayerRunnable extends BukkitRunnable {

    private final ZPlayer player;

    public ZPlayerRunnable(ZPlayer player) {
        this.player = player;
    }

    @Override
    public void run() {
        if (player.getNpc() == null)
            return;

        Location destination = player.getLocation();
        Location current = player.getNpc().getStoredLocation();
        double dist = current.distance(destination);
        if (dist > ZGame.TILE_SIZE / 4.0)
            NMS.setDestination(player.getNpc().getEntity(), destination.getX(), destination.getY(), destination.getZ(), 5.0F);

        if (player.getParticle() != null)
            player.getParticle().spawnParticle(current);
    }
}
