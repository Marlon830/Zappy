package org.zoatmc.core.game.listener;

import org.bukkit.Sound;
import org.bukkit.entity.Player;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.ZEventHandler;
import org.zoatmc.core.game.event.ZEventListener;
import org.zoatmc.core.game.event.watcher.ZGameEggDeathEvent;
import org.zoatmc.core.game.event.watcher.ZGameEggReplacedPerPlayerEvent;
import org.zoatmc.core.game.event.watcher.ZGameEggSpawnEvent;
import org.zoatmc.core.game.object.ZEgg;
import org.zoatmc.core.game.object.ZPlayer;

public class ZGameEggListener implements ZEventListener {

    @ZEventHandler
    public void onEggSpawn(ZGameEggSpawnEvent event) {
        ZGame game = event.getGame();
        ZEgg egg = event.getEgg();
        ZPlayer player = event.getPlayer();

        if (player != null) {
            player.setParticle(null);
            if (player.getNpc() != null) {
                Player p = (Player) player.getNpc().getEntity();
                p.getWorld().playSound(p.getLocation(), Sound.ENTITY_CHICKEN_EGG, 5, 1);
            }
        }

        game.getMap().getTile(egg.getX(), egg.getY()).addEgg();
        game.addEgg(egg);
    }

    @ZEventHandler
    public void onEggReplacedPerPlayer(ZGameEggReplacedPerPlayerEvent event) {
        ZGame game = event.getGame();
        ZEgg egg = event.getEgg();

        game.getMap().getTile(egg.getX(), egg.getY()).removeEgg();
        game.removeEgg(egg);
    }

    @ZEventHandler
    public void onEggDeath(ZGameEggDeathEvent event) {
        ZGame game = event.getGame();
        ZEgg egg = event.getEgg();

        game.getMap().getTile(egg.getX(), egg.getY()).removeEgg();
        game.removeEgg(egg);
    }

}
