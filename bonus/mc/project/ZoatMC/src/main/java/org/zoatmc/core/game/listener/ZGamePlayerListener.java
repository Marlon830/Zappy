package org.zoatmc.core.game.listener;

import net.citizensnpcs.api.CitizensAPI;
import net.citizensnpcs.api.npc.NPC;
import net.citizensnpcs.util.PlayerAnimation;
import org.bukkit.*;
import org.bukkit.entity.EntityType;
import org.bukkit.entity.Item;
import org.bukkit.entity.Player;
import org.bukkit.event.player.PlayerTeleportEvent;
import org.bukkit.inventory.ItemStack;
import org.bukkit.util.Vector;
import org.joml.Vector2i;
import org.joml.Vector3d;
import org.zoatmc.core.ZoatPlugin;
import org.zoatmc.core.command.ZoatFormatter;
import org.zoatmc.core.game.ZGame;
import org.zoatmc.core.game.event.ZEventHandler;
import org.zoatmc.core.game.event.ZEventListener;
import org.zoatmc.core.game.event.watcher.*;
import org.zoatmc.core.game.manager.ZControllerManager;
import org.zoatmc.core.game.object.*;

import java.util.List;

public class ZGamePlayerListener implements ZEventListener {

    private final ZParticle FORK_PARTICLE = new ZParticle(Particle.HEART, new Vector3d(0, 2, 0), new Vector3d(.1, .1, .1), 1, 1, true);
    private final ZParticle INCANTATION_PARTICLE = new ZParticle(Particle.ENCHANT, new Vector3d(), new Vector3d(0.5, 0.5, 0.5), 10, 1, true);
    private final ZParticle INCANTATION_SUCCESS_PARTICLE = new ZParticle(Particle.HAPPY_VILLAGER, new Vector3d(0, 2, 0), new Vector3d(0.5, 0.5, 0.5), 10, 1, true);

    @ZEventHandler
    public void onPlayerSpawn(ZGamePlayerJoinEvent event) {
        ZGame game = event.getGame();
        ZPlayer player = event.getPlayer();
        NPC npc = CitizensAPI.getNPCRegistry().createNPC(EntityType.PLAYER, player.getName());
        npc.spawn(player.getLocation());

        ZPlayerController controller = game.getPlayerController();
        if (controller != null) {
            controller.setPlayer(player);
            player.setController(controller);
            controller.getPlayer().spigot().sendMessage(ZoatFormatter.info("You are now controlling player '%s'.", player.getName()));
        }

        player.update(false);
        player.setNpc(npc);
        game.addPlayer(player);
        player.start();
    }

    @ZEventHandler
    public void onPlayerDeath(ZGamePlayerDeathEvent event) {
        ZGame game = event.getGame();
        ZPlayer player = event.getPlayer();

        game.removePlayer(player);
        player.kill();

        ZPlayerController controller = player.getController();
        if (controller != null) {
            controller.setPlayer(null);
            player.setController(null);
            ZControllerManager.removeController(controller);
            controller.getPlayer().getInventory().clear();
            controller.getPlayer().spigot().sendMessage(ZoatFormatter.info("You are no longer controlling player '%s'.", player.getName()));
        }
    }

    @ZEventHandler
    public void onPlayerMove(ZGamePlayerPositionEvent event) {
        ZPlayer player = event.getPlayer();

        if (player == null)
            return;

        NPC npc = player.getNpc();

        if (npc == null)
            return;

        int dist = Math.abs(player.getX() - event.getPosition().x) + Math.abs(player.getY() - event.getPosition().y);
        boolean directionChanged = player.getDirection() != event.getDirection();

        player.setPosition(event.getPosition());
        player.setDirection(event.getDirection());

        if (dist > 2)
            npc.teleport(player.getLocation(), PlayerTeleportEvent.TeleportCause.PLUGIN);

        if (directionChanged) {
            Location location = npc.getStoredLocation().clone();
            location.setYaw(player.getRotation());
            npc.teleport(location, PlayerTeleportEvent.TeleportCause.PLUGIN);
        }

        player.update(false);
    }

    @ZEventHandler
    public void onPlayerLevelUp(ZGamePlayerLevelEvent event) {
        ZPlayer player = event.getPlayer();

        if (player == null || event.getLevel() == player.getLevel())
            return;

        player.setLevel(event.getLevel());
        player.update(true);
    }

