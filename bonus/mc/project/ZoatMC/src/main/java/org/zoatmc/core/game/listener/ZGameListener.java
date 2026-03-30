package org.zoatmc.core.game.listener;

import org.bukkit.*;
import org.bukkit.entity.Firework;
import org.bukkit.entity.Player;
import org.bukkit.entity.TNTPrimed;
import org.bukkit.inventory.meta.FireworkMeta;
import org.bukkit.util.Vector;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.ZEventHandler;
import org.zoatmc.core.game.event.ZEventListener;
import org.zoatmc.core.game.event.watcher.ZGameEndEvent;
import org.zoatmc.core.game.event.watcher.ZGameTeamNameEvent;
import org.zoatmc.core.game.manager.ZGameManager;
import org.zoatmc.core.game.object.ZPlayer;
import org.zoatmc.core.game.object.ZTeam;

import java.io.IOException;
import java.util.Random;

public class ZGameListener implements ZEventListener {

    @ZEventHandler
    public void onGameEnded(ZGameEndEvent event) {
        ZGame game = event.getGame();
        ZTeam winner = event.getWinner();

        for (int i = 0; i < 7; i++) {
            Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), () -> {
                game.getPlayers(winner).forEach(this::throwFirework);
            }, i * 20L);
        }

        Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), () -> {
            game.getMap().forEachTile(tile -> {
                Location location = tile.getLocation().add(ZGame.TILE_SIZE / 2.0, 10, ZGame.TILE_SIZE / 2.0);
                World world = location.getWorld();

                if (world == null)
                    return;

                world.spawn(location, TNTPrimed.class, tnt -> {
                    tnt.setFuseTicks(40);
                    tnt.setVelocity(new Vector(0.0, -0.5, 0.0));
                });
            });
        }, 160L);

        Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), () -> {
            try {
                ZGameManager.removeGame(game);
            } catch (IOException e) {
                Bukkit.getLogger().warning("Failed to end the game!");
            }
        }, 200L);
    }

    private void throwFirework(ZPlayer player) {
        Location location = player.getNpc().getStoredLocation().clone().add(0, 1, 0);
        World world = location.getWorld();

        if (world == null)
            return;

        Firework fw = world.spawn(location, Firework.class, firework -> {
            Random random = new Random();
            Color color = player.getTeam().getColor();
            FireworkEffect.Type[] types = FireworkEffect.Type.values();

            firework.setShooter((Player) player.getNpc().getEntity());

            FireworkMeta fwm = firework.getFireworkMeta();
            fwm.setPower(random.nextInt(5, 20));
            fwm.addEffect(FireworkEffect.builder()
                    .withTrail()
                    .with(types[random.nextInt(types.length)])
                    .flicker(random.nextBoolean())
                    .withColor(color)
                    .withFade(Color.fromRGB(
                            Math.clamp(color.getRed() + random.nextInt(-32, 32), 0, 255),
                            Math.clamp(color.getGreen() + random.nextInt(-32, 32), 0, 255),
                            Math.clamp(color.getBlue() + random.nextInt(-32, 32), 0, 255)))
                    .build());
            firework.setFireworkMeta(fwm);
        });

        Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), fw::detonate, 20L);
    }

    @ZEventHandler
    public void onTeamNameEvent(ZGameTeamNameEvent event) {
        ZGame game = event.getGame();

        game.addTeam(event.getTeamName());
    }

}