    @ZEventHandler
    public void onPlayerInventoryChange(ZGamePlayerInventoryEvent event) {
        ZPlayer player = event.getPlayer();
        player.getInventory().setResourcesQuantities(event.getInventory());
        player.update(false);
    }

    @ZEventHandler
    public void onPlayerIncantation(ZGamePlayerIncantationEvent event) {
        for (ZPlayer player : event.getPlayers())
            player.setParticle(INCANTATION_PARTICLE);
    }

    @ZEventHandler
    public void onPlayerEndIncantation(ZGamePlayerEndIncantationEvent event) {
        Vector2i position = new Vector2i(event.getX(), event.getY());
        boolean success = event.isSuccess();
        ZGame game = event.getGame();
        List<ZPlayer> players = game.getPlayers(position);

        for (ZPlayer player : players) {
            if (player.getParticle() == INCANTATION_PARTICLE)
                player.setParticle(null);

            if (success)
                INCANTATION_SUCCESS_PARTICLE.spawnParticle(player.getLocation());
        }

        if (success && !players.isEmpty()) {
            ZPlayer player = players.getFirst();
            Player p = (Player) player.getNpc().getEntity();
            p.getWorld().playSound(p.getLocation(), Sound.ENTITY_EXPERIENCE_ORB_PICKUP, 10, 0.5f);
        }
    }

    @ZEventHandler
    public void onPlayerLayingEgg(ZGamePlayerForkEvent event) {
        ZPlayer player = event.getPlayer();

        player.setParticle(FORK_PARTICLE);
    }

    @ZEventHandler
    public void onPlayerTakeResource(ZGamePlayerTakeResourceEvent event) {
        ZPlayer player = event.getPlayer();
        ZMap map = event.getGame().getMap();
        ZTile tile = map.getTile(player.getX(), player.getY());
        ZContent.ResourceType type = event.getResourceType();

        player.getInventory().addResourceQuantity(type, 1);
        tile.removeResourceQuantity(type, 1);
        tile.updateDisplays();
        player.update(false);

        NPC npc = player.getNpc();
        if (npc != null) {
            Player p = (Player) npc.getEntity();
            p.getInventory().setItemInMainHand(new ItemStack(type.getMaterial()));
        }
    }

    @ZEventHandler
    public void onPlayerDropResource(ZGamePlayerDropResourceEvent event) {
        ZPlayer player = event.getPlayer();
        ZMap map = event.getGame().getMap();
        ZTile tile = map.getTile(player.getX(), player.getY());
        ZContent.ResourceType type = event.getResourceType();

        player.getInventory().removeResourceQuantity(type, 1);
        tile.addResourceQuantity(type, 1);
        tile.updateDisplays();
        player.update(false);

        NPC npc = player.getNpc();
        if (npc != null) {
            Player p = (Player) npc.getEntity();
            p.getInventory().setItemInMainHand(null);
            Item item = p.getWorld().dropItem(p.getLocation().clone().add(0, 1.5, 0), new ItemStack(type.getMaterial()));
            item.setPickupDelay(100);
            item.setVelocity(p.getLocation().getDirection().multiply(.1));
            PlayerAnimation.ARM_SWING.play(p);
            Bukkit.getScheduler().runTaskLater(ZoatPlugin.getInstance(), item::remove, 20);
        }
    }

    @ZEventHandler
    public void onPlayerBroadcast(ZGamePlayerBroadcastEvent event) {
        ZGame game = event.getGame();
        String message = event.getMessage();
        ZPlayer player = event.getPlayer();

        Bukkit.broadcastMessage("§7[§e" + game.getName() + "§7][§e" + player.getTeam().getName() + "§7] §e" + player.getName() + "§7: " + message);

        game.getPlayers().forEach(p -> {
            if (p == player)
                return;

            drawLine(player, p);
        });
    }

    private void drawLine(ZPlayer p1, ZPlayer p2) {
        Location loc1 = p1.getLocation().clone().add(0, 1, 0);
        Location loc2 = p2.getLocation().clone().add(0, 1, 0);
        Location loc = loc1.clone();
        World world = loc.getWorld();

        if (world == null)
            return;

        double dist = loc1.distance(loc2);
        double offset = .2;
        Vector dir = loc2.toVector().subtract(loc1.toVector()).normalize();
        Vector vec = dir.clone().multiply(offset);

        for (double i = 0; i < dist; i += offset) {
            world.spawnParticle(Particle.DUST, loc, 1, 0, 0, 0, .1, new Particle.DustOptions(Color.RED, 1));
            loc.add(vec);
        }
    }

}
